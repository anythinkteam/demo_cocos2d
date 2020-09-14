//
// Created by TopOn on 2020/5/19.
//


#ifndef PROJ_ANDROID_ATNATIVEPROPERTY_H
#define PROJ_ANDROID_ATNATIVEPROPERTY_H

#include "ATNativeItemProperty.h"
#include "cocos2d.h"

class ATNativeProperty {
public:
    ATNativeItemProperty parent;
    ATNativeItemProperty icon;
    ATNativeItemProperty mainImage;
    ATNativeItemProperty title;
    ATNativeItemProperty desc;
    ATNativeItemProperty adLogo;
    ATNativeItemProperty cta;
    ATNativeItemProperty rating;

    ATNativeProperty(){};

    std::string toJsonString();
};


#endif //PROJ_ANDROID_ATNATIVEPROPERTY_H