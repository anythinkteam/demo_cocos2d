package com.anythink.cocos2dx.bridge;



/**
 * Copyright (C) 2018 {XX} Science and Technology Co., Ltd.
 * 主要是注册JNI Native的方法 SDK会通过这些方法 回调到COCOS2D的C层  JAVA回调C层
 * @version V{XX_XX}
 * @Author ：Created by zhoushubin on 2018/11/8.
 * @Email: zhoushubin@salmonads.com
 * @since
 */
public class ATListenerEventJniHelper {

    public static native void onBannerLoaded(String placementId);
    public static native void onBannerFailed(String placementId, String adError);
    public static native void onBannerClicked(String placementId, String extra);
    public static native void onBannerShow(String placementId, String extra);
    public static native void onBannerClose(String placementId, String extra);
    public static native void onBannerAutoRefreshed(String placementId, String extra);
    public static native void onBannerAutoRefreshFail(String placementId, String adError, String extra);



    public static native void onInterstitialAdLoaded(String placementId);
    public static native void onInterstitialAdLoadFail(String placementId, String adError);
    public static native void onInterstitialAdClicked(String placementId, String extra);
    public static native void onInterstitialAdShow(String placementId, String extra);
    public static native void onInterstitialAdClose(String placementId, String extra);
    public static native void onInterstitialAdVideoStart(String placementId, String extra);
    public static native void onInterstitialAdVideoEnd(String placementId, String extra);
    public static native void onInterstitialAdVideoError(String placementId, String adError);



    public static native void onRewardedVideoAdLoaded(String placementId); //广告加载成功
    public static native void onRewardedVideoAdFailed(String placementId,String adError);//广告加载失败
    public static native void onRewardedVideoAdPlayStart(String placementId, String extra);//开始播放
    public static native void onRewardedVideoAdPlayEnd(String placementId, String extra);//结束播放
    public static native void onRewardedVideoAdPlayFailed(String placementId,String adError, String extra);//播放失败
    public static native void onRewardedVideoAdClosed(String placementId, boolean isRewarded, String extra);//广告关闭
    public static native void onRewardedVideoAdPlayClicked(String placementId, String extra);//广告点击
    public static native void onRewardedVideoAdRewarded(String placementId, String extra);//广告点击


    public static native void onNativeAdLoaded(String placementId);
    public static native void onNativeAdLoadFail(String placementId,String adError);
    public static native void onNativeAdShow(String placementId, String extra);
    public static native void onNativeAdClick(String placementId, String extra);
    public static native void onNativeAdVideoStart(String placementId, String extra);
    public static native void onNativeAdVideoEnd(String placementId, String extra);
    public static native void onNativeAdCloseButtonTapped(String placementId, String extra);

    public static native void onNativeBannerAdLoaded(String placementId);
    public static native void onNativeBannerAdLoadFail(String placementId, String adError);
    public static native void onNativeBannerAdClick(String placementId, String extra);
    public static native void onNativeBannerAdShow(String placementId, String extra);
    public static native void onNativeBannerAdClose(String placementId, String extra);
    public static native void onNativeBannerAdAutoRefreshed(String placementId, String extra);
    public static native void onNativeBannerAdAutoRefreshFail(String placementId, String adError, String extra);

    public static native void onSDKInitSuccess();
    public static native void onSDKInitFail(String errorMsg);

    public static native void onGdprAuth(int gdprLevel);
    public static native void onPageLoadFail();

    public static native void onUserLocation(int userLocation);

}
