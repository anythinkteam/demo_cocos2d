package com.uparpu.cocos2dx.bridge;

import android.app.Activity;

import com.uparpu.api.AdError;
import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.rewardvideo.api.UpArpuRewardVideoAd;
import com.uparpu.rewardvideo.api.UpArpuRewardVideoListener;

public class UpArpuRewardedVideoImpl {
    final String TAG = "UpArpuRewardedVideoImpl";
    String mUnitId;
    UpArpuRewardVideoAd upArpuRewardVideoAd;

    boolean mIsReady = false;

    public UpArpuRewardedVideoImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(Activity context) {
        upArpuRewardVideoAd = new UpArpuRewardVideoAd(context, mUnitId);

        upArpuRewardVideoAd.setAdListener(new UpArpuRewardVideoListener() {

            @Override
            public void onRewardedVideoAdLoaded() {
                mIsReady = true;
                UpArpuListenerEventJniHelper.onRewardedVideoAdLoaded(mUnitId);
            }

            @Override
            public void onRewardedVideoAdFailed(AdError adError) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdFailed(mUnitId, adError.printStackTrace());
            }

            @Override
            public void onRewardedVideoAdPlayStart(UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdPlayStart(mUnitId);
            }

            @Override
            public void onRewardedVideoAdPlayEnd(UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdPlayEnd(mUnitId);
            }

            @Override
            public void onRewardedVideoAdPlayFailed(AdError adError, UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdPlayFailed(mUnitId, adError.printStackTrace());
            }

            @Override
            public void onRewardedVideoAdClosed(boolean b, UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdClosed(mUnitId, b);
            }

            @Override
            public void onRewardedVideoAdPlayClicked(UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onRewardedVideoAdPlayClicked(mUnitId);
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

    public void show() {
        if (upArpuRewardVideoAd != null) {
            upArpuRewardVideoAd.show();
        }
    }

    public void setUserInfo(String userId, String userData) {
        if (upArpuRewardVideoAd != null) {
            upArpuRewardVideoAd.setUserData(userId, userData);
        }
    }

}
