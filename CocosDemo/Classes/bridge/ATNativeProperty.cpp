//
// Created by TopOn on 2020/5/19.
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS

#include "ATNativeProperty.h"
#include "ATCocosSdk.h"
#include "CCSerialization.h"

#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "bridge/ATNativeProperty.h"
#include "bridge/ATCocosSdk.h"
#include "bridge/CCSerialization.h"

#endif


std::string ATNativeProperty::toJsonString() {

    cocos2d::ValueMap valueMap = cocos2d::ValueMap();
    valueMap[ATCocosSdk::KEY_PARENT] = this->parent.toValueMap();
    valueMap[ATCocosSdk::KEY_ICON] = this->icon.toValueMap();
    valueMap[ATCocosSdk::KEY_MAIN_IMAGE] = this->mainImage.toValueMap();
    valueMap[ATCocosSdk::KEY_TITLE] = this->title.toValueMap();
    valueMap[ATCocosSdk::KEY_DESC] = this->desc.toValueMap();
    valueMap[ATCocosSdk::KEY_AD_LOGO] = this->adLogo.toValueMap();
    valueMap[ATCocosSdk::KEY_CTA] = this->cta.toValueMap();
    valueMap[ATCocosSdk::KEY_RATING] = this->rating.toValueMap();

    return cocos2d::StringUtils::getStringFromValueMap(valueMap);
}
