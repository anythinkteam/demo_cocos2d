package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.text.TextUtils;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.ATAdStatusInfo;
import com.anythink.core.api.AdError;
import com.anythink.rewardvideo.api.ATRewardVideoAd;
import com.anythink.rewardvideo.api.ATRewardVideoListener;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ATRewardedVideoImpl {
    final String TAG = "ATRewardedVideoImpl";
    String mPlacementId;
    ATRewardVideoAd upArpuRewardVideoAd;

    boolean mIsReady = false;
    boolean mIsRewarded = false;

    public ATRewardedVideoImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(Activity context, Map<String, String> extra) {
        upArpuRewardVideoAd = new ATRewardVideoAd(context, mPlacementId);

        upArpuRewardVideoAd.setAdListener(new ATRewardVideoListener() {

            @Override
            public void onRewardedVideoAdLoaded() {
                mIsReady = true;
                ATListenerEventJniHelper.onRewardedVideoAdLoaded(mPlacementId);
            }

            @Override
            public void onRewardedVideoAdFailed(AdError adError) {
                ATListenerEventJniHelper.onRewardedVideoAdFailed(mPlacementId, adError.printStackTrace());
            }

            @Override
            public void onRewardedVideoAdPlayStart(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onRewardedVideoAdPlayStart(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                mIsRewarded = false;
            }

            @Override
            public void onRewardedVideoAdPlayEnd(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onRewardedVideoAdPlayEnd(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onRewardedVideoAdPlayFailed(AdError adError, ATAdInfo adInfo) {
                ATListenerEventJniHelper.onRewardedVideoAdPlayFailed(mPlacementId, adError.printStackTrace(), ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onRewardedVideoAdClosed(ATAdInfo atAdInfo) {
                ATListenerEventJniHelper.onRewardedVideoAdClosed(mPlacementId, mIsRewarded, ATUtils.adInfoToJsonstring(atAdInfo));
            }

            @Override
            public void onRewardedVideoAdPlayClicked(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onRewardedVideoAdPlayClicked(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onReward(ATAdInfo atAdInfo) {
                mIsRewarded = true;
                ATListenerEventJniHelper.onRewardedVideoAdRewarded(mPlacementId, ATUtils.adInfoToJsonstring(atAdInfo));
            }
        });

        if (extra != null) {

            String userId = extra.get("key_user_id");
            String userData = extra.get("key_media_ext");

            Map<String, Object> localExtra = new HashMap<>();

            if (userId != null && !TextUtils.isEmpty(userId)) {
                localExtra.put("user_id", userId);
            }
            if (userData != null && !TextUtils.isEmpty(userData)) {
                localExtra.put("user_custom_data", userData);
            }

            LogUtils.i(TAG, "loadRewardVideo, localExtra userId [" + userId + "]");
            LogUtils.i(TAG, "loadRewardVideo, localExtra userData [" + userData + "]");

            localExtra.putAll(extra);
            upArpuRewardVideoAd.setLocalExtra(localExtra);
        }

        upArpuRewardVideoAd.load();
    }

    public boolean isAdReady() {
        try {
            if (upArpuRewardVideoAd != null) {
                return upArpuRewardVideoAd.isAdReady();
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
        return mIsReady;
    }

    public String checkAdStatus() {

        if (upArpuRewardVideoAd != null) {
            ATAdStatusInfo atAdStatusInfo = upArpuRewardVideoAd.checkAdStatus();
            boolean loading = atAdStatusInfo.isLoading();
            boolean ready = atAdStatusInfo.isReady();
            ATAdInfo atTopAdInfo = atAdStatusInfo.getATTopAdInfo();

            try {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("isLoading", loading);
                jsonObject.put("isReady", ready);
                jsonObject.put("adInfo", atTopAdInfo);

                String result = jsonObject.toString();
                LogUtils.i(TAG, "rewardvideo.placementId [" + mPlacementId + "], checkAdStatus: " + result);

                return result;
            } catch (Throwable e) {
                e.printStackTrace();
                LogUtils.i(TAG, "rewardvideo.placementId [" + mPlacementId + "], error: " + e.getMessage());
            }
        }
        return "";
    }

    public void show(Activity activity, String scenario) {
        if (upArpuRewardVideoAd != null) {
            upArpuRewardVideoAd.show(activity, scenario);
        }
    }

    public void setUserInfo(String userId, String userData) {
        if (upArpuRewardVideoAd != null) {
            upArpuRewardVideoAd.setUserData(userId, userData);
        }
    }

}
