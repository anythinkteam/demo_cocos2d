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
    
    virtual void onBannerShow(const char * placementId) {};
    
    virtual void onBannerClicked(const char * placementId) {};
    
    virtual void onBannerClose(const char * placementId) {};
    
    virtual void onBannerAutoRefresh(const char * placementId) {};
    
    virtual void onBannerAutoRefreshFail(const char * placementId, const char * errorString) {};
    
};

#endif /* ATCocosBannerAdListener_h */
