# UPARPU SDK Cocos2dX版本集成说明
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
UpArpu Cocos2dx版本SDK是基于UpArpu的Android及iOS版本做二次封装的版本，方便基于Cocos2d环境开发的开发者集成使用，支持的广告形式包括激励视频广告、插屏广告、banner广告、原生广告、原生拼banner广告、开屏广告。

<h2 id='2'>2 集成引用配置 </h2>

###2.1 文件说明

| 文件 | 说明 | 是否必须|
| --- | --- |---|
| Classes/sdk目录| 里面包括SDK需要用到的调用接口类及回调接口,具体见下方说明|Y|
| Classes/uparpudemo目录| 相关接口调用示例|N|
| CMakeLists.txt| android编译需要使用的配置，具体见下方说明|Y|
| proj.ios_mac/ios/sdk| iOS版SDK转换接口具体实现|Y|
| proj.ios_mac/ios| 部分demo展示参考代码，主要是AppController.mm有开屏启动示例|N|
| proj.android/app/jni/uparpucpp目录| Android版SDK转换接口具体JNI实现|Y|
| proj.android/app/src/com/uparpu/cocos2dx/bridge目录| Android版SDK转换接口的java实现|Y|


###2.2 通用集成环境配置说明
1、拷贝Classes中sdk目录下的文件到项目工程中；</br>

###2.3 iOS集成环境配置说明
1、将Classes中sdk目录中的文件拖进xcode的Classes group中；</br>
2、拷贝proj.ios\_mac/ios/sdk，到项目工程proj.ios_mac/ios目录中，并将内容拖动到xcode的ios group中；</br>
3、iOS版本依赖的SDK库文件采用另一个包独立提供方式，集成聚合SDK需要导入的Framework文件如下：</br>

| 文件 | 说明 | 是否必须|
| --- | --- |---|
| UpArpuSDK.framework| 集成需要的基础库 |Y|
| UpArpuSDK.bundle| 集成需要的资源文件|Y|
| UpArpuNative.framework| 集成Native广告需要的库，包括普通Native、NativeBanner和NativeSplash|Y|
| UpArpuBanner.framework| 集成Banner广告需要的库|Y|
| UpArpuInterstitial.framework| 集成Interstitial广告需要的库|Y|
| UpArpuRewardedVideo.framework| 集成RewardedVideo广告需要的库|Y|
| UpArpuHeaderBidding.framework| 支持HeaderBidding广告需要的库|Y|
| UpArpu\_xx\_adapter.framework| 聚合其他network需要的adapter库文件，根据实际集成network选择|N|
| 第三方network SDK库文件| 聚合其他network需要的库文件，根据实际集成network选择|N|



###2.4 Android集成环境配置说明
####2.4.1 源代码的导入
1、将Classes中的sdk目录下和proj.android/app/jni/uparpucpp的文件配置到CMakeList.txt,使项目导入该.cpp和.h文件;</br>
2、proj.android/app/src/com/uparpu/cocos2dx/bridge目录的java代码（包括整个路径目录）复制到游戏的android项目的／app/src下

####2.4.2 AAR包的导入
在**proj.android/app/libs**目录下：

| 文件夹| 说明| 是否必须|
| ---| ---| ---|
|aar\_uparpu |UpArpu在Android层aar包|Y|
|aar\_plugin|UpArpu使用的第三方平台的插件包|Y|
|aar\_gms\_service|集成海外平台的SDK必须导入的，国内用户可不用导入| N|
|aar\_*|剩余aar文件夹都是对应各个平台的aar包，按需导入|N|

将需要的一并导入到游戏项目libs路径下，通过gradle方式引入aar包**（可参考Demo的引入方式）**
<br>
<br>
gradle需要引入v7的插件包（必须导入）：

```java
implementation 'com.android.support:appcompat-v7:28.0.0'
```

<h2 id='3'>3 SDK初始化及GDPR调用说明 </h2>

### 3.1 API说明

类名：UpArpuCocosSdk.h</br>

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
	UpArpuCocosSdk::setDebugLog(true);
    UpArpuCocosSdk::setChannel("test_cocos");
    cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
    
    customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
    
    UpArpuCocosSdk::setCustomData(customDict);
    CCLOG("UparpuDemoMainScene::onAdLoadSuccess" + UpArpuCocosSdk::isEUTraffic()?"YES":"NO");
    UpArpuCocosSdk::setGDPRLevel(0);
    
    const char* appId = "appId";
    const char* appKey = "appKey";
    
    UpArpuCocosSdk::initSDK(appId, appKey);
				
```

<h2 id='4'>4 激励视频广告调用说明 </h2>

### 4.1 API说明

类名：UpArpuCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadRewardedVideoAd|const char * placementId, const char * userId, cocos2d::CCDictionary  * parameters|用于load激励视频广告，unitId为广告位id；userId为启动激励用到的用户id，可为空；customObject可为第三方平台设置信息，可为空|
|showRewardedVideoAd|const char * placementId|展示指定广告位的激励视频广告|
|isRewardedVideoAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setRewardedVideoAdListener|UpArpuCocosRewardedVideoAdListener * listener, const char * placementId|设置回调对象|

### 4.2 Listener回调方法说明

接口名：UpArpuCocosRewardedVideoAdListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onRewardedVideoLoadSuccess|const char * placementId|广告加载完成|
|onRewardedVideoLoadFailed|const char * placementId, const char * errorString|广告加载失败，errorString为加载失败的原因|
|onRewardedVideoClicked|const char * placementId|激励视频产生点击|
|onRewardedVideoPlayStart|const char * placementId|视频播放开始|
|onRewardedVideoPlayEnd|const char * placementId|视频播放结束|
|onRewardedVideoShowFail|unitId: char, errorMsg: char |视频播放失败，errorMsg为加载失败的原因|
|onRewardedVideoClose|const char * placementId, bool isRewarded|视频关闭，isRewarded为是否产生激励|

### 4.3 调用示例

1、加载广告

```
 UpArpuCocosSdk::setRewardedVideoAdListener(this, rvPlacementId);
                UpArpuCocosSdk::loadRewardedVideoAd(rvPlacementId, NULL, NULL);
```

2、展示广告

```
if(UpArpuCocosSdk::isRewardedVideoAdReady(rvPlacementId)){
                    UpArpuCocosSdk::showRewardedVideoAd(rvPlacementId);
                }else{
                    CCLOG("UpArpuCocosSdk::isRewardedVideoAdReady is false");
                }
```

<h2 id='5'>5 插屏广告调用说明 </h2>

### 5.1 API说明

类名：UpArpuCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadInterstitialAd|const char * placementId, cocos2d::CCDictionary  * parameters|用于load插屏广告，unitId为广告位id；parameters可为第三方平台设置信息，可为空|
|showInterstitialAd| parameters |展示指定广告位的插屏广告|
|isInterstitialAdReady| parameters |判断指定广告位的广告是否加载完成|
|setInterstitialAdListener|listener:UpArpuCocosInterstitialAdListener|设置回调对象|

### 5.2 Listener回调方法说明

接口：UpArpuCocosInterstitialAdListener

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
 UpArpuCocosSdk::setInterstitialAdListener(this, interPlacementId);
                UpArpuCocosSdk::loadInterstitialAd(interPlacementId, NULL);			
```

2、展示广告

```
 if(UpArpuCocosSdk::isInterstitialAdReady(interPlacementId)){
                    UpArpuCocosSdk::showInterstitialAd(interPlacementId);
                }else{
                    CCLOG("UpArpuCocosSdk::isInterstitialAdReady is false");
                }
```


<h2 id='6'>6 banner调用说明 </h2>


### 6.1 API说明

类名：UpArpuCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadBannerAd| const char * placementId, cocos2d::CCDictionary  * parameters|用于加载banner广告，placementId为广告位id；parameters可为第三方平台设置信息，可为空|
|showBannerAd|const char * placementId, cocos2d::CCDictionary  * parameters|展示指定广告位的banner广告，parameters为指定banner展示的x坐标、y坐标、w宽、h高|
|removeBannerAd|const char * placementId|移除banner广告|
|isBannerAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setBannerAdListener|UpArpuCocosBannerAdListener * listener, const char * placementId|设置回调对象|

### 6.2 Listener回调方法说明

接口：UpArpuCocosBannerAdListener

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
UpArpuCocosSdk::setBannerAdListener(this, bannerPlacementId);
                cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
                #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;
                std::string widthStr = StringUtils::format("%d", (int)(width/UpArpuCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/UpArpuCocosSdk::getScreenScale()));
                customDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                customDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
              
                #endif
                
                UpArpuCocosSdk::loadBannerAd(bannerPlacementId, customDict);
				
```

2、展示banner广告

```
 if(UpArpuCocosSdk::isBannerAdReady(bannerPlacementId)){
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;

                    cocos2d::CCDictionary * rectDict = cocos2d::CCDictionary::create();
                    
                    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    std::string widthStr = StringUtils::format("%d", (int)(width/UpArpuCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/UpArpuCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/UpArpuCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
                    #endif
                    
                    
                    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
                    #endif
                    
                    UpArpuCocosSdk::showBannerAd(bannerPlacementId, rectDict);
                }else{
                     CCLOG("UpArpuCocosSdk::isBannerAdReady is false");
                }			
```

3、移除banner广告

```
 UpArpuCocosSdk::removeBannerAd(bannerPlacementId);
```

<h2 id='7'>7 原生广告调用说明 </h2>

### 7.1 API说明

类名：UpArpuCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadNativeAd| unitId: char, parameters:CCDictionary|用于加载native广告，unitId为广告位id；parameters可为第三方平台设置信息，可为空|
|showNativeAd|unitId:String, parameters:CCDictionary|展示指定广告位的Native广告，parameters为指定native广告展示的位置|
|removeNativeAd|unitId:char|移除原生广告|
|isNativeAdReady|unitId:String|判断指定广告位的广告是否加载完成|
|setNativeAdListener|listener:UpArpuNativeListener|设置回调对象|



### 7.2 Listener回调方法说明

接口：UpArpuNativeListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onNativeAdLoadSuccess| unitId: char |广告加载完成|
|onNativeAdLoadFailed|unitId: char, errorMsg: char |广告加载失败，errorMsg为加载失败的原因|
|onNativeAdClick|unitId:char|广告产生点击|
|onNativeAdShow|unitId:String|广告展示|
|onNativeAdVideoStart|unitId: char |原生视频播放开始，不同network可能支持不一样|
|onNativeAdVideoEnd|unitId: char |原生视频播放结束，不同network可能支持不一样|

### 7.3 元素配置说明
#### 7.3.1 Android原生广告布局配置
在游戏项目里增加**proj.android/app/res/layout/uparpu\_cocos2d\_native\_ad\_item.xml**的布局文件，可用于自定义布局，以Android布局的方式来调整想要的样式，需要配合**proj.android/app/src/com.uparpu.cocos2dx.brdige/UpArpuNativeRender.java**来使用加载元素内容 （具体可看Demo的实现）

#### 7.3.2 iOS原生广告布局配置
调整ios/sdk/UPArpuNativeAdWrapper.mm类文件中，通过UPArpuCocosNativeAdView进行可约束实现，目前已支持一种样式，并可通过API去设置展示位置及大小。</br>
如需要调整原生banner和此样式无法满足需求，可通过调整UPArpuNativeAdWrapper.mm实现的约束布局进行实现。</br>

### 7.4 调用示例

1、加载原生广告

```

UpArpuCocosSdk::setNativeAdListener(this, nativePlacementId);
UpArpuCocosSdk::loadNativeAd(nativePlacementId, NULL);
				
```

2、展示原生广告

```
 Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
                
                auto *glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                
                
                if (UpArpuCocosSdk::isNativeAdReady(nativePlacementId)) {
                    
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;
                    
                   
                    
                    cocos2d::CCDictionary *rectDict = cocos2d::CCDictionary::create();
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                   
                    std::string widthStr = StringUtils::format("%d", (int)(width/UpArpuCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)(width *2/3/UpArpuCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height- width *2/3 - 10)/UpArpuCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
#endif
                    
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width *2/ 3);
                    std::string yStr = StringUtils::format("%d", height- width *2/ 3);
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
#endif
                    
                    
//                    rectDict->setObject(cocos2d::CCString::create("0"), "x");
//                    rectDict->setObject(cocos2d::CCString::create(yStr), "y");
//                    rectDict->setObject(cocos2d::CCString::create(widthStr), "w");
//                    rectDict->setObject(cocos2d::CCString::create(heightStr), "h");
                    UpArpuCocosSdk::showNativeAd(nativePlacementId, rectDict);
                } else {
                    CCLOG("UpArpuCocosSdk::isNativeAdReady is false");
                }							
```

3、移除原生广告

```
UpArpuCocosSdk::removeNativeAd(nativePlacementId);
```

<h2 id='8'>8 原生拼banner广告调用说明 </h2>

此广告形式为基于原生拼接的banner广告，使用的是uparpu及network的原生广告位；
Android支持的分辨率(配置指定传入宽高参数)：auto、320\*50、640\*100；
iOS支持的分辨率(配置指定传入宽高参数)：auto。

### 8.1 API说明

类名：UpArpuCocosSdk

| API | 参数说明 | 功能说明|
| --- | --- |---|
| loadNativeBannerAd| const char * placementId, cocos2d::CCDictionary  * customData|用于加载nativebanner广告，placementId为广告位id；customData可为第三方平台设置信息，可为空|
|showNativeBannerAd|const char * placementId, cocos2d::CCDictionary  * rect, cocos2d::CCDictionary  * extra|展示指定广告位的Nativebanner广告，rect为指定nativebanner广告展示的位置，extra为具体的元素相关配置项|
|removeNativeBannerAd|const char * placementId|移除NativeBanner广告|
|isNativeBannerAdReady|const char * placementId|判断指定广告位的广告是否加载完成|
|setNativeBannerAdListener|listener:UpArpuCocosNativeBannerAdListener|设置回调对象|


### 8.2 Listener回调方法说明

接口：UpArpuNativeListener

| API | 参数说明 | 功能说明|
| --- | --- |---|
|onNativeBannerAdLoadSuccess| const char * placementId |广告加载完成|
|onNativeBannerAdLoadFailed|const char * placementId, const char * errorString |广告加载失败及相关的错误信息|
|onNativeBannerShow|const char * placementId|广告位展示|
|onNativeBannerClicked|const char * placementId|广告位产生点击|
|onNativeBannerAutoRefreshFail|const char * placementId, const char * errorString|广告自动刷新失败及相关的错误信息|
|onNativeBannerClose|const char * placementId|用户点击banner关闭按钮|
|onNativeBannerAutoRefresh|const char * placementId|广告自动刷新|

### 8.3 相关素材配置说明

类名：UpArpuCocosSdk

| API | 参数说明 |
| --- | --- |
| UpArpuCocosSdk::KEY\_POS\_X| 配置展示的x位置，示例:"0"|
| UpArpuCocosSdk::KEY\_POS\_Y| 配置展示的y位置，示例:"100"|
| UpArpuCocosSdk::KEY\_WIDTH| 配置展示的width，示例:"320"|
| UpArpuCocosSdk::KEY\_HEIGHT| 配置展示的height，示例:"50"|
| UpArpuCocosSdk::KEY\_MAIN\_BG\_COLOR| 配置展示的背景颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_REFRESH\_INTERVEL| 配置自动刷新的时间间隔，单位秒,示例"5"|
| UpArpuCocosSdk::KEY\_BUTTON\_CLOSE\_STATUS| 配置关闭按钮隐藏状态,false为显示关闭按钮，true为隐藏关闭按钮|
| UpArpuCocosSdk::KEY\_BUTTON\_CTA\_BG| 配置CTA按钮背景颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_BUTTON\_CTA\_TITLE\_FONT| 配置CTA按钮文字字体大小，示例:"12"|
| UpArpuCocosSdk::KEY\_BUTTON\_CTA\_TITLE\_COLOR| 配置CTA按钮文字颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_TITLE\_FONT| 配置标题文字大小，示例:"12"|
| UpArpuCocosSdk::KEY\_TITLE\_COLOR| 配置标题文字颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_TEXT\_FONT| 配置文本文字大小，示例:"12"|
| UpArpuCocosSdk::KEY\_TEXT\_COLOR| 配置文本文字颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_ADVERTISER\_TEXT\_FONT| 配置广告主文字颜色，示例:"10"|
| UpArpuCocosSdk::KEY\_ADVERTISER\_TEXT\_COLOR| 配置广告主文字颜色，示例:"#ffffff"|
| UpArpuCocosSdk::KEY\_IS\_SHOW\_CTA| 是否展示CTA按钮，仅android支持，示例:"true"|
| UpArpuCocosSdk::KEY\_BANNER\_SIZE\_TYPE| banner大小类型，仅android支持|


### 8.3 调用示例

1、加载广告

```

UpArpuCocosSdk::setNativeBannerAdListener(this, nativebannerPlacementId);
                
                
                cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
                
                #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;
                
                std::string widthStr = StringUtils::format("%d", (int)(width/UpArpuCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/UpArpuCocosSdk::getScreenScale()));
                customDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                customDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
                
                #endif

                customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
                
                UpArpuCocosSdk::loadNativeBannerAd(nativebannerPlacementId, customDict);
				
```

2、展示native拼banner广告

```
 if(UpArpuCocosSdk::isNativeBannerAdReady(nativebannerPlacementId)){
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;
                    
                    cocos2d::CCDictionary * rectDict = cocos2d::CCDictionary::create();
                    cocos2d::CCDictionary * extraDict = cocos2d::CCDictionary::create();
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    std::string widthStr = StringUtils::format("%d", (int)(width/UpArpuCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/UpArpuCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/UpArpuCocosSdk::getScreenScale()));
                    
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);
                    
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), UpArpuCocosSdk::KEY_MAIN_BG_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("5"), UpArpuCocosSdk::KEY_REFRESH_INTERVEL);
                    extraDict->setObject(cocos2d::CCString::create("NO"), UpArpuCocosSdk::KEY_BUTTON_CLOSE_STATUS);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_BUTTON_CTA_BG);
                    extraDict->setObject(cocos2d::CCString::create("12"), UpArpuCocosSdk::KEY_BUTTON_CTA_TITLE_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), UpArpuCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("12"), UpArpuCocosSdk::KEY_TITLE_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("12"), UpArpuCocosSdk::KEY_TEXT_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("10"), UpArpuCocosSdk::KEY_ADVERTISER_TEXT_FONT);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_ADVERTISER_TEXT_COLOR);
#endif
           
                    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);
                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);

                    rectDict->setObject(cocos2d::CCString::create("0"), UpArpuCocosSdk::KEY_POS_X);
                    rectDict->setObject(cocos2d::CCString::create(yStr), UpArpuCocosSdk::KEY_POS_Y);
                    rectDict->setObject(cocos2d::CCString::create(widthStr), UpArpuCocosSdk::KEY_WIDTH);
                    rectDict->setObject(cocos2d::CCString::create(heightStr), UpArpuCocosSdk::KEY_HEIGHT);

                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), UpArpuCocosSdk::KEY_MAIN_BG_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("10000"), UpArpuCocosSdk::KEY_REFRESH_INTERVEL);
                    extraDict->setObject(cocos2d::CCString::create("false"), UpArpuCocosSdk::KEY_BUTTON_CLOSE_STATUS);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_BUTTON_CTA_BG);
                    extraDict->setObject(cocos2d::CCString::create("#ffffff"), UpArpuCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_TITLE_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("#000000"), UpArpuCocosSdk::KEY_ADVERTISER_TEXT_COLOR);
                    extraDict->setObject(cocos2d::CCString::create("true"), UpArpuCocosSdk::KEY_IS_SHOW_CTA);
                    extraDict->setObject(cocos2d::CCString::create("3"), UpArpuCocosSdk::KEY_BANNER_SIZE_TYPE);
#endif
                    
                    UpArpuCocosSdk::showNativeBannerAd(nativebannerPlacementId, rectDict, extraDict);
                    
                }else{
                    CCLOG("UpArpuCocosSdk::isNativeBannerAdReady is false");
                }			
```

3、移除native拼banner广告


```
 UpArpuCocosSdk::removeNativeBannerAd(nativebannerPlacementId);
```

3、移除原生广告

```
UpArpuCocosSdk::removeNativeAd(nativePlacementId);
```

<h2 id='9'>9 Splash开屏广告调用说明 </h2>

目前Splash开屏广告仅支持中国的广告平台穿山甲、Baidu、GDT，具体调用示例如下：
</br>
iOS:</br>

```

[[UPArpuAdManager sharedManager] loadADWithPlacementID:@"b5c1b048c498b9" extra:@{kUPArpuSplashExtraTolerateTimeoutKey:@3.0} customData:nil delegate:self window:window containerView:nil];

```

iOS里面的window可直接使用AppController类中的windonw去展示</br>

Android: 需要在应用里创建一个Activity，详细Demo可以查看：**proj.android/app/src/org.cocos2dx.cpp/SplashActivity**</br>

```
//示例代码
new UpArpuSplashAd(this, container, skipView, "b5bea7bfd93f01", this);


```


<h2 id='10'>10 network配置说明 </h2>

### 10.1 iOS配置注意项
#### 10.1.1 admob配置
1、plist中添加：</br>
GADApplicationIdentifier：admob的application id</br>
#### 10.1.2 Mintegral配置
1、添加依赖库</br>
CoreGraphics.framework </br>
Foundation.framework</br>
UIKit.framework</br>
libsqlite3.tbd (It's libsqlite3.dylib below Xcode7)</br>
libz.tbd (It'slibz.dylib below Xcode7)</br>
AdSupport.framwork</br>
StoreKit.framewrok</br>
QuartzCore.framework</br>
CoreLocation.framework</br>
CoreTelephony.framework</br>
MobileCoreServices.framework</br>
Accelerate.framework</br>
AVFoundation.framework</br>
WebKit.framework</br>

#### 10.1.3 Inmobi配置
1、添加依赖库</br>
libsqlite3.0.tbd</br>
libz.tbd</br>
WebKit.framework</br>
libxml2.tbd （请仅在使用China SDK时添加此项）</br>

#### 10.1.4 Mopub配置
1、添加依赖库</br>
AdSupport.framework</br>
AVFoundation.framework</br>
CoreGraphics.framework</br>
CoreLocation.framework</br>
CoreMedia.framework</br>
CoreTelephony.framework</br>
Foundation.framework</br>
MediaPlayer.framework</br>
MessageUI.framework</br>
QuartzCore.framework</br>
SafariServices.framework</br>
StoreKit.framework</br>
SystemConfiguration.framework</br>
UIKit.framework</br>
WebKit.framework</br>

#### 10.1.5 GDT配置
1、添加依赖库</br>
AdSupport.framework</br>
CoreLocation.framework</br>
QuartzCore.framework</br>
SystemConfiguration.framework</br>
CoreTelephony.framework</br>
libz.tbd</br>
Security.framework</br>
StoreKit.framework</br>
libxml2.tbd</br>
AVFoundation.framework</br>
WebKit.framework</br>

#### 10.1.6 Chartboost配置
1、添加依赖库</br>
StoreKit</br>
Foundation</br>
CoreGraphics</br>
WebKit</br>
AVFoundation</br>
UIKit框架</br>

#### 10.1.7 Vungle配置
1、添加依赖库</br>
AdSupport.framework</br>
AudioToolbox.framework</br>
AVFoundation.framework</br>
CFNetwork.framework</br>
CoreGraphics.framework</br>
CoreMedia.framework</br>
libz.dylib or libz.tbd</br>
MediaPlayer.framework</br>
QuartzCore.framework</br>
StoreKit.framework</br>
SystemConfiguration.framework</br>

#### 10.1.8 TT穿山甲配置
1、添加依赖库</br>
StoreKit.framework</br>
MobileCoreServices.framework</br>
WebKit.framework</br>
MediaPlayer.framework</br>
CoreMedia.framework</br>
AVFoundation.framework</br>
CoreTelephony.framework</br>
SystemConfiguration.framework</br>
AdSupport.framework程式</br>
CoreMotion.framework</br>
libresolv.9.tbd</br>

#### 10.1.9 AppNext配置
1、添加依赖库</br>
QuartzCore.framework</br>
Security.framework</br>
CFNetwork.framework</br>
AVFoundation.framework</br>
SystemConfiguration.framework</br>
MobileCoreServices.framework</br>
CoreGraphics.framework</br>
CoreMedia.framework</br>
AdSupport.framework</br>
UIKit.framework</br>
Foundation.framework</br>
CoreTelephony.framework</br>

#### 10.1.10 nend配置
1、添加依赖库</br>
AdSupport.framework程式</br>
Security.framework</br>
ImageIO.framework</br>
AVFoundation.framework</br>
CoreMedia.framework</br>
SystemConfiguration.framework</br>
WebKit.framework</br>
可选的静态库</br>
通过添加下列静态库可以获取更详细的广告信息。</br>
CoreLocation.framework</br>
CoreMotion.framework</br>
CoreTelephony.framework</br>

### 10.2 Android配置注意项
暂无


<h2 id='11'>11 版本更新记录说明 </h2>
最新的SDK版本号更新如下：</br>
iOS聚合SDK版本为5.4.1</br>

| Network | SDK Version |
|---|---|
| Facebook | 5.5.1 |
| Admob | 7.52.0 |
| Inmobi | 7.3.1 |
| Flurry | 9.0.0 |
| Applovin | 6.10.0 |
| Mintegral | 5.8.7 |
| Mopub | 5.10.0 |
| GDT | 4.11.2|
| Yeahmobi | 3.2.0 |
| Appnext | 1.9.3 |
| Chartboost | 8.0.3 |
| Ironsource | 6.10.0 |
| Vungle | 6.4.6 |
| Adcolony | 4.1.2.0 |
| UnityAds | 3.4.0 |
| TT | 2.5.1.5 |
| Tapjoy | 12.3.4 |
| Oneway | 2.1.0 |
| Baidu | 4.6.7 |
| MobPower | 1.0.0 |
| Nend | 5.3.1 |
| Maio | 1.5.0 |
| ks | 2.5.1.12 |
| sigmob | 2.15.2 |
| Ogury | 1.0.3 |

Android聚合SDK版本为4.1.2</br>

| Network | SDK Version |
|---|---|
|Facebook | 5.3.1 |
|Admob | 17.2.0 |
|Inmobi | 7.2.7 | 
|Flurry| 11.5.0 | 
|Applovin| 9.7.1 | 
|Mintegral | 9.12.4 |
|Mopub | 5.3.0 |
|GDT | 4.40.910|
|Chartboost | 7.2.0| 
|Tapjoy | 12.2.1 |
|Ironsource | 6.8.1|
|UnityAds | 3.1.0 |
|Vungle | 6.3.24 | 
|Adcolony | 3.3.10 | 
|TouTiao|v2.2.0.1|
|玩转互联 | 6.0.2  |
|Oneway|2.1.3|
|MobPower | 4.8.0 |
|Yeahmobi|4.0.6 |
|Appnext|2.4.5.472|
|Baidu|5.81 |
|Nend|5.1.0 |
|Maio|1.1.7 |
|StartApp|4.0.2|
|SuperAwesome|3.6.5|