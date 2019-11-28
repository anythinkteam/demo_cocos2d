package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.anythink.core.api.ATSDK;
import com.anythink.core.api.ATSDKInitListener;

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

    public static void initCustomMap(Map<String, String> customMap) {
        ATSDK.initCustomMap(customMap);
        for (Object key : customMap.keySet()) {
            Log.i(TAG, "key:" + key + "--value:" + customMap.get(key));
        }
    }


    public static void initSDK(final String appid, final String appKey) {
        LogUtils.i(TAG, "initSDK,appid [" + appid + "]");
        if (TextUtils.isEmpty(appid) || TextUtils.isEmpty(appKey)) {
            ATListenerEventJniHelper.onSDKInitFail("appid or appkey isEmpty... init failed");
            return;
        }

        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }

        ATSDK.init(sApplicationContext, appid, appKey, new ATSDKInitListener() {
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
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }


        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ATSDK.showGdprAuth(sActivity);
            }
        });
    }

    public static void setGDPRLevel(int pGDPRUploadDataLevel) {
        LogUtils.i(TAG, "setGDPRLevel");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATSDK.setGDPRUploadDataLevel(sActivity, pGDPRUploadDataLevel);
    }

    public static boolean isEUTraffic() {
        LogUtils.i(TAG, "isEUTraffic");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return false;
        }
        return ATSDK.isEUTraffic(sActivity);
    }

    /**
     * -----------------------------------------------------------Interstitial----------------------------------------------------------------------------
     **/
    static Map<String, ATInterstitalImpl> mATInterstitialMap = new HashMap<>();

    /**
     * 插屏广告加载
     *
     * @param unitid
     */
    public synchronized static void loadInterstitialAd(final String unitid) {
        LogUtils.i(TAG, "loadInterstitial,unitid [" + unitid + "]");

        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return;
        }

        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }

        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(unitid)) {
            demoInterstitial = mATInterstitialMap.get(unitid);
        }
        if (demoInterstitial == null) {
            demoInterstitial = new ATInterstitalImpl(unitid);
            mATInterstitialMap.put(unitid, demoInterstitial);
        }

        final ATInterstitalImpl finalInterstital = demoInterstitial;

        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalInterstital.loadAd(sActivity);
            }
        });
    }


    /**
     * 插屏广告是否Ready
     *
     * @param pUnitid
     * @return
     */
    public static boolean isInterstitialAdReady(final String pUnitid) {
        LogUtils.i(TAG, "isInterstitalReady,pUnitid [" + pUnitid + "]");
        if (TextUtils.isEmpty(pUnitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return false;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return false;
        }
        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(pUnitid)) {
            demoInterstitial = mATInterstitialMap.get(pUnitid);
        }
        if (demoInterstitial == null) {
            return false;
        }
        return demoInterstitial.isAdReady();


    }

    /**
     * 展示插屏广告
     *
     * @param pUnitid
     */
    public static void showInterstitialAd(final String pUnitid) {

        LogUtils.i(TAG, "showInterstitial,pUnitid [" + pUnitid + "]");
        if (TextUtils.isEmpty(pUnitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATInterstitalImpl demoInterstitial = null;
        if (mATInterstitialMap.containsKey(pUnitid)) {
            demoInterstitial = mATInterstitialMap.get(pUnitid);
        }
        if (demoInterstitial == null) {
            return;
        }
        final ATInterstitalImpl finalATInterstitial = demoInterstitial;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATInterstitial.show();
            }
        });
    }


    /**
     * -----------------------------------------------------------RewardedVideo----------------------------------------------------------------------------
     **/
    static Map<String, ATRewardedVideoImpl> mATRewardVideoMap = new HashMap<>();

    public static void loadRewardedVideoAd(final String unitid, final String userid) {
        LogUtils.i(TAG, "loadRewardVideo,unitid [" + unitid + "]");
        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return;
        }
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATRewardedVideoImpl demoRewardVideoAd = null;
        if (mATRewardVideoMap.containsKey(unitid)) {
            demoRewardVideoAd = mATRewardVideoMap.get(unitid);
        }

        if (demoRewardVideoAd == null) {
            demoRewardVideoAd = new ATRewardedVideoImpl(unitid);
            demoRewardVideoAd.setUserInfo(userid, "");
            mATRewardVideoMap.put(unitid, demoRewardVideoAd);
        }

        final ATRewardedVideoImpl finalATRewardVideo = demoRewardVideoAd;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATRewardVideo.loadAd(sActivity);
            }
        });
    }


    public static void showRewardedVideoAd(final String unitid) {
        LogUtils.i(TAG, "showRewardVideo,unitid [" + unitid + "]");
        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return;
        }
        final ATRewardedVideoImpl finalATRewardVideo = mATRewardVideoMap.get(unitid);
        if (finalATRewardVideo == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATRewardVideo.show();
            }
        });
    }


    public static boolean isRewardedVideoAdReady(final String unitid) {
        LogUtils.i(TAG, "isRewardedVideoReady,unitid [" + unitid + "]");
        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return false;
        }
        ATRewardedVideoImpl finalATRewardVideo = mATRewardVideoMap.get(unitid);
        if (finalATRewardVideo == null) {
            return false;
        }

        return finalATRewardVideo.isAdReady();
    }

    /**
     * -----------------------------------------------------------Banner----------------------------------------------------------------------------
     **/

    private static Map<String, ATBannerImpl> mBannerHashMap = new HashMap();

    public static void loadBannerAd(final String pUnitid) {
        LogUtils.i(TAG, "initBanner-->" + pUnitid);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATBannerImpl demoBannerImpl = null;

        if (mBannerHashMap.containsKey(pUnitid)) {
            demoBannerImpl = mBannerHashMap.get(pUnitid);
        }
        if (demoBannerImpl == null) {
            demoBannerImpl = new ATBannerImpl(pUnitid);
            mBannerHashMap.put(pUnitid, demoBannerImpl);
        }

        final ATBannerImpl finalATBannerImpl = demoBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATBannerImpl.loadAd(sActivity);
            }
        });


    }

    public static boolean isBannerAdReady(final String pUnitid) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
        if (uparpuBannerImpl == null) {
            return false;
        }
        return uparpuBannerImpl.isAdReady();
    }

    public static void showBannerAd(final String pUnitid, final Map<String, String> rectMap) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
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


    public static void removeBannerAd(final String pUnitid) {
        final ATBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
        if (uparpuBannerImpl == null) {
            return;
        }
        if (!mBannerHashMap.containsKey(pUnitid)) {
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

    public static void loadNativeAd(String unitId, final Map<String, Object> localMap) {
        LogUtils.i(TAG, "loadNativeAd-->" + unitId);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATNativeAdImpl demoNativeImpl = null;

        if (mATNativeImplMap.containsKey(unitId)) {
            demoNativeImpl = mATNativeImplMap.get(unitId);
        }
        if (demoNativeImpl == null) {
            demoNativeImpl = new ATNativeAdImpl(unitId);
            mATNativeImplMap.put(unitId, demoNativeImpl);
        }

        final ATNativeAdImpl finalATBannerImpl = demoNativeImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATBannerImpl.loadAd(sActivity, localMap);
            }
        });
    }

    public static boolean isNativeAdReady(String unitId) {
        final ATNativeAdImpl uparpuNativeadImpl = mATNativeImplMap.get(unitId);
        if (uparpuNativeadImpl == null) {
            return false;
        }
        return uparpuNativeadImpl.isAdReady();
    }

    public static void showNativeAd(String unitId, final Map<String, String> rectMap) {
        final ATNativeAdImpl uparpuNativeImpl = mATNativeImplMap.get(unitId);
        if (uparpuNativeImpl == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                int left = Integer.parseInt(rectMap.get("x"));
                int top = Integer.parseInt(rectMap.get("y"));
                int width = Integer.parseInt(rectMap.get("w"));
                int height = Integer.parseInt(rectMap.get("h"));
                uparpuNativeImpl.showAd(sActivity, left, top, width, height);
            }
        });
    }

    public static void removeNativeAd(String unitId) {
        final ATNativeAdImpl uparpuNativeImpl = mATNativeImplMap.get(unitId);
        if (uparpuNativeImpl == null) {
            return;
        }
        if (!mATNativeImplMap.containsKey(unitId)) {
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

    public static void loadNativeBannerAd(final String pUnitid, final Map<String, String> localMap) {
        LogUtils.i(TAG, "loadNativeBannerAd-->" + pUnitid);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        ATNativeBannerImpl demoBannerImpl = null;

        if (mNativeBannerHashMap.containsKey(pUnitid)) {
            demoBannerImpl = mNativeBannerHashMap.get(pUnitid);
        }
        if (demoBannerImpl == null) {
            demoBannerImpl = new ATNativeBannerImpl(pUnitid);
            mNativeBannerHashMap.put(pUnitid, demoBannerImpl);
        }

        final ATNativeBannerImpl finalATNativeBannerImpl = demoBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalATNativeBannerImpl.loadAd(sActivity);
            }
        });


    }

    public static boolean isNativeBannerAdReady(final String pUnitid) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
        if (uparpuNativeBannerImpl == null) {
            return false;
        }
        return uparpuNativeBannerImpl.isAdReady();
    }

    public static void showNativeBannerAd(final String pUnitid, final Map<String, String> rectMap, final Map<String,String> extraMap) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
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


    public static void removeNativeBannerAd(final String pUnitid) {
        final ATNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
        if (uparpuNativeBannerImpl == null) {
            return;
        }
        if (!mNativeBannerHashMap.containsKey(pUnitid)) {
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
