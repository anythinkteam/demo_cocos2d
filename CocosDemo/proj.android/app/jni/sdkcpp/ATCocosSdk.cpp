//
// Created by 张仕仁 on 2019-07-25.
//

#include "bridge/ATCocosSdk.h"
#include "bridge/CCSerialization.h"
#include "ATUtil.h"
#include <jni.h>
#include <json/writer.h>
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "ATListenerManager.h"

USING_NS_CC;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define UPARPUSDKHELPER   "com/anythink/cocos2dx/bridge/ATSDKJniHelper"
#endif

const char* ATCocosSdk::KEY_WIDTH = "width";
const char* ATCocosSdk::KEY_HEIGHT = "height";
const char* ATCocosSdk::KEY_POS_X = "x";
const char* ATCocosSdk::KEY_POS_Y = "y";

const char* ATCocosSdk::KEY_BACKGROUND_COLOR = "key_background_color";
const char* ATCocosSdk::KEY_TEXT_SIZE = "key_text_size";

const char* ATCocosSdk::KEY_PARENT = "parent";
const char* ATCocosSdk::KEY_ICON = "icon";
const char* ATCocosSdk::KEY_MAIN_IMAGE = "mainImage";
const char* ATCocosSdk::KEY_TITLE = "title";
const char* ATCocosSdk::KEY_DESC = "desc";
const char* ATCocosSdk::KEY_AD_LOGO = "adLogo";
const char* ATCocosSdk::KEY_CTA = "cta";
const char* ATCocosSdk::KEY_RATING = "rating";


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
const char* ATCocosSdk::KEY_BANNER_SIZE_TYPE = "key_banner_size_type";
const char* ATCocosSdk::KEY_IS_SHOW_CTA = "key_is_show_cta";

const char* ATCocosSdk::KEY_USER_ID = "key_user_id";
const char* ATCocosSdk::KEY_MEDIA_EXT = "key_media_ext";

const int ATCocosSdk::USER_LOCATION_UNKNOWN = 0;
const int ATCocosSdk::USER_LOCATION_IN_EU = 1;
const int ATCocosSdk::USER_LOCATION_OUT_OF_EU = 2;

const int ATCocosSdk::GDPR_PERSONALIZED = 0;
const int ATCocosSdk::GDPR_NONPERSONALIZED = 1;
const int ATCocosSdk::GDPR_UNKNOWN= 2;


//for android and ios
const char* ATCocosSdk::OS_VERSION_NAME = "os_vn";
const char* ATCocosSdk::OS_VERSION_CODE = "os_vc";
const char* ATCocosSdk::APP_PACKAGE_NAME = "package_name";
const char* ATCocosSdk::APP_VERSION_NAME = "app_vn";
const char* ATCocosSdk::APP_VERSION_CODE = "app_vc";

const char* ATCocosSdk::BRAND = "brand";
const char* ATCocosSdk::MODEL = "model";
const char* ATCocosSdk::DEVICE_SCREEN_SIZE = "screen";
const char* ATCocosSdk::MNC = "mnc";
const char* ATCocosSdk::MCC = "mcc";

const char* ATCocosSdk::LANGUAGE = "language";
const char* ATCocosSdk::TIMEZONE = "timezone";
const char* ATCocosSdk::USER_AGENT = "ua";
const char* ATCocosSdk::ORIENTATION = "orient";
const char* ATCocosSdk::NETWORK_TYPE = "network_type";

//for android
const char* ATCocosSdk::INSTALLER = "it_src";
const char* ATCocosSdk::ANDROID_ID = "android_id";
const char* ATCocosSdk::GAID = "gaid";
const char* ATCocosSdk::MAC = "mac";
const char* ATCocosSdk::IMEI = "imei";
const char* ATCocosSdk::OAID = "oaid";

//for ios
const char* ATCocosSdk::IDFA = "idfa";
const char* ATCocosSdk::IDFV = "idfv";


const char* ATCocosSdk::KEY_TOP = "top";
const char* ATCocosSdk::KEY_BOTTOM = "bottom";

const char* ATCocosSdk::KEY_INLINE_ADAPTIVE_WIDTH = "inline_adaptive_width";
const char* ATCocosSdk::KEY_INLINE_ADAPTIVE_ORIENTATION = "inline_adaptive_orientation";
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_CURRENT = 0;
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_PORTRAIT = 1;
const int ATCocosSdk::INLINE_ADAPTIVE_ORIENTATION_LANDSCAPE = 2;

const char* ATCocosSdk::KEY_ADAPTIVE_WIDTH = "adaptive_width";
const char* ATCocosSdk::KEY_ADAPTIVE_ORIENTATION = "adaptive_orientation";
const int ATCocosSdk::ADAPTIVE_ORIENTATION_CURRENT = 0;
const int ATCocosSdk::ADAPTIVE_ORIENTATION_PORTRAIT = 1;
const int ATCocosSdk::ADAPTIVE_ORIENTATION_LANDSCAPE = 2;

const char* ATCocosSdk::KEY_USE_REWARDED_VIDEO_AS_INTERSTITIAL = "UseRewardedVideoAsInterstitial";

bool ATCocosSdk::initSDK(const char *appid, const char *appkey) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "initSDK",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("initSDK");
        jstring appidstr = ATUtil::charTojstring(info.env, appid);
        jstring appkeystr = ATUtil::charTojstring(info.env, appkey);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, appidstr, appkeystr);
        return true;
    } else {
        ATUtil::printLog("initSDK error");
        return false;
    }
}

void ATCocosSdk::showGdprAuth() {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showGDPR", "()V");
    if (ret) {
        ATUtil::printLog("showGDPR");
        info.env->CallStaticVoidMethod(info.classID, info.methodID);

    } else {
        ATUtil::printLog("showGDPR error");
    }
}

void ATCocosSdk::showGdprAuthWithListener(ATCocosGDPRListener * listener) {
    ATListenerManager::getInstance()->setGdprListener(listener);
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showGdprWidthListener", "()V");
    if (ret) {
        ATUtil::printLog("showGdprWidthListener");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, listener);

    } else {
        ATUtil::printLog("showGdprWidthListener error");
    }
}

void ATCocosSdk::setGDPRLevel(const int32_t level) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setGDPRLevel",
                                              "(I)V");
    if (ret) {
        ATUtil::printLog("setGDPRLevel");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, (jint) level);

    } else {
        ATUtil::printLog("setGDPRLevel error");
    }
}

int ATCocosSdk::getGDPRLevel() {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "getGDPRLevel",
                                              "()I");
    if (ret) {
        ATUtil::printLog("getGDPRLevel");
        jint result = info.env->CallStaticIntMethod(info.classID, info.methodID);
        return result;
    } else {
        ATUtil::printLog("getGDPRLevel error");
        return 2;
    }
}

bool ATCocosSdk::isEUTraffic() {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isEUTraffic", "()Z");
    if (ret) {
        ATUtil::printLog("isEUTraffic");
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isEUTraffic error");
        return false;
    }
}

void ATCocosSdk::getUserLocation(ATCocosUserLocationListener * listener) {
    ATListenerManager::getInstance()->setUserLocationListener(listener);
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "getUserLocation", "()V");
    if (ret) {
        ATUtil::printLog("getUserLocation");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, listener);

    } else {
        ATUtil::printLog("getUserLocation error");
    }
}

void ATCocosSdk::integrationChecking() {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "integrationChecking", "()V");
    if (ret) {
        ATUtil::printLog("integrationChecking");
        info.env->CallStaticVoidMethod(info.classID, info.methodID);
    } else {
        ATUtil::printLog("integrationChecking error");
    }
}


void ATCocosSdk::setDebugLog(bool value) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setDebugLog", "(Z)V");
    if (ret) {
        ATUtil::printLog("setDebugLog");
        jboolean isDebugBool = JNI_FALSE;
        if (value) {
            isDebugBool = JNI_TRUE;
        }
        info.env->CallStaticVoidMethod(info.classID, info.methodID, isDebugBool);
    } else {
        ATUtil::printLog("setDebugLog error");
    }
}

void ATCocosSdk::setChannel(const char *channel) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setChannel",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("setChannel");
        jstring channelString = ATUtil::charTojstring(info.env, channel);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, channelString);
    } else {
        ATUtil::printLog("setChannel error");
    }
}

void ATCocosSdk::setSubChannel(const char *subChannel) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setSubChannel",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("setSubChannel");
        jstring channelString = ATUtil::charTojstring(info.env, subChannel);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, channelString);
    } else {
        ATUtil::printLog("setSubChannel error");
    }
}

void ATCocosSdk::setCustomData(cocos2d::ValueMap customData) {

    if(customData.bucket_count() == 0) {
        ATUtil::printLog("setCustomData size = 0");
        return;
    }

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : customData) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "initCustomMap",
                                              "(Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("initCustomMap");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, HashMap);
    } else {
        ATUtil::printLog("initCustomMap error");
    }
}

void ATCocosSdk::setPlacementCustomData(const char *placementId, cocos2d::ValueMap customData) {

    if(customData.bucket_count() == 0) {
        ATUtil::printLog("setPlacementCustomData or size = 0");
        return;
    }

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : customData) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "initPlacementCustomMap",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("setPlacementCustomMap");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);
    } else {
        ATUtil::printLog("setPlacementCustomMap error");
    }
}

void ATCocosSdk::deniedUploadDeviceInfo(cocos2d::ValueVector deniedInfo) {

    if(deniedInfo.empty()) {
        ATUtil::printLog("deniedUploadDeviceInfo  size = 0");
        return;
    }

    //获取java的StringBuilder类
    jclass class_stringbuilder = JniHelper::getEnv()->FindClass("java/lang/StringBuilder");
    jmethodID stringbuilder_init = JniHelper::getEnv()->GetMethodID(class_stringbuilder, "<init>", "()V");
    jobject StringBuilder = JniHelper::getEnv()->NewObject(class_stringbuilder, stringbuilder_init, "");
    jmethodID StringBuilder_append = JniHelper::getEnv()->GetMethodID(class_stringbuilder, "append",
                                                                      "(Ljava/lang/String;)Ljava/lang/StringBuilder;");

    jmethodID StringBuilder_toString = JniHelper::getEnv()->GetMethodID(class_stringbuilder, "toString",
                                                                      "()Ljava/lang/String;");

    int size = deniedInfo.size();
    std::string deniedinfo;
    for(int i = 0; i < size; i++) {

        deniedinfo = deniedInfo.at(i).asString();
        if (i != 0) {
            JniHelper::getEnv()->CallObjectMethod(StringBuilder, StringBuilder_append,
                                                  JniHelper::getEnv()->NewStringUTF(","));
        }

        JniHelper::getEnv()->CallObjectMethod(StringBuilder, StringBuilder_append,
                                              JniHelper::getEnv()->NewStringUTF(deniedinfo.c_str()));
    }

//    jstring infoString = JniHelper::getEnv()->CallObjectMethod(StringBuilder, StringBuilder_toString);

    std::string s = "2";
    s = s + "3";

    ATUtil::printLog("deniedUploadDeviceInfo -----------------");
    ATUtil::printLog(s.c_str());


    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "deniedUploadDeviceInfo",
                                              "(Ljava/lang/String;)V");

    if (ret) {
        ATUtil::printLog("deniedUploadDeviceInfo");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, JniHelper::getEnv()->CallObjectMethod(StringBuilder, StringBuilder_toString));

    } else {
        ATUtil::printLog("deniedUploadDeviceInfo error");
    }
}


/**------------------------------------------- Banner -------------------------------------------------------------**/
void ATCocosSdk::loadBannerAd(const char *placementId, cocos2d::ValueMap parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadBannerAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");

    if (ret) {
        ATUtil::printLog("loadBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring str = 0;
        if(parameters.bucket_count() > 0) {
            str = ATUtil::charTojstring(info.env, cocos2d::StringUtils::getStringFromValueMap(parameters).c_str());
        }
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, str);

    } else {
        ATUtil::printLog("loadBannerAd error");
    }
}

bool ATCocosSdk::isBannerAdReady(const char *placementId) {

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isBannerAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isBannerReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isBannerReady error");
        return false;
    }
}


void ATCocosSdk::showBannerAd(const char *placementId, cocos2d::ValueMap parameters) {
        JniMethodInfo info;

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : parameters) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showBannerAd",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("showBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        ATUtil::printLog("showBannerAd error");
    }

}

void ATCocosSdk::showBannerAdInPostion(const char * placementId, std::string postion) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showBannerAdInPosition",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showBannerAdInPostion");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring positionstr = ATUtil::charTojstring(info.env, postion.c_str());
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, positionstr);

    } else {
        ATUtil::printLog("showBannerAdInPostion error");
    }
}



void ATCocosSdk::removeBannerAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("removeBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("removeBannerAd error");
    }
}

void ATCocosSdk::setBannerAdListener(ATCocosBannerAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addBannerListener(placementId, listener);
}

/**------------------------------------------- Interstitial -------------------------------------------------------------**/


void ATCocosSdk::loadInterstitialAd(const char *placementId, cocos2d::ValueMap parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadInterstitialAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("loadInterstitialAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring str = 0;
        if(parameters.bucket_count() > 0) {
            str = ATUtil::charTojstring(info.env, cocos2d::StringUtils::getStringFromValueMap(parameters).c_str());
        }
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, str);

    } else {
        ATUtil::printLog("loadInterstitialAd error");
    }
}


bool ATCocosSdk::isInterstitialAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isInterstitialAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isInterstitialAdReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isInterstitialAdReady error");
        return false;
    }
}

char * ATCocosSdk::checkInterstitialAdStatus(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "checkInterstitialAdStatus",
                                              "(Ljava/lang/String;)Ljava/lang/String;");
    if (ret) {
        ATUtil::printLog("checkInterstitialAdStatus");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring result =  (jstring) info.env->CallStaticObjectMethod(info.classID, info.methodID, unitidstr);
        return ATUtil::jstringTostring(info.env, result);
    } else {
        ATUtil::printLog("checkInterstitialAdStatus error");
        return nullptr;
    }
}


void ATCocosSdk::showInterstitialAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showInterstitialAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showInterstitialAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("showInterstitialAd error");
    }
}

void ATCocosSdk::showInterstitialAdInScenario(const char *placementId, const char *scenario) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showInterstitialAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showInterstitialAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring scenariostr = ATUtil::charTojstring(info.env, scenario);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, scenariostr);

    } else {
        ATUtil::printLog("showInterstitialAd error");
    }
}

void ATCocosSdk::setInterstitialAdListener(ATCocosInterstitialAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addInterstitialListener(placementId, listener);
}

/**------------------------------------------- RewardedVideo -------------------------------------------------------------**/


bool ATCocosSdk::isRewardedVideoAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isRewardedVideoAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isRewardedVideoAdReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isRewardedVideoAdReady error");
        return false;
    }
}

char * ATCocosSdk::checkRewardedVideoAdStatus(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "checkRewardedVideoAdStatus",
                                              "(Ljava/lang/String;)Ljava/lang/String;");
    if (ret) {
        ATUtil::printLog("checkRewardedVideoAdStatus");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring result =  (jstring) info.env->CallStaticObjectMethod(info.classID, info.methodID, unitidstr);
        return ATUtil::jstringTostring(info.env, result);
    } else {
        ATUtil::printLog("checkRewardedVideoAdStatus error");
        return nullptr;
    }
}


void ATCocosSdk::loadRewardedVideoAd(const char *placementId, cocos2d::ValueMap parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadRewardedVideoAd",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : parameters) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }


    if (ret) {
        ATUtil::printLog("loadRewardedVideoAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        ATUtil::printLog("loadRewardedVideoAd error");
    }
}

void ATCocosSdk::showRewardedVideoAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showRewardedVideoAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showRewardedVideoAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("showRewardedVideoAd error");
    }
}

void ATCocosSdk::showRewardedVideoAdInScenario(const char *placementId, const char *scenario) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showRewardedVideoAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showRewardedVideoAdInScenario");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring scenariostr = ATUtil::charTojstring(info.env, scenario);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, scenariostr);

    } else {
        ATUtil::printLog("showRewardedVideoAdInScenario error");
    }
}

void ATCocosSdk::setRewardedVideoAdListener(ATCocosRewardedVideoAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addRewardedVideoListener(placementId, listener);
}

/**------------------------------------------- NativeAd -------------------------------------------------------------**/

void ATCocosSdk::loadNativeAd(const char *placementId, cocos2d::ValueMap parameters) {
    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : parameters) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }


    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadNativeAd",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("loadNativeAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        ATUtil::printLog("loadNativeAd error");
    }
}

void ATCocosSdk::showNativeAd(const char *placementId, std::string parameters) {
    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showNativeAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showNativeAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jstring configstr = ATUtil::charTojstring(info.env, parameters.c_str());
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, configstr);

    } else {
        ATUtil::printLog("showNativeAd error");
    }
}

bool ATCocosSdk::isNativeAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isNativeAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isNativeAdReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isNativeAdReady error");
        return false;
    }
}

void ATCocosSdk::removeNativeAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeNativeAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("removeNativeAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("removeNativeAd error");
    }
}

void ATCocosSdk::setNativeAdListener(ATCocosNativeAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addNativeListener(placementId, listener);
}


/**------------------------------------------- Native BannerAd -------------------------------------------------------------**/
void ATCocosSdk::loadNativeBannerAd(const char *placementId,
                                        cocos2d::ValueMap parameters) {
    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : parameters) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadNativeBannerAd",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("loadNativeBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        ATUtil::printLog("loadNativeBannerAd error");
    }

}

void ATCocosSdk::showNativeBannerAd(const char *placementId,
                                        cocos2d::ValueMap parameters, cocos2d::ValueMap  extra) {

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init = JniHelper::getEnv()->GetMethodID(class_hashmap, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject HashMap = JniHelper::getEnv()->NewObject(class_hashmap, hashmap_init, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put = JniHelper::getEnv()->GetMethodID(class_hashmap, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : parameters) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    /*C语言版本，下同*/
    //获取java的HashMap类
    jclass class_hashmap_extra = JniHelper::getEnv()->FindClass("java/util/HashMap");
    //获取类似于java 的new HashMap();
    jmethodID hashmap_init_extra = JniHelper::getEnv()->GetMethodID(class_hashmap_extra, "<init>", "()V");
    //初始化。类似于hashMap=new HashMap();
    jobject extraHashMap = JniHelper::getEnv()->NewObject(class_hashmap_extra, hashmap_init_extra, "");
    //获取hashMap.put()的ID
    jmethodID HashMap_put_extra = JniHelper::getEnv()->GetMethodID(class_hashmap_extra, "put",
                                                             "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for(auto iter : extra) {
        auto key = iter.first;
        auto value = iter.second;
        JniHelper::getEnv()->CallObjectMethod(extraHashMap, HashMap_put_extra,
                                              JniHelper::getEnv()->NewStringUTF(key.c_str()),
                                              JniHelper::getEnv()->NewStringUTF(value.asString().c_str()));
    }

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showNativeBannerAd",
                                              "(Ljava/lang/String;Ljava/util/Map;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("showNativeBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap, extraHashMap);

    } else {
        ATUtil::printLog("showNativeBannerAd error");
    }
}

bool ATCocosSdk::isNativeBannerAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isNativeBannerAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isNativeBannerAdReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isNativeBannerAdReady error");
        return false;
    }
}

void ATCocosSdk::removeNativeBannerAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeNativeBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("removeNativeBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("removeNativeBannerAd error");
    }
}

void ATCocosSdk::setNativeBannerAdListener(ATCocosNativeBannerAdListener *listener,
                                               const char *placementId) {
    ATListenerManager::getInstance()->addNativeBannerAdListener(placementId, listener);
}


