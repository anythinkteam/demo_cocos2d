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
#import "ATCocosUserLocationListener.h"
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
const char* ATCocosSdk::KEY_BACKGROUND_COLOR = "backgroundColor";
const char* ATCocosSdk::KEY_TEXT_SIZE = "textSize";
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

const int ATCocosSdk::USER_LOCATION_UNKNOWN = 0;
const int ATCocosSdk::USER_LOCATION_IN_EU = 1;
const int ATCocosSdk::USER_LOCATION_OUT_OF_EU = 2;

const int ATCocosSdk::GDPR_PERSONALIZED = 0;
const int ATCocosSdk::GDPR_NONPERSONALIZED = 1;
const int ATCocosSdk::GDPR_UNKNOWN = 2;

const char* ATCocosSdk::KEY_USER_ID = "key_user_id";
const char* ATCocosSdk::KEY_MEDIA_EXT = "key_media_ext";

const char* ATCocosSdk::KEY_PARENT = "parent";
const char* ATCocosSdk::KEY_ICON = "icon";
const char* ATCocosSdk::KEY_MAIN_IMAGE = "mainImage";
const char* ATCocosSdk::KEY_TITLE = "title";
const char* ATCocosSdk::KEY_DESC = "desc";
const char* ATCocosSdk::KEY_AD_LOGO = "adLogo";
const char* ATCocosSdk::KEY_CTA = "cta";
const char* ATCocosSdk::KEY_RATING = "rating";

const char* ATCocosSdk::KEY_TOP = "top";
const char* ATCocosSdk::KEY_BOTTOM = "bottom";

const char* ATCocosSdk::KEY_INLINE_ADAPTIVE_WIDTH = "inline_adaptive_width";
const char* ATCocosSdk::KEY_INLINE_ADAPTIVE_ORIENTATION = "inline_adaptive_orientation";
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_CURRENT = 0;
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_PORTRAIT = 1;
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_LANDSCAPE = 2;

const char* ATCocosSdk::KEY_USE_REWARDED_VIDEO_AS_INTERSTITIAL = "uses_rewarded_video_flag";

//iOS + Android
void ATCocosSdk::setChannel(const char * channel) {
    NSString *mChannel = [ATCocosUtils nsstringFromCString:channel];
     NSLog(@"ATCocosSdk::setChannel mChannel:%@", mChannel);
    [[ATAPI sharedInstance] setChannel:mChannel];
}

//iOS + Android
void ATCocosSdk::setSubChannel(const char *subChannel) {
    NSString *mSubChannel = [ATCocosUtils nsstringFromCString:subChannel];
     NSLog(@"ATCocosSdk::setSubChannel mSubChannel:%@", mSubChannel);
    [[ATAPI sharedInstance] setSubchannel:mSubChannel];
}

//iOS + Android
void ATCocosSdk::setCustomData(cocos2d::ValueMap customData) {
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:customData];
    NSLog(@"ATCocosSdk::setCustomData:%@", customDict);
    [[ATAPI sharedInstance] setCustomData:customDict];
}

void ATCocosSdk::setPlacementCustomData(const char *placementId, cocos2d::ValueMap customData) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:customData];
    NSLog(@"ATSDKManager::setCustomData:%@ forPlacementID:%@", customDict, mPlacementId);
    [[ATAPI sharedInstance] setCustomData:customDict forPlacementID:mPlacementId];
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

void ATCocosSdk::integrationChecking() {
    [ATAPI integrationChecking];
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
    [[ATAPI sharedInstance] presentDataConsentDialogInViewController:rootViewController loadingFailureCallback:^(NSError *error) {
        NSLog(@"Failed to load data consent dialog page.");
        listener -> onPageLoadFail();
    } dismissalCallback:^{
        listener -> onGDPRDataConsentSet(ATCocosSdk::getGDPRLevel());
    }];
}

//iOS + Android.
bool ATCocosSdk::isEUTraffic() {
    BOOL euResult = [[ATAPI sharedInstance] inDataProtectionArea];
    return euResult;
}

//iOS + Android.
void ATCocosSdk::getUserLocation(ATCocosUserLocationListener *listener) {
    [[ATAPI sharedInstance] getUserLocationWithCallback:^(ATUserLocation location) {
        listener -> onUserLocation(location);
        
        if (location == ATUserLocationInEU) {
            NSLog(@"----------ATUserLocationInEU");
            if ([ATAPI sharedInstance].dataConsentSet == ATDataConsentSetUnknown) {
                NSLog(@"----------ATDataConsentSetUnknown");
            }
        }else if (location == ATUserLocationOutOfEU){
            NSLog(@"----------ATUserLocationOutOfEU");
        }else{
            NSLog(@"----------ATUserLocationUnknown");
        }
    }];
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
void ATCocosSdk::loadRewardedVideoAd(const char *placementId, cocos2d::ValueMap parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:parameters];
    [[ATRewardedVideoWrapper sharedInstance] loadRewardedVideoWithPlacementID:mPlacementId extra:customDict];
}

//iOS + Android.
bool ATCocosSdk::isRewardedVideoAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATRewardedVideoWrapper sharedInstance] rewardedVideoReadyForPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showRewardedVideoAd(const char * placementId) {
     NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATRewardedVideoWrapper sharedInstance] showRewardedVideoWithPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showRewardedVideoAdInScenario(const char *placementId, const char *scenario) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *mScenario = [ATCocosUtils nsstringFromCString:scenario];
    [[ATRewardedVideoWrapper sharedInstance] showRewardedVideoWithPlacementID:mPlacementId scene:mScenario];
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
void ATCocosSdk::loadInterstitialAd(const char *placementId, cocos2d::ValueMap parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:parameters];
    [[ATInterstitialAdWrapper sharedInstance] loadInterstitialAdWithPlacementID:mPlacementId extra:customDict];
}

//iOS + Android.
bool ATCocosSdk::isInterstitialAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATInterstitialAdWrapper sharedInstance] interstitialAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showInterstitialAd(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    [[ATInterstitialAdWrapper sharedInstance] showInterstitialAdWithPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showInterstitialAdInScenario(const char *placementId, const char *scenario) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *mScenario = [ATCocosUtils nsstringFromCString:scenario];
    [[ATInterstitialAdWrapper sharedInstance] showInterstitialAdWithPlacementID:mPlacementId scene:mScenario];
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
void ATCocosSdk::loadBannerAd(const char *placementId, cocos2d::ValueMap parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:parameters];
    [[ATBannerAdWrapper sharedInstance] loadBannerAdWithPlacementID:mPlacementId extra:customDict];
}

//iOS + Android.
bool ATCocosSdk::isBannerAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return  [[ATBannerAdWrapper sharedInstance] bannerAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
//parameters x、y、w、h
void ATCocosSdk::showBannerAd(const char *placementId, cocos2d::ValueMap parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:parameters];
    [[ATBannerAdWrapper sharedInstance] showBannerAdWithPlacementID:mPlacementId rect:customDict];
}

void ATCocosSdk::showBannerAdInPostion(const char *placementId, std::string postion) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *position = [NSString stringWithCString:postion.c_str()encoding:[NSString defaultCStringEncoding]];
    [[ATBannerAdWrapper sharedInstance] showBannerWithPlacementID:mPlacementId position:position];
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
void ATCocosSdk::loadNativeBannerAd(const char *placementId, cocos2d::ValueMap customData) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *customDict = [ATCocosUtils nsDictionaryFromValueMap:customData];
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
void ATCocosSdk::showNativeBannerAd(const char *placementId, cocos2d::ValueMap rect, cocos2d::ValueMap extra) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSDictionary *rectDict = [ATCocosUtils nsDictionaryFromValueMap:rect];
    NSDictionary *extraDict = [ATCocosUtils nsDictionaryFromValueMap:extra];
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
void ATCocosSdk::loadNativeAd(const char *placementId, cocos2d::ValueMap parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *extraJsonStr = [ATCocosUtils nsStringFromValueMap:parameters];
    [[ATNativeAdWrapper sharedInstance] loadNativeAdWithPlacementID:mPlacementId extra:extraJsonStr];
}

//iOS + Android.
bool ATCocosSdk::isNativeAdReady(const char * placementId) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    return [[ATNativeAdWrapper sharedInstance] isNativeAdReadyForPlacementID:mPlacementId];
}

//iOS + Android.
void ATCocosSdk::showNativeAd(const char *placementId, std::string parameters) {
    NSString *mPlacementId = [ATCocosUtils nsstringFromCString:placementId];
    NSString *metricsJSONString = [NSString stringWithCString:parameters.c_str()encoding:[NSString defaultCStringEncoding]];
    //frame
    [[ATNativeAdWrapper sharedInstance] showNativeAdWithPlacementID:mPlacementId metrics:metricsJSONString];
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
