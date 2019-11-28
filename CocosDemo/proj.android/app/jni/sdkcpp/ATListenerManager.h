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
    void addNativeBannerAdListener(const char *placementId, ATCocosNativeBannerAdListener *listener);


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

private:
    static ATListenerManager *sIntance;

    ATListenerManager();

    ~ATListenerManager();

    map<string, ATCocosInterstitialAdListener *> *interstitialDic;
    map<string, ATCocosBannerAdListener *> *bannerDic;
    map<string, ATCocosNativeAdListener *> *nativeDic;
    map<string, ATCocosRewardedVideoAdListener *> *rewardedVideoDic;
    map<string, ATCocosNativeBannerAdListener *> *nativeBannerDic;
};


#endif //PROJ_ANDROID_UPARPULISTENERMANAGER_H
