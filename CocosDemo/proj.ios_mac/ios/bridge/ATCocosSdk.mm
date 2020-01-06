//
//  ATCocosSdk.mm
//  up_sdk_cocos-mobile
//
//  Created by Stephen on 2019/7/23.
//
#import "ATCocosSdk.h"
//#include "ATCocosRewardedVideoAdListener.h"

#import "ATCocosUtils.h"
#import <AnyThinkSDK/ATAPI.h>
#import "ATRewardedVideoWrapper.h"
#import "ATInterstitialAdWrapper.h"
#import "ATBannerAdWrapper.h"
#import "ATNativeBannerAdWrapper.h"
#import "ATNativeAdWrapper.h"
#import "ATCocosGDPRListener.h"
//#import <ATInterstitial/ATInterstitial.h>
//#import <ATNative/ATNative.h>
//@import ATSDK;
//@import ATRewardedVideo;

//#import <CoreTelephony/CTTelephonyNetworkInfo.h>
//#import <CoreTelephony/CTCarrier.h>


/**
 const for sdk
 **/
const char* ATCocosSdk::KEY_WIDTH = "w";
const char* ATCocosSdk::KEY_HEIGHT = "h";
const char* ATCocosSdk::KEY_POS_X = "x";
const char* ATCocosSdk::KEY_POS_Y = "y";
const char* ATCocosSdk::KEY_MAIN_BG_COLOR = "key_main_bg_color";
const char* ATCocosSdk::KEY_REFRESH_INTERVEL = "key_refresh_intervel";
const char* ATCocosSdk::KEY_BUTTON_CLOSE_STATUS = "key_button_close_status";
const char* ATCocosSdk::KEY_BUTTON_CTA_BG = "key_button_cta_bg";
const char* ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT = "key_button_cta_title_font";
const char* ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR = "key_button_cta_title_color";
const char* ATCocosSdk::KEY_TITLE_FONT = "key_title_font";
const char* ATCocosSdk::KEY_TITLE_COLOR = "key_title_color";
const char* ATCocosSdk::KEY_TEXT_FONT = "key_text_font";
const char* ATCocosSdk::KEY_TEXT_COLOR = "key_text_color";
const char* ATCocosSdk::KEY_ADVERTISER_TEXT_FONT = "key_advertiser_text_font";
const char* ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR = "key_advertiser_text_color";


//iOS + Android
void ATCocosSdk::setChannel(const char * channel) {
    NSString *mChannel = [ATCocosUtils nsstringFromCString:channel];
     NSLog(@"ATCocosSdk::setChannel mChannel:%@", mChannel);
    [[ATAPI sharedInstance] setChannel:mChannel];
}
//iOS + Android
void ATCocosSdk::setCustomData(cocos2d::CCDictionary * customData) {
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromCCDictionary:customData];
    NSLog(@"ATCocosSdk::setCustomData:%@", customDict);
    [[ATAPI sharedInstance] setCustomData:customDict];
}

bool ATCocosSdk::initSDK(const char * appId, const char * appKey) {

    NSString *mAppId = [ATCocosUtils nsstringFromCString:appId];
    NSString *mAppKey = [ATCocosUtils nsstringFromCString:appKey];
    NSLog(@"ATCocosSdk::initSDK appid:%@,appkey:%@", mAppId, mAppKey);

    BOOL initResult = [[ATAPI sharedInstance] startWithAppID:mAppId appKey:mAppKey error:nil];
    
  
    
    return initResult;
}
//iOS + Android
void ATCocosSdk::setDebugLog(bool value) {
    
    [ATAPI setLogEnabled:value];
    
}
//iOS
void ATCocosSdk::setGDPRLevel(int level) {
    level = level + 1;
    if (level == 3) {level = 0;}
    if (level > 2 || level < 0) { level = 0;}
    [[ATAPI sharedInstance] setDataConsentSet:ATDataConsentSet(level) consentString:nil];
}
//iOS
int ATCocosSdk::getGDPRLevel() {
    int gdprLevel = (int)[ATAPI sharedInstance].dataConsentSet;
    gdprLevel = gdprLevel - 1;
    if (gdprLevel == -1) { gdprLevel = 2;}
    if (gdprLevel < -1 || gdprLevel > 1) { gdprLevel = 2;}
    return gdprLevel;
}
void ATCocosSdk::showGdprAuth() {
    
    UIViewController *rootViewController = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
    [[ATAPI sharedInstance]presentDataConsentDialogInViewController:rootViewController dismissalCallback:^{
    }];
}

//iOS + Android
void ATCocosSdk::showGdprAuthWithListener(ATCocosGDPRListener * listener) {
    
    UIViewController *rootViewController = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
    [[ATAPI sharedInstance]presentDataConsentDialogInViewController:rootViewController dismissalCallback:^{
        listener -> onGDPRDataConsentSet(ATCocosSdk::getGDPRLevel());
    }];
}
//iOS + Android.
bool ATCocosSdk::isEUTraffic() {
    BOOL euResult = [[ATAPI sharedInstance] inDataProtectionArea];
    return euResult;
}

/**
 adtype rewarded video
 **/
//iOS + Android.
void ATCocosSdk::setRewardedVideoAdListener(ATCocosRewardedVideoAdListener * listener, const char * placementId) {
     NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATRewardedVideoWrapper sharedInstance] setCallBack:(void*)listener forKey:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::loadRewardedVideoAd(const char * placementId, const char * userId, cocos2d::CCDictionary  * parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *mUserId = nil;
    if(userId != NULL){
        mUserId = [ATCocosUtils nsstringFromCString:userId];
    }
    NSDictionary *customDict = nil;
    if(parameters){
        customDict = [ATCocosUtils nsDictionaryFromCCDictionary:parameters];
    }
    [[ATRewardedVideoWrapper sharedInstance] loadRewardedVideoWithPlacementID:mPlacementId userId:mUserId customData:customDict];

}

//iOS + Android.
bool ATCocosSdk::isRewardedVideoAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATRewardedVideoWrapper sharedInstance] rewardedVideoReadyForPlacementID:mPlacementId];
}

/**
 
 **/
//iOS + Android.
void ATCocosSdk::showRewardedVideoAd(const char * placementId) {
     NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATRewardedVideoWrapper sharedInstance] showRewardedVideoWithPlacementID:mPlacementId];
}


/**
 adtype interstitial
 **/
//iOS + Android.
void ATCocosSdk::setInterstitialAdListener(ATCocosInterstitialAdListener * listener, const char * placementId) {
    
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATInterstitialAdWrapper sharedInstance] setCallBack:(void*)listener forKey:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::loadInterstitialAd(const char * placementId, cocos2d::CCDictionary  * parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
  
    NSDictionary *customDict = nil;
    if(parameters){
        customDict = [ATCocosUtils nsDictionaryFromCCDictionary:parameters];
    }
    [[ATInterstitialAdWrapper sharedInstance] loadInterstitialAdWithPlacementID:mPlacementId customData:customDict];
}

//iOS + Android.
bool ATCocosSdk::isInterstitialAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATInterstitialAdWrapper sharedInstance] interstitialAdReadyForPlacementID:mPlacementId];
}

/**
 
 **/
//iOS + Android.
void ATCocosSdk::showInterstitialAd(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATInterstitialAdWrapper sharedInstance] showInterstitialAdWithPlacementID:mPlacementId];
}


/**
 adtype banner
 **/
//iOS + Android.
void ATCocosSdk::setBannerAdListener(ATCocosBannerAdListener * listener, const char * placementId) {
    
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATBannerAdWrapper sharedInstance] setCallBack:(void*)listener forKey:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::loadBannerAd(const char * placementId, cocos2d::CCDictionary  * parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    
    NSDictionary *customDict = nil;
    if(parameters){
        customDict = [ATCocosUtils nsDictionaryFromCCDictionary:parameters];
    }
    [[ATBannerAdWrapper sharedInstance] loadBannerAdWithPlacementID:mPlacementId customData:customDict];
}

//iOS + Android.
bool ATCocosSdk::isBannerAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATBannerAdWrapper sharedInstance] bannerAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
//parameters x、y、w、h
void ATCocosSdk::showBannerAd(const char * placementId, cocos2d::CCDictionary  * parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    
    NSDictionary *customDict = nil;
    if(parameters){
        customDict = [ATCocosUtils nsDictionaryFromCCDictionary:parameters];
    }
    [[ATBannerAdWrapper sharedInstance] showBannerAdWithPlacementID:mPlacementId rect:customDict];
}

//iOS + Android.
void ATCocosSdk::removeBannerAd(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    
    [[ATBannerAdWrapper sharedInstance] removeBannerAdWithPlacementID:mPlacementId];
}


/**
 adtype native banner
 **/
//iOS + Android.
void ATCocosSdk::setNativeBannerAdListener(ATCocosNativeBannerAdListener * listener, const char * placementId){
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATNativeBannerAdWrapper sharedInstance] setCallBack:(void*)listener forKey:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::loadNativeBannerAd(const char * placementId, cocos2d::CCDictionary  * customData) {
    
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];

    NSDictionary *customDict = nil;
    if(customData){
        customDict = [ATCocosUtils nsDictionaryFromCCDictionary:customData];
    }
    [[ATNativeBannerAdWrapper sharedInstance] loadNativeBannerAdWithPlacementID:mPlacementId customData:customDict];
    
}

//iOS + Android.
bool ATCocosSdk::isNativeBannerAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
   
    return [[ATNativeBannerAdWrapper sharedInstance] isNativeBannerAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
//rect x、y、w、h
//customData
//补充相关的配置参数
void ATCocosSdk::showNativeBannerAd(const char * placementId, cocos2d::CCDictionary  * rect, cocos2d::CCDictionary  * extra) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    
    NSDictionary *rectDict = nil;
    if(rect){
        rectDict = [ATCocosUtils nsDictionaryFromCCDictionary:rect];
    }
    
    NSDictionary *extraDict = nil;
    if(extra){
        extraDict = [ATCocosUtils nsDictionaryFromCCDictionary:extra];
    }
    [[ATNativeBannerAdWrapper sharedInstance] showNativeBannerAdWithPlacementID:mPlacementId rect:rectDict extra:extraDict];
}

//iOS + Android.
void ATCocosSdk::removeNativeBannerAd(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    
    [[ATNativeBannerAdWrapper sharedInstance] removeNativeBannerAdWithPlacementID:mPlacementId];
}



/**
 adtype native
 **/
//iOS + Android.
void ATCocosSdk::setNativeAdListener(ATCocosNativeAdListener * listener, const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATNativeAdWrapper sharedInstance] setCallBack:(void*)listener forKey:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::loadNativeAd(const char * placementId, cocos2d::CCDictionary  * parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATNativeAdWrapper sharedInstance] loadNativeAdWithPlacementID:mPlacementId customData:parameters];
}

//iOS + Android.
bool ATCocosSdk::isNativeAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return [[ATNativeAdWrapper sharedInstance] isNativeAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showNativeAd(const char * placementId, cocos2d::CCDictionary  * parameters) {
    
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    //frame
    NSMutableDictionary *rectDict = nil;
    if(parameters){
        rectDict = [ATCocosUtils nsDictionaryFromCCDictionary:parameters];
    }
  
    
    [[ATNativeAdWrapper sharedInstance] showNativeAdWithPlacementID:mPlacementId rectDict:rectDict];
    
}

//iOS + Android.
void ATCocosSdk::removeNativeAd(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATNativeAdWrapper sharedInstance] removeNativeAdViewWithPlacementID:mPlacementId];
}



/**
 
 **/
//iOS.
double ATCocosSdk::getScreenScale() {
     NSLog(@"scale:%f",[UIScreen mainScreen].scale);
    return [UIScreen mainScreen].scale;
}
