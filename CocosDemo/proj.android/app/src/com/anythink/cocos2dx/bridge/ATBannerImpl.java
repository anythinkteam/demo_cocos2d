package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.anythink.banner.api.ATBannerListener;
import com.anythink.banner.api.ATBannerView;
import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.cocos2dx.bridge.utils.CommonUtil;
import com.anythink.cocos2dx.bridge.utils.Const;
import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.AdError;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class ATBannerImpl {
    private final String TAG = "ATBannerImpl";

    ATBannerView mBannerView;
    String mPlacementId;
    boolean mIsAdReady;

    public ATBannerImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(final Activity context, String extra) {
        if (mBannerView == null) {
            mBannerView = new ATBannerView(context);
        }
        mBannerView.setPlacementId(mPlacementId);
        mBannerView.setBannerAdListener(new ATBannerListener() {
            @Override
            public void onBannerLoaded() {
                mIsAdReady = true;
                ATListenerEventJniHelper.onBannerLoaded(mPlacementId);
            }

            @Override
            public void onBannerFailed(AdError adError) {
                ATListenerEventJniHelper.onBannerFailed(mPlacementId, adError.printStackTrace());
            }

            @Override
            public void onBannerClicked(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onBannerClicked(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerShow(ATAdInfo adInfo) {
                mIsAdReady = false;
                ATListenerEventJniHelper.onBannerShow(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerClose(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onBannerClose(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerAutoRefreshed(ATAdInfo adInfo) {
                ATListenerEventJniHelper.onBannerAutoRefreshed(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
            }

            @Override
            public void onBannerAutoRefreshFail(AdError adError) {
                ATListenerEventJniHelper.onBannerAutoRefreshFail(mPlacementId, adError.printStackTrace(), "");
            }
        });

        if (!TextUtils.isEmpty(extra)) {//针对 穿山甲第一次banner尺寸不对
            try {
                LogUtils.i(TAG, "loadBanner, placementId: " + mPlacementId + ", extra: " + extra);
                JSONObject jsonObject = new JSONObject(extra);
                int width = 0;
                int height = 0;
                if (jsonObject.has(Const.WIDTH)) {
                    width = jsonObject.optInt(Const.WIDTH);
                }
                if (jsonObject.has(Const.HEIGHT)) {
                    height = jsonObject.optInt(Const.HEIGHT);
                }

                if (mBannerView != null) {
                    LogUtils.i(TAG, "loadBanner, width: " + width + ", height: " + height);
                    if (mBannerView.getLayoutParams() == null) {
                        FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(width, height);
                        mBannerView.setLayoutParams(lp);
                    } else {
                        mBannerView.getLayoutParams().width = width;
                        mBannerView.getLayoutParams().height = height;
                    }
                }

                Map<String, Object> localExtra = new HashMap<>();
                if (jsonObject.has("inline_adaptive_width")) {
                    int inline_adaptive_width = Integer.parseInt(jsonObject.get("inline_adaptive_width").toString());
                    LogUtils.i(TAG, "inline_adaptive_width: " + inline_adaptive_width);
                    localExtra.put("inline_adaptive_width", inline_adaptive_width);
                }
                if (jsonObject.has("inline_adaptive_orientation")) {
                    int inline_adaptive_orientation = Integer.parseInt(jsonObject.get("inline_adaptive_orientation").toString());
                    LogUtils.i(TAG, "inline_adaptive_orientation: " + inline_adaptive_orientation);
                    localExtra.put("inline_adaptive_orientation", inline_adaptive_orientation);
                }

                if (!jsonObject.has("adaptive_type")) {
                    localExtra.put("adaptive_type", 0);
                }

                CommonUtil.fillMapFromJsonObject(localExtra, jsonObject);

                mBannerView.setLocalExtra(localExtra);
            } catch (Throwable e) {
                e.printStackTrace();
            }
            mBannerView.loadAd();
        }
    }

    public boolean isAdReady() {
        return mIsAdReady;
    }

    public void showAd(final Activity activity, final int left, final int top,
                       final int width, final int height) {
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

    public void showAd(final Activity activity, final String position) {
        if (activity != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    synchronized (ATBannerImpl.this) {
                        try {
                            if (mBannerView != null) {
                                int width = 0;
                                int height = 0;
                                if (mBannerView.getLayoutParams() != null) {
                                    width = mBannerView.getLayoutParams().width;
                                    height = mBannerView.getLayoutParams().height;
                                }
                                FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(width, height);

                                if (layoutParams != null) {
                                    if (Const.BANNER_POSITION_TOP.equals(position)) {
                                        layoutParams.gravity = Gravity.CENTER_HORIZONTAL | Gravity.TOP;
                                    } else {
                                        layoutParams.gravity = Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM;
                                    }
                                    if (mBannerView.getParent() != null) {
                                        ((ViewGroup) mBannerView.getParent()).removeView(mBannerView);
                                    }
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
