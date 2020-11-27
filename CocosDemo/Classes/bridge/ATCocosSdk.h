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
#include "ATCocosGDPRListener.h"
#include "ATCocosUserLocationListener.h"
using namespace std;


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

    static const char* KEY_BACKGROUND_COLOR;
    static const char* KEY_TEXT_SIZE;


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

    static const char* KEY_USER_ID;
    static const char* KEY_MEDIA_EXT;

    static const int USER_LOCATION_UNKNOWN;
    static const int USER_LOCATION_IN_EU;
    static const int USER_LOCATION_OUT_OF_EU;

    static const int GDPR_PERSONALIZED;
    static const int GDPR_NONPERSONALIZED;
    static const int GDPR_UNKNOWN;


    //for android and ios
    static const char* OS_VERSION_NAME;
    static const char* OS_VERSION_CODE;
    static const char* APP_PACKAGE_NAME;
    static const char* APP_VERSION_NAME;
    static const char* APP_VERSION_CODE;

    static const char* BRAND;
    static const char* MODEL;
    static const char* DEVICE_SCREEN_SIZE;
    static const char* MNC;
    static const char* MCC;

    static const char* LANGUAGE;
    static const char* TIMEZONE;
    static const char* USER_AGENT;
    static const char* ORIENTATION;
    static const char* NETWORK_TYPE;

    //for android
    static const char* INSTALLER;
    static const char* ANDROID_ID;
    static const char* GAID;
    static const char* MAC;
    static const char* IMEI;
    static const char* OAID;

    //for ios
    static const char* IDFA;
    static const char* IDFV;


    static const char* KEY_PARENT;
    static const char* KEY_ICON;
    static const char* KEY_MAIN_IMAGE;
    static const char* KEY_TITLE;
    static const char* KEY_DESC;
    static const char* KEY_AD_LOGO;
    static const char* KEY_CTA;
    static const char* KEY_RATING;

    static const char* KEY_TOP;
    static const char* KEY_BOTTOM;

    static const char* KEY_INLINE_ADAPTIVE_WIDTH;
    static const char* KEY_INLINE_ADAPTIVE_ORIENTATION;
    static const int INLINE_ADAPTIVE_ORIENTATION_CURRENT;
    static const int INLINE_ADAPTIVE_ORIENTATION_PORTRAIT;
    static const int INLINE_ADAPTIVE_ORIENTATION_LANDSCAPE;

    static const char* KEY_ADAPTIVE_WIDTH;
    static const char* KEY_ADAPTIVE_ORIENTATION;
    static const int ADAPTIVE_ORIENTATION_CURRENT;
    static const int ADAPTIVE_ORIENTATION_PORTRAIT;
    static const int ADAPTIVE_ORIENTATION_LANDSCAPE;

    static const char* KEY_USE_REWARDED_VIDEO_AS_INTERSTITIAL;

//    const char* KEY_
    
    
    /**
     sdk core
     **/
    //iOS + Android
    static void setChannel(const char * channel);
    //iOS + Android
    static void setSubChannel(const char * subChannel);
    //iOS + Android
    static void setCustomData(cocos2d::ValueMap customData);
    //iOS + Android
    static void setPlacementCustomData(const char * placementId, cocos2d::ValueMap customData);

    //iOS + Android
    static void integrationChecking();

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
    
    static void showGdprAuthWithListener(ATCocosGDPRListener * listener);

    //iOS + Android.
    static bool isEUTraffic();

    //iOS + Android.
    static void getUserLocation(ATCocosUserLocationListener * listener);

    //iOS + Android.
    static void deniedUploadDeviceInfo(cocos2d::ValueVector deniedInfo);

    
    /**
     adtype native
     **/
    //iOS + Android.
    static void setNativeAdListener(ATCocosNativeAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadNativeAd(const char * placementId, cocos2d::ValueMap parameters);
    
    //iOS + Android.
    static bool isNativeAdReady(const char * placementId);
    
    //iOS + Android.
//    static void showNativeAd(const char * placementId, cocos2d::ValueMap parameters);
    static void showNativeAd(const char * placementId, std::string parameters);

    //iOS + Android.
    static void removeNativeAd(const char * placementId);
    
    /**
     adtype banner
     **/
    //iOS + Android.
    static void setBannerAdListener(ATCocosBannerAdListener * listener, const char * placementId);
    
    //iOS + Android. the parameters support the custom data by k-v
    static void loadBannerAd(const char * placementId, cocos2d::ValueMap parameters);
    
    //iOS + Android.
    static bool isBannerAdReady(const char * placementId);
    
    //iOS + Android.
    //parameters support the value:x、y、w、h
    //ios only support x、y, the size support 320*50
    static void showBannerAd(const char * placementId, cocos2d::ValueMap parameters);
    static void showBannerAdInPostion(const char * placementId, std::string postion);

    //iOS + Android.
    static void removeBannerAd(const char * placementId);
    
    
    /**
     adtype native banner
     **/
    //iOS + Android.
    static void setNativeBannerAdListener(ATCocosNativeBannerAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadNativeBannerAd(const char * placementId, cocos2d::ValueMap customData);
    
    //iOS + Android.
    static bool isNativeBannerAdReady(const char * placementId);
    
    //iOS + Android.
    //parameters x、y、w、h
    //补充相关的配置参数
    static void showNativeBannerAd(const char * placementId, cocos2d::ValueMap rect, cocos2d::ValueMap extra);
    
    //iOS + Android.
    static void removeNativeBannerAd(const char * placementId);
    
    /**
     adtype rewarded video
     **/
    //iOS + Android.
    static void setRewardedVideoAdListener(ATCocosRewardedVideoAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadRewardedVideoAd(const char * placementId, cocos2d::ValueMap parameters);
    
    //iOS + Android.
    static bool isRewardedVideoAdReady(const char * placementId);

    //iOS + Android.
    static char* checkRewardedVideoAdStatus(const char * placementId);
    
    /**
     
     **/
    //iOS + Android.
    static void showRewardedVideoAd(const char * placementId);
    //iOS + Android.
    static void showRewardedVideoAdInScenario(const char * placementId, const char * scenario);
    
    
    /**
     adtype interstitial
     **/
    //iOS + Android.
    static void setInterstitialAdListener(ATCocosInterstitialAdListener * listener, const char * placementId);
    
    //iOS + Android.
    static void loadInterstitialAd(const char * placementId, cocos2d::ValueMap parameters);
    
    //iOS + Android.
    static bool isInterstitialAdReady(const char * placementId);

    //iOS + Android.
    static char* checkInterstitialAdStatus(const char * placementId);

    /**
     
     **/
    //iOS + Android.
    static void showInterstitialAd(const char * placementId);

    //iOS + Android.
    static void showInterstitialAdInScenario(const char * placementId, const char * scenario);
 
    /**
     
     **/
    //iOS.
    static double getScreenScale();
    
};


#endif /* ATCocosSdk_h */
