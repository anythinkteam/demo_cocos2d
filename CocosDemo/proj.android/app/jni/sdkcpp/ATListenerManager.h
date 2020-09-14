//
// Created by 张仕仁 on 2019-07-29.
//

#ifndef PROJ_ANDROID_ATLISTENERMANAGER_H
#define PROJ_ANDROID_ATLISTENERMANAGER_H

#include "cocos2d.h"
#include "bridge/ATCocosInterstitialAdListener.h"
#include "bridge/ATCocosBannerAdListener.h"
#include "bridge/ATCocosNativeAdListener.h"
#include "bridge/ATCocosRewardedVideoAdListener.h"
#include "bridge/ATCocosNativeBannerAdListener.h"
#include "bridge/ATCocosGDPRListener.h"
#include "bridge/ATCocosUserLocationListener.h"

using namespace std;

class ATListenerManager {
public:
    static ATListenerManager *getInstance() {
        if (sIntance == NULL) {
            sIntance = new ATListenerManager();
        }
        return sIntance;
    }

    /**
     * 获取 Native的listener
     * @param pat
     */
    void addNativeListener(const char *placementId, ATCocosNativeAdListener *listener);

    /**
     * 获取 Interstitial 的listener
     * @param pat
     */
    void
    addInterstitialListener(const char *placementId, ATCocosInterstitialAdListener *listener);

    /***
     * 获取 Banner 的listener
     * @param pat
     */
    void addBannerListener(const char *placementId, ATCocosBannerAdListener *listener);

    /***
     * 获取 RewardedVideo 的listener
     * @param env
     */
    void
    addRewardedVideoListener(const char *placementId, ATCocosRewardedVideoAdListener *listener);

    /***
     * 获取 Native Banner 的listener
     * @param pat
     */
    void
    addNativeBannerAdListener(const char *placementId, ATCocosNativeBannerAdListener *listener);

    /***
    * 获取 GDPR 的listener
    * @param pat
    */
    void setGdprListener(ATCocosGDPRListener *listener);

    /***
   * 获取 是否欧盟地区 的listener
   * @param pat
   */
    void setUserLocationListener(ATCocosUserLocationListener *listener);

    /**--------------------------------------get-------------------------------------------**/
    /**
     * 获取 Native的listener
     * @param pat
     */
    ATCocosNativeAdListener *getNativeListener(const char *placementId);

    /**
     * 获取 Interstitial 的listener
     * @param pat
     */
    ATCocosInterstitialAdListener *getInterstitialListener(const char *placementId);

    /***
     * 获取 Banner 的listener
     * @param pat
     */
    ATCocosBannerAdListener *getBannerListener(const char *placementId);

    /***
     * 获取 RewardedVideo 的listener
     * @param env
     */
    ATCocosRewardedVideoAdListener *getRewardedVideoListener(const char *placementId);

    /***
     * 获取 NativeBanner 的listener
     * @param env
     */
    ATCocosNativeBannerAdListener *getNativeBannerAdListener(const char *placementId);

    /***
    * 获取 GDPR 的listener
    * @param pat
    */
    ATCocosGDPRListener *getGdprListener();

    /***
    * 获取 是否欧盟地区 的listener
    * @param pat
    */
    ATCocosUserLocationListener *getUserLocationListener();


private:
    static ATListenerManager *sIntance;

    ATListenerManager();

    ~ATListenerManager();

    map<string, ATCocosInterstitialAdListener *> *interstitialDic;
    map<string, ATCocosBannerAdListener *> *bannerDic;
    map<string, ATCocosNativeAdListener *> *nativeDic;
    map<string, ATCocosRewardedVideoAdListener *> *rewardedVideoDic;
    map<string, ATCocosNativeBannerAdListener *> *nativeBannerDic;

    ATCocosGDPRListener *gdprListener;
    ATCocosUserLocationListener *userLocationListener;
};


#endif //PROJ_ANDROID_UPARPULISTENERMANAGER_H
