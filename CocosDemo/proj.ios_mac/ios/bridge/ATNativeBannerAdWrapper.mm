//
//  ATNativeBannerAdWrapper.m
//  UnityContainer
//
//  Created by Martin Lau on 2019/4/23.
//  Copyright © 2019 Martin Lau. All rights reserved.
//

#import "ATNativeBannerAdWrapper.h"
#import <AnyThinkNative/ATNativeBannerWrapper.h>
#import <objc/runtime.h>
#import "ATCocosUtils.h"
#include "ATCocosSdk.h"
#include "ATCocosNativeBannerAdListener.h"

//@interface UIViewController(ATUtilities)
//-(void)AT_presentViewController:(UIViewController *)viewControllerToPresent animated:(BOOL)flag completion:(void (^)(void))completion;
//-(void) AT_dismissViewControllerAnimated:(BOOL)flag completion:(void (^)(void))completion;
//@end


@interface ATNativeBannerAdWrapper()<ATNativeBannerDelegate>
@property(nonatomic, readonly) NSMutableDictionary<NSString*, UIView*> *nativeBannerAdViews;
@end

static NSString *const kATSharedCallbackKey = @"placement_id_placement_holder";
@implementation ATNativeBannerAdWrapper
//+(void) swizzleMethodWithSelector:(SEL)originalSel swizzledMethodSelector:(SEL)swizzledMethodSel inClass:(Class)inClass {
//    if (originalSel != NULL && swizzledMethodSel != NULL && inClass != nil) {
//        Method originalMethod = class_getInstanceMethod(inClass, originalSel);
//        Method swizzledMethod = class_getInstanceMethod(inClass, swizzledMethodSel);
//
//        BOOL didAddMethod = class_addMethod(inClass, originalSel, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
//
//        if (didAddMethod) {
//            class_replaceMethod(inClass, swizzledMethodSel, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
//        } else {
//            method_exchangeImplementations(originalMethod, swizzledMethod);
//        }
//    }
//}

+(instancetype)sharedInstance {
    static ATNativeBannerAdWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ATNativeBannerAdWrapper alloc] init];
    });
    return sharedInstance;
}

-(instancetype) init {
    self = [super init];
    if (self != nil) {
        _nativeBannerAdViews = [NSMutableDictionary new];
//        [ATNativeBannerAdWrapper swizzleMethodWithSelector:@selector(presentViewController:animated:completion:) swizzledMethodSelector:@selector(AT_presentViewController:animated:completion:) inClass:[UIViewController class]];
//        [ATNativeBannerAdWrapper swizzleMethodWithSelector:@selector(dismissViewControllerAnimated:completion:) swizzledMethodSelector:@selector(AT_dismissViewControllerAnimated:completion:) inClass:[UIViewController class]];
    }
    return self;
}


-(void) noop {
    
}

/**
 
 **/
-(void) showNativeBannerAdWithPlacementID:(NSString*)placementID rect:(NSDictionary*)rectDict extra:(NSDictionary*)extraDict {
    NSLog(@"ATNativeBannerAdWrapper::showNativeBannerAdWithPlacementID:%@ rect:%@ extra:%@", placementID, rectDict, extraDict);
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([rectDict isKindOfClass:[NSDictionary class]] && rectDict != nil) {
            
            NSMutableDictionary *extra = [NSMutableDictionary dictionaryWithDictionary:@{kExtraInfoNativeAdTypeKey:@(ATGDTNativeAdTypeSelfRendering), kATNativeBannerAdShowingExtraAdSizeKey:[NSValue valueWithCGSize:CGSizeMake([rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]] doubleValue], [rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]] doubleValue])], kATExtraNativeImageSizeKey:kATExtraNativeImageSize690_388, kATNativeBannerAdShowingExtraBackgroundColorKey:[UIColor whiteColor]}];
            if ([extraDict isKindOfClass:[NSDictionary class]] && extraDict != nil) {
                
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_MAIN_BG_COLOR]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraBackgroundColorKey] = [UIColor colorWithHexString:@"#ffffff"];
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_REFRESH_INTERVEL]] respondsToSelector:@selector(doubleValue)]) {
                    extra[kATNativeBannerAdShowingExtraAutorefreshIntervalKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_REFRESH_INTERVEL]] doubleValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CLOSE_STATUS]] respondsToSelector:@selector(boolValue)]) {
                    extra[kATNativeBannerAdShowingExtraHideCloseButtonFlagKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CLOSE_STATUS]] boolValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_BG]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraCTAButtonBackgroundColorKey] = [UIColor colorWithHexString:extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_BG]]];
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT]] respondsToSelector:@selector(doubleValue)]) {
                    extra[kATNativeBannerAdShowingExtraCTAButtonTitleFontKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT]] doubleValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraCTAButtonTitleColorKey] = [UIColor colorWithHexString:extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR]]];
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TITLE_FONT]] respondsToSelector:@selector(doubleValue)]) {
                    extra[kATNativeBannerAdShowingExtraTitleFontKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TITLE_FONT]] doubleValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TITLE_COLOR]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraTitleColorKey] = [UIColor colorWithHexString:extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TITLE_COLOR]]];
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TEXT_FONT]] respondsToSelector:@selector(doubleValue)]) {
                    extra[kATNativeBannerAdShowingExtraTextFontKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TEXT_FONT]] doubleValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TEXT_COLOR]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraTextColorKey] = [UIColor colorWithHexString:extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_TEXT_COLOR]]];
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_ADVERTISER_TEXT_FONT]] respondsToSelector:@selector(doubleValue)]) {
                    extra[kATNativeBannerAdShowingExtraAdvertiserTextFontKey] = @([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_ADVERTISER_TEXT_FONT]] doubleValue]);
                }
                if ([extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR]] isKindOfClass:[NSString class]]) {
                    extra[kATNativeBannerAdShowingExtraAdvertiserTextColorKey] = [UIColor colorWithHexString:extraDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR]]];
                }
            }
            ATNativeBannerView *bannerView = [ATNativeBannerWrapper retrieveNativeBannerAdViewWithPlacementID:placementID extra:extra delegate:self];
            UIButton *bannerCointainer = [UIButton buttonWithType:UIButtonTypeCustom];
            [bannerCointainer addTarget:self action:@selector(noop) forControlEvents:UIControlEventTouchUpInside];
            bannerCointainer.frame = CGRectMake([rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_POS_X]] doubleValue], [rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_POS_Y]] doubleValue], [rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_WIDTH]] doubleValue], [rectDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::ATCocosSdk::KEY_HEIGHT]] doubleValue]);
            bannerView.frame = bannerCointainer.bounds;
            [bannerCointainer addSubview:bannerView];
            [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:bannerCointainer];
            self->_nativeBannerAdViews[placementID] = bannerCointainer;
        }
    });
}

-(void) removeNativeBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeBannerAdWrapper::removeNativeBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        [self->_nativeBannerAdViews[placementID] removeFromSuperview];
        [self->_nativeBannerAdViews removeObjectForKey:placementID];
    });
}

-(void) showNativeBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeBannerAdWrapper::showNativeBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        self->_nativeBannerAdViews[placementID].hidden = NO;
    });
}

-(void) hideNativeBannerAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeBannerAdWrapper::hideNativeBannerAdWithPlacementID:%@", placementID);
    dispatch_async(dispatch_get_main_queue(), ^{
        self->_nativeBannerAdViews[placementID].hidden = YES;
    });
}

-(void) loadNativeBannerAdWithPlacementID:(NSString*)placementID customData:(NSDictionary*)customData  {
    NSLog(@"ATNativeBannerAdWrapper::loadNativeBannerAdWithPlacementID:%@ customData:%@", placementID, customData);
//    [self setCallBack:callback forKey:kATSharedCallbackKey];
//    [self setCallBack:callback forKey:placementID];
    [ATNativeBannerWrapper loadNativeBannerAdWithPlacementID:placementID extra:nil customData:customData delegate:self];
}

-(BOOL) isNativeBannerAdReadyForPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeBannerAdWrapper::isNativeBannerAdReadyForPlacementID:%@", placementID);
    return [ATNativeBannerWrapper nativeBannerAdReadyForPlacementID:placementID];
}

#pragma mark - delegate(s)
-(void) didFinishLoadingNativeBannerAdWithPlacementID:(NSString *)placementID {
    NSLog(@"ATNativeBannerAdWrapper::didFinishLoadingNativeBannerAdWithPlacementID:%@", placementID);
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onNativeBannerAdLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadNativeBannerAdWithPlacementID:(NSString*)placementID error:(NSError*)error {
    NSLog(@"ATNativeBannerAdWrapper::didFailToLoadNativeBannerAdWithPlacementID:%@ error:%@", placementID, error);
//    NSLog(@"ATNativeBannerAdWrapper::didFailToLoadNativeBannerAdWithPlacementID:%@ error:%@", placementID, error);
//    error = error != nil ? error : [NSError errorWithDomain:@"com.AT.Unity3DPackage" code:100001 userInfo:@{NSLocalizedDescriptionKey:@"AT has failed to load native banner ad", NSLocalizedFailureReasonErrorKey:@"AT has failed to load native banner ad"}];
//    [self invokeCallback:@"OnNativeBannerAdLoadingFailure" placementID:placementID error:error extra:nil];
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
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
        pDelegate->onNativeBannerAdLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
}

#pragma mark - native banner delegate with networkID and adsouceID
-(void) didShowNativeBannerAdInView:(ATNativeBannerView*)bannerView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeBannerAdWrapper::didShowNativeBannerAdInView:placementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeBannerShowWithExtra(cPlacementId, cExtra);
    }
}

-(void) didClickNativeBannerAdInView:(ATNativeBannerView*)bannerView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeBannerClickedWithExtra(cPlacementId, cExtra);
    }
}

-(void) didClickCloseButtonInNativeBannerAdView:(ATNativeBannerView*)bannerView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeBannerCloseWithExtra(cPlacementId, cExtra);
    }
}

-(void) didAutorefreshNativeBannerAdInView:(ATNativeBannerView*)bannerView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeBannerAutoRefreshWithExtra(cPlacementId, cExtra);
    }
}

-(void) didFailToAutorefreshNativeBannerAdInView:(ATNativeBannerView*)bannerView placementID:(NSString*)placementID extra:(NSDictionary *)extra error:(NSError*)error {
    void* callback = [[ATNativeBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeBannerAdListener* pDelegate = (ATCocosNativeBannerAdListener*)callback;
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
        pDelegate->onNativeBannerAutoRefreshFailWithExtra(cPlacementId, errorDict.jsonString.UTF8String, cExtra);
    }
}

@end



//#pragma mark - vc swizzling
//@implementation UIViewController (ATUtilities)
//
//-(void)AT_presentViewController:(UIViewController *)viewControllerToPresent animated:(BOOL)flag completion:(void (^)(void))completion {
//    [self AT_presentViewController:viewControllerToPresent animated:flag completion:completion];
////    [[ATNativeBannerAdWrapper sharedInstance] invokeCallback:@"PauseAudio" placementID:kATSharedCallbackKey error:nil extra:nil];
//    NSLog(@"oc : AT_presentViewController, callback to PauseAudio");
//}
//
//-(void) AT_dismissViewControllerAnimated:(BOOL)flag completion:(void (^)(void))completion {
//    [self AT_dismissViewControllerAnimated:flag completion:completion];
////    [[ATNativeBannerAdWrapper sharedInstance] invokeCallback:@"ResumeAudio" placementID:kATSharedCallbackKey error:nil extra:nil];
//    NSLog(@"oc : AT_dismissViewControllerAnimated, callback to ResumeAudio");
//}
//@end
