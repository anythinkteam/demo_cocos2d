package com.uparpu.cocos2dx.bridge;

import android.app.Activity;
import android.graphics.Color;
import android.text.TextUtils;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.nativead.banner.api.UpArpuNaitveBannerListener;
import com.uparpu.nativead.banner.api.UpArpuNaitveBannerSize;
import com.uparpu.nativead.banner.api.UpArpuNativeBannerConfig;
import com.uparpu.nativead.banner.api.UpArpuNativeBannerView;

import java.util.Map;

public class UpArpuNativeBannerImpl {
    UpArpuNativeBannerView mNativeBannerView;
    String mUnitId;

    boolean mIsAdReady;

    public UpArpuNativeBannerImpl(String unitId) {
        mUnitId = unitId;
    }

    public void loadAd(final Activity activity) {
        synchronized (UpArpuNativeBannerImpl.this) {


            if (mNativeBannerView == null) {
                mNativeBannerView = new UpArpuNativeBannerView(activity);
            }
            mNativeBannerView.setUnitId(mUnitId);
            mNativeBannerView.setAdListener(new UpArpuNaitveBannerListener() {
                @Override
                public void onAdLoaded() {
                    mIsAdReady = true;
                    UpArpuListenerEventJniHelper.onNativeBannerAdLoaded(mUnitId);
                }

                @Override
                public void onAdError(String adError) {
                    UpArpuListenerEventJniHelper.onNativeBannerAdLoadFail(mUnitId, adError);
                }

                @Override
                public void onAdClick(UpArpuAdInfo adInfo) {
                    UpArpuListenerEventJniHelper.onNativeBannerAdClick(mUnitId);
                }

                @Override
                public void onAdShow(UpArpuAdInfo adInfo) {
                    UpArpuListenerEventJniHelper.onNativeBannerAdShow(mUnitId);
                }

                @Override
                public void onAdClose() {
                    UpArpuListenerEventJniHelper.onNativeBannerAdClose(mUnitId);
                }

                @Override
                public void onAutoRefresh(UpArpuAdInfo adInfo) {
                    UpArpuListenerEventJniHelper.onNativeBannerAdAutoRefreshed(mUnitId);
                }

                @Override
                public void onAutoRefreshFail(String s) {
                    UpArpuListenerEventJniHelper.onNativeBannerAdAutoRefreshFail(mUnitId, s);
                }

            });
            mNativeBannerView.loadAd(null);
        }
    }

    public boolean isAdReady() {
        return mIsAdReady;
    }

    public void showAd(Activity activity, Map<String, String> configMap, Map<String,String> extraMap) {
        synchronized (UpArpuNativeBannerImpl.this) {

            UpArpuNativeBannerConfig config = new UpArpuNativeBannerConfig();

            try {
                String bgColor = extraMap.get("key_main_bg_color");
                if (!TextUtils.isEmpty(bgColor)) {
                    if(mNativeBannerView != null){
                        mNativeBannerView.setBackgroundColor(Color.parseColor(bgColor));
                    }
                }

                String isShowCloseStr = configMap.get("key_button_close_status");
                if(!TextUtils.isEmpty(isShowCloseStr)){
                    config.isCloseBtnShow = Boolean.parseBoolean(isShowCloseStr);
                }

                String ctaBgColorStr = extraMap.get("key_button_cta_bg");
                if(!TextUtils.isEmpty(ctaBgColorStr)){
                    config.ctaBgColor = Color.parseColor(ctaBgColorStr);
                }

                String ctaTitleColorStr = extraMap.get("key_button_cta_title_color");
                if (!TextUtils.isEmpty(ctaTitleColorStr)) {
                    config.ctaColor = Color.parseColor(ctaTitleColorStr);
                }

                String adTitleColor = extraMap.get("key_title_color");
                if(!TextUtils.isEmpty(adTitleColor)){
                    config.titleColor = Color.parseColor(adTitleColor);
                }

                String adDescColor = extraMap.get("key_text_color");
                if(!TextUtils.isEmpty(adDescColor)){
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
                        config.bannerSize = UpArpuNaitveBannerSize.BANNER_SIZE_320x50;
                    } else if (bannerSize == 2) {
                        config.bannerSize = UpArpuNaitveBannerSize.BANNER_SIZE_640x150;
                    } else {
                        config.bannerSize = UpArpuNaitveBannerSize.BANNER_SIZE_AUTO;
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
                int w = Integer.parseInt(configMap.get("w"));
                int h = Integer.parseInt(configMap.get("h"));


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
        synchronized (UpArpuNativeBannerImpl.this) {
            if (mNativeBannerView != null && mNativeBannerView.getParent() != null) {
                ViewParent viewParent = mNativeBannerView.getParent();
                ((ViewGroup) viewParent).removeView(mNativeBannerView);
                mNativeBannerView = null;
            }
        }
    }
}
