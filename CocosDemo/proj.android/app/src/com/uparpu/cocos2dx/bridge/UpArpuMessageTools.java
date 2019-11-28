package com.uparpu.cocos2dx.bridge;//package com.uparpu.cocos2d;
//
//import android.app.AlertDialog;
//import android.content.Context;
//import android.os.Handler;
//import android.os.Message;
//import android.util.Log;
//import android.widget.Toast;
//
//import com.uparpu.api.AdError;
//
//import org.json.JSONObject;
//
//
///**
// * Copyright (C) 2018 {XX} Science and Technology Co., Ltd.
// * 这里只是发一些消息或者有什么回到信息调用一下  提供给C层反射调用
// * @version V{XX_XX}
// * @Author ：Created by zhoushubin on 2018/11/8.
// * @Email: zhoushubin@salmonads.com
// * @since
// */
//public class UparpuMessageTools {
//    private static Context sContext;
//    private static String TAG = "UparpuMessageTools";
//
//    public static void init(Context pContext){
//        sContext = pContext;
//    };
//
//    private static Handler sHandler =new Handler()
//    {
//        @Override
//        public void handleMessage(Message msg)
//        {
//            //接受消息然后去做相应的事情
//            if(msg.what == 999)
//            {
//                Log.d(TAG, String.valueOf(msg.obj));  //获取到Handler传递的参数数据
//                AlertDialog.Builder builder = new AlertDialog.Builder(sContext);
//                builder.setTitle("message");
//                builder.setMessage(msg.obj.toString());
//                builder.show();
//            }
//            if(msg.what == 888)
//            {
//                Log.d(TAG, String.valueOf(msg.obj));  //获取到Handler传递的参数数据
//                Toast.makeText(sContext,msg.obj.toString(),Toast.LENGTH_SHORT).show();
//            }
//            super.handleMessage(msg);
//        }
//    };
//
//    public static void showDialog(String msgStr){
//        Log.i(TAG,"showDialog");
//        //抛出Message
//        Message msg = new Message();
//        msg.what = 999;
//        msg.obj = " "+msgStr;
//        sHandler.sendMessage(msg);
//
//    }
//
//
//
//    public static void showToast(String msgStr){
//        Log.i(TAG,"showToast");
//        //抛出Message
//        Message msg = new Message();
//        msg.what = 888;
//        msg.obj = " "+msgStr;
//        sHandler.sendMessage(msg);
//
//    }
//
//    public static ParseAdErrorInterface getDefParseAdErrorInterfaceImpl(){
//        return sDefParseAdErrorInterface;
//    }
//    private   static ParseAdErrorInterface sDefParseAdErrorInterface = new ParseAdErrorInterface(){
//
//        @Override
//        public String parse(String msg, Object pObject,String key) {
//            JSONObject   _jsonObject = new JSONObject();
//            try {
//                //这里是回调接口参数 解析用的 msg ；可能是APPID,UNITYD等  pObject 可能是一个基本基础类型或者AdError
//                //在这里转换下 成String 到NATIVE层 可以根据这里对的规则进行转换 返回对的参数就是UparpuListenerEventJniHelper里面方法的参数
//                //开发者可以在这里封装自己合适的字符串拼接风格
//                _jsonObject.put("id", msg);
//                if (pObject != null) {
//                    if (pObject instanceof AdError) {
//                        AdError _adError = (AdError) pObject;
//                        _jsonObject.put("error_code",_adError.getCode());
//                        _jsonObject.put("error_msg",_adError.getDesc());
//                        _jsonObject.put("error_stacktrace",_adError.printStackTrace());
//                    } else {
//                        _jsonObject.put(key,pObject);
//                    }
//                }
//            }catch (Exception e){
//                e.printStackTrace();
//            }
//            return _jsonObject.toString();
//        }
//    };
//
//}
