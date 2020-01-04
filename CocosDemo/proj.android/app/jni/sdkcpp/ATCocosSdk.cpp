//
// Created by 张仕仁 on 2019-07-25.
//

#include "bridge/ATCocosSdk.h"
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
const char* ATCocosSdk::KEY_BANNER_SIZE_TYPE = "key_banner_size_type";
const char* ATCocosSdk::KEY_IS_SHOW_CTA = "key_is_show_cta";


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

void ATCocosSdk::setCustomData(cocos2d::CCDictionary *customData) {
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

    DictElement *pElement;

    CCDICT_FOREACH(customData, pElement) {
            const char *key = pElement->getStrKey();
            const char *value = ((CCString *) pElement->getObject())->getCString();
            JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                  JniHelper::getEnv()->NewStringUTF(key),
                                                  JniHelper::getEnv()->NewStringUTF(value));
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

/**------------------------------------------- Banner -------------------------------------------------------------**/
void ATCocosSdk::loadBannerAd(const char *placementId, cocos2d::CCDictionary *parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("loadBannerAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

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


void ATCocosSdk::showBannerAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
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

    DictElement *pElement;

    CCDICT_FOREACH(parameters, pElement) {
            const char *key = pElement->getStrKey();
            const char *value = ((CCString *) pElement->getObject())->getCString();
            JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                  JniHelper::getEnv()->NewStringUTF(key),
                                                  JniHelper::getEnv()->NewStringUTF(value));
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


void ATCocosSdk::loadInterstitialAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadInterstitialAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("loadInterstitialAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

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

void ATCocosSdk::setInterstitialAdListener(ATCocosInterstitialAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addInterstitialListener(placementId, listener);
}

/**------------------------------------------- RewardedVideo -------------------------------------------------------------**/


bool ATCocosSdk::isRewardedVideoAdReady(const char *unitid) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isRewardedVideoAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        ATUtil::printLog("isRewardedVideoAdReady");
        jstring unitidstr = ATUtil::charTojstring(info.env, unitid);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        ATUtil::printLog("isRewardedVideoAdReady error");
        return false;
    }
}


void ATCocosSdk::loadRewardedVideoAd(const char *placementId, const char *userId,
                                         cocos2d::CCDictionary *parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadRewardedVideoAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("loadRewardedVideoAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        if (userId == NULL) {
            userId = "";
        }
        jstring userIdStr = ATUtil::charTojstring(info.env, userId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, userIdStr);

    } else {
        ATUtil::printLog("loadRewardedVideoAd error");
    }
}

void ATCocosSdk::showRewardedVideoAd(const char *unitid) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showRewardedVideoAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        ATUtil::printLog("showRewardedVideoAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, unitid);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        ATUtil::printLog("showRewardedVideoAd error");
    }
}

void ATCocosSdk::setRewardedVideoAdListener(ATCocosRewardedVideoAdListener *listener, const char * placementId) {
    ATListenerManager::getInstance()->addRewardedVideoListener(placementId, listener);
}

/**------------------------------------------- NativeAd -------------------------------------------------------------**/

void ATCocosSdk::loadNativeAd(const char *placementId, cocos2d::CCDictionary *parameters) {
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

    DictElement *pElement;

    if (parameters != NULL) {
        CCDICT_FOREACH(parameters, pElement) {
                const char *key = pElement->getStrKey();
                const char *value = ((CCString *) pElement->getObject())->getCString();
                JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                      JniHelper::getEnv()->NewStringUTF(key),
                                                      JniHelper::getEnv()->NewStringUTF(value));
            }
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

void ATCocosSdk::showNativeAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
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

    DictElement *pElement;
    if (parameters != NULL) {
        CCDICT_FOREACH(parameters, pElement) {
                const char *key = pElement->getStrKey();
                const char *value = ((CCString *) pElement->getObject())->getCString();
                JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                      JniHelper::getEnv()->NewStringUTF(key),
                                                      JniHelper::getEnv()->NewStringUTF(value));
            }
    }

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showNativeAd",
                                              "(Ljava/lang/String;Ljava/util/Map;)V");
    if (ret) {
        ATUtil::printLog("showNativeAd");
        jstring unitidstr = ATUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

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
                                        cocos2d::CCDictionary *parameters) {
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

    DictElement *pElement;

    if (parameters != NULL) {
        CCDICT_FOREACH(parameters, pElement) {
                const char *key = pElement->getStrKey();
                const char *value = ((CCString *) pElement->getObject())->getCString();
                JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                      JniHelper::getEnv()->NewStringUTF(key),
                                                      JniHelper::getEnv()->NewStringUTF(value));
            }
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
                                        cocos2d::CCDictionary *parameters, cocos2d::CCDictionary  * extra) {

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

    DictElement *pElement;

    if (parameters != NULL) {
        CCDICT_FOREACH(parameters, pElement) {
                const char *key = pElement->getStrKey();
                const char *value = ((CCString *) pElement->getObject())->getCString();
                JniHelper::getEnv()->CallObjectMethod(HashMap, HashMap_put,
                                                      JniHelper::getEnv()->NewStringUTF(key),
                                                      JniHelper::getEnv()->NewStringUTF(value));
            }
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

    DictElement *extraElement;

    if (extra != NULL) {
        CCDICT_FOREACH(extra, extraElement) {
                const char *key = extraElement->getStrKey();
                const char *value = ((CCString *) extraElement->getObject())->getCString();
                JniHelper::getEnv()->CallObjectMethod(extraHashMap, HashMap_put_extra,
                                                      JniHelper::getEnv()->NewStringUTF(key),
                                                      JniHelper::getEnv()->NewStringUTF(value));
            }
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