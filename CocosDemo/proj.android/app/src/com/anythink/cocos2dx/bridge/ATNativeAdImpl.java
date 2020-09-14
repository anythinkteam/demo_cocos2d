package com.anythink.cocos2dx.bridge;

import android.app.Activity;
import android.text.TextUtils;
import android.util.Log;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.anythink.cocos2dx.bridge.utils.ATUtils;
import com.anythink.cocos2dx.bridge.utils.Const;
import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.AdError;
import com.anythink.nativead.api.ATNative;
import com.anythink.nativead.api.ATNativeAdView;
import com.anythink.nativead.api.ATNativeDislikeListener;
import com.anythink.nativead.api.ATNativeEventListener;
import com.anythink.nativead.api.ATNativeNetworkListener;
import com.anythink.nativead.api.NativeAd;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Map;


public class ATNativeAdImpl {

    private static final String TAG = ATNativeAdImpl.class.getSimpleName();
    ATNative mATNative;
    String mPlacementId;

    ATNativeAdView mATNativeView;
    ViewInfo pViewInfo;

    public ATNativeAdImpl(String placementId) {
        mPlacementId = placementId;
    }

    public void loadAd(final Activity context, final Map<String, Object> localMap) {

        if (mATNative == null) {
            mATNative = new ATNative(context, mPlacementId, new ATNativeNetworkListener() {
                @Override
                public void onNativeAdLoaded() {
                    ATListenerEventJniHelper.onNativeAdLoaded(mPlacementId);
                }

                @Override
                public void onNativeAdLoadFail(AdError adError) {
                    ATListenerEventJniHelper.onNativeAdLoadFail(mPlacementId, adError.printStackTrace());
                }
            });
        }

        if (localMap != null) {//设置穿山甲广告大小
            try {
                if (localMap.containsKey(Const.WIDTH)) {
                    Object width = localMap.get(Const.WIDTH);
                    if (width != null) {
                        LogUtils.i(TAG, "native setLoalExtra  width: " + width);
                        localMap.put("key_width", width);
                        localMap.put("tt_image_width", width);
                        localMap.put("mintegral_auto_render_native_width", width);
                    }
                }
                if (localMap.containsKey(Const.HEIGHT)) {
                    Object height = localMap.get(Const.HEIGHT);
                    if (height != null) {
                        LogUtils.i(TAG, "native setLoalExtra  height: " + height);
                        localMap.put("key_height", height);
                        localMap.put("tt_image_height", height);
                        localMap.put("mintegral_auto_render_native_height", height);
                    }
                }
                mATNative.setLocalExtra(localMap);

            } catch (Throwable e) {
                e.printStackTrace();
            }
        }

        mATNative.makeAdRequest();
    }


    public boolean isAdReady() {
        if (mATNative != null) {
            return mATNative.getNativeAd() != null;
        }
        return false;
    }


    public void showAd(final Activity activity, final String json) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mATNative != null) {
                    NativeAd nativeAd = mATNative.getNativeAd();
                    if (nativeAd != null) {
                        parseViewInfo(activity, json);

                        if (mATNativeView != null && mATNativeView.getParent() != null) {
                            ((ViewGroup) mATNativeView.getParent()).removeView(mATNativeView);
                            mATNativeView = null;
                        }
                        mATNativeView = new ATNativeAdView(activity);
                        nativeAd.setNativeEventListener(new ATNativeEventListener() {
                            @Override
                            public void onAdImpressed(ATNativeAdView upArpuNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdShow(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                            }

                            @Override
                            public void onAdClicked(ATNativeAdView upArpuNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdClick(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
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

                        nativeAd.setDislikeCallbackListener(new ATNativeDislikeListener() {
                            @Override
                            public void onAdCloseButtonClick(ATNativeAdView atNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdCloseButtonTapped(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                            }
                        });
                    }

                    try {

                        ATNativeRender render = new ATNativeRender(activity, pViewInfo);
                        nativeAd.renderAdView(mATNativeView, render);

                        if (pViewInfo.adLogoView != null) {
                            FrameLayout.LayoutParams adLogoLayoutParams = new FrameLayout.LayoutParams(pViewInfo.adLogoView.mWidth, pViewInfo.adLogoView.mHeight);
                            adLogoLayoutParams.leftMargin = pViewInfo.adLogoView.mX;
                            adLogoLayoutParams.topMargin = pViewInfo.adLogoView.mY;
                            nativeAd.prepare(mATNativeView, adLogoLayoutParams);
                        } else {
                            nativeAd.prepare(mATNativeView);
                        }

                        ViewInfo.addNativeAdView2Activity(activity, pViewInfo, mATNativeView);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
            }
        });
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
                                ATListenerEventJniHelper.onNativeAdShow(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                            }

                            @Override
                            public void onAdClicked(ATNativeAdView upArpuNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdClick(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
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

                        nativeAd.setDislikeCallbackListener(new ATNativeDislikeListener() {
                            @Override
                            public void onAdCloseButtonClick(ATNativeAdView atNativeAdView, ATAdInfo adInfo) {
                                ATListenerEventJniHelper.onNativeAdCloseButtonTapped(mPlacementId, ATUtils.adInfoToJsonstring(adInfo));
                            }
                        });
                    }


                    try {


                        ATNativeRender render = new ATNativeRender(activity, pViewInfo);

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

    private ViewInfo parseViewInfo(Activity activity, String showConfig) {
        pViewInfo = new ViewInfo();

        if (TextUtils.isEmpty(showConfig)) {
            Log.e(TAG, "showConfig is null ,user defult");
            pViewInfo = ViewInfo.createDefualtView(activity);
        }

        try {
            JSONObject _jsonObject = new JSONObject(showConfig);

            if (_jsonObject.has(Const.parent)) {
                String tempjson = _jsonObject.getString(Const.parent);
                LogUtils.e(TAG, "parent----> " + tempjson);
                pViewInfo.rootView = pViewInfo.parseINFO(tempjson, "parent", 0, 0);
            }

            if (_jsonObject.has(Const.icon)) {
                String tempjson = _jsonObject.getString(Const.icon);
                LogUtils.e(TAG, "appIcon----> " + tempjson);
                pViewInfo.IconView = pViewInfo.parseINFO(tempjson, "appIcon", 0, 0);
            }

            if (_jsonObject.has(Const.mainImage)) {
                String tempjson = _jsonObject.getString(Const.mainImage);
                LogUtils.e(TAG, "mainImage----> " + tempjson);
                pViewInfo.imgMainView = pViewInfo.parseINFO(tempjson, "mainImage", 0, 0);

            }

            if (_jsonObject.has(Const.title)) {
                String tempjson = _jsonObject.getString(Const.title);
                LogUtils.e(TAG, "title----> " + tempjson);
                pViewInfo.titleView = pViewInfo.parseINFO(tempjson, "title", 0, 0);
            }

            if (_jsonObject.has(Const.desc)) {
                String tempjson = _jsonObject.getString(Const.desc);
                LogUtils.e(TAG, "desc----> " + tempjson);
                pViewInfo.descView = pViewInfo.parseINFO(tempjson, "desc", 0, 0);
            }

            if (_jsonObject.has(Const.adLogo)) {
                String tempjson = _jsonObject.getString(Const.adLogo);
                LogUtils.e(TAG, "adLogo----> " + tempjson);
                pViewInfo.adLogoView = pViewInfo.parseINFO(tempjson, "adLogo", 0, 0);
            }

            if (_jsonObject.has(Const.cta)) {
                String tempjson = _jsonObject.getString(Const.cta);
                LogUtils.e(TAG, "cta----> " + tempjson);
                pViewInfo.ctaView = pViewInfo.parseINFO(tempjson, "cta", 0, 0);
            }

        } catch (JSONException pE) {
            pE.printStackTrace();
        }
        return pViewInfo;
    }


}
