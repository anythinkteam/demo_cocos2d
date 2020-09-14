package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.graphics.Color;
import android.text.TextUtils;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.core.api.ATAdInfo;
import com.anythink.nativead.banner.api.ATNativeBannerConfig;
import com.anythink.nativead.banner.api.ATNativeBannerListener;
import com.anythink.nativead.banner.api.ATNativeBannerSize;
import com.anythink.nativead.banner.api.ATNativeBannerView;

import java.util.Map;

public class ATNativeBannerImpl {
    ATNativeBannerView mNativeBannerView;
    String mPlacementId;

    boolean mIsAdReady;

    public ATNativeBannerImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(final Activity activity) {
        loadAd(activity, null);
    }

    public void loadAd(final Activity activity, Map<String, Object> localMap) {
        synchronized (ATNativeBannerImpl.this) {


            if (mNativeBannerView == null) {
                mNativeBannerView = new ATNativeBannerView(activity);
            }
            mNativeBannerView.setUnitId(mPlacementId);
            mNativeBannerView.setAdListener(new ATNativeBannerListener() {
                @Override
                public void onAdLoaded() {
                    mIsAdReady = true;
                    ATListenerEventJniHelper.onNativeBannerAdLoaded(mPlacementId);
                }

                @Override
                public void onAdError(String adError) {
                    ATListenerEventJniHelper.onNativeBannerAdLoadFail(mPlacementId, adError);
                }

                @Override
                public void onAdClick(ATAdInfo adInfo) {
                    ATListenerEventJniHelper.onNativeBannerAdClick(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                }

                @Override
                public void onAdShow(ATAdInfo adInfo) {
                    ATListenerEventJniHelper.onNativeBannerAdShow(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                }

                @Override
                public void onAdClose() {
                    ATListenerEventJniHelper.onNativeBannerAdClose(mPlacementId, "");
                }

                @Override
                public void onAutoRefresh(ATAdInfo adInfo) {
                    ATListenerEventJniHelper.onNativeBannerAdAutoRefreshed(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                }

                @Override
                public void onAutoRefreshFail(String s) {
                    ATListenerEventJniHelper.onNativeBannerAdAutoRefreshFail(mPlacementId, s, "");
                }

            });
            if (localMap != null) {
                mNativeBannerView.setLocalExtra(localMap);
            }
            mNativeBannerView.loadAd(null);
        }
    }

    public boolean isAdReady() {
        return mIsAdReady;
    }

    public void showAd(Activity activity, Map<String, String> configMap, Map<String, String> extraMap) {
        synchronized (ATNativeBannerImpl.this) {

            ATNativeBannerConfig config = new ATNativeBannerConfig();

            try {
                String bgColor = extraMap.get("key_main_bg_color");
                if (!TextUtils.isEmpty(bgColor)) {
                    if (mNativeBannerView != null) {
                        mNativeBannerView.setBackgroundColor(Color.parseColor(bgColor));
                    }
                }

                String isShowCloseStr = configMap.get("key_button_close_status");
                if (!TextUtils.isEmpty(isShowCloseStr)) {
                    config.isCloseBtnShow = Boolean.parseBoolean(isShowCloseStr);
                }

                String ctaBgColorStr = extraMap.get("key_button_cta_bg");
                if (!TextUtils.isEmpty(ctaBgColorStr)) {
                    config.ctaBgColor = Color.parseColor(ctaBgColorStr);
                }

                String ctaTitleColorStr = extraMap.get("key_button_cta_title_color");
                if (!TextUtils.isEmpty(ctaTitleColorStr)) {
                    config.ctaColor = Color.parseColor(ctaTitleColorStr);
                }

                String adTitleColor = extraMap.get("key_title_color");
                if (!TextUtils.isEmpty(adTitleColor)) {
                    config.titleColor = Color.parseColor(adTitleColor);
                }

                String adDescColor = extraMap.get("key_text_color");
                if (!TextUtils.isEmpty(adDescColor)) {
                    config.descColor = Color.parseColor(adDescColor);
                }

                String interval = extraMap.get("key_refresh_intervel");
                if (!TextUtils.isEmpty(interval)) {
                    config.refreshTime = Long.parseLong(interval);
                }

                String bannerSizeStr = extraMap.get("key_banner_size_type");
                if (!TextUtils.isEmpty(bannerSizeStr)) {
                    int bannerSize = Integer.parseInt(bannerSizeStr);
                    if (bannerSize == 1) {
                        config.bannerSize = ATNativeBannerSize.BANNER_SIZE_320x50;
                    } else if (bannerSize == 2) {
                        config.bannerSize = ATNativeBannerSize.BANNER_SIZE_640x150;
                    } else {
                        config.bannerSize = ATNativeBannerSize.BANNER_SIZE_AUTO;
                    }
                }

                String isShowCtaStr = extraMap.get("key_is_show_cta");

                if (!TextUtils.isEmpty(isShowCtaStr)) {
                    config.isCtaBtnShow = Boolean.parseBoolean(isShowCtaStr);
                }


            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                int x = Integer.parseInt(configMap.get("x"));
                int y = Integer.parseInt(configMap.get("y"));
                int w = Integer.parseInt(configMap.get("width"));
                int h = Integer.parseInt(configMap.get("height"));


                if (mNativeBannerView != null) {
                    FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(w, h);
                    layoutParams.leftMargin = x;
                    layoutParams.topMargin = y;

                    mNativeBannerView.setBannerConfig(config);
                    if (mNativeBannerView.getParent() != null) {
                        ((ViewGroup) mNativeBannerView.getParent()).removeView(mNativeBannerView);
                    }
                    activity.findViewById(android.R.id.content);
                    activity.addContentView(mNativeBannerView, layoutParams);
                } else {
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }


    }

    public void removeAd() {
        synchronized (ATNativeBannerImpl.this) {
            if (mNativeBannerView != null && mNativeBannerView.getParent() != null) {
                ViewParent viewParent = mNativeBannerView.getParent();
                ((ViewGroup) viewParent).removeView(mNativeBannerView);
                mNativeBannerView = null;
            }
        }
    }
}
