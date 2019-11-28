package com.uparpu.cocos2dx.bridge;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.uparpu.cocos2dx.bridge.utils.image.CommonImageLoader;
import com.uparpu.nativead.api.UpArpuNativeAdRenderer;
import com.uparpu.nativead.unitgroup.api.CustomNativeAd;

import org.cocos2dx.up_sdk_cocos.R;


/**
 * Copyright (C) 2018 {XX} Science and Technology Co., Ltd.
 *
 * @version V{XX_XX}
 */
public class UpArpuNativeRender implements UpArpuNativeAdRenderer<CustomNativeAd> {

    Activity mActivity;

    public UpArpuNativeRender(Activity pActivity) {
        mActivity = pActivity;
    }


    @Override
    public View createView(Context context, int networkType) {
        return LayoutInflater.from(context).inflate(R.layout.uparpu_cocos2d_native_ad_item, null);
    }

    @Override
    public void renderAdView(View view, CustomNativeAd ad) {

        TextView titleView = (TextView) view.findViewById(R.id.native_ad_title);
        TextView descView = (TextView) view.findViewById(R.id.native_ad_desc);
        TextView ctaView = (TextView) view.findViewById(R.id.native_ad_install_btn);
        TextView adFromView = (TextView) view.findViewById(R.id.native_ad_from);

        FrameLayout contentArea = (FrameLayout) view.findViewById(R.id.native_ad_content_image_area);
        View mediaView = ad.getAdMediaView(contentArea, contentArea.getWidth());
        View adiconView = ad.getAdIconView();

        FrameLayout iconArea = (FrameLayout) view.findViewById(R.id.native_ad_image);
        final RecycleImageView iconView = new RecycleImageView(mActivity);
        iconView.setImageDrawable(null);
        if (adiconView == null) {
            iconArea.addView(iconView);
            CommonImageLoader.getInstance().startLoadImage(ad.getIconImageUrl(), 0, new CommonImageLoader.ImageCallback() {
                @Override
                public void onSuccess(Bitmap bitmap, String url) {
                    iconView.setImageBitmap(bitmap);
                }

                @Override
                public void onFail() {

                }
            });
        } else {
            iconArea.addView(adiconView);
        }


        final RecycleImageView logoView = (RecycleImageView) view.findViewById(R.id.native_ad_logo);
        if (!TextUtils.isEmpty(ad.getAdChoiceIconUrl())) {
            logoView.setVisibility(View.VISIBLE);
            CommonImageLoader.getInstance().startLoadImage(ad.getAdChoiceIconUrl(), 0, new CommonImageLoader.ImageCallback() {
                @Override
                public void onSuccess(Bitmap bitmap, String url) {
                    logoView.setImageBitmap(bitmap);
                }

                @Override
                public void onFail() {

                }
            });
        } else {
            logoView.setVisibility(View.GONE);
        }


        contentArea.removeAllViews();
        if (mediaView != null) {
            contentArea.addView(mediaView, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));

        } else {

            final RecycleImageView imageView = new RecycleImageView(mActivity);

            CommonImageLoader.getInstance().startLoadImage(ad.getMainImageUrl(), 0, new CommonImageLoader.ImageCallback() {
                @Override
                public void onSuccess(Bitmap bitmap, String url) {
                    imageView.setImageBitmap(bitmap);
                }

                @Override
                public void onFail() {

                }
            });

            ViewGroup.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT);
            imageView.setLayoutParams(params);
            contentArea.addView(imageView, params);

        }

        titleView.setText(ad.getTitle());
        descView.setText(ad.getDescriptionText());
        ctaView.setText(ad.getCallToActionText());
        if (!TextUtils.isEmpty(ad.getAdFrom())) {
            adFromView.setText(ad.getAdFrom() != null ? ad.getAdFrom() : "");
            adFromView.setVisibility(View.VISIBLE);
        } else {
            adFromView.setVisibility(View.GONE);
        }


    }
}
