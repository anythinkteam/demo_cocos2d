//
//  ATBannerAdWrapper.m
//  UnityContainer
//
//  Created by Martin Lau on 2019/1/8.
//  Copyright © 2019 Martin Lau. All rights reserved.
//

#import "ATBannerAdWrapper.h"
#import "ATCocosUtils.h"
#import <AnyThinkBanner/AnyThinkBanner.h>
#import "ATCocosBannerAdListener.h"
#include "ATCocosSdk.h"
//5.6.6版本以上支持 admob 自适应banner （用到时再import该头文件）
//#import <GoogleMobileAds/GoogleMobileAds.h>

@interface ATBannerAdWrapper()<ATBannerDelegate>
@property(nonatomic, readonly) NSMutableDictionary<NSString*, ATBannerView*> *bannerViewStorage;
@property(nonatomic, readonly) BOOL interstitialOrRVBeingShown;
@end

UIEdgeInsets SafeAreaInsets_ATCocosCreatorBanner() {
    return ([[UIApplication sharedApplication].keyWindow respondsToSelector:@selector(safeAreaInsets)] ? [UIApplication sharedApplication].keyWindow.safeAreaInsets : UIEdgeInsetsZero);
}

@implementation ATBannerAdWrapper
+(instancetype)sharedInstance {
    static ATBannerAdWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ATBannerAdWrapper alloc] init];
    });
    return sharedInstance;
}

-(instancetype) init {
     self = [super init];
     if (self != nil) {
         _bannerViewStorage = [NSMutableDictionary<NSString*, ATBannerView*> new];
         
     }
    return self;
}

-(void) loadBannerAdWithPlacementID:(NSString*)placementID  extra:(NSDictionary*)customData {
    NSLog(@"ATBannerAdWrapper::loadBannerWithPlacementID:%@ extra:%@", placementID, customData);
    NSMutableDictionary *extra = [NSMutableDictionary dictionary];
    if ([customData isKindOfClass:[NSDictionary class]]  && customData != nil) {
        if ([customData[@"w"] isKindOfClass:[NSString class]] && [customData[@"h"] isKindOfClass:[NSString class]]) {
            extra[kATAdLoadingExtraBannerAdSizeKey] = [NSValue valueWithCGSize:CGSizeMake([customData[@"w"] doubleValue], [customData[@"h"] doubleValue])];
        }
//        // admob 自适应banner，5.6.6版本以上支持
//        if (customData[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_INLINE_ADAPTIVE_WIDTH]] != nil && customData[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_INLINE_ADAPTIVE_ORIENTATION]] != nil) {
//            //GADCurrentOrientationAnchoredAdaptiveBannerAdSizeWithWidth 自适应
//            //GADPortraitAnchoredAdaptiveBannerAdSizeWithWidth 竖屏
//            //GADLandscapeAnchoredAdaptiveBannerAdSizeWithWidth 横屏
//            CGFloat admobBannerWidth = [customData[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_ADAPTIVE_WIDTH]] doubleValue];
//            GADAdSize admobSize;
//            if ([customData[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_ADAPTIVE_ORIENTATION]] integerValue] == 1) {
//                admobSize = GADPortraitAnchoredAdaptiveBannerAdSizeWithWidth(admobBannerWidth);
//            } else if ([customData[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_ADAPTIVE_ORIENTATION]] integerValue] == 2) {
//                admobSize = GADLandscapeAnchoredAdaptiveBannerAdSizeWithWidth(admobBannerWidth);
//            } else {
//                admobSize = GADCurrentOrientationAnchoredAdaptiveBannerAdSizeWithWidth(admobBannerWidth);
//            }
//            extra[kATAdLoadingExtraAdmobBannerSizeKey] = [NSValue valueWithCGSize:admobSize.size];
//            extra[kATAdLoadingExtraAdmobAdSizeFlagsKey] = @(admobSize.flags);
//        }
    }
    
    if (extra[kATAdLoadingExtraBannerAdSizeKey] == nil) {
        extra[kATAdLoadingExtraBannerAdSizeKey] = [NSValue valueWithCGSize:CGSizeMake(320.0f, 50.0f)];
    }
    
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:extra delegate:self];
}

-(bool) bannerAdReadyForPlacementID:(NSString*)placementID {
    NSLog(@"ATBannerAdWrapper::bannerReadyForPlacementID:%@", placementID);
    return [[ATAdManager sharedManager] bannerAdReadyForPlacementID:placementID];
}

-(void) showBannerWithPlacementID:(NSString*)placementID position:(NSString*)position {
    NSLog(@"ATBannerAdWrapper::showBannerWithPlacementID:%@ position:%@", placementID, position);
    dispatch_async(dispatch_get_main_queue(), ^{
        ATBannerView *bannerView = [[ATAdManager sharedManager] retrieveBannerViewForPlacementID:placementID];
        if (bannerView != nil) {
            self->_bannerViewStorage[placementID] = bannerView;
            bannerView.delegate = self;
            bannerView.frame = CGRectMake((CGRectGetWidth(UIScreen.mainScreen.bounds) - CGRectGetWidth(bannerView.bounds)) / 2.0f, [@{@"top":@(SafeAreaInsets_ATCocosCreatorBanner().top), @"bottom":@(CGRectGetHeight(UIScreen.mainScreen.bounds) - SafeAreaInsets_ATCocosCreatorBanner().bottom - CGRectGetHeight(bannerView.bounds))}[position] doubleValue] , CGRectGetWidth(bannerView.bounds), CGRectGetHeight(bannerView.bounds));
            [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:bannerView];
        }
    });
}

-(void) showBannerAdWithPlacementID:(NSString*)placementID rect:(NSDictionary *)rectDict {
    NSLog(@"ATBannerAdWrapper::showBannerWithPlacementID:%@ rect:%@", placementID, rectDict);
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([rectDict isKindOfClass:[NSDictionary class]] && rectDict != nil) {
            NSLog(@"dict:%@", rectDict);
            ATBannerView *bannerView = [[ATAdManager sharedManager] retrieveBannerViewForPlacementID:placementID];
           
            bannerView.delegate = self;
            
            UIButton *bannerCointainer = [UIButton buttonWithType:UIButtonTypeCustom];
            [bannerCointainer addTarget:self action:@selector(noop) forControlEvents:UIControlEventTouchUpInside];
            bannerCointainer.frame = CGRectMake([rectDict[@"x"] doubleValue], [rectDict[@"y"] doubleValue], [rectDict[@"w"] doubleValue], [rectDict[@"h"] doubleValue]);
            bannerView.frame = bannerCointainer.bounds;
            [bannerCointainer addSubview:bannerView];
            [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:bannerCointainer];
            self->_bannerViewStorage[placementID] = bannerView;
        }
    });
}

-(void) removeBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATBannerAdWrapper::removeBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        if(self->_bannerViewStorage[placementID] != nil){
            [self->_bannerViewStorage[placementID] removeFromSuperview];
            [self->_bannerViewStorage removeObjectForKey:placementID];
        }
    });
}

-(void) showBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATBannerAdWrapper::showBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        ATBannerView *bannerView = self->_bannerViewStorage[placementID];
        if (bannerView.superview != nil) { bannerView.hidden = NO; }
    });
}

-(void) hideBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATBannerAdWrapper::hideBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        ATBannerView *bannerView = self->_bannerViewStorage[placementID];
        if (bannerView.superview != nil) { bannerView.hidden = YES; }
    });
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

-(void) noop {
}

#pragma mark - banner delegate method(s)
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {
    NSLog(@"ATBannerAdWrapper::didFinishLoadingADWithPlacementID:%@", placementID);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerAdLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    NSLog(@"ATBannerAdWrapper::didFailToLoadADWithPlacementID:%@ error:%@", placementID, error);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];

    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        
        NSMutableDictionary *errorDict = [NSMutableDictionary dictionaryWithObject:[NSString stringWithFormat:@"%ld", error.code] forKey:@"code"];
        if ([error.userInfo[NSLocalizedDescriptionKey] length] > 0) {
            errorDict[@"desc"] = error.userInfo[NSLocalizedDescriptionKey];
        } else {
            errorDict[@"desc"] = @"";
        }
        if ([error.userInfo[NSLocalizedFailureReasonErrorKey] length] > 0) {
            errorDict[@"reason"] = error.userInfo[NSLocalizedFailureReasonErrorKey];
        } else {
            errorDict[@"reason"] = @"";
        }
        pDelegate->onBannerAdLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
}

#pragma - mark delegate with adsourceID and networkID
-(void) bannerView:(ATBannerView*)bannerView didShowAdWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATBannerAdWrapper::bannerView:didShowAdWithPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerShowWithExtra(cPlacementId, cExtra);
    }
}

-(void) bannerView:(ATBannerView*)bannerView didClickWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATBannerAdWrapper::bannerView:didClickWithPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerClickedWithExtra(cPlacementId, cExtra);
    }
}

-(void) bannerView:(ATBannerView*)bannerView didCloseWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATBannerAdWrapper::bannerView:didCloseWithPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerCloseWithExtra(cPlacementId, cExtra);
    }
}

-(void) bannerView:(ATBannerView*)bannerView didTapCloseButtonWithPlacementID:(NSString*)placementID extra:(NSDictionary*)extra {
    NSLog(@"ATBannerAdWrapper::bannerView:didTapCloseButtonWithPlacementID:%@ extra: %@", placementID,extra);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerCloseWithExtra(cPlacementId, cExtra);
    }
}

-(void) bannerView:(ATBannerView*)bannerView didAutoRefreshWithPlacement:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATBannerAdWrapper::bannerView:didAutoRefreshWithPlacement:%@ extra:%@", placementID, extra);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerAutoRefreshWithExtra(cPlacementId, cExtra);
    }
}

-(void) bannerView:(ATBannerView*)bannerView failedToAutoRefreshWithPlacementID:(NSString*)placementID  extra:(NSDictionary *)extra error:(NSError*)error {
    NSLog(@"ATBannerAdWrapper::bannerView:failedToAutoRefreshWithPlacementID:%@ error:%@", placementID, error);
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        NSMutableDictionary *errorDict = [NSMutableDictionary dictionaryWithObject:[NSString stringWithFormat:@"%ld", error.code] forKey:@"code"];
        if ([error.userInfo[NSLocalizedDescriptionKey] length] > 0) {
            errorDict[@"desc"] = error.userInfo[NSLocalizedDescriptionKey];
        } else {
            errorDict[@"desc"] = @"";
        }
        if ([error.userInfo[NSLocalizedFailureReasonErrorKey] length] > 0) {
            errorDict[@"reason"] = error.userInfo[NSLocalizedFailureReasonErrorKey];
        } else {
            errorDict[@"reason"] = @"";
        }
        pDelegate->onBannerAutoRefreshFailWithExtra(cPlacementId, errorDict.jsonString.UTF8String, cExtra);
    }
}

@end
