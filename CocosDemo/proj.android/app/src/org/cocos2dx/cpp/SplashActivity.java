package org.cocos2dx.cpp;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.anythink.core.api.AdError;
import com.anythink.core.api.ATAdInfo;
import com.anythink.splashad.api.ATSplashAd;
import com.anythink.splashad.api.ATSplashAdListener;

import org.cocos2dx.demo_cocos2d.R;


public class SplashActivity extends Activity implements ATSplashAdListener {
    TextView skipView;
    ATSplashAd splashAd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.demo_cocos2d_splash_ad_layout);

        FrameLayout container = findViewById(R.id.demo_cocos2d_splash_ad_container);
        skipView = findViewById(R.id.demo_cocos2d_splash_ad_skip);
        skipView.setVisibility(View.VISIBLE);

        splashAd = new ATSplashAd(this, container, skipView, "b5c4ad30cd359d", this);


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
    public void onAdShow(ATAdInfo adInfo) {
    }

    @Override
    public void onAdClick(ATAdInfo adInfo) {
    }

    @Override
    public void onAdDismiss(ATAdInfo adInfo) {
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
