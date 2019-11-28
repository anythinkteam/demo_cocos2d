package com.uparpu.cocos2dx.bridge;

import android.content.Context;

import com.uparpu.api.AdError;
import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.interstitial.api.UpArpuInterstitial;
import com.uparpu.interstitial.api.UpArpuInterstitialListener;

public class UpArpuInterstitalImpl {
    final String TAG = "UpArpuInterstitalImpl";
    String mUnitId;
    UpArpuInterstitial upArpuInterstitial;

    boolean mIsReady = false;

    public UpArpuInterstitalImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(Context context) {
        upArpuInterstitial = new UpArpuInterstitial(context, mUnitId);

        upArpuInterstitial.setAdListener(new UpArpuInterstitialListener() {
            @Override
            public void onInterstitialAdLoaded() {
                LogUtils.i(TAG, "sdk onInterstitialAdLoaded");
                mIsReady = true;
                UpArpuListenerEventJniHelper.onInterstitialAdLoaded(mUnitId);
            }

            @Override
            public void onInterstitialAdLoadFail(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdLoadFail");
                UpArpuListenerEventJniHelper.onInterstitialAdLoadFail(mUnitId, pAdError.printStackTrace());
            }

            @Override
            public void onInterstitialAdClicked(UpArpuAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClicked");
                UpArpuListenerEventJniHelper.onInterstitialAdClicked(mUnitId);
            }

            @Override
            public void onInterstitialAdShow(UpArpuAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdShow");
                mIsReady = false;
                UpArpuListenerEventJniHelper.onInterstitialAdShow(mUnitId);

            }

            @Override
            public void onInterstitialAdClose(UpArpuAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClose");
                UpArpuListenerEventJniHelper.onInterstitialAdClose(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoStart() {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoStart");
                UpArpuListenerEventJniHelper.onInterstitialAdVideoStart(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoEnd() {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoEnd");
                UpArpuListenerEventJniHelper.onInterstitialAdVideoEnd(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoError(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoError");
                UpArpuListenerEventJniHelper.onInterstitialAdVideoError(mUnitId, pAdError.printStackTrace());
            }
        });
        upArpuInterstitial.load();
    }

    public boolean isAdReady() {
        try {
            if (upArpuInterstitial != null) {
                return upArpuInterstitial.isAdReady();
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
        return mIsReady;
    }

    public void show() {
        if (upArpuInterstitial != null) {
            upArpuInterstitial.show();
        }
    }

}
