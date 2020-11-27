package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.anythink.core.api.ATGDPRAuthCallback;
import com.anythink.core.api.ATSDK;
import com.anythink.core.api.ATSDKInitListener;
import com.anythink.core.api.NetTrafficeCallback;

import java.util.HashMap;
import java.util.Map;

/**
 * Copyright (C) 2018 {XX} Science and Technology Co., Ltd.
 * 提供C层反射调用 ，这里负责SDK的函数调用 C层调用JAVA
 */
public class ATSDKJniHelper {
    private static final String TAG = "ATSDKJniHelper";
    private static Activity sActivity;
    private static Context sApplicationContext;

    public static boolean isDebug = true;


    public static void init(Activity activity) {
        sApplicationContext = activity.getApplicationContext();
        sActivity = activity;
    }

    public static void setDebugLog(boolean isDebug) {
        LogUtils.isDebug = isDebug;
        if (isDebug) {
            LogUtils.i(TAG, "setDebugLog: true");
        }
        ATSDK.setNetworkLogDebug(isDebug);
    }

    public static void setChannel(String channel) {
        LogUtils.i(TAG, "setChannel: " + channel);
        ATSDK.setChannel(channel);
    }

    public static void setSubChannel(String subChannel) {
        LogUtils.i(TAG, "setSubChannel: " + subChannel);
        ATSDK.setSubChannel(subChannel);
    }

    public static void initCustomMap(Map<String, Object> customMap) {
        ATSDK.initCustomMap(customMap);
        for (Object key : customMap.keySet()) {
            Log.i(TAG, "key:" + key + " -- value:" + customMap.get(key));
        }
    }

    public static void initPlacementCustomMap(String placementId, Map<String, Object> customMap) {
        ATSDK.initPlacementCustomMap(placementId, customMap);
        for (Object key : customMap.keySet()) {
            Log.i(TAG, "placementId: " + placementId + ",  key:" + key + " -- value:" + customMap.get(key));
        }
    }

    public static void integrationChecking() {
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATSDK.integrationChecking(sApplicationContext);
    }

    public static void initSDK(final String appId, final String appKey) {
        LogUtils.i(TAG, "initSDK,appid [" + appId + "]");
        if (TextUtils.isEmpty(appId) || TextUtils.isEmpty(appKey)) {
            ATListenerEventJniHelper.onSDKInitFail("appid or appkey isEmpty... init failed");
            return;
        }

        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }

        ATSDK.init(sApplicationContext, appId, appKey, new ATSDKInitListener() {
            @Override
            public void onSuccess() {
                Log.i(TAG, "sdk onSDKInitSuccess");
                ATListenerEventJniHelper.onSDKInitSuccess();
            }

            @Override
            public void onFail(String error) {
                LogUtils.e(TAG, "sdk onSDKInitFailed,palce check...[" + error + "]");
                ATListenerEventJniHelper.onSDKInitFail(error);
            }
        });
    }

    public static void showGDPR() {
        LogUtils.i(TAG, "showGDPR");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }


        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ATSDK.showGdprAuth(sActivity);
            }
        });
    }

    public static void showGdprWidthListener() {
        LogUtils.i(TAG, "showGDPR");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }


        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ATSDK.showGdprAuth(sActivity, new ATGDPRAuthCallback() {
                    @Override
                    public void onAuthResult(int i) {
                        LogUtils.e(TAG, "sdk onAuthResult, GDPR: [" + i + "]");
                        ATListenerEventJniHelper.onGdprAuth(i);
                    }

                    @Override
                    public void onPageLoadFail() {
                        LogUtils.e(TAG, "sdk onPageLoadFail");
                        ATListenerEventJniHelper.onPageLoadFail();
                    }
                });
            }
        });
    }

    public static void setGDPRLevel(int pGDPRUploadDataLevel) {
        LogUtils.i(TAG, "setGDPRLevel");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATSDK.setGDPRUploadDataLevel(sActivity, pGDPRUploadDataLevel);
    }

    public static int getGDPRLevel() {
        LogUtils.i(TAG, "getGDPRDataLevel");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return ATSDK.UNKNOWN;
        }
        return ATSDK.getGDPRDataLevel(sActivity);
    }

    public static boolean isEUTraffic() {
        LogUtils.i(TAG, "isEUTraffic");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return false;
        }
        return ATSDK.isEUTraffic(sActivity);
    }

    public static void getUserLocation() {
        LogUtils.i(TAG, "getUserLocation");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATSDK.checkIsEuTraffic(sApplicationContext, new NetTrafficeCallback() {
            @Override
            public void onResultCallback(boolean b) {
                final int result = b ? 1 : 2;

                LogUtils.i(TAG, "sdk getUserLocation: [" + result + "]");
                ATListenerEventJniHelper.onUserLocation(result);
            }

            @Override
            public void onErrorCallback(String s) {
                LogUtils.e(TAG, "sdk getUserLocation error: " + s);
                ATListenerEventJniHelper.onUserLocation(0);
            }
        });
    }

    public static void deniedUploadDeviceInfo(String arrayString) {
        LogUtils.i(TAG, "deniedUploadDeviceInfo " + arrayString);
        if (!TextUtils.isEmpty(arrayString)) {
            String[] split = arrayString.split(",");
            ATSDK.deniedUploadDeviceInfo(split);
        }
    }

    /**
     * -----------------------------------------------------------Interstitial----------------------------------------------------------------------------
     **/
    static Map<String, ATInterstitalImpl> mATInterstitialMap = new HashMap<>();

    /**
     * 插屏广告加载
     *
     * @param placementId
     */
    public synchronized static void loadInterstitialAd(final String placementId, String extra) {
        LogUtils.i(TAG, "loadInterstitial,placementId [" + placementId + "], extra: " + extra);

        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return;
        }

        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }

        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(placementId)) {
            demoInterstitial = mATInterstitialMap.get(placementId);
        }
        if (demoInterstitial == null) {
            demoInterstitial = new ATInterstitalImpl(placementId);
            mATInterstitialMap.put(placementId, demoInterstitial);
        }

        final ATInterstitalImpl finalInterstital = demoInterstitial;

        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalInterstital.loadAd(sActivity, extra);
            }
        });
    }


    /**
     * 插屏广告是否Ready
     *
     * @param placementId
     * @return
     */
    public static boolean isInterstitialAdReady(final String placementId) {
        LogUtils.i(TAG, "isInterstitalReady,placementId [" + placementId + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return false;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return false;
        }
        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(placementId)) {
            demoInterstitial = mATInterstitialMap.get(placementId);
        }
        if (demoInterstitial == null) {
            return false;
        }
        return demoInterstitial.isAdReady();


    }

    public static String checkInterstitialAdStatus(final String placementId) {
        LogUtils.i(TAG, "checkRewardedVideoAdStatus,placementId [" + placementId + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return "";
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return "";
        }
        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(placementId)) {
            demoInterstitial = mATInterstitialMap.get(placementId);
        }
        if (demoInterstitial == null) {
            return "";
        }
        return demoInterstitial.checkAdStatus();
    }


    /**
     * 展示插屏广告
     *
     * @param placementId
     */
    public static void showInterstitialAd(final String placementId, final String scenario) {

        LogUtils.i(TAG, "showInterstitial,placementId [" + placementId + "], scenario [" + scenario + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(placementId)) {
            demoInterstitial = mATInterstitialMap.get(placementId);
        }
        if (demoInterstitial == null) {
            return;
        }
        final ATInterstitalImpl finalATInterstitial = demoInterstitial;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATInterstitial.show(sActivity, scenario);
            }
        });
    }


    /**
     * -----------------------------------------------------------RewardedVideo----------------------------------------------------------------------------
     **/
    static Map<String, ATRewardedVideoImpl> mATRewardVideoMap = new HashMap<>();

    public static void loadRewardedVideoAd(final String placementId, final Map<String, String> extra) {
        LogUtils.i(TAG, "loadRewardVideo,placementId [" + placementId + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATRewardedVideoImpl demoRewardVideoAd = null;
        if (mATRewardVideoMap.containsKey(placementId)) {
            demoRewardVideoAd = mATRewardVideoMap.get(placementId);
        }

        final String[] extraArray = new String[2];
        if (extra != null) {
            extraArray[0] = extra.get("key_user_id");
            extraArray[1] = extra.get("key_media_ext");

            LogUtils.i(TAG, "loadRewardVideo, userId [" + extraArray[0] + "]");
            LogUtils.i(TAG, "loadRewardVideo, userData [" + extraArray[1] + "]");
        }

        if (demoRewardVideoAd == null) {
            demoRewardVideoAd = new ATRewardedVideoImpl(placementId);
            mATRewardVideoMap.put(placementId, demoRewardVideoAd);
        }

        final ATRewardedVideoImpl finalATRewardVideo = demoRewardVideoAd;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATRewardVideo.setUserInfo(extraArray[0], extraArray[1]);
                finalATRewardVideo.loadAd(sActivity, extra);
            }
        });
    }


    public static void showRewardedVideoAd(final String placementId, final String scenario) {
        LogUtils.i(TAG, "showRewardVideo,placementId [" + placementId + "], scenario [" + scenario + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return;
        }
        final ATRewardedVideoImpl finalATRewardVideo = mATRewardVideoMap.get(placementId);
        if (finalATRewardVideo == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATRewardVideo.show(sActivity, scenario);
            }
        });
    }


    public static boolean isRewardedVideoAdReady(final String placementId) {
        LogUtils.i(TAG, "isRewardedVideoReady,placementId [" + placementId + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return false;
        }
        ATRewardedVideoImpl finalATRewardVideo = mATRewardVideoMap.get(placementId);
        if (finalATRewardVideo == null) {
            return false;
        }

        return finalATRewardVideo.isAdReady();
    }

    public static String checkRewardedVideoAdStatus(final String placementId) {
        LogUtils.i(TAG, "checkRewardedVideoAdStatus,placementId [" + placementId + "]");
        if (TextUtils.isEmpty(placementId)) {
            LogUtils.e(TAG, "placementId isEmpty... call failed");
            return "";
        }
        ATRewardedVideoImpl finalATRewardVideo = mATRewardVideoMap.get(placementId);
        if (finalATRewardVideo == null) {
            return "";
        }

        return finalATRewardVideo.checkAdStatus();
    }

    /**
     * -----------------------------------------------------------Banner----------------------------------------------------------------------------
     **/

    private static Map<String, ATBannerImpl> mBannerHashMap = new HashMap();

    public static void loadBannerAd(final String placementId, final String extra) {
        LogUtils.i(TAG, "initBanner-->" + placementId + ", extra--> " + extra);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATBannerImpl demoBannerImpl = null;

        if (mBannerHashMap.containsKey(placementId)) {
            demoBannerImpl = mBannerHashMap.get(placementId);
        }
        if (demoBannerImpl == null) {
            demoBannerImpl = new ATBannerImpl(placementId);
            mBannerHashMap.put(placementId, demoBannerImpl);
        }

        final ATBannerImpl finalATBannerImpl = demoBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATBannerImpl.loadAd(sActivity, extra);
            }
        });


    }

    public static boolean isBannerAdReady(final String placementId) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(placementId);
        if (uparpuBannerImpl == null) {
            return false;
        }
        return uparpuBannerImpl.isAdReady();
    }

    public static void showBannerAd(final String placementId, final Map<String, String> rectMap) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(placementId);
        if (uparpuBannerImpl == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                int left = Integer.parseInt(rectMap.get("x"));
                int top = Integer.parseInt(rectMap.get("y"));
                int width = Integer.parseInt(rectMap.get("w"));
                int height = Integer.parseInt(rectMap.get("h"));
                uparpuBannerImpl.showAd(sActivity, left, top, width, height);
            }
        });

    }

    public static void showBannerAdInPosition(final String placementId, final String position) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(placementId);
        if (uparpuBannerImpl == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuBannerImpl.showAd(sActivity, position);
            }
        });

    }


    public static void removeBannerAd(final String placementId) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(placementId);
        if (uparpuBannerImpl == null) {
            return;
        }
        if (!mBannerHashMap.containsKey(placementId)) {
            return;
        }

        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuBannerImpl.removeAd();
            }
        });

    }

    /**
     * -----------------------------------------------------------NativeAd----------------------------------------------------------------------------
     **/
    static Map<String, ATNativeAdImpl> mATNativeImplMap = new HashMap<>();

    public static void loadNativeAd(String placementId, final Map<String, Object> localMap) {
        LogUtils.i(TAG, "loadNativeAd-->" + placementId);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATNativeAdImpl demoNativeImpl = null;

        if (mATNativeImplMap.containsKey(placementId)) {
            demoNativeImpl = mATNativeImplMap.get(placementId);
        }
        if (demoNativeImpl == null) {
            demoNativeImpl = new ATNativeAdImpl(placementId);
            mATNativeImplMap.put(placementId, demoNativeImpl);
        }

        final ATNativeAdImpl finalATBannerImpl = demoNativeImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATBannerImpl.loadAd(sActivity, localMap);
            }
        });
    }

    public static boolean isNativeAdReady(String placementId) {
        final ATNativeAdImpl uparpuNativeadImpl = mATNativeImplMap.get(placementId);
        if (uparpuNativeadImpl == null) {
            return false;
        }
        return uparpuNativeadImpl.isAdReady();
    }

    public static void showNativeAd(String placementId, final String json) {
        final ATNativeAdImpl uparpuNativeImpl = mATNativeImplMap.get(placementId);
        if (uparpuNativeImpl == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuNativeImpl.showAd(sActivity, json);
            }
        });
    }

    public static void removeNativeAd(String placementId) {
        final ATNativeAdImpl uparpuNativeImpl = mATNativeImplMap.get(placementId);
        if (uparpuNativeImpl == null) {
            return;
        }
        if (!mATNativeImplMap.containsKey(placementId)) {
            return;
        }

        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuNativeImpl.removeAd();
            }
        });
    }

    /**
     * -----------------------------------------------------------Native Banner----------------------------------------------------------------------------
     **/
    private static Map<String, ATNativeBannerImpl> mNativeBannerHashMap = new HashMap();

    public static void loadNativeBannerAd(final String placementId, final Map<String, Object> localMap) {
        LogUtils.i(TAG, "loadNativeBannerAd-->" + placementId);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call method ATSDKJniHelper.init() frist in activity..");
            return;
        }
        ATNativeBannerImpl demoBannerImpl = null;

        if (mNativeBannerHashMap.containsKey(placementId)) {
            demoBannerImpl = mNativeBannerHashMap.get(placementId);
        }
        if (demoBannerImpl == null) {
            demoBannerImpl = new ATNativeBannerImpl(placementId);
            mNativeBannerHashMap.put(placementId, demoBannerImpl);
        }

        final ATNativeBannerImpl finalATNativeBannerImpl = demoBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATNativeBannerImpl.loadAd(sActivity, localMap);
            }
        });


    }

    public static boolean isNativeBannerAdReady(final String placementId) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(placementId);
        if (uparpuNativeBannerImpl == null) {
            return false;
        }
        return uparpuNativeBannerImpl.isAdReady();
    }

    public static void showNativeBannerAd(final String placementId, final Map<String, String> rectMap, final Map<String, String> extraMap) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(placementId);
        if (uparpuNativeBannerImpl == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuNativeBannerImpl.showAd(sActivity, rectMap, extraMap);
            }
        });

    }


    public static void removeNativeBannerAd(final String placementId) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(placementId);
        if (uparpuNativeBannerImpl == null) {
            return;
        }
        if (!mNativeBannerHashMap.containsKey(placementId)) {
            return;
        }

        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                uparpuNativeBannerImpl.removeAd();
            }
        });

    }
}
