//
//  ATCocosBannerAdListener.h
//  up_sdk_cocos
//
//  Created by Topon on 2019/7/25.
//

#ifndef ATCocosBannerAdListener_h
#define ATCocosBannerAdListener_h

class ATCocosBannerAdListener {
    
public:
    
    virtual void onBannerAdLoadSuccess(const char * placementId) {};
    
    virtual void onBannerAdLoadFailed(const char * placementId, const char * errorString) {};
      
    //banner extra listener
    virtual void onBannerShowWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onBannerClickedWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onBannerCloseWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onBannerAutoRefreshWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onBannerAutoRefreshFailWithExtra(const char * placementId, const char * errorString, const char * extra) {};
    
};

#endif /* ATCocosBannerAdListener_h */
