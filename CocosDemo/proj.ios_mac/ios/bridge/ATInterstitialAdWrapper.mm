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

-(void) loadInterstitialAdWithPlacementID:(NSString*)placementID  customData:(NSDictionary*)customData {
    //    [self setCallBack:callback forKey:placementID];
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:nil customData:customData delegate:self];
}


-(BOOL) interstitialAdReadyForPlacementID:(NSString*)placementID {
    return [[ATAdManager sharedManager] interstitialReadyForPlacementID:placementID];
}

-(void) showInterstitialAdWithPlacementID:(NSString*)placementID {
    [[ATAdManager sharedManager] showInterstitialWithPlacementID:placementID inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

#pragma mark - delegate method(s)
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {

    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onInterstitalLoadSuccess(cPlacementId);
    }
    
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    
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

-(void) interstitialDidShowForPlacementID:(NSString*)placementID {

    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onInterstitalShow(cPlacementId);
    }
}

-(void) interstitialFailedToShowForPlacementID:(NSString*)placementID error:(NSError*)error {
//    error = error != nil ? error : [NSError errorWithDomain:@"com.AT.Unity3DPackage" code:100001 userInfo:@{NSLocalizedDescriptionKey:@"AT has failed to show ad", NSLocalizedFailureReasonErrorKey:@"AT has failed to show ad"}];
//    [self invokeCallback:@"OnInterstitialAdFailedToShow" placementID:placementID error:error extra:nil];
}

-(void) interstitialDidStartPlayingVideoForPlacementID:(NSString*)placementID {
  
}

-(void) interstitialDidEndPlayingVideoForPlacementID:(NSString*)placementID {

}

-(void) interstitialDidFailToPlayVideoForPlacementID:(NSString*)placementID error:(NSError*)error {
//    [self invokeCallback:@"OnInterstitialAdVideoPlayFailure" placementID:placementID error:error extra:nil];
}

-(void) interstitialDidCloseForPlacementID:(NSString*)placementID {
    
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onInterstitalClose(cPlacementId);
    }
    
}

-(void) interstitialDidClickForPlacementID:(NSString*)placementID  {
    
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onInterstitalClicked(cPlacementId);
    }
   
}

#pragma mark - delegate with networkID and adsourceID

-(void) interstitialDidShowForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalShowWithExtra(cPlacementId, cExtra);
    }}

-(void) interstitialFailedToShowForPlacementID:(NSString*)placementID error:(NSError*)error extra:(NSDictionary *)extra {
}

-(void) interstitialDidFailToPlayVideoForPlacementID:(NSString*)placementID error:(NSError*)error extra:(NSDictionary*)extra {
}

-(void) interstitialDidStartPlayingVideoForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
}

-(void) interstitialDidEndPlayingVideoForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
}

-(void) interstitialDidCloseForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalCloseWithExtra(cPlacementId, cExtra);
    }}

-(void) interstitialDidClickForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    void* callback = [[ATInterstitialAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosInterstitialAdListener* pDelegate = (ATCocosInterstitialAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char *cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onInterstitalClickedWithExtra(cPlacementId, cExtra);
    }
    
}
@end
