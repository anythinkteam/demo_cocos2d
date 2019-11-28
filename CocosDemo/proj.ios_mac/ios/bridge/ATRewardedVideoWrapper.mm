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


-(void) loadRewardedVideoWithPlacementID:(NSString*)placementID  userId:(NSString*)userId  customData:(NSDictionary*)customData {
//    [self setCallBack:callback forKey:placementID];
    if(userId != nil){
        [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:@{kATAdLoadingExtraUserIDKey:userId} customData:customData delegate:self];
    }else{
        [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:nil customData:customData delegate:self];
    }
    
}

-(BOOL) rewardedVideoReadyForPlacementID:(NSString*)placementID {
    return [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:placementID];
}

-(void) showRewardedVideoWithPlacementID:(NSString*)placementID {
    AudioSessionCategory = [AVAudioSession sharedInstance].category;
    [[ATAdManager sharedManager] showRewardedVideoWithPlacementID:placementID inViewController:[UIApplication sharedApplication].delegate.window.rootViewController delegate:self];
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
    
    ATCocosRewardedVideoAdListener* callback = (ATCocosRewardedVideoAdListener*)[[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        callback->onRewardedVideoLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    ATCocosRewardedVideoAdListener* callback = (ATCocosRewardedVideoAdListener*)[[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != nil) {
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
        callback->onRewardedVideoLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
   
}

#pragma mark - showing delegate
-(void) rewardedVideoDidRewardSuccessForPlacemenID:(NSString *)placementID extra:(NSDictionary *)extra{
      void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
      
      if (callback != NULL) {
          ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
          const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
          pDelegate->onRewardedVideoDidRewardSuccess(cPlacementId);
      }
}


-(void) rewardedVideoDidStartPlayingForPlacementID:(NSString*)placementID {
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onRewardedVideoPlayStart(cPlacementId);
    }
    
}

-(void) rewardedVideoDidEndPlayingForPlacementID:(NSString*)placementID {
    [[AVAudioSession sharedInstance] setCategory:AudioSessionCategory error:nil];
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onRewardedVideoPlayEnd(cPlacementId);
    }
   
}

-(void) rewardedVideoDidFailToPlayForPlacementID:(NSString*)placementID error:(NSError*)error {
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
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
        pDelegate->onRewardedVideoShowFail(cPlacementId, errorDict.jsonString.UTF8String);
    }
   
}

-(void) rewardedVideoDidCloseForPlacementID:(NSString*)placementID rewarded:(BOOL)rewarded {
   
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onRewardedVideoClose(cPlacementId, rewarded);
    }
   
}

-(void) rewardedVideoDidClickForPlacementID:(NSString*)placementID {
    
    void* callback = [[ATRewardedVideoWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosRewardedVideoAdListener* pDelegate = (ATCocosRewardedVideoAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onRewardedVideoClicked(cPlacementId);
    }
    
}
@end
