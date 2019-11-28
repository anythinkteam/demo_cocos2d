//
// Created by 周树斌 on 2018/11/9.
//

#include "UpArpuUtil.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define UPARPUSDKTOOLS   "com/uparpu/cocos2dx/bridge/UpArpuMessageTools"
#define UPARPUCOCOS2DBridgeVersion  "uparpu_cocos2dx_bridge_v1.0.0"
#endif


void UpArpuUtil::showMsg( const char* pat) {
    JniMethodInfo info;
    printLog("....showMsg");

    //getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
    bool ret = JniHelper::getStaticMethodInfo(info,UPARPUSDKTOOLS,"showDialog","(Ljava/lang/String;)V");
    if(ret)
    {
        jstring jmsg = charTojstring(info.env, pat);
        printLog("call void showMsg() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID,jmsg);
    }else{
        printLog("call void showMsg() failed");
    }
}


void UpArpuUtil::showToast(const char *pat)  {
    JniMethodInfo info;
    printLog("....showToast");

    //getStaticMethodInfo判断java定义的静态函数是否存在，返回bool
    bool ret = JniHelper::getStaticMethodInfo(info,UPARPUSDKTOOLS,"showToast","(Ljava/lang/String;)V");
    if(ret)
    {
        jstring jmsg = charTojstring(info.env, pat);
        printLog("call void showToast() successed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID,jmsg);
  }else{
        printLog("call void showToast() failed");
    }
}



jstring UpArpuUtil::charTojstring(JNIEnv* env, const char* pat) {
    //定义java String类 strClass 这里和普通的JNI不一样的是 不需要带L 普通的jNI是Ljava/lang/String
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取java String类方法String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray((jsize)strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
    //设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("utf8");
    //将byte数组转换为java String,并输出
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}


char*  UpArpuUtil::jstringTostring(JNIEnv *env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);

        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);//释放
    return rtn;
}


/***
 * 打印日志，开发者可以按照自己的习惯进行设置
 * @param pat
 */
void  UpArpuUtil::printLog(const char * pat)
{
   log("cocos2dx native----(uparpuSDKLog): %s",pat);

}
