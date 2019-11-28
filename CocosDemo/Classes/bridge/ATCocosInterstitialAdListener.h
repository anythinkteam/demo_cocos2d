//
//  ATCocosInterstitialAdListener.h
//  up_sdk_cocos
//
//  Created by Topon on 2019/7/25.
//

#ifndef ATCocosInterstitialAdListener_h
#define ATCocosInterstitialAdListener_h

class ATCocosInterstitialAdListener {
    
public:
    
    virtual void onInterstitalLoadSuccess(const char * placementId) {};
    
    virtual void onInterstitalLoadFailed(const char * placementId, const char * errorString) {};
    
    virtual void onInterstitalShow(const char * placementId) {};
    
    virtual void onInterstitalClose(const char * placementId) {};
    
    virtual void onInterstitalClicked(const char * placementId) {};
    
};

#endif /* ATCocosInterstitialAdListener_h */
