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
    
    //interstitial extra listener
    virtual void onInterstitalShowWithExtra(const char * placementId,const char * extra) {};
    
    virtual void onInterstitalCloseWithExtra(const char * placementId,const char * extra) {};
    
    virtual void onInterstitalClickedWithExtra(const char * placementId,const char * extra) {};
    
};

#endif /* ATCocosInterstitialAdListener_h */
