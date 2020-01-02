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
    
    //native banner extra
    virtual void onNativeBannerShowWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onNativeBannerClickedWithExtra(const char * placementId, const char * extra) {};
    
    virtual void onNativeBannerAutoRefreshFailWithExtra(const char * placementId, const char * errorString, const char * extra) {};
    
    virtual void onNativeBannerCloseWithExtra(const char * placementId,const char * extra) {};
    
    virtual void onNativeBannerAutoRefreshWithExtra(const char * placementId,const char * extra) {};
    

};

#endif /* ATCocosNativeBannerListener_h */
