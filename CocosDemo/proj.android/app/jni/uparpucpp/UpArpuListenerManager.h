//
// Created by 张仕仁 on 2019-07-29.
//

#ifndef PROJ_ANDROID_UPARPULISTENERMANAGER_H
#define PROJ_ANDROID_UPARPULISTENERMANAGER_H

#include "cocos2d.h"
#include "sdk/UpArpuCocosInterstitialAdListener.h"
#include "sdk/UpArpuCocosBannerAdListener.h"
#include "sdk/UpArpuCocosNativeAdListener.h"
#include "sdk/UpArpuCocosRewardedVideoAdListener.h"
#include "sdk/UpArpuCocosNativeBannerAdListener.h"

using namespace std;

class UpArpuListenerManager {
public:
    static UpArpuListenerManager *getInstance() {
        if (sIntance == NULL) {
            sIntance = new UpArpuListenerManager();
        }
        return sIntance;
    }

    /**
     * 获取 Native的listener
     * @param pat
     */
    void addNativeListener(const char *placementId, UpArpuCocosNativeAdListener *listener);

    /**
     * 获取 Interstitial 的listener
     * @param pat
     */
    void
    addInterstitialListener(const char *placementId, UpArpuCocosInterstitialAdListener *listener);

    /***
     * 获取 Banner 的listener
     * @param pat
     */
    void addBannerListener(const char *placementId, UpArpuCocosBannerAdListener *listener);

    /***
     * 获取 RewardedVideo 的listener
     * @param env
     */
    void
    addRewardedVideoListener(const char *placementId, UpArpuCocosRewardedVideoAdListener *listener);

    /***
     * 获取 Native Banner 的listener
     * @param pat
     */
    void addNativeBannerAdListener(const char *placementId, UpArpuCocosNativeBannerAdListener *listener);


    /**--------------------------------------get-------------------------------------------**/
    /**
     * 获取 Native的listener
     * @param pat
     */
    UpArpuCocosNativeAdListener *getNativeListener(const char *placementId);

    /**
     * 获取 Interstitial 的listener
     * @param pat
     */
    UpArpuCocosInterstitialAdListener *getInterstitialListener(const char *placementId);

    /***
     * 获取 Banner 的listener
     * @param pat
     */
    UpArpuCocosBannerAdListener *getBannerListener(const char *placementId);

    /***
     * 获取 RewardedVideo 的listener
     * @param env
     */
    UpArpuCocosRewardedVideoAdListener *getRewardedVideoListener(const char *placementId);

    /***
     * 获取 NativeBanner 的listener
     * @param env
     */
    UpArpuCocosNativeBannerAdListener *getNativeBannerAdListener(const char *placementId);

private:
    static UpArpuListenerManager *sIntance;

    UpArpuListenerManager();

    ~UpArpuListenerManager();

    map<string, UpArpuCocosInterstitialAdListener *> *interstitialDic;
    map<string, UpArpuCocosBannerAdListener *> *bannerDic;
    map<string, UpArpuCocosNativeAdListener *> *nativeDic;
    map<string, UpArpuCocosRewardedVideoAdListener *> *rewardedVideoDic;
    map<string, UpArpuCocosNativeBannerAdListener *> *nativeBannerDic;
};


#endif //PROJ_ANDROID_UPARPULISTENERMANAGER_H
