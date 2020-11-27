package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.cocos2dx.bridge.utils.CommonUtil;
import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.ATAdStatusInfo;
import com.anythink.core.api.AdError;
import com.anythink.interstitial.api.ATInterstitial;
import com.anythink.interstitial.api.ATInterstitialListener;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ATInterstitalImpl {
    final String TAG = "ATInterstitalImpl";
    String mPlacementId;
    ATInterstitial demoInterstitial;

    boolean mIsReady = false;

    public ATInterstitalImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(Context context, String extra) {
        demoInterstitial = new ATInterstitial(context, mPlacementId);

        demoInterstitial.setAdListener(new ATInterstitialListener() {
            @Override
            public void onInterstitialAdLoaded() {
                LogUtils.i(TAG, "sdk onInterstitialAdLoaded");
                mIsReady = true;
                ATListenerEventJniHelper.onInterstitialAdLoaded(mPlacementId);
            }

            @Override
            public void onInterstitialAdLoadFail(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdLoadFail");
                ATListenerEventJniHelper.onInterstitialAdLoadFail(mPlacementId, pAdError.printStackTrace());
            }

            @Override
            public void onInterstitialAdClicked(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClicked");
                ATListenerEventJniHelper.onInterstitialAdClicked(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onInterstitialAdShow(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdShow");
                mIsReady = false;
                ATListenerEventJniHelper.onInterstitialAdShow(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));

            }

            @Override
            public void onInterstitialAdClose(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClose");
                ATListenerEventJniHelper.onInterstitialAdClose(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onInterstitialAdVideoStart(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoStart");
                ATListenerEventJniHelper.onInterstitialAdVideoStart(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onInterstitialAdVideoEnd(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoEnd");
                ATListenerEventJniHelper.onInterstitialAdVideoEnd(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onInterstitialAdVideoError(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoError");
                ATListenerEventJniHelper.onInterstitialAdVideoError(mPlacementId, pAdError.printStackTrace());
            }
        });

        if (!TextUtils.isEmpty(extra)) {
            try {
                LogUtils.i(TAG, "loadInterstitial, placementId: " + mPlacementId + ", extra: " + extra);
                JSONObject jsonObject = new JSONObject(extra);
                Map<String, Object> localExtra = new HashMap<>();
                if (jsonObject.has("UseRewardedVideoAsInterstitial")) {
                    boolean useRewardedVideoAsInterstitial = (Boolean) jsonObject.get("UseRewardedVideoAsInterstitial");
                    LogUtils.i(TAG, "is_use_rewarded_video_as_interstitial: " + useRewardedVideoAsInterstitial);
                    localExtra.put("is_use_rewarded_video_as_interstitial", useRewardedVideoAsInterstitial);
                }

                CommonUtil.fillMapFromJsonObject(localExtra, jsonObject);

                demoInterstitial.setLocalExtra(localExtra);
            } catch (Throwable e) {
                e.printStackTrace();
            }
        }

        demoInterstitial.load();
    }

    public boolean isAdReady() {
        try {
            if (demoInterstitial != null) {
                return demoInterstitial.isAdReady();
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
        return mIsReady;
    }

    public String checkAdStatus() {

        if (demoInterstitial != null) {
            ATAdStatusInfo atAdStatusInfo = demoInterstitial.checkAdStatus();
            boolean loading = atAdStatusInfo.isLoading();
            boolean ready = atAdStatusInfo.isReady();
            ATAdInfo atTopAdInfo = atAdStatusInfo.getATTopAdInfo();

            try {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("isLoading", loading);
                jsonObject.put("isReady", ready);
                jsonObject.put("adInfo", atTopAdInfo);

                String result = jsonObject.toString();
                LogUtils.i(TAG, "intestitial.placementId [" + mPlacementId + "], checkAdStatus: " + result);

                return result;
            } catch (Throwable e) {
                e.printStackTrace();
                LogUtils.i(TAG, "intestitial.placementId [" + mPlacementId + "], error: " + e.getMessage());
            }
        }
        return "";
    }


    public void show(Activity activity, String scenario) {
        if (demoInterstitial != null) {
            demoInterstitial.show(activity, scenario);
        }
    }

}
