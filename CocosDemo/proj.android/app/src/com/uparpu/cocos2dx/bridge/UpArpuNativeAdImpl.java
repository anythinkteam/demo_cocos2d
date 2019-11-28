package com.uparpu.cocos2dx.bridge;

import android.app.Activity;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.uparpu.api.AdError;
import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.nativead.api.NativeAd;
import com.uparpu.nativead.api.UpArpuNative;
import com.uparpu.nativead.api.UpArpuNativeAdView;
import com.uparpu.nativead.api.UpArpuNativeEventListener;
import com.uparpu.nativead.api.UpArpuNativeNetworkListener;

import java.util.Map;


public class UpArpuNativeAdImpl {
    UpArpuNative mUpArpuNative;
    String mUnitId;

    UpArpuNativeAdView mUpArpuNativeView;

    public UpArpuNativeAdImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(final Activity context, final Map<String, Object> localMap) {

        if (mUpArpuNative == null) {
            mUpArpuNative = new UpArpuNative(context.getApplicationContext(), mUnitId, new UpArpuNativeNetworkListener() {
                @Override
                public void onNativeAdLoaded() {
                    UpArpuListenerEventJniHelper.onNativeAdLoaded(mUnitId);
                }

                @Override
                public void onNativeAdLoadFail(AdError adError) {
                    UpArpuListenerEventJniHelper.onNativeAdLoadFail(mUnitId, adError.printStackTrace());
                }
            });
        }

        mUpArpuNative.setLocalExtra(localMap);

        mUpArpuNative.makeAdRequest();
    }


    public boolean isAdReady() {
        if (mUpArpuNative != null) {
            return mUpArpuNative.getNativeAd() != null;
        }
        return false;
    }

    public void showAd(final Activity activity, final int x, final int y, final int width, final int height) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mUpArpuNative != null) {
                    NativeAd nativeAd = mUpArpuNative.getNativeAd();
                    if (nativeAd != null) {
                        if (mUpArpuNativeView != null && mUpArpuNativeView.getParent() != null) {
                            ((ViewGroup) mUpArpuNativeView.getParent()).removeView(mUpArpuNativeView);
                            mUpArpuNativeView = null;
                        }
                        mUpArpuNativeView = new UpArpuNativeAdView(activity);
                        nativeAd.setNativeEventListener(new UpArpuNativeEventListener() {
                            @Override
                            public void onAdImpressed(UpArpuNativeAdView upArpuNativeAdView, UpArpuAdInfo adInfo) {
                                UpArpuListenerEventJniHelper.onNativeAdShow(mUnitId);
                            }

                            @Override
                            public void onAdClicked(UpArpuNativeAdView upArpuNativeAdView, UpArpuAdInfo adInfo) {
                                UpArpuListenerEventJniHelper.onNativeAdClick(mUnitId);
                            }

                            @Override
                            public void onAdVideoStart(UpArpuNativeAdView upArpuNativeAdView) {
                            }

                            @Override
                            public void onAdVideoEnd(UpArpuNativeAdView upArpuNativeAdView) {
                            }

                            @Override
                            public void onAdVideoProgress(UpArpuNativeAdView upArpuNativeAdView, int i) {
                            }
                        });
                    }


                    try {


                        UpArpuNativeRender render = new UpArpuNativeRender(activity);

                        nativeAd.renderAdView(mUpArpuNativeView, render);
                        nativeAd.prepare(mUpArpuNativeView);

                        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(width, height);
                        layoutParams.leftMargin = x;
                        layoutParams.topMargin = y;

                        activity.addContentView(mUpArpuNativeView, layoutParams);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
            }
        });
    }

    public void removeAd() {
        if (mUpArpuNativeView != null && mUpArpuNativeView.getParent() != null) {
            ViewParent viewParent = mUpArpuNativeView.getParent();
            ((ViewGroup) viewParent).removeView(mUpArpuNativeView);
        }

    }


}
