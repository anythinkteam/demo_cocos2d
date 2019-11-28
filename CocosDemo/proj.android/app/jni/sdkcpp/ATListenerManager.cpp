//
// Created by 张仕仁 on 2019-07-29.
//

#include "ATListenerManager.h"
#include "cocos2d.h"

ATListenerManager *ATListenerManager::sIntance;

ATListenerManager::ATListenerManager() {
    interstitialDic = new map<string, ATCocosInterstitialAdListener *>();
    bannerDic = new map<string, ATCocosBannerAdListener *>();
    nativeDic = new map<string, ATCocosNativeAdListener *>();
    rewardedVideoDic = new map<string, ATCocosRewardedVideoAdListener *>();
    nativeBannerDic = new map<string, ATCocosNativeBannerAdListener *>();
}

void ATListenerManager::addNativeBannerAdListener(const char *placementId,
                                                      ATCocosNativeBannerAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        nativeBannerDic->insert(std::make_pair(placementIdString, listener));
    }
}



ATCocosNativeBannerAdListener *ATListenerManager::getNativeBannerAdListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, ATCocosNativeBannerAdListener *>::iterator itr = nativeBannerDic->find(
            placementIdString);
    return itr->second;
}


void ATListenerManager::addBannerListener(const char *placementId,
                                              ATCocosBannerAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        bannerDic->insert(std::make_pair(placementIdString, listener));
    }

}


ATCocosBannerAdListener *ATListenerManager::getBannerListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, ATCocosBannerAdListener *>::iterator itr = bannerDic->find(
            placementIdString);
    return itr->second;
}


void ATListenerManager::addNativeListener(const char *placementId,
                                              ATCocosNativeAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        nativeDic->insert(std::make_pair(placementIdString, listener));
    }
}

ATCocosNativeAdListener *ATListenerManager::getNativeListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, ATCocosNativeAdListener *>::iterator itr = nativeDic->find(
            placementIdString);
    return itr->second;
}


void ATListenerManager::addInterstitialListener(const char *placementId,
                                                    ATCocosInterstitialAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        interstitialDic->insert(std::make_pair(placementIdString, listener));
    }
}

ATCocosInterstitialAdListener *
ATListenerManager::getInterstitialListener(const char *placementId) {
    string placementIdString = placementId;
    std::map<string, ATCocosInterstitialAdListener *>::iterator itr = interstitialDic->find(
            placementIdString);
    return itr->second;
}

void ATListenerManager::addRewardedVideoListener(const char *placementId,
                                                     ATCocosRewardedVideoAdListener *listener) {
    string placementIdString = placementId;
    if (listener != NULL) {
        rewardedVideoDic->insert(std::make_pair(placementIdString, listener));
    }
}

ATCocosRewardedVideoAdListener *ATListenerManager::getRewardedVideoListener(
        const char *placementId) {
    string placementIdString = placementId;
    std::map<string, ATCocosRewardedVideoAdListener *>::iterator itr = rewardedVideoDic->find(
            placementIdString);
    return itr->second;
}


