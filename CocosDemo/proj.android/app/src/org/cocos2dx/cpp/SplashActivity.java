package org.cocos2dx.cpp;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.uparpu.api.AdError;
import com.uparpu.api.UpArpuAdInfo;
import com.uparpu.splashad.api.UpArpuSplashAd;
import com.uparpu.splashad.api.UpArpuSplashAdListener;

import org.cocos2dx.up_sdk_cocos.R;

public class SplashActivity extends Activity implements UpArpuSplashAdListener {
    TextView skipView;
    UpArpuSplashAd splashAd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.uparpu_cocos2d_splash_ad_layout);

        FrameLayout container = findViewById(R.id.uparpu_cocos2d_splash_ad_container);
        skipView = findViewById(R.id.uparpu_cocos2d_splash_ad_skip);
        skipView.setVisibility(View.VISIBLE);

        splashAd = new UpArpuSplashAd(this, container, skipView, "b5c4ad30cd359d", this);


    }

    @Override
    public void onAdLoaded() {
        skipView.setVisibility(View.VISIBLE);
        skipView.setBackgroundColor(0x88000000);
    }

    @Override
    public void onNoAdError(AdError adError) {
        finish();
    }

    @Override
    public void onAdShow(UpArpuAdInfo adInfo) {
    }

    @Override
    public void onAdClick(UpArpuAdInfo adInfo) {
    }

    @Override
    public void onAdDismiss(UpArpuAdInfo adInfo) {
        finish();
    }

    @Override
    public void onAdTick(long millisUtilFinished) {
        skipView.setVisibility(View.VISIBLE);
        skipView.setText(String.valueOf(millisUtilFinished / 1000) + "| SKIP");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (splashAd != null) {
            splashAd.onDestory();
        }

    }
}
