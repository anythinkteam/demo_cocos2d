package com.anythink.cocos2dx.bridge.utils;

import com.anythink.core.api.ATAdInfo;

import org.json.JSONException;
import org.json.JSONObject;

public class ATUtils {
    public static String adInfoToJsonstring(ATAdInfo adInfo){
        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put("network_firm_id", adInfo.getNetworkType());
            jsonObject.put("ad_source_id", adInfo.getAdsourceId());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return jsonObject.toString();

    }
}
