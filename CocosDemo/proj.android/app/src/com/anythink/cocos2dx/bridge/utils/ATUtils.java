package com.anythink.cocos2dx.bridge.utils;

import com.anythink.core.api.ATAdInfo;

import org.json.JSONException;
import org.json.JSONObject;

public class ATUtils {
    public static String adInfoToJsonstring(ATAdInfo adInfo){
        return adInfo.toString();
    }
}
