//
//  ATCocosNativeBannerListener.h
//  up_sdk_cocos
//
//  Created by Topon on 2019/7/25.
//

#ifndef ATCocosNativeBannerAdListener_h
#define ATCocosNativeBannerAdListener_h

class ATCocosNativeBannerAdListener {
    
public:
    
    virtual void onNativeBannerAdLoadSuccess(const char * placementId) {};
    
    virtual void onNativeBannerAdLoadFailed(const char * placementId, const char * errorString) {};
    
    virtual void onNativeBannerShow(const char * placementId) {};
    
    virtual void onNativeBannerClicked(const char * placementId) {};
    
    virtual void onNativeBannerAutoRefreshFail(const char * placementId, const char * errorString) {};
    
    virtual void onNativeBannerClose(const char * placementId) {};
    
    virtual void onNativeBannerAutoRefresh(const char * placementId) {};
    

};

#endif /* ATCocosNativeBannerListener_h */
