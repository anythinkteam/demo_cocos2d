package com.anythink.cocos2dx.bridge;

import android.app.Activity;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.AdError;
import com.anythink.rewardvideo.api.ATRewardVideoAd;
import com.anythink.rewardvideo.api.ATRewardVideoListener;

public class ATRewardedVideoImpl {
    final String TAG = "ATRewardedVideoImpl";
    String mPlacementId;
    ATRewardVideoAd upArpuRewardVideoAd;

    boolean mIsReady = false;
    boolean mIsRewarded = false;

    public ATRewardedVideoImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(Activity context) {
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
