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

    public static native void onBannerLoaded(String unitId);
    public static native void onBannerFailed(String unitId, String adError);
    public static native void onBannerClicked(String unitId);
    public static native void onBannerShow(String unitId);
    public static native void onBannerClose(String unitId);
    public static native void onBannerAutoRefreshed(String unitId);
    public static native void onBannerAutoRefreshFail(String unitId, String adError);



    public static native void onInterstitialAdLoaded(String unitId);
    public static native void onInterstitialAdLoadFail(String unitId, String adError);
    public static native void onInterstitialAdClicked(String unitId);
    public static native void onInterstitialAdShow(String unitId);
    public static native void onInterstitialAdClose(String unitId);
    public static native void onInterstitialAdVideoStart(String unitId);
    public static native void onInterstitialAdVideoEnd(String unitId);
    public static native void onInterstitialAdVideoError(String unitId, String adError);



    public static native void onRewardedVideoAdLoaded(String unitId); //广告加载成功
    public static native void onRewardedVideoAdFailed(String unitId,String adError);//广告加载失败
    public static native void onRewardedVideoAdPlayStart(String unitId);//开始播放
    public static native void onRewardedVideoAdPlayEnd(String unitId);//结束播放
    public static native void onRewardedVideoAdPlayFailed(String unitId,String adError);//播放失败
    public static native void onRewardedVideoAdClosed(String unitId, boolean isRewarded);//广告关闭
    public static native void onRewardedVideoAdPlayClicked(String unitId);//广告点击
    public static native void onRewardedVideoAdRewarded(String unitId);//广告点击


    public static native void onNativeAdLoaded(String unitId);
    public static native void onNativeAdLoadFail(String unitId,String adError);
    public static native void onNativeAdShow(String unitId);
    public static native void onNativeAdClick(String unitId);

    public static native void onNativeBannerAdLoaded(String unitId);
    public static native void onNativeBannerAdLoadFail(String unitId, String adError);
    public static native void onNativeBannerAdClick(String unitId);
    public static native void onNativeBannerAdShow(String unitId);
    public static native void onNativeBannerAdClose(String unitId);
    public static native void onNativeBannerAdAutoRefreshed(String unitId);
    public static native void onNativeBannerAdAutoRefreshFail(String unitId, String adError);

    public static native void onSDKInitSuccess();
    public static native void onSDKInitFail(String errorMsg);
}
