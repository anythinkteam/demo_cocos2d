//
//  ATCocosRewardedVideoAdListener.h
//  up_sdk_cocos
//
//  Created by Topon on 2019/7/25.
//

#ifndef ATCocosRewardedVideoAdListener_h
#define ATCocosRewardedVideoAdListener_h

class ATCocosRewardedVideoAdListener {
    
public:
    
    virtual void onRewardedVideoLoadSuccess(const char * placementId) {};
    
    virtual void onRewardedVideoLoadFailed(const char * placementId, const char * errorString) {};
    
    virtual void onRewardedVideoPlayStart(const char * placementId) {};
    
    virtual void onRewardedVideoPlayEnd(const char * placementId) {};
    
    virtual void onRewardedVideoShowFail(const char * placementId, const char * errorString) {};
    
    virtual void onRewardedVideoClose(const char * placementId, bool isRewarded) {};
    
    virtual void onRewardedVideoClicked(const char * placementId) {};
    
    virtual void onRewardedVideoDidRewardSuccess(const char * placementId) {};
    
};

#endif /* ATCocosRewardedVideoAdListener_h */
