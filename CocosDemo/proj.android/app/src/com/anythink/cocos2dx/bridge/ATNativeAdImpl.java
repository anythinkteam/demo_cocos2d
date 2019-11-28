package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.anythink.core.api.AdError;
import com.anythink.core.api.ATAdInfo;
import com.anythink.nativead.api.NativeAd;
import com.anythink.nativead.api.ATNative;
import com.anythink.nativead.api.ATNativeAdView;
import com.anythink.nativead.api.ATNativeEventListener;
import com.anythink.nativead.api.ATNativeNetworkListener;

import java.util.Map;


public class ATNativeAdImpl {
    ATNative mATNative;
    String mUnitId;

    ATNativeAdView mATNativeView;

    public ATNativeAdImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(final Activity context, final Map<String, Object> localMap) {

        if (mATNative == null) {
            mATNative = new ATNative(context.getApplicationContext(), mUnitId, new ATNativeNetworkListener() {
                @Override
                public void onNativeAdLoaded() {
                    ATListenerEventJniHelper.onNativeAdLoaded(mUnitId);
                }

                @Override
                public void onNativeAdLoadFail(AdError adError) {
                    ATListenerEventJniHelper.onNativeAdLoadFail(mUnitId, adError.printStackTrace());
                }
            });
        }

        mATNative.setLocalExtra(localMap);

        mATNative.makeAdRequest();
    }


    public boolean isAdReady() {
        if (mATNative != null) {
            return mATNative.getNativeAd() != null;
        }
        return false;
    }

    public void showAd(final Activity activity, final int x, final int y, final int width, final int height) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mATNative != null) {
                    NativeAd nativeAd = mATNative.getNativeAd();
                    if (nativeAd != null) {
                        if (mATNativeView != null && mATNativeView.getParent() != null) {
                            ((ViewGroup) mATNativeView.getParent()).removeView(mATNativeView);
                            mATNativeView = null;
                        }
                        mATNativeView = new ATNativeAdView(activity);
                        nativeAd.setNativeEventListener(new ATNativeEventListener() {
                            @Override
                            public void onAdImpressed(ATNativeAdView upArpuNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdShow(mUnitId);
                            }

                            @Override
                            public void onAdClicked(ATNativeAdView upArpuNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdClick(mUnitId);
                            }

                            @Override
                            public void onAdVideoStart(ATNativeAdView upArpuNativeAdView) {
                            }

                            @Override
                            public void onAdVideoEnd(ATNativeAdView upArpuNativeAdView) {
                            }

                            @Override
                            public void onAdVideoProgress(ATNativeAdView upArpuNativeAdView, int i) {
                            }
                        });
                    }


                    try {


                        ATNativeRender render = new ATNativeRender(activity);

                        nativeAd.renderAdView(mATNativeView, render);
                        nativeAd.prepare(mATNativeView);

                        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(width, height);
                        layoutParams.leftMargin = x;
                        layoutParams.topMargin = y;

                        activity.addContentView(mATNativeView, layoutParams);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
            }
        });
    }

    public void removeAd() {
        if (mATNativeView != null && mATNativeView.getParent() != null) {
            ViewParent viewParent = mATNativeView.getParent();
            ((ViewGroup) viewParent).removeView(mATNativeView);
        }

    }


}
