//
//  ATInterstitialAdWrapper.m
//  UnityContainer
//
//  Created by Martin Lau on 2019/1/8.
//  Copyright © 2019 Martin Lau. All rights reserved.
//

#import "ATInterstitialAdWrapper.h"
#import "ATCocosUtils.h"
#import <AnyThinkInterstitial/AnyThinkInterstitial.h>
#import "ATCocosInterstitialAdListener.h"

@implementation ATInterstitialAdWrapper
+(instancetype)sharedInstance {
    static ATInterstitialAdWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ATInterstitialAdWrapper alloc] init];
    });
    return sharedInstance;
}

-(instancetype) init {
    self = [super init];
    return self;
}

-(void) loadInterstitialAdWithPlacementID:(NSString*)placementID extra:(NSDictionary*)customData {
    NSLog(@"ATInterstitialAdWrapper::loadInterstitialWithPlacementID:%@", placementID);
    NSLog(@"loadInterstitialExtra = %@", customData);
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:customData delegate:self];
}

-(BOOL) interstitialAdReadyForPlacementID:(NSString*)placementID {
    NSLog(@"ATInterstitialAdWrapper::interstitialReadyForPlacementID:%@", placementID);
    return [[ATAdManager sharedManager] interstitialReadyForPlacementID:placementID];
}

-(NSString *) checkInterstitialAdStatus:(NSString*)placementID {
    NSLog(@"ATInterstitialAdWrapper::checkInterstitialAdStatus:%@", placementID);
    ATCheckLoadModel *checkLoadModel = [[ATAdManager sharedManager] checkInterstitialLoadStatusForPlacementID:placementID];
    NSMutableDictionary *statusDict = [NSMutableDictionary dictionary];
    statusDict[@"isLoading"] = @(checkLoadModel.isLoading);
    statusDict[@"isReady"] = @(checkLoadModel.isReady);
    statusDict[@"adInfo"] = checkLoadModel.adOfferInfo;
    NSLog(@"ATInterstitialAdWrapper::statusDict = %@", statusDict);
    return statusDict.jsonString;
}

-(void) showInterstitialAdWithPlacementID:(NSString*)placementID {
    NSLog(@"ATInterstitialAdWrapper::showInterstitialWithPlacementID:%@", placementID);
    [[ATAdManager sharedManager] showInterstitialWithPlacementID:placementID inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
}

-(void) showInterstitialAdWithPlacementID:(NSString*)placementID scene:(NSString*)scene{
    NSLog(@"ATInterstitialAdWrapper::showInterstitialWithPlacementID:%@ scene:%@", placementID, scene);
    [[ATAdManager sharedManager] showInterstitialWithPlacementID:placementID scene:scene inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

#pragma mark - delegate method(s)
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {
    NSLog(@"ATInterstitialAdWrapper::didFinishLoadingADWithPlacementID:%@", placementID);
    
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onInterstitalLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    NSLog(@"ATInterstitialAdWrapper::didFailToLoadADWithPlacementID:%@ error:%@", placementID, error);
    
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
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
        pDelegate->onInterstitalLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
}

#pragma mark - delegate with networkID and adsourceID
-(void) interstitialDidShowForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidShowForPlacementID:%@ extra:%@", placementID, extra);
    
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalShowWithExtra(cPlacementId, cExtra);
    }
}

-(void) interstitialFailedToShowForPlacementID:(NSString*)placementID error:(NSError*)error extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialFailedToShowForPlacementID:%@ error:%@ extra:%@", placementID, error, extra);
}

-(void) interstitialDidFailToPlayVideoForPlacementID:(NSString*)placementID error:(NSError*)error extra:(NSDictionary*)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidFailToPlayVideoForPlacementID:%@ error:%@ extra:%@", placementID, error, extra);
}

-(void) interstitialDidStartPlayingVideoForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidStartPlayingVideoForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalPlayStartWithExtra(cPlacementId, cExtra);
    }
}

-(void) interstitialDidEndPlayingVideoForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidEndPlayingVideoForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalPlayEndWithExtra(cPlacementId, cExtra);
    }
}

-(void) interstitialDidCloseForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidCloseForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalCloseWithExtra(cPlacementId, cExtra);
    }
}

-(void) interstitialDidClickForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATInterstitialAdWrapper::interstitialDidClickForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalClickedWithExtra(cPlacementId, cExtra);
    }
}

@end
