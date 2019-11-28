package com.anythink.cocos2dx.bridge;

import android.util.Log;

public class LogUtils {
    public static boolean isDebug = false;

    public static void i(String tag, String msg) {
        if (isDebug) {
            Log.i(tag, msg);
        }
    }

    public static void e(String tag, String msg) {
        if (isDebug) {
            Log.e(tag, msg);
        }
    }

}
