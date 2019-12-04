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

@interface ATBannerAdWrapper()<ATBannerDelegate>
@property(nonatomic, readonly) NSMutableDictionary<NSString*, ATBannerView*> *bannerViewStorage;
@property(nonatomic, readonly) BOOL interstitialOrRVBeingShown;
@end
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

-(void) loadBannerAdWithPlacementID:(NSString*)placementID  customData:(NSDictionary*)customData {

    NSDictionary *extra = nil;
    if ([customData isKindOfClass:[NSDictionary class]]  && customData != nil) {
        
       if ([customData[@"w"] isKindOfClass:[NSString class]] && [customData[@"h"] isKindOfClass:[NSString class]]) {
            extra = @{kATAdLoadingExtraBannerAdSizeKey:[NSValue valueWithCGSize:CGSizeMake([customData[@"w"] doubleValue], [customData[@"h"] doubleValue])]};
        }
    }
    
    if (extra == nil) {
        extra = @{kATAdLoadingExtraBannerAdSizeKey:[NSValue valueWithCGSize:CGSizeMake(320.0f, 50.0f)]};
    }
    
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:extra customData:customData delegate:self];
}

-(bool) bannerAdReadyForPlacementID:(NSString*)placementID {
    
    return [[ATAdManager sharedManager] bannerAdReadyForPlacementID:placementID];
}


-(void) showBannerAdWithPlacementID:(NSString*)placementID rect:(NSDictionary *)rectDict {
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
    dispatch_async(dispatch_get_main_queue(), ^{
        if(self->_bannerViewStorage[placementID] != nil){
            [self->_bannerViewStorage[placementID] removeFromSuperview];
            [self->_bannerViewStorage removeObjectForKey:placementID];
        }
       
    });
}

-(void) showBannerAdWithPlacementID:(NSString*)placementID {
    dispatch_async(dispatch_get_main_queue(), ^{
        ATBannerView *bannerView = self->_bannerViewStorage[placementID];
        if (bannerView.superview != nil) { bannerView.hidden = NO; }
    });
}

-(void) hideBannerAdWithPlacementID:(NSString*)placementID {
    dispatch_async(dispatch_get_main_queue(), ^{
        ATBannerView *bannerView = self->_bannerViewStorage[placementID];
        if (bannerView.superview != nil) { bannerView.hidden = YES; }
    });
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

#pragma mark - banner delegate method(s)
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {

    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerAdLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
  
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

-(void) bannerView:(ATBannerView *)bannerView didShowAdWithPlacementID:(NSString *)placementID {

    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerShow(cPlacementId);
    }
    
}

-(void) bannerView:(ATBannerView*)bannerView didClickWithPlacementID:(NSString*)placementID {

    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerClicked(cPlacementId);
    }
    
}

-(void) bannerView:(ATBannerView*)bannerView didCloseWithPlacementID:(NSString*)placementID {
    
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerClose(cPlacementId);
    }
    
}

-(void) bannerView:(ATBannerView *)bannerView didAutoRefreshWithPlacement:(NSString *)placementID {
    
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onBannerAutoRefresh(cPlacementId);
    }
}

-(void) bannerView:(ATBannerView *)bannerView failedToAutoRefreshWithPlacementID:(NSString *)placementID error:(NSError *)error {
    
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
        pDelegate->onBannerAutoRefreshFail(cPlacementId, errorDict.jsonString.UTF8String);
    }
    
}

#pragma - mark delegate with adsourceID and networkID
-(void) bannerView:(ATBannerView*)bannerView didShowAdWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerShowWithExtra(cPlacementId, cExtra);
    }
}
-(void) bannerView:(ATBannerView*)bannerView didClickWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerClickedWithExtra(cPlacementId, cExtra);
    }
}
-(void) bannerView:(ATBannerView*)bannerView didCloseWithPlacementID:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerCloseWithExtra(cPlacementId, cExtra);
    }
}
-(void) bannerView:(ATBannerView*)bannerView didAutoRefreshWithPlacement:(NSString*)placementID extra:(NSDictionary *)extra{
    void* callback = [[ATBannerAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosBannerAdListener* pDelegate = (ATCocosBannerAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onBannerAutoRefreshWithExtra(cPlacementId, cExtra);
    }
}
-(void) bannerView:(ATBannerView*)bannerView failedToAutoRefreshWithPlacementID:(NSString*)placementID  extra:(NSDictionary *)extra error:(NSError*)error {
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
