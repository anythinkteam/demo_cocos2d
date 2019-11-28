//
//  ATCocosNativeAdListener.h
//  up_sdk_cocos
//
//  Created by Topon on 2019/7/25.
//

#ifndef ATCocosNativeAdListener_h
#define ATCocosNativeAdListener_h

class ATCocosNativeAdListener {
    
public:
    
    virtual void onNativeAdLoadSuccess(const char * placementId) {};
    
    virtual void onNativeAdLoadFailed(const char * placementId, const char * errorString) {};
    
    virtual void onNativeAdVideoStart(const char * placementId) {};
    
    virtual void onNativeAdVideoEnd(const char * placementId) {};
    
    virtual void onNativeAdShow(const char * placementId) {};
    
    virtual void onNativeAdClick(const char * placementId) {};
    
};



#endif /* ATCocosNativeAdListener_h */
