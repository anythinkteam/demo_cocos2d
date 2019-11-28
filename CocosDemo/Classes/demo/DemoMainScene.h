
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
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
#include <ui/UIWidget.h>
#include "cocos2d.h"
#include "sdk/ATCocosRewardedVideoAdListener.h"
#include "sdk/ATCocosInterstitialAdListener.h"
#include "sdk/ATCocosBannerAdListener.h"
#include "sdk/ATCocosNativeAdListener.h"
#include "sdk/ATCocosNativeBannerAdListener.h"
#endif



class DemoMainScene : public cocos2d::Scene, public ATCocosRewardedVideoAdListener, public ATCocosInterstitialAdListener, public ATCocosBannerAdListener, public ATCocosNativeAdListener , public ATCocosNativeBannerAdListener{
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
    
    virtual void onRewardedVideoPlayStart(const char * placementId);
    
    virtual void onRewardedVideoPlayEnd(const char * placementId);
    
    virtual void onRewardedVideoShowFail(const char * placementId, const char * errorString);
    
    virtual void onRewardedVideoClose(const char * placementId, bool isRewarded);
    
    virtual void onRewardedVideoClicked(const char * placementId);
    
    virtual void onRewardedVideoDidRewardSuccess(const char * placementId);
    
    //interstitial listener
    virtual void onInterstitalLoadSuccess(const char * placementId);
    
    virtual void onInterstitalLoadFailed(const char * placementId, const char * errorString);
    
    virtual void onInterstitalShow(const char * placementId);
    
    virtual void onInterstitalClose(const char * placementId);
    
    virtual void onInterstitalClicked(const char * placementId);
    
    //banner listener
    virtual void onBannerAdLoadSuccess(const char * placementId);
    
    virtual void onBannerAdLoadFailed(const char * placementId, const char * errorString);
    
    virtual void onBannerShow(const char * placementId);
    
    virtual void onBannerClicked(const char * placementId);
    
    virtual void onBannerClose(const char * placementId);
    
    virtual void onBannerAutoRefresh(const char * placementId);
    
    virtual void onBannerAutoRefreshFail(const char * placementId, const char * errorString);

    //native listener
    virtual void onNativeAdLoadSuccess(const char * placementId);

    virtual void onNativeAdLoadFailed(const char * placementId, const char * errorString);

    virtual void onNativeAdVideoStart(const char * placementId);

    virtual void onNativeAdVideoEnd(const char * placementId);

    virtual void onNativeAdShow(const char * placementId);

    virtual void onNativeAdClick(const char * placementId);

    //native banner listener
    virtual void onNativeBannerAdLoadSuccess(const char * placementId);

    virtual void onNativeBannerAdLoadFailed(const char * placementId, const char * errorString);

    virtual void onNativeBannerShow(const char * placementId);

    virtual void onNativeBannerClicked(const char * placementId);

    virtual void onNativeBannerAutoRefreshFail(const char * placementId, const char * errorString);

    virtual void onNativeBannerClose(const char * placementId);

    virtual void onNativeBannerAutoRefresh(const char * placementId);
    
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
