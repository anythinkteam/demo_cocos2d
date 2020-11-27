
#ifndef PROJ_ANDROID_STUDIO_DemoMAINSCENE_H
#define PROJ_ANDROID_STUDIO_DemoMAINSCENE_H


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
#include <ui/UIWidget.h>
#include "cocos2d.h"
#include "ATCocosRewardedVideoAdListener.h"
#include "ATCocosInterstitialAdListener.h"
#include "ATCocosBannerAdListener.h"
#include "ATCocosNativeAdListener.h"
#include "ATCocosNativeBannerAdListener.h"
#include "ATCocosGDPRListener.h"
#include "ATCocosUserLocationListener.h"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
//#include <ui/UIWidget.h>
//#include "cocos2d.h"
//#include "bridge/ATCocosRewardedVideoAdListener.h"
//#include "bridge/ATCocosInterstitialAdListener.h"
//#include "bridge/ATCocosBannerAdListener.h"
//#include "bridge/ATCocosNativeAdListener.h"
//#include "bridge/ATCocosNativeBannerAdListener.h"
//#include "bridge/ATCocosGDPRListener.h"
//#include "bridge/ATCocosUserLocationListener.h"

#endif



class DemoMainScene : public cocos2d::Scene, public ATCocosRewardedVideoAdListener, public ATCocosInterstitialAdListener, public ATCocosBannerAdListener, public ATCocosNativeAdListener , public ATCocosNativeBannerAdListener, public ATCocosGDPRListener, public ATCocosUserLocationListener{
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(DemoMainScene);


    //**********************************
    //***********UI start***************
    //**********************************


    /**
     ** 添加按钮和注册按钮事件
     */
    void addGDPRButton();

    void initGPPRButtonTouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);

    void initLoadNativeAdBtn();
    void initShowNativeAdBtn();
    void initCleanNativeAdBtn();

    void initLoadNativeBannerBtn();
    void initShowNativeBannerBtn();
    void initCleanNativeBannerBtn();

    void initLoadBannerBtn();
    void initShowBannerBtn();
    void initCleanBannerBtn();
//
    void initLoadInterstitialBtn();
    void initShowInterstitialBtn();
//
    void initLoadRewardedVideoBtn();
    void initShowRewardedVideoBtn();

    void initNetworkBtn();

    void initClickEvent(cocos2d::Ref *pSender,
                        cocos2d::ui::Widget::TouchEventType type);

    //rewarded video listener
    virtual void onRewardedVideoLoadSuccess(const char * placementId);

    virtual void onRewardedVideoLoadFailed(const char * placementId, const char * errorString);

    //rewardedVideo extra listener
    virtual void onRewardedVideoDidRewardSuccessWithExtra(const char * placementId, const char * extra);

    virtual void onRewardedVideoPlayStartWithExtra(const char * placementId, const char * extra);

    virtual void onRewardedVideoPlayEndWithExtra(const char * placementId, const char * extra);

    virtual void onRewardedVideoShowFailWithExtra(const char * placementId, const char * errorString, const char * extra);

    virtual void onRewardedVideoCloseWithExtra(const char * placementId, bool isRewarded, const char * extra);

    virtual void onRewardedVideoClickedWithExtra(const char * placementId, const char * extra);

    //interstitial listener
    virtual void onInterstitalLoadSuccess(const char * placementId);

    virtual void onInterstitalLoadFailed(const char * placementId, const char * errorString);

    //interstitial extra listener
    virtual void onInterstitalShowWithExtra(const char * placementId,const char * extra);

    virtual void onInterstitalCloseWithExtra(const char * placementId,const char * extra);

    virtual void onInterstitalClickedWithExtra(const char * placementId,const char * extra);

    virtual void onInterstitalPlayStartWithExtra(const char * placementId,const char * extra);

    virtual void onInterstitalPlayEndWithExtra(const char * placementId,const char * extra);

    //banner listener
    virtual void onBannerAdLoadSuccess(const char * placementId);

    virtual void onBannerAdLoadFailed(const char * placementId, const char * errorString);

    //banner extra listener
    virtual void onBannerShowWithExtra(const char * placementId, const char * extra);

    virtual void onBannerClickedWithExtra(const char * placementId, const char * extra);

    virtual void onBannerCloseWithExtra(const char * placementId, const char * extra);

    virtual void onBannerAutoRefreshWithExtra(const char * placementId, const char * extra);

    virtual void onBannerAutoRefreshFailWithExtra(const char * placementId, const char * errorString, const char * extra);

    //native listener
    virtual void onNativeAdLoadSuccess(const char * placementId);

    virtual void onNativeAdLoadFailed(const char * placementId, const char * errorString);

    //native extra listener
    virtual void onNativeAdVideoStartWithExtra(const char * placementId, const char * extra);

    virtual void onNativeAdVideoEndWithExtra(const char * placementId, const char * extra);

    virtual void onNativeAdShowWithExtra(const char * placementId, const char * extra);

    virtual void onNativeAdClickWithExtra(const char * placementId, const char *extra);

    virtual void onNativeAdCloseButtonTappedWithExtra(const char * placementId, const char *extra);

    //native banner listener
    virtual void onNativeBannerAdLoadSuccess(const char * placementId);

    virtual void onNativeBannerAdLoadFailed(const char * placementId, const char * errorString);

    //native banner extra listener
    virtual void onNativeBannerShowWithExtra(const char * placementId, const char * extra);

    virtual void onNativeBannerClickedWithExtra(const char * placementId, const char * extra);

    virtual void onNativeBannerAutoRefreshFailWithExtra(const char * placementId, const char * errorString, const char * extra);

    virtual void onNativeBannerCloseWithExtra(const char * placementId,const char * extra);

    virtual void onNativeBannerAutoRefreshWithExtra(const char * placementId,const char * extra);

    //GDPR listener
    virtual void onGDPRDataConsentSet(int dataConsent);
    virtual void onPageLoadFail();

    virtual void onUserLocation(int location);


private:
    const char* appId;
    const char* appKey;
    const char* rvPlacementId;
    const char* interPlacementId;
    const char* bannerPlacementId;
    const char* nativePlacementId;
    const char* nativebannerPlacementId;
};


#endif //PROJ_ANDROID_STUDIO_DemoMAINSCENE_H
