//
//  ATCocosSdk.h
//  up_sdk_cocos-mobile
//
//  Created by Stephen on 2019/7/23.
//

#ifndef ATCocosSdk_h
#define ATCocosSdk_h

#include "cocos2d.h"
#include "ATCocosBannerAdListener.h"
#include "ATCocosInterstitialAdListener.h"
#include "ATCocosNativeAdListener.h"
#include "ATCocosRewardedVideoAdListener.h"
#include "ATCocosNativeBannerAdListener.h"


#define UPARPU_COCOS_SDK_VERSION   "1.0.0"

class ATCocosSdk {
    
public:
   
    /**
     const for sdk
     **/
    static const char* KEY_WIDTH;
    static const char* KEY_HEIGHT;
    static const char* KEY_POS_X;
    static const char* KEY_POS_Y;
    static const char* KEY_MAIN_BG_COLOR;
    static const char* KEY_REFRESH_INTERVEL;
    static const char* KEY_BUTTON_CLOSE_STATUS;
    static const char* KEY_BUTTON_CTA_BG;
    static const char* KEY_BUTTON_CTA_TITLE_FONT;
    static const char* KEY_BUTTON_CTA_TITLE_COLOR;
    static const char* KEY_TITLE_FONT;
    static const char* KEY_TITLE_COLOR;
    static const char* KEY_TEXT_FONT;
    static const char* KEY_TEXT_COLOR;
    static const char* KEY_ADVERTISER_TEXT_FONT;
    static const char* KEY_ADVERTISER_TEXT_COLOR;
    static const char* KEY_BANNER_SIZE_TYPE;
    static const char* KEY_IS_SHOW_CTA;
    
//    const char* KEY_
    
    
    /**
     sdk core
     **/
    //iOS + Android
    static void setChannel(const char * channel);
    //iOS + Android
    static void setCustomData(cocos2d::CCDictionary * customData);
    //iOS + Android
    static bool initSDK(const char * appId, const char * appKey);
    //iOS + Android
    static void setDebugLog(bool value);
    //iOS
    static void setGDPRLevel(int level);
    //iOS
    static int getGDPRLevel();
    //iOS + Android
    static void showGdprAuth();
    //iOS + Android.
    static bool isEUTraffic();
    
    /**
     adtype native
     **/
    //iOS + Android.
    static void setNativeAdListener(ATCocosNativeAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadNativeAd(const char * placementId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static bool isNativeAdReady(const char * placementId);
    
    //iOS + Android.
    static void showNativeAd(const char * placementId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static void removeNativeAd(const char * placementId);
    
    /**
     adtype banner
     **/
    //iOS + Android.
    static void setBannerAdListener(ATCocosBannerAdListener * listener, const char * placementId);
    
    //iOS + Android. the parameters support the custom data by k-v
    static void loadBannerAd(const char * placementId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static bool isBannerAdReady(const char * placementId);
    
    //iOS + Android.
    //parameters support the value:x、y、w、h
    //ios only support x、y, the size support 320*50
    static void showBannerAd(const char * placementId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static void removeBannerAd(const char * placementId);
    
    
    /**
     adtype native banner
     **/
    //iOS + Android.
    static void setNativeBannerAdListener(ATCocosNativeBannerAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadNativeBannerAd(const char * placementId, cocos2d::CCDictionary  * customData);
    
    //iOS + Android.
    static bool isNativeBannerAdReady(const char * placementId);
    
    //iOS + Android.
    //parameters x、y、w、h
    //补充相关的配置参数
    static void showNativeBannerAd(const char * placementId, cocos2d::CCDictionary  * rect, cocos2d::CCDictionary  * extra);
    
    //iOS + Android.
    static void removeNativeBannerAd(const char * placementId);
    
    /**
     adtype rewarded video
     **/
    //iOS + Android.
    static void setRewardedVideoAdListener(ATCocosRewardedVideoAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadRewardedVideoAd(const char * placementId, const char * userId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static bool isRewardedVideoAdReady(const char * placementId);
    
    /**
     
     **/
    //iOS + Android.
    static void showRewardedVideoAd(const char * placementId);
    
    
    /**
     adtype interstitial
     **/
    //iOS + Android.
    static void setInterstitialAdListener(ATCocosInterstitialAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadInterstitialAd(const char * placementId, cocos2d::CCDictionary  * parameters);
    
    //iOS + Android.
    static bool isInterstitialAdReady(const char * placementId);
    
    /**
     
     **/
    //iOS + Android.
    static void showInterstitialAd(const char * placementId);
    
 
    /**
     
     **/
    //iOS.
    static double getScreenScale();
    
};


#endif /* ATCocosSdk_h */
