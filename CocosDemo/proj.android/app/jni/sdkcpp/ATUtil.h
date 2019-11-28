
#ifndef PROJ_ANDROID_STUDIO_ATUTIL_H
#define PROJ_ANDROID_STUDIO_ATUTIL_H

#include <ui/UIWidget.h>
#include "cocos2d.h"
#include <jni.h>


class ATUtil {
    public:
        /**
         * 弹窗 小提示
         * @param pat
         */
        static void showMsg(const char* pat);

        /**
         * 弹窗 小提示
         * @param pat
         */
        static void showToast(const char* pat);
        /***
         * JAVA 字符串和C++字符串转化
         * @param env
         * @param pat
         * @return
         */
        static jstring charTojstring(JNIEnv* env, const char* pat);
        /***
         * JAVA 字符串和C++字符串转化
         * @param env
         * @param pat
         * @return
         */
        static char* jstringTostring(JNIEnv* env, jstring jstr);
        /**
         * 打印一下日志
         * @param pat
         */
        static void printLog(const char* pat);

        static void pareResultJson(JNIEnv * jniEnv,jstring jstring1);

};



#endif //PROJ_ANDROID_STUDIO_UPARPUUTIL_H
