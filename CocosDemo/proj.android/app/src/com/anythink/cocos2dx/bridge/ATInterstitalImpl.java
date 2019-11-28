package com.anythink.cocos2dx.bridge;

import android.content.Context;

import com.anythink.core.api.AdError;
import com.anythink.core.api.ATAdInfo;
import com.anythink.interstitial.api.ATInterstitial;
import com.anythink.interstitial.api.ATInterstitialListener;

public class ATInterstitalImpl {
    final String TAG = "ATInterstitalImpl";
    String mUnitId;
    ATInterstitial demoInterstitial;

    boolean mIsReady = false;

    public ATInterstitalImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(Context context) {
        demoInterstitial = new ATInterstitial(context, mUnitId);

        demoInterstitial.setAdListener(new ATInterstitialListener() {
            @Override
            public void onInterstitialAdLoaded() {
                LogUtils.i(TAG, "sdk onInterstitialAdLoaded");
                mIsReady = true;
                ATListenerEventJniHelper.onInterstitialAdLoaded(mUnitId);
            }

            @Override
            public void onInterstitialAdLoadFail(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdLoadFail");
                ATListenerEventJniHelper.onInterstitialAdLoadFail(mUnitId, pAdError.printStackTrace());
            }

            @Override
            public void onInterstitialAdClicked(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClicked");
                ATListenerEventJniHelper.onInterstitialAdClicked(mUnitId);
            }

            @Override
            public void onInterstitialAdShow(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdShow");
                mIsReady = false;
                ATListenerEventJniHelper.onInterstitialAdShow(mUnitId);

            }

            @Override
            public void onInterstitialAdClose(ATAdInfo adInfo) {
                LogUtils.i(TAG, "sdk onInterstitialAdClose");
                ATListenerEventJniHelper.onInterstitialAdClose(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoStart() {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoStart");
                ATListenerEventJniHelper.onInterstitialAdVideoStart(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoEnd() {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoEnd");
                ATListenerEventJniHelper.onInterstitialAdVideoEnd(mUnitId);
            }

            @Override
            public void onInterstitialAdVideoError(AdError pAdError) {
                LogUtils.i(TAG, "sdk onInterstitialAdVideoError");
                ATListenerEventJniHelper.onInterstitialAdVideoError(mUnitId, pAdError.printStackTrace());
            }
        });
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

    public void show() {
        if (demoInterstitial != null) {
            demoInterstitial.show();
        }
    }

}
