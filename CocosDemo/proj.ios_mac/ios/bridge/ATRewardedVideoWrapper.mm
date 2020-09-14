//
//  ATRewardedVideoWrapper.m
//  UnityContainer
//
//  Created by Martin Lau on 08/08/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import "ATRewardedVideoWrapper.h"
#import <AnyThinkRewardedVideo/AnyThinkRewardedVideo.h>
#import <AVFoundation/AVFoundation.h>
#import "ATCocosUtils.h"

#include "ATCocosRewardedVideoAdListener.h"



static AVAudioSessionCategory AudioSessionCategory;
@implementation ATRewardedVideoWrapper
+(instancetype)sharedInstance {
    static ATRewardedVideoWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ATRewardedVideoWrapper alloc] init];
    });
    return sharedInstance;
}

-(instancetype) init {
    self = [super init];
    return self;
}

-(void) loadRewardedVideoWithPlacementID:(NSString*)placementID  extra:(NSDictionary*)customData  {
    NSLog(@"ATRewardedVideoWrapper::loadRewardedVideoWithPlacementID:%@ extra:%@", placementID, customData);
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:customData delegate:self];
}

-(BOOL) rewardedVideoReadyForPlacementID:(NSString*)placementID {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoReadyForPlacementID:%@", placementID);
    return [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:placementID];
}

-(void) showRewardedVideoWithPlacementID:(NSString*)placementID {
    NSLog(@"ATRewardedVideoWrapper::showRewardedVideoWithPlacementID:%@", placementID);
    AudioSessionCategory = [AVAudioSession sharedInstance].category;
    [[ATAdManager sharedManager] showRewardedVideoWithPlacementID:placementID inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
}

-(void) showRewardedVideoWithPlacementID:(NSString*)placementID scene:(NSString*)scene {
    NSLog(@"ATRewardedVideoWrapper::showRewardedVideoWithPlacementID:%@ scene:%@", placementID, scene);
    AudioSessionCategory = [AVAudioSession sharedInstance].category;
    [[ATAdManager sharedManager] showRewardedVideoWithPlacementID:placementID scene:scene inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

-(void) setExtra:(NSString*)extra {
    if ([extra isKindOfClass:[NSString class]]) {
        NSDictionary *extraDict = [NSJSONSerialization JSONObjectWithData:[extra dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingAllowFragments error:nil];
        if ([extraDict isKindOfClass:[NSDictionary class]]) [[ATAdManager sharedManager] setExtra:extraDict];
    }
}

#pragma mark - delegate
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {
    NSLog(@"ATRewardedVideoWrapper::didFinishLoadingADWithPlacementID:%@", placementID);
    ATCocosRewardedVideoAdListener* callback = (ATCocosRewardedVideoAdListener*)[[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        callback->onRewardedVideoLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    NSLog(@"ATRewardedVideoWrapper::didFailToLoadADWithPlacementID:%@ error:%@", placementID, error);
    ATCocosRewardedVideoAdListener* callback = (ATCocosRewardedVideoAdListener*)[[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != nil) {
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        
        NSMutableDictionary *errorDict = [NSMutableDictionary dictionaryWithObject:[NSString stringWithFormat:@"%ld", (long)error.code] forKey:@"code"];
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
        callback->onRewardedVideoLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
}

#pragma mark - showing delegate
-(void) rewardedVideoDidRewardSuccessForPlacemenID:(NSString *)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidRewardSuccessForPlacemenID:%@ extra:%@", placementID, extra);
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];

    if (callback != NULL) {
      ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
      const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
      const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
      pDelegate->onRewardedVideoDidRewardSuccessWithExtra(cPlacementId, cExtra);
    }
}


#pragma mark - delegate with adsourceID and networkID
-(void) rewardedVideoDidStartPlayingForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidStartPlayingForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onRewardedVideoPlayStartWithExtra(cPlacementId, cExtra);
    }
}

-(void) rewardedVideoDidEndPlayingForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidEndPlayingForPlacementID:%@ extra:%@", placementID, extra);
    [[AVAudioSession sharedInstance] setCategory:AudioSessionCategory error:nil];
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onRewardedVideoPlayEndWithExtra(cPlacementId, cExtra);
    }
}

-(void) rewardedVideoDidFailToPlayForPlacementID:(NSString*)placementID error:(NSError*)error extra:(NSDictionary *)extra {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidFailToPlayForPlacementID:%@ error:%@ extra:%@", placementID, error, extra);
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        
        NSMutableDictionary *errorDict = [NSMutableDictionary dictionaryWithObject:[NSString stringWithFormat:@"%ld", (long)error.code] forKey:@"code"];
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
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onRewardedVideoShowFailWithExtra(cPlacementId, errorDict.jsonString.UTF8String, cExtra);
    }
}

-(void) rewardedVideoDidCloseForPlacementID:(NSString*)placementID rewarded:(BOOL)rewarded extra:(NSDictionary *)extra {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidCloseForPlacementID:%@ rewarded:%@ extra:%@", placementID, rewarded ? @"1" : @"0", extra);
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onRewardedVideoCloseWithExtra(cPlacementId, rewarded, cExtra);
    }
}

-(void) rewardedVideoDidClickForPlacementID:(NSString*)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATRewardedVideoWrapper::rewardedVideoDidClickForPlacementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onRewardedVideoClickedWithExtra(cPlacementId, cExtra);
    }
}

@end
