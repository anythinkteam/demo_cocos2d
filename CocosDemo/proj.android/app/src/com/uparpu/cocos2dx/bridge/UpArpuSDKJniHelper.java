package com.uparpu.cocos2dx.bridge;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.uparpu.api.UpArpuSDK;
import com.uparpu.api.UpArpuSDKInitListener;

import java.util.HashMap;
import java.util.Map;

/**
 * Copyright (C) 2018 {XX} Science and Technology Co., Ltd.
 * 提供C层反射调用 ，这里负责SDK的函数调用 C层调用JAVA
 */
public class UpArpuSDKJniHelper {
    private static final String TAG = "UpArpuSDKJniHelper";
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
        UpArpuSDK.setNetworkLogDebug(isDebug);
    }

    public static void setChannel(String channel) {
        LogUtils.i(TAG, "setChannel: " + channel);
        UpArpuSDK.setChannel(channel);
    }

    public static void initCustomMap(Map<String, String> customMap) {
        UpArpuSDK.initCustomMap(customMap);
        for (Object key : customMap.keySet()) {
            Log.i(TAG, "key:" + key + "--value:" + customMap.get(key));
        }
    }


    public static void initSDK(final String appid, final String appKey) {
        LogUtils.i(TAG, "initSDK,appid [" + appid + "]");
        if (TextUtils.isEmpty(appid) || TextUtils.isEmpty(appKey)) {
            UpArpuListenerEventJniHelper.onSDKInitFail("appid or appkey isEmpty... init failed");
            return;
        }

        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }

        UpArpuSDK.init(sApplicationContext, appid, appKey, new UpArpuSDKInitListener() {
            @Override
            public void onSuccess() {
                Log.i(TAG, "sdk onSDKInitSuccess");
                UpArpuListenerEventJniHelper.onSDKInitSuccess();
            }

            @Override
            public void onFail(String error) {
                LogUtils.e(TAG, "sdk onSDKInitFailed,palce check...[" + error + "]");
                UpArpuListenerEventJniHelper.onSDKInitFail(error);
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
                UpArpuSDK.showGdprAuth(sActivity);
            }
        });
    }

    public static void setGDPRLevel(int pGDPRUploadDataLevel) {
        LogUtils.i(TAG, "setGDPRLevel");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        UpArpuSDK.setGDPRUploadDataLevel(sActivity, pGDPRUploadDataLevel);
    }

    public static boolean isEUTraffic() {
        LogUtils.i(TAG, "isEUTraffic");
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return false;
        }
        return UpArpuSDK.isEUTraffic(sActivity);
    }

    /**
     * -----------------------------------------------------------Interstitial----------------------------------------------------------------------------
     **/
    static Map<String, UpArpuInterstitalImpl> mUpArpuInterstitialMap = new HashMap<>();

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

        UpArpuInterstitalImpl upArpuInterstitial = null;
        if (mUpArpuInterstitialMap.containsKey(unitid)) {
            upArpuInterstitial = mUpArpuInterstitialMap.get(unitid);
        }
        if (upArpuInterstitial == null) {
            upArpuInterstitial = new UpArpuInterstitalImpl(unitid);
            mUpArpuInterstitialMap.put(unitid, upArpuInterstitial);
        }

        final UpArpuInterstitalImpl finalInterstital = upArpuInterstitial;

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
        UpArpuInterstitalImpl upArpuInterstitial = null;
        if (mUpArpuInterstitialMap.containsKey(pUnitid)) {
            upArpuInterstitial = mUpArpuInterstitialMap.get(pUnitid);
        }
        if (upArpuInterstitial == null) {
            return false;
        }
        return upArpuInterstitial.isAdReady();


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
        UpArpuInterstitalImpl upArpuInterstitial = null;
        if (mUpArpuInterstitialMap.containsKey(pUnitid)) {
            upArpuInterstitial = mUpArpuInterstitialMap.get(pUnitid);
        }
        if (upArpuInterstitial == null) {
            return;
        }
        final UpArpuInterstitalImpl finalUpArpuInterstitial = upArpuInterstitial;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuInterstitial.show();
            }
        });
    }


    /**
     * -----------------------------------------------------------RewardedVideo----------------------------------------------------------------------------
     **/
    static Map<String, UpArpuRewardedVideoImpl> mUpArpuRewardVideoMap = new HashMap<>();

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
        UpArpuRewardedVideoImpl upArpuRewardVideoAd = null;
        if (mUpArpuRewardVideoMap.containsKey(unitid)) {
            upArpuRewardVideoAd = mUpArpuRewardVideoMap.get(unitid);
        }

        if (upArpuRewardVideoAd == null) {
            upArpuRewardVideoAd = new UpArpuRewardedVideoImpl(unitid);
            upArpuRewardVideoAd.setUserInfo(userid, "");
            mUpArpuRewardVideoMap.put(unitid, upArpuRewardVideoAd);
        }

        final UpArpuRewardedVideoImpl finalUpArpuRewardVideo = upArpuRewardVideoAd;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuRewardVideo.loadAd(sActivity);
            }
        });
    }


    public static void showRewardedVideoAd(final String unitid) {
        LogUtils.i(TAG, "showRewardVideo,unitid [" + unitid + "]");
        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return;
        }
        final UpArpuRewardedVideoImpl finalUpArpuRewardVideo = mUpArpuRewardVideoMap.get(unitid);
        if (finalUpArpuRewardVideo == null) {
            return;
        }
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuRewardVideo.show();
            }
        });
    }


    public static boolean isRewardedVideoAdReady(final String unitid) {
        LogUtils.i(TAG, "isRewardedVideoReady,unitid [" + unitid + "]");
        if (TextUtils.isEmpty(unitid)) {
            LogUtils.e(TAG, "unitid isEmpty... call failed");
            return false;
        }
        UpArpuRewardedVideoImpl finalUpArpuRewardVideo = mUpArpuRewardVideoMap.get(unitid);
        if (finalUpArpuRewardVideo == null) {
            return false;
        }

        return finalUpArpuRewardVideo.isAdReady();
    }

    /**
     * -----------------------------------------------------------Banner----------------------------------------------------------------------------
     **/

    private static Map<String, UpArpuBannerImpl> mBannerHashMap = new HashMap();

    public static void loadBannerAd(final String pUnitid) {
        LogUtils.i(TAG, "initBanner-->" + pUnitid);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        UpArpuBannerImpl upArpuBannerImpl = null;

        if (mBannerHashMap.containsKey(pUnitid)) {
            upArpuBannerImpl = mBannerHashMap.get(pUnitid);
        }
        if (upArpuBannerImpl == null) {
            upArpuBannerImpl = new UpArpuBannerImpl(pUnitid);
            mBannerHashMap.put(pUnitid, upArpuBannerImpl);
        }

        final UpArpuBannerImpl finalUpArpuBannerImpl = upArpuBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuBannerImpl.loadAd(sActivity);
            }
        });


    }

    public static boolean isBannerAdReady(final String pUnitid) {
        final UpArpuBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
        if (uparpuBannerImpl == null) {
            return false;
        }
        return uparpuBannerImpl.isAdReady();
    }

    public static void showBannerAd(final String pUnitid, final Map<String, String> rectMap) {
        final UpArpuBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
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
        final UpArpuBannerImpl uparpuBannerImpl = mBannerHashMap.get(pUnitid);
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
    static Map<String, UpArpuNativeAdImpl> mUpArpuNativeImplMap = new HashMap<>();

    public static void loadNativeAd(String unitId, final Map<String, Object> localMap) {
        LogUtils.i(TAG, "loadNativeAd-->" + unitId);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        UpArpuNativeAdImpl upArpuNativeImpl = null;

        if (mUpArpuNativeImplMap.containsKey(unitId)) {
            upArpuNativeImpl = mUpArpuNativeImplMap.get(unitId);
        }
        if (upArpuNativeImpl == null) {
            upArpuNativeImpl = new UpArpuNativeAdImpl(unitId);
            mUpArpuNativeImplMap.put(unitId, upArpuNativeImpl);
        }

        final UpArpuNativeAdImpl finalUpArpuBannerImpl = upArpuNativeImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuBannerImpl.loadAd(sActivity, localMap);
            }
        });
    }

    public static boolean isNativeAdReady(String unitId) {
        final UpArpuNativeAdImpl uparpuNativeadImpl = mUpArpuNativeImplMap.get(unitId);
        if (uparpuNativeadImpl == null) {
            return false;
        }
        return uparpuNativeadImpl.isAdReady();
    }

    public static void showNativeAd(String unitId, final Map<String, String> rectMap) {
        final UpArpuNativeAdImpl uparpuNativeImpl = mUpArpuNativeImplMap.get(unitId);
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
        final UpArpuNativeAdImpl uparpuNativeImpl = mUpArpuNativeImplMap.get(unitId);
        if (uparpuNativeImpl == null) {
            return;
        }
        if (!mUpArpuNativeImplMap.containsKey(unitId)) {
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
    private static Map<String, UpArpuNativeBannerImpl> mNativeBannerHashMap = new HashMap();

    public static void loadNativeBannerAd(final String pUnitid, final Map<String, String> localMap) {
        LogUtils.i(TAG, "loadNativeBannerAd-->" + pUnitid);
        if (sActivity == null) {
            LogUtils.e(TAG, "JNIHelper must inited ,call methon UparpuSDKJniHelper.init() frist in activity..");
            return;
        }
        UpArpuNativeBannerImpl upArpuBannerImpl = null;

        if (mNativeBannerHashMap.containsKey(pUnitid)) {
            upArpuBannerImpl = mNativeBannerHashMap.get(pUnitid);
        }
        if (upArpuBannerImpl == null) {
            upArpuBannerImpl = new UpArpuNativeBannerImpl(pUnitid);
            mNativeBannerHashMap.put(pUnitid, upArpuBannerImpl);
        }

        final UpArpuNativeBannerImpl finalUpArpuNativeBannerImpl = upArpuBannerImpl;
        sActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                finalUpArpuNativeBannerImpl.loadAd(sActivity);
            }
        });


    }

    public static boolean isNativeBannerAdReady(final String pUnitid) {
        final UpArpuNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
        if (uparpuNativeBannerImpl == null) {
            return false;
        }
        return uparpuNativeBannerImpl.isAdReady();
    }

    public static void showNativeBannerAd(final String pUnitid, final Map<String, String> rectMap, final Map<String,String> extraMap) {
        final UpArpuNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
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
        final UpArpuNativeBannerImpl uparpuNativeBannerImpl = mNativeBannerHashMap.get(pUnitid);
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
