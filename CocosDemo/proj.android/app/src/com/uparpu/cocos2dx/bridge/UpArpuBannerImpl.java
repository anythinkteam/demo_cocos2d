package com.uparpu.cocos2dx.bridge;

import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.uparpu.api.AdError;
import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.banner.api.UpArpuBannerListener;
import com.uparpu.banner.api.UpArpuBannerView;

public class UpArpuBannerImpl {
    private final String TAG = "UpArpuBannerImpl";

    UpArpuBannerView mBannerView;
    String mUnitId;
    boolean mIsAdReady;

    public UpArpuBannerImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(final Activity context) {
        if (mBannerView == null) {
            mBannerView = new UpArpuBannerView(context);
        }
        mBannerView.setUnitId(mUnitId);
        mBannerView.setBannerAdListener(new UpArpuBannerListener() {
            @Override
            public void onBannerLoaded() {
                mIsAdReady = true;
                UpArpuListenerEventJniHelper.onBannerLoaded(mUnitId);
            }

            @Override
            public void onBannerFailed(AdError adError) {
                UpArpuListenerEventJniHelper.onBannerFailed(mUnitId, adError.printStackTrace());
            }

            @Override
            public void onBannerClicked(UpArpuAdInfo adInfo) {
                UpArpuListenerEventJniHelper.onBannerClicked(mUnitId);
            }

            @Override
            public void onBannerShow(UpArpuAdInfo adInfo) {
                mIsAdReady = false;
                UpArpuListenerEventJniHelper.onBannerShow(mUnitId);
            }

            @Override
            public void onBannerClose() {
                UpArpuListenerEventJniHelper.onBannerClose(mUnitId);
            }

            @Override
            public void onBannerAutoRefreshed(UpArpuAdInfo adInfo) { UpArpuListenerEventJniHelper.onBannerAutoRefreshed(mUnitId);
            }

            @Override
            public void onBannerAutoRefreshFail(AdError adError) {
                UpArpuListenerEventJniHelper.onBannerAutoRefreshFail(mUnitId, adError.printStackTrace());
            }
        });
        mBannerView.loadAd();
    }


    public boolean isAdReady() {
        return mIsAdReady;
    }

    public void showAd(final Activity activity, final int left, final int top, final int width, final int height) {
        if (activity != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    synchronized (UpArpuBannerImpl.this) {
                        try {
                            if (mBannerView != null) {
                                FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(width, height);
                                layoutParams.leftMargin = left;
                                layoutParams.topMargin = top;
                                if (mBannerView.getParent() != null) {
                                    ((ViewGroup) mBannerView.getParent()).removeView(mBannerView);
                                }
                                activity.addContentView(mBannerView, layoutParams);
                                mBannerView.setVisibility(View.VISIBLE);
                            } else {
                                LogUtils.i(TAG, "show error  ..you must call initBanner first " + this);
                            }
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }

                }
            });
        }

    }

    public void removeAd() {
        synchronized (UpArpuBannerImpl.this) {
            if (mBannerView != null && mBannerView.getParent() != null) {
                ViewParent viewParent = mBannerView.getParent();
                ((ViewGroup) viewParent).removeView(mBannerView);
                mBannerView = null;
            }
        }
    }


}
