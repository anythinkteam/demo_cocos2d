//
// Created by TopOn on 2020/5/19.
//

#ifndef PROJ_ANDROID_ATNATIVEITEMPROPERTY_H
#define PROJ_ANDROID_ATNATIVEITEMPROPERTY_H

#include <cocos2d.h>
class ATNativeItemProperty {
public:

    int x;
    int y;
    int width;
    int height;
    std::string backgroundColor;
    std::string textColor;
    int textSize;


    ATNativeItemProperty(int x, int y, int width, int height, std::string backgroundColor, std::string textColor, int textSize);

    ATNativeItemProperty(){};

    cocos2d::ValueMap toValueMap();

};


#endif //PROJ_ANDROID_ATNATIVEITEMPROPERTY_H