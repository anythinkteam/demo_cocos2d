//
// Created by 张仕仁 on 2019-07-29.
//

#include "UpArpuListenerManager.h"
#include "cocos2d.h"

UpArpuListenerManager *UpArpuListenerManager::sIntance;

UpArpuListenerManager::UpArpuListenerManager() {
    interstitialDic = new map<string, UpArpuCocosInterstitialAdListener *>();
    bannerDic = new map<string, UpArpuCocosBannerAdListener *>();
    nativeDic = new map<string, UpArpuCocosNativeAdListener *>();
    rewardedVideoDic = new map<string, UpArpuCocosRewardedVideoAdListener *>();
    nativeBannerDic = new map<string, UpArpuCocosNativeBannerAdListener *>();
}

void UpArpuListenerManager::addNativeBannerAdListener(const char *placementId,
                                                      UpArpuCocosNativeBannerAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        nativeBannerDic->insert(std::make_pair(placementIdString, listener));
    }
}



UpArpuCocosNativeBannerAdListener *UpArpuListenerManager::getNativeBannerAdListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, UpArpuCocosNativeBannerAdListener *>::iterator itr = nativeBannerDic->find(
            placementIdString);
    return itr->second;
}


void UpArpuListenerManager::addBannerListener(const char *placementId,
                                              UpArpuCocosBannerAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        bannerDic->insert(std::make_pair(placementIdString, listener));
    }

}


UpArpuCocosBannerAdListener *UpArpuListenerManager::getBannerListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, UpArpuCocosBannerAdListener *>::iterator itr = bannerDic->find(
            placementIdString);
    return itr->second;
}


void UpArpuListenerManager::addNativeListener(const char *placementId,
                                              UpArpuCocosNativeAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        nativeDic->insert(std::make_pair(placementIdString, listener));
    }
}

UpArpuCocosNativeAdListener *UpArpuListenerManager::getNativeListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, UpArpuCocosNativeAdListener *>::iterator itr = nativeDic->find(
            placementIdString);
    return itr->second;
}


void UpArpuListenerManager::addInterstitialListener(const char *placementId,
                                                    UpArpuCocosInterstitialAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        interstitialDic->insert(std::make_pair(placementIdString, listener));
    }
}

UpArpuCocosInterstitialAdListener *
UpArpuListenerManager::getInterstitialListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, UpArpuCocosInterstitialAdListener *>::iterator itr = interstitialDic->find(
            placementIdString);
    return itr->second;
}

void UpArpuListenerManager::addRewardedVideoListener(const char *placementId,
                                                     UpArpuCocosRewardedVideoAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        rewardedVideoDic->insert(std::make_pair(placementIdString, listener));
    }
}

UpArpuCocosRewardedVideoAdListener *UpArpuListenerManager::getRewardedVideoListener(
        const char *placementId) {
    string placementIdString = placementId;
    std::map<string, UpArpuCocosRewardedVideoAdListener *>::iterator itr = rewardedVideoDic->find(
            placementIdString);
    return itr->second;
}


