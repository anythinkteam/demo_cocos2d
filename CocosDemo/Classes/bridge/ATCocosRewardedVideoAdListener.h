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
    
    virtual void onRewardedVideoDidRewardSuccessWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onRewardedVideoPlayStartWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onRewardedVideoPlayEndWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onRewardedVideoShowFailWithExtra(const char * placementId, const char * errorString, const char * extra) {};
    
    virtual void onRewardedVideoCloseWithExtra(const char * placementId, bool isRewarded, const char * extra) {};
    
    virtual void onRewardedVideoClickedWithExtra(const char * placementId, const char * extra) {};
    
};

#endif /* ATCocosRewardedVideoAdListener_h */
