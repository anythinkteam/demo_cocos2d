package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.core.api.AdError;
import com.anythink.core.api.ATAdInfo;
import com.anythink.banner.api.ATBannerListener;
import com.anythink.banner.api.ATBannerView;

public class ATBannerImpl {
    private final String TAG = "ATBannerImpl";

    ATBannerView mBannerView;
    String mUnitId;
    boolean mIsAdReady;

    public ATBannerImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(final Activity context) {
        if (mBannerView == null) {
            mBannerView = new ATBannerView(context);
        }
        mBannerView.setUnitId(mUnitId);
        mBannerView.setBannerAdListener(new ATBannerListener() {
            @Override
            public void onBannerLoaded() {
                mIsAdReady = true;
                ATListenerEventJniHelper.onBannerLoaded(mUnitId);
            }

            @Override
            public void onBannerFailed(AdError adError) {
                ATListenerEventJniHelper.onBannerFailed(mUnitId, adError.printStackTrace());
            }

            @Override
            public void onBannerClicked(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onBannerClicked(mUnitId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerShow(ATAdInfo adInfo) {
                mIsAdReady = false;
                ATListenerEventJniHelper.onBannerShow(mUnitId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerClose() {
                ATListenerEventJniHelper.onBannerClose(mUnitId, "");
            }

            @Override
            public void onBannerAutoRefreshed(ATAdInfo adInfo) { ATListenerEventJniHelper.onBannerAutoRefreshed(mUnitId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerAutoRefreshFail(AdError adError) {
                ATListenerEventJniHelper.onBannerAutoRefreshFail(mUnitId, adError.printStackTrace(), "");
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
                    synchronized (ATBannerImpl.this) {
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
        synchronized (ATBannerImpl.this) {
            if (mBannerView != null && mBannerView.getParent() != null) {
                ViewParent viewParent = mBannerView.getParent();
                ((ViewGroup) viewParent).removeView(mBannerView);
                mBannerView = null;
            }
        }
    }


}
