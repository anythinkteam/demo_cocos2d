//
// Created by 张仕仁 on 2019-07-25.
//

#include "sdk/UpArpuCocosSdk.h"
#include "UpArpuUtil.h"
#include <jni.h>
#include <json/writer.h>
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "UpArpuListenerManager.h"

USING_NS_CC;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define UPARPUSDKHELPER   "com/uparpu/cocos2dx/bridge/UpArpuSDKJniHelper"
#endif

const char* UpArpuCocosSdk::KEY_WIDTH = "w";
const char* UpArpuCocosSdk::KEY_HEIGHT = "h";
const char* UpArpuCocosSdk::KEY_POS_X = "x";
const char* UpArpuCocosSdk::KEY_POS_Y = "y";
const char* UpArpuCocosSdk::KEY_MAIN_BG_COLOR = "key_main_bg_color";
const char* UpArpuCocosSdk::KEY_REFRESH_INTERVEL = "key_refresh_intervel";
const char* UpArpuCocosSdk::KEY_BUTTON_CLOSE_STATUS = "key_button_close_status";
const char* UpArpuCocosSdk::KEY_BUTTON_CTA_BG = "key_button_cta_bg";
const char* UpArpuCocosSdk::KEY_BUTTON_CTA_TITLE_FONT = "key_button_cta_title_font";
const char* UpArpuCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR = "key_button_cta_title_color";
const char* UpArpuCocosSdk::KEY_TITLE_FONT = "key_title_font";
const char* UpArpuCocosSdk::KEY_TITLE_COLOR = "key_title_color";
const char* UpArpuCocosSdk::KEY_TEXT_FONT = "key_text_font";
const char* UpArpuCocosSdk::KEY_TEXT_COLOR = "key_text_color";
const char* UpArpuCocosSdk::KEY_ADVERTISER_TEXT_FONT = "key_advertiser_text_font";
const char* UpArpuCocosSdk::KEY_ADVERTISER_TEXT_COLOR = "key_advertiser_text_color";
const char* UpArpuCocosSdk::KEY_BANNER_SIZE_TYPE = "key_banner_size_type";
const char* UpArpuCocosSdk::KEY_IS_SHOW_CTA = "key_is_show_cta";


bool UpArpuCocosSdk::initSDK(const char *appid, const char *appkey) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "initSDK",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("initSDK");
        jstring appidstr = UpArpuUtil::charTojstring(info.env, appid);
        jstring appkeystr = UpArpuUtil::charTojstring(info.env, appkey);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, appidstr, appkeystr);
        return true;
    } else {
        UpArpuUtil::printLog("initSDK error");
        return false;
    }
}

void UpArpuCocosSdk::showGdprAuth() {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showGDPR", "()V");
    if (ret) {
        UpArpuUtil::printLog("showGDPR");
        info.env->CallStaticVoidMethod(info.classID, info.methodID);

    } else {
        UpArpuUtil::printLog("showGDPR error");
    }
}

void UpArpuCocosSdk::setGDPRLevel(const int32_t level) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setGDPRLevel",
                                              "(I)V");
    if (ret) {
        UpArpuUtil::printLog("setGDPRLevel");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, (jint) level);

    } else {
        UpArpuUtil::printLog("setGDPRLevel error");
    }
}

bool UpArpuCocosSdk::isEUTraffic() {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isEUTraffic", "()Z");
    if (ret) {
        UpArpuUtil::printLog("isEUTraffic");
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isEUTraffic error");
        return false;
    }
}

void UpArpuCocosSdk::setDebugLog(bool value) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setDebugLog", "(Z)V");
    if (ret) {
        UpArpuUtil::printLog("setDebugLog");
        jboolean isDebugBool = JNI_FALSE;
        if (value) {
            isDebugBool = JNI_TRUE;
        }
        info.env->CallStaticVoidMethod(info.classID, info.methodID, isDebugBool);
    } else {
        UpArpuUtil::printLog("setDebugLog error");
    }
}

void UpArpuCocosSdk::setChannel(const char *channel) {
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "setChannel",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("setChannel");
        jstring channelString = UpArpuUtil::charTojstring(info.env, channel);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, channelString);
    } else {
        UpArpuUtil::printLog("setChannel error");
    }
}

void UpArpuCocosSdk::setCustomData(cocos2d::CCDictionary *customData) {
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
        UpArpuUtil::printLog("initCustomMap");
        info.env->CallStaticVoidMethod(info.classID, info.methodID, HashMap);
    } else {
        UpArpuUtil::printLog("initCustomMap error");
    }
}

/**------------------------------------------- Banner -------------------------------------------------------------**/
void UpArpuCocosSdk::loadBannerAd(const char *placementId, cocos2d::CCDictionary *parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("loadBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("loadBannerAd error");
    }
}

bool UpArpuCocosSdk::isBannerAdReady(const char *placementId) {

    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isBannerAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        UpArpuUtil::printLog("isBannerReady");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isBannerReady error");
        return false;
    }
}


void UpArpuCocosSdk::showBannerAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
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
        UpArpuUtil::printLog("showBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        UpArpuUtil::printLog("showBannerAd error");
    }

}

void UpArpuCocosSdk::removeBannerAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("removeBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("removeBannerAd error");
    }
}

void UpArpuCocosSdk::setBannerAdListener(UpArpuCocosBannerAdListener *listener, const char * placementId) {
    UpArpuListenerManager::getInstance()->addBannerListener(placementId, listener);
}

/**------------------------------------------- Interstitial -------------------------------------------------------------**/


void UpArpuCocosSdk::loadInterstitialAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadInterstitialAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("loadInterstitialAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("loadInterstitialAd error");
    }
}


bool UpArpuCocosSdk::isInterstitialAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isInterstitialAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        UpArpuUtil::printLog("isInterstitialAdReady");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isInterstitialAdReady error");
        return false;
    }
}


void UpArpuCocosSdk::showInterstitialAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showInterstitialAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("showInterstitialAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("showInterstitialAd error");
    }
}

void UpArpuCocosSdk::setInterstitialAdListener(UpArpuCocosInterstitialAdListener *listener, const char * placementId) {
    UpArpuListenerManager::getInstance()->addInterstitialListener(placementId, listener);
}

/**------------------------------------------- RewardedVideo -------------------------------------------------------------**/


bool UpArpuCocosSdk::isRewardedVideoAdReady(const char *unitid) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isRewardedVideoAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        UpArpuUtil::printLog("isRewardedVideoAdReady");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, unitid);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isRewardedVideoAdReady error");
        return false;
    }
}


void UpArpuCocosSdk::loadRewardedVideoAd(const char *placementId, const char *userId,
                                         cocos2d::CCDictionary *parameters) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "loadRewardedVideoAd",
                                              "(Ljava/lang/String;Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("loadRewardedVideoAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        if (userId == NULL) {
            userId = "";
        }
        jstring userIdStr = UpArpuUtil::charTojstring(info.env, userId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, userIdStr);

    } else {
        UpArpuUtil::printLog("loadRewardedVideoAd error");
    }
}

void UpArpuCocosSdk::showRewardedVideoAd(const char *unitid) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "showRewardedVideoAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("showRewardedVideoAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, unitid);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("showRewardedVideoAd error");
    }
}

void UpArpuCocosSdk::setRewardedVideoAdListener(UpArpuCocosRewardedVideoAdListener *listener, const char * placementId) {
    UpArpuListenerManager::getInstance()->addRewardedVideoListener(placementId, listener);
}

/**------------------------------------------- NativeAd -------------------------------------------------------------**/

void UpArpuCocosSdk::loadNativeAd(const char *placementId, cocos2d::CCDictionary *parameters) {
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
        UpArpuUtil::printLog("loadNativeAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        UpArpuUtil::printLog("loadNativeAd error");
    }
}

void UpArpuCocosSdk::showNativeAd(const char *placementId, cocos2d::CCDictionary  * parameters) {
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
        UpArpuUtil::printLog("showNativeAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        UpArpuUtil::printLog("showNativeAd error");
    }
}

bool UpArpuCocosSdk::isNativeAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isNativeAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        UpArpuUtil::printLog("isNativeAdReady");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isNativeAdReady error");
        return false;
    }
}

void UpArpuCocosSdk::removeNativeAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeNativeAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("removeNativeAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("removeNativeAd error");
    }
}

void UpArpuCocosSdk::setNativeAdListener(UpArpuCocosNativeAdListener *listener, const char * placementId) {
    UpArpuListenerManager::getInstance()->addNativeListener(placementId, listener);
}


/**------------------------------------------- Native BannerAd -------------------------------------------------------------**/
void UpArpuCocosSdk::loadNativeBannerAd(const char *placementId,
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
        UpArpuUtil::printLog("loadNativeBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap);

    } else {
        UpArpuUtil::printLog("loadNativeBannerAd error");
    }

}

void UpArpuCocosSdk::showNativeBannerAd(const char *placementId,
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
        UpArpuUtil::printLog("showNativeBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr, HashMap, extraHashMap);

    } else {
        UpArpuUtil::printLog("showNativeBannerAd error");
    }
}

bool UpArpuCocosSdk::isNativeBannerAdReady(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "isNativeBannerAdReady",
                                              "(Ljava/lang/String;)Z");
    if (ret) {
        UpArpuUtil::printLog("isNativeBannerAdReady");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        jboolean result = info.env->CallStaticBooleanMethod(info.classID, info.methodID, unitidstr);
        return result == JNI_TRUE;
    } else {
        UpArpuUtil::printLog("isNativeBannerAdReady error");
        return false;
    }
}

void UpArpuCocosSdk::removeNativeBannerAd(const char *placementId) {
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info, UPARPUSDKHELPER, "removeNativeBannerAd",
                                              "(Ljava/lang/String;)V");
    if (ret) {
        UpArpuUtil::printLog("removeNativeBannerAd");
        jstring unitidstr = UpArpuUtil::charTojstring(info.env, placementId);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, unitidstr);

    } else {
        UpArpuUtil::printLog("removeNativeBannerAd error");
    }
}

void UpArpuCocosSdk::setNativeBannerAdListener(UpArpuCocosNativeBannerAdListener *listener,
                                               const char *placementId) {
    UpArpuListenerManager::getInstance()->addNativeBannerAdListener(placementId, listener);
}