# TopOn SDK Cocos2d版本集成说明
[1 SDK说明](#1)</br>
[2 集成引用配置](#2)</br>
[3 SDK初始化及GDPR调用说明](#3)</br>
[4 激励视频广告调用说明](#4)</br>
[5 插屏广告调用说明](#5)</br>
[6 banner调用说明](#6)</br>
[7 原生广告调用说明](#7)</br>
[8 原生拼banner广告调用说明](#8)</br>
[9 Splash开屏广告调用说明](#9)</br>
[10 network配置说明](#10)</br>
[11 版本更新记录说明](#11)</br>


<h2 id='1'>1 SDK说明 </h2>
TopOn Cocos2dx版本SDK是基于TopOn的Android及iOS版本做二次封装的版本，方便基于Cocos2d环境开发的开发者集成使用，支持的广告形式包括激励视频广告、插屏广告、banner广告、原生广告、原生拼banner广告、开屏广告。

<h2 id='2'>2 集成引用配置 </h2>

###2.1 文件说明

| 文件 | 说明 | 是否必须|
| --- | --- |---|
| Classes/bridge目录| 里面包括SDK需要用到的调用接口类及回调接口,具体见下方说明|Y|
| Classes/demo目录| 相关接口调用示例|N|
| CMakeLists.txt| android编译需要使用的配置，具体见下方说明|Y|
| proj.ios_mac/ios/sdk| iOS版SDK转换接口具体实现|Y|
| proj.ios_mac/ios| 部分demo展示参考代码，主要是AppController.mm有开屏启动示例|N|
| proj.android/app/jni/sdkcpp目录| Android版SDK转换接口具体JNI实现|Y|
| proj.android/app/src/com/anythink/cocos2dx/bridge目录| Android版SDK转换接口的java实现|Y|


###2.2 通用集成环境配置说明
1、拷贝Classes中sdk目录下的文件到项目工程中；</br>

###2.3 iOS集成环境配置说明
1、将Classes中sdk目录中的文件拖进xcode的Classes group中；</br>
2、拷贝proj.ios\_mac/ios/sdk，到项目工程proj.ios_mac/ios目录中，并将内容拖动到xcode的ios group中；</br>
具体xcode环境配置及framework引用，请参照iOS帮助文档：</br>
[iOS集成帮助文档(中文)](https://github.com/anythinkteam/demo_ios/blob/master/iOS_Doc_CHN/iOS_Integration_Guide.md)


###2.4 Android集成环境配置说明
####2.4.1 源代码的导入
1、将Classes中的sdk目录下和proj.android/app/jni/sdkcpp的文件配置到CMakeList.txt,使项目导入该.cpp和.h文件;</br>
2、proj.android/app/src/com/anythink/cocos2dx/bridge目录的java代码（包括整个路径目录）复制到游戏的android项目的／app/src下</br>

具体Android Studio环境配置及AAR库引用，请参照Android帮助文档：</br>
[Android集成帮助文档(中文)](https://github.com/anythinkteam/demo_android/blob/master/zh/Android_TopOn_SDK_%E9%9B%86%E6%88%90%E6%96%87%E6%A1%A3.md)
</br>


<h2 id='3'>3 SDK初始化及GDPR调用说明 </h2>

### 3.1 API说明

类名：ATCocosSdk.h</br>

说明：以下为android&ios通用API</br>

| API | 参数说明 | 功能说明|
| --- | --- |---|
| setChannel| const char * channel|配置SDK的渠道号信息|
| setCustomData|cocos2d::CCDictionary * customData|配置自定义参数|
|setDebugLog|bool value |打开debug模式，用于SDK查看更多的日志|
|setGDPRLevel|int level |面向欧盟地区，设置GDPR隐私等级，值说明：0(完全个性化)，1(不收集设备信息,无个性化),2(禁止使用)|
|setDebugLog|bool value |打开debug模式，用于SDK查看更多的日志|
|showGdprAuth||展示GDPR授权页面|
| isEUTraffic||判断是否欧盟国家|
| initSDK |const char * appId, const char * appKey|初始化SDK|

iOS部分需要API</br>

| API | 参数说明 | 功能说明|
| --- | --- |---|
| getScreenScale| |获取屏幕大小|

SDK使用其他广告形式前，需要调用initSDK方法；涉及欧盟地区或者相关用户隐私协议控制，可通过setGDPRLevel控制数据上报权限；通过setDebugLog方法，可以开启调试日志，方便定位SDK集成中遇到的问题；</br>
SDK需要的appid、appkey等参数可通过开发者后台创建app之后获取。</br>

### 3.2 调用示例

```
	ATCocosSdk::setDebugLog(true);
    ATCocosSdk::setChannel("test_cocos");
    cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
    
    customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
    
    ATCocosSdk::setCustomData(customDict);
    CCLOG("DemoMainScene::onAdLoadSuccess" + ATCocosSdk::isEUTraffic()?"YES":"NO");
    ATCocosSdk::setGDPRLevel(0);
    
    const char* appId = "appId";
    const char* appKey = "appKey";
    
    ATCocosSdk::initSDK(appId, appKey);
				
```

<h2 id='4'>4 激励视频广告调用说明 </h2>

### 4.1 API说明

类名：ATCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadRewardedVideoAd|const char * placementId, const char * userId, cocos2d::CCDictionary  * parameters|用于load激励视频广告，unitId为广告位id；userId为启动激励用到的用户id，可为空；customObject可为第三方平台设置信息，可为空|
|showRewardedVideoAd|const char * placementId|展示指定广告位的激励视频广告|
|isRewardedVideoAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setRewardedVideoAdListener|ATCocosRewardedVideoAdListener * listener, const char * placementId|设置回调对象|

### 4.2 Listener回调方法说明

接口名：ATCocosRewardedVideoAdListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onRewardedVideoLoadSuccess|const char * placementId|广告加载完成|
|onRewardedVideoLoadFailed|const char * placementId, const char * errorString|广告加载失败，errorString为加载失败的原因|
|onRewardedVideoClicked|const char * placementId|激励视频产生点击|
|onRewardedVideoPlayStart|const char * placementId|视频播放开始|
|onRewardedVideoPlayEnd|const char * placementId|视频播放结束|
|onRewardedVideoShowFail|unitId: char, errorMsg: char |视频播放失败，errorMsg为加载失败的原因|
|onRewardedVideoClose|const char * placementId, bool isRewarded|视频关闭，isRewarded为是否产生激励，可能出现因延迟激励导致没有正常激励|
|onRewardedVideoDidRewardSuccess|const char * placementId|是否产生激励|

### 4.3 调用示例

1、加载广告

```
 ATCocosSdk::setRewardedVideoAdListener(this, rvPlacementId);
                ATCocosSdk::loadRewardedVideoAd(rvPlacementId, NULL, NULL);
```

2、展示广告

```
if(ATCocosSdk::isRewardedVideoAdReady(rvPlacementId)){
                    ATCocosSdk::showRewardedVideoAd(rvPlacementId);
                }else{
                    CCLOG("ATCocosSdk::isRewardedVideoAdReady is false");
                }
```

<h2 id='5'>5 插屏广告调用说明 </h2>

### 5.1 API说明

类名：ATCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadInterstitialAd|const char * placementId, cocos2d::CCDictionary  * parameters|用于load插屏广告，unitId为广告位id；parameters可为第三方平台设置信息，可为空|
|showInterstitialAd| parameters |展示指定广告位的插屏广告|
|isInterstitialAdReady| parameters |判断指定广告位的广告是否加载完成|
|setInterstitialAdListener|listener:ATCocosInterstitialAdListener|设置回调对象|

### 5.2 Listener回调方法说明

接口：ATCocosInterstitialAdListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onInterstitalLoadSuccess|const char * placementId|广告加载完成|
|onInterstitalLoadFailed|const char * placementId, const char * errorString|广告加载失败，errorString为加载失败的原因|
|onInterstitalClicked|const char * placementId|广告产生点击|
|onInterstitalShow|const char * placementId|广告展示|
|onInterstitalClose|const char * placementId|广告关闭|


### 5.3 调用示例

1、加载广告

```
 ATCocosSdk::setInterstitialAdListener(this, interPlacementId);
                ATCocosSdk::loadInterstitialAd(interPlacementId, NULL);			
```

2、展示广告

```
 if(ATCocosSdk::isInterstitialAdReady(interPlacementId)){
                    ATCocosSdk::showInterstitialAd(interPlacementId);
                }else{
                    CCLOG("ATCocosSdk::isInterstitialAdReady is false");
                }
```


<h2 id='6'>6 banner调用说明 </h2>


### 6.1 API说明

类名：ATCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadBannerAd| const char * placementId, cocos2d::CCDictionary  * parameters|用于加载banner广告，placementId为广告位id；parameters可为第三方平台设置信息，可为空|
|showBannerAd|const char * placementId, cocos2d::CCDictionary  * parameters|展示指定广告位的banner广告，parameters为指定banner展示的x坐标、y坐标、w宽、h高|
|removeBannerAd|const char * placementId|移除banner广告|
|isBannerAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setBannerAdListener|ATCocosBannerAdListener * listener, const char * placementId|设置回调对象|

### 6.2 Listener回调方法说明

接口：ATCocosBannerAdListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onBannerAdLoadSuccess|const char * placementId|广告加载完成|
|onBannerAdLoadFailed|const char * placementId, const char * errorString|广告加载失败，errorString为加载失败的原因|
|onBannerClicked|const char * placementId|广告产生点击|
|onBannerShow|const char * placementId|广告展示|
|onBannerClose|const char * placementId|广告关闭|
|onBannerAutoRefresh|const char * placementId|广告自动刷新|
|onBannerAutoRefreshFail|const char * placementId, const char * errorString|广告自动刷新失败，errorString为失败的原因|


### 6.3 调用示例

1、加载banner广告

```
ATCocosSdk::setBannerAdListener(this, bannerPlacementId);
                cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
                #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;
                std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                customDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                customDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
              
                #endif
                
                ATCocosSdk::loadBannerAd(bannerPlacementId, customDict);
				
```

2、展示banner广告

```
 if(ATCocosSdk::isBannerAdReady(bannerPlacementId)){
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;

                    cocos2d::CCDictionary * rectDict = cocos2d::CCDictionary::create();
                    
                    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/ATCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
                    #endif
                    
                    
                    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
                    #endif
                    
                    ATCocosSdk::showBannerAd(bannerPlacementId, rectDict);
                }else{
                     CCLOG("ATCocosSdk::isBannerAdReady is false");
                }			
```

3、移除banner广告

```
 ATCocosSdk::removeBannerAd(bannerPlacementId);
```

<h2 id='7'>7 原生广告调用说明 </h2>

### 7.1 API说明

类名：ATCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadNativeAd| const char * placementId, parameters:CCDictionary|用于加载native广告，unitId为广告位id；parameters可为第三方平台设置信息，可为空|
|showNativeAd|const char * placementId, parameters:CCDictionary|展示指定广告位的Native广告，parameters为指定native广告展示的位置|
|removeNativeAd|const char * placementId|移除原生广告|
|isNativeAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setNativeAdListener|ATCocosNativeAdListener * listener, const char * placementId|设置回调对象|



### 7.2 Listener回调方法说明

接口：ATNativeListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onNativeAdLoadSuccess|const char * placementId|广告加载完成|
|onNativeAdLoadFailed|const char * placementId, const char * errorString |广告加载失败，errorMsg为加载失败的原因|
|onNativeAdClick|const char * placementId|广告产生点击|
|onNativeAdShow|const char * placementId|广告展示|
|onNativeAdVideoStart|const char * placementId|原生视频播放开始，不同network可能支持不一样|
|onNativeAdVideoEnd|const char * placementId|原生视频播放结束，不同network可能支持不一样|
|onNativeAdShowWithExtra|const char * placementId, const char * extra|广告位展示<br>extra包含adsourceId和networkId|
|onNativeAdClickWithExtra|const char * placementId, const char * extra|广告位产生点击<br>extra包含adsourceId和networkId|
|onNativeAdVideoStartWithExtra|const char * placementId, const char * extra|原生视频播放开始，不同network可能支持不一样br>extra包含adsourceId和networkId|
|onNativeAdVideoEndWithExtra|const char * placementId, const char * extra|原生视频播放结束，不同network可能支持不一样br>extra包含adsourceId和networkId|

### 7.3 元素配置说明
#### 7.3.1 Android原生广告布局配置
在游戏项目里增加**proj.android/app/res/layout/demo\_cocos2d\_native\_ad\_item.xml**的布局文件，可用于自定义布局，以Android布局的方式来调整想要的样式，需要配合**proj.android/app/src/com.anythink.cocos2dx.brdige/ATNativeRender.java**来使用加载元素内容 （具体可看Demo的实现）

#### 7.3.2 iOS原生广告布局配置
调整ios/sdk/ATNativeAdWrapper.mm类文件中，通过ATCocosNativeAdView进行可约束实现，目前已支持一种样式，并可通过API去设置展示位置及大小。</br>
如需要调整原生banner和此样式无法满足需求，可通过调整ATNativeAdWrapper.mm实现的约束布局进行实现。</br>

### 7.4 调用示例

1、加载原生广告

```

ATCocosSdk::setNativeAdListener(this, nativePlacementId);
ATCocosSdk::loadNativeAd(nativePlacementId, NULL);
				
```

2、展示原生广告

```
 Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
                
                auto *glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                
                
                if (ATCocosSdk::isNativeAdReady(nativePlacementId)) {
                    
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;
                    
                   
                    
                    cocos2d::CCDictionary *rectDict = cocos2d::CCDictionary::create();
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                   
                    std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)(width *2/3/ATCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height- width *2/3 - 10)/ATCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
#endif
                    
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width *2/ 3);
                    std::string yStr = StringUtils::format("%d", height- width *2/ 3);
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
#endif
                    
                    
//                    rectDict->setObject(cocos2d::CCString::create("0"), "x");
//                    rectDict->setObject(cocos2d::CCString::create(yStr), "y");
//                    rectDict->setObject(cocos2d::CCString::create(widthStr), "w");
//                    rectDict->setObject(cocos2d::CCString::create(heightStr), "h");
                    ATCocosSdk::showNativeAd(nativePlacementId, rectDict);
                } else {
                    CCLOG("ATCocosSdk::isNativeAdReady is false");
                }							
```

3、移除原生广告

```
ATCocosSdk::removeNativeAd(nativePlacementId);
```

<h2 id='8'>8 原生拼banner广告调用说明 </h2>

此广告形式为基于原生拼接的banner广告，使用的是TopOn及network的原生广告位；
Android支持的分辨率(配置指定传入宽高参数)：auto、320\*50、640\*100；
iOS支持的分辨率(配置指定传入宽高参数)：auto。

### 8.1 API说明

类名：ATCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadNativeBannerAd| const char * placementId, cocos2d::CCDictionary  * customData|用于加载nativebanner广告，placementId为广告位id；customData可为第三方平台设置信息，可为空|
|showNativeBannerAd|const char * placementId, cocos2d::CCDictionary  * rect, cocos2d::CCDictionary  * extra|展示指定广告位的Nativebanner广告，rect为指定nativebanner广告展示的位置，extra为具体的元素相关配置项|
|removeNativeBannerAd|const char * placementId|移除NativeBanner广告|
|isNativeBannerAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setNativeBannerAdListener|listener:ATCocosNativeBannerAdListener|设置回调对象|


### 8.2 Listener回调方法说明

接口：ATNativeListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onNativeBannerAdLoadSuccess| const char * placementId |广告加载完成|
|onNativeBannerAdLoadFailed|const char * placementId, const char * errorString |广告加载失败及相关的错误信息|
|onNativeBannerShow|const char * placementId|广告位展示|
|onNativeBannerClicked|const char * placementId|广告位产生点击|
|onNativeBannerAutoRefreshFail|const char * placementId, const char * errorString|广告自动刷新失败及相关的错误信息|
|onNativeBannerClose|const char * placementId|用户点击banner关闭按钮|
|onNativeBannerAutoRefresh|const char * placementId|广告自动刷新|
|onNativeBannerShowWithExtra|const char * placementId, const char * extra|广告位展示<br>extra包含adsourceId和networkId|
|onNativeBannerClickedWithExtra|const char * placementId|广告位产生点击<br>extra包含adsourceId和networkId|
|onNativeBannerAutoRefreshFailWithExtra|const char * placementId, const char * errorString|广告自动刷新失败及相关的错误信息<br>extra包含adsourceId和networkId|
|onNativeBannerCloseWithExtra|const char * placementId|用户点击banner关闭按钮<br>extra包含adsourceId和networkId|
|onNativeBannerAutoRefreshWithExtra|const char * placementId|广告自动刷新<br>extra包含adsourceId和networkId|

### 8.3 相关素材配置说明

类名：ATCocosSdk

| API | 参数说明 |
| --- | --- |
| ATCocosSdk::KEY\_POS\_X| 配置展示的x位置，示例:"0"|
| ATCocosSdk::KEY\_POS\_Y| 配置展示的y位置，示例:"100"|
| ATCocosSdk::KEY\_WIDTH| 配置展示的width，示例:"320"|
| ATCocosSdk::KEY\_HEIGHT| 配置展示的height，示例:"50"|
| ATCocosSdk::KEY\_MAIN\_BG\_COLOR| 配置展示的背景颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_REFRESH\_INTERVEL| 配置自动刷新的时间间隔，单位秒,示例"5"|
| ATCocosSdk::KEY\_BUTTON\_CLOSE\_STATUS| 配置关闭按钮隐藏状态,false为显示关闭按钮，true为隐藏关闭按钮|
| ATCocosSdk::KEY\_BUTTON\_CTA\_BG| 配置CTA按钮背景颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_BUTTON\_CTA\_TITLE\_FONT| 配置CTA按钮文字字体大小，示例:"12"|
| ATCocosSdk::KEY\_BUTTON\_CTA\_TITLE\_COLOR| 配置CTA按钮文字颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_TITLE\_FONT| 配置标题文字大小，示例:"12"|
| ATCocosSdk::KEY\_TITLE\_COLOR| 配置标题文字颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_TEXT\_FONT| 配置文本文字大小，示例:"12"|
| ATCocosSdk::KEY\_TEXT\_COLOR| 配置文本文字颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_ADVERTISER\_TEXT\_FONT| 配置广告主文字颜色，示例:"10"|
| ATCocosSdk::KEY\_ADVERTISER\_TEXT\_COLOR| 配置广告主文字颜色，示例:"#ffffff"|
| ATCocosSdk::KEY\_IS\_SHOW\_CTA| 是否展示CTA按钮，仅android支持，示例:"true"|
| ATCocosSdk::KEY\_BANNER\_SIZE\_TYPE| banner大小类型，仅android支持|


### 8.3 调用示例

1、加载广告

```

ATCocosSdk::setNativeBannerAdListener(this, nativebannerPlacementId);
                
                
                cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
                
                #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;
                
                std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                customDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                customDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
                
                #endif

                customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
                
                ATCocosSdk::loadNativeBannerAd(nativebannerPlacementId, customDict);
				
```

2、展示native拼banner广告

```
 if(ATCocosSdk::isNativeBannerAdReady(nativebannerPlacementId)){
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;
                    
                    cocos2d::CCDictionary * rectDict = cocos2d::CCDictionary::create();
                    cocos2d::CCDictionary * extraDict = cocos2d::CCDictionary::create();
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/ATCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);
                    
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), ATCocosSdk::KEY_MAIN_BG_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("5"), ATCocosSdk::KEY_REFRESH_INTERVEL);
                    extraDict->setObject(cocos2d::CCString::create("NO"), ATCocosSdk::KEY_BUTTON_CLOSE_STATUS);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_BUTTON_CTA_BG);
                    extraDict->setObject(cocos2d::CCString::create("12"), ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("12"), ATCocosSdk::KEY_TITLE_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("12"), ATCocosSdk::KEY_TEXT_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("10"), ATCocosSdk::KEY_ADVERTISER_TEXT_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR);
#endif
           
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);
                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);

                    rectDict->setObject(cocos2d::CCString::create("0"), ATCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), ATCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), ATCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), ATCocosSdk::KEY_HEIGHT);

                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), ATCocosSdk::KEY_MAIN_BG_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("10000"), ATCocosSdk::KEY_REFRESH_INTERVEL);
                    extraDict->setObject(cocos2d::CCString::create("false"), ATCocosSdk::KEY_BUTTON_CLOSE_STATUS);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_BUTTON_CTA_BG);
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("true"), ATCocosSdk::KEY_IS_SHOW_CTA);
                    extraDict->setObject(cocos2d::CCString::create("3"), ATCocosSdk::KEY_BANNER_SIZE_TYPE);
#endif
                    
                    ATCocosSdk::showNativeBannerAd(nativebannerPlacementId, rectDict, extraDict);
                    
                }else{
                    CCLOG("ATCocosSdk::isNativeBannerAdReady is false");
                }			
```

3、移除native拼banner广告


```
 ATCocosSdk::removeNativeBannerAd(nativebannerPlacementId);
```

3、移除原生广告

```
ATCocosSdk::removeNativeAd(nativePlacementId);
```

<h2 id='9'>9 Splash开屏广告调用说明 </h2>

目前Splash开屏广告仅支持中国的广告平台穿山甲、Baidu、GDT，具体调用示例如下：
</br>
iOS:</br>

```

[[ATAdManager sharedManager] loadADWithPlacementID:@"b5c1b048c498b9" extra:@{kATSplashExtraTolerateTimeoutKey:@3.0} customData:nil delegate:self window:window containerView:nil];

```

iOS里面的window可直接使用AppController类中的windonw去展示</br>

Android: 需要在应用里创建一个Activity，详细Demo可以查看：**proj.android/app/src/org.cocos2dx.cpp/SplashActivity**</br>

```
//示例代码
new ATSplashAd(this, container, skipView, "b5bea7bfd93f01", this);


```

<h2 id='11'>11 版本更新记录说明 </h2>
最新的SDK版本号更新如下：</br>

|| SDK version |note|
|---|---|---|
|cocos| v5.2.1 |iOS：KS需要额外引入KSThirdRelySDK.framework (这个framework是由*AFNetworking/Godzippa/MJExtension/SDWebImage* 四个第三方依赖的源码打包出来的framework，这是为了防止快手平台的广告在cocos下直接调用其第三方依赖而导致崩溃)|
|cocos| v5.4.1 |iOS：gdt update 4.11.2,sigmob update 2.15.2,MTG update 5.8.7<br>去掉不带extra参数的回调|


