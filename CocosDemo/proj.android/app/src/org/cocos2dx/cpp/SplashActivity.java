package org.cocos2dx.cpp;

import android.app.Activity;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.anythink.core.api.ATAdInfo;
import com.anythink.core.api.ATSDK;
import com.anythink.core.api.AdError;
import com.anythink.splashad.api.ATSplashAd;
import com.anythink.splashad.api.ATSplashAdListener;

import org.cocos2dx.demo_cocos2d.R;


public class SplashActivity extends Activity implements ATSplashAdListener {
    ATSplashAd splashAd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.demo_cocos2d_splash_ad_layout);

        if (ATSDK.isChinaSDK()) {
            FrameLayout container = findViewById(R.id.splash_ad_container);
            ViewGroup.LayoutParams layoutParams = container.getLayoutParams();
            /**You should set size to the layout param.**/
            layoutParams.width = getResources().getDisplayMetrics().widthPixels;
            layoutParams.height = (int) (getResources().getDisplayMetrics().heightPixels * 0.85);


            splashAd = new ATSplashAd(this, container, "b5c05090192a58", this);//baidu
//        splashAd = new ATSplashAd(this, container, "b5d76150bab3ad", this);//Sigmob
//        splashAd = new ATSplashAd(this, container, "b5bea7c1b653ef", this);//头条
//        splashAd = new ATSplashAd(this, container, "b5bea7bfd93f01", this);//GDT
        } else {
            jumpToMainActivity();
        }


    }

    @Override
    public void onAdLoaded() {
        Log.i("SplashAdShowActivity", "onAdLoaded---------");
    }

    @Override
    public void onNoAdError(AdError adError) {
        Log.i("SplashAdShowActivity", "onNoAdError---------:" + adError.printStackTrace());
        jumpToMainActivity();
    }

    @Override
    public void onAdShow(ATAdInfo entity) {
        Log.i("SplashAdShowActivity", "onAdShow:\n" + entity.toString());
        if (entity.getNetworkFirmId() == 22) {
            /**
             * Only for Baidu:
             * The display time and the skipped advertising style can be configured through the Baidu's backstage（Recommend）
             * , and can be customized and modified in your application.
             */
            skipViewSetting(); //If setting skipview by Baidu's backstage, you should not run this method.
        }
    }

    private void skipViewSetting() {
        final TextView skipView = findViewById(R.id.splash_ad_skip);
        CountDownTimer countDownTimer = new CountDownTimer(5000L, 1000L) {
            @Override
            public void onTick(long millisUntilFinished) {
                skipView.setText((millisUntilFinished / 1000) + " | 跳过");
            }

            @Override
            public void onFinish() {
                jumpToMainActivity();
            }
        };

        countDownTimer.start();
        skipView.setVisibility(View.VISIBLE);

        skipView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jumpToMainActivity();
            }
        });
    }

    @Override
    public void onAdClick(ATAdInfo entity) {
        Log.i("SplashAdShowActivity", "onAdClick:\n" + entity.toString());
    }

    @Override
    public void onAdDismiss(ATAdInfo entity) {
        Log.i("SplashAdShowActivity", "onAdDismiss:\n" + entity.toString());
        jumpToMainActivity();
    }

    @Override
    public void onAdTick(long millisUtilFinished) {
        Log.i("SplashAdShowActivity", "onAdTick---------：" + millisUtilFinished);
    }

    boolean hasHandleJump = false;

    public void jumpToMainActivity() {
        if (!hasHandleJump) {
            hasHandleJump = true;
            finish();
            Toast.makeText(this, "start your MainActivity.", Toast.LENGTH_SHORT).show();
        }

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (splashAd != null) {
            splashAd.onDestory();
        }

    }
}
