//
// Created by TopOn on 2020/5/19.
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS

#include "ATNativeItemProperty.h"
#include "ATCocosSdk.h"

#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "bridge/ATNativeItemProperty.h"
#include "bridge/ATCocosSdk.h"

#endif
ATNativeItemProperty::ATNativeItemProperty(int x, int y, int width, int height, std::string backgroundColor, std::string textColor, int textSize) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->backgroundColor = backgroundColor;
        this->textColor = textColor;
        this->textSize = textSize;
}

cocos2d::ValueMap ATNativeItemProperty::toValueMap() {
        cocos2d::ValueMap valueMap = cocos2d::ValueMap();
        valueMap[ATCocosSdk::KEY_POS_X] = this->x;
        valueMap[ATCocosSdk::KEY_POS_Y] = this->y;
        valueMap[ATCocosSdk::KEY_WIDTH] = this->width;
        valueMap[ATCocosSdk::KEY_HEIGHT] = this->height;
        valueMap[ATCocosSdk::KEY_BACKGROUND_COLOR] = this->backgroundColor;
        valueMap[ATCocosSdk::KEY_TEXT_SIZE] = this->textSize;
        valueMap[ATCocosSdk::KEY_TEXT_COLOR] = this->textColor;
        return valueMap;
}
