package com.anythink.cocos2dx.bridge.utils;

import android.content.Context;

import org.json.JSONObject;

import java.util.Iterator;
import java.util.Map;

public class CommonUtil {

    /**
     * 将dip或dp值转换为px值，保证尺寸大小不变
     *
     * @param dipValue （DisplayMetrics类中属性density）
     * @return
     */
    public static int dip2px(Context context, float dipValue) {
        float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dipValue * scale + 0.5f);
    }

    public static void fillMapFromJsonObject(Map<String, Object> localExtra, JSONObject jsonObject) {
        try {
            Iterator<String> keys = jsonObject.keys();
            String key;
            while (keys.hasNext()) {
                key = keys.next();
                Object value = jsonObject.opt(key);
                localExtra.put(key, value);
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }
}
