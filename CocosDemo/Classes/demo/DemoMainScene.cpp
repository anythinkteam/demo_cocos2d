
#include "DemoMainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
#include "ATCocosSdk.h"
#include "ATNativeItemProperty.h"
#include "ATNativeProperty.h"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
#include "bridge/ATCocosSdk.h"
#include "bridge/ATNativeItemProperty.h"
#include "bridge/ATNativeProperty.h"
#endif


#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif


#define UPARPUSDK_APPID   "a5aa1f9deda26d"
#define UPARPUSDK_APPKEY   "4f7b9ac17decb9babec83aac078742c7"


USING_NS_CC;

Scene* DemoMainScene::createScene()
{
    return DemoMainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DemoMainScene.cpp\n");
}



// on "init" you need to initialize your instance
bool DemoMainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DemoMainScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

//    UparpuSDK::initSDK(UPARPUSDK_APPID,UPARPUSDK_APPKEY);

//    addInitSDKButton();
//    addJump2VideoButton();
//    addJump2InterstitialButton();
//    addJump2BannerButton();

    addGDPRButton();
    initLoadNativeAdBtn();
    initShowNativeAdBtn();
    initCleanNativeAdBtn();

    initLoadNativeBannerBtn();
    initShowNativeBannerBtn();
    initCleanNativeBannerBtn();

    initLoadBannerBtn();
    initShowBannerBtn();
    initCleanBannerBtn();

    initLoadInterstitialBtn();
    initShowInterstitialBtn();

    initLoadRewardedVideoBtn();
    initShowRewardedVideoBtn();
//    addSetGDPRLevelButton();
//    addIsEUTrafficButton();
//    addshowSplashBannerButton();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
    appId = "a5b0e8491845b3";
    appKey = "7eae0567827cfe2b22874061763f30c9";
    
//    myoffer
    rvPlacementId = "b5db6c247dbb1e";
    interPlacementId = "b5db6c26999c31";
    bannerPlacementId = "b5f33c3231eb91";
    nativePlacementId = "b5f33878ee0646";
    nativebannerPlacementId = "b5f33878ee0646";
    
    
    
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
    appId = "a5aa1f9deda26d";
    appKey = "4f7b9ac17decb9babec83aac078742c7";
    rvPlacementId = "b5b449fb3d89d7";
    interPlacementId = "b5baca53984692";
    bannerPlacementId = "b5baca4f74c3d8";
    nativePlacementId = "b5aa1fa2cae775";
    nativebannerPlacementId = "b5aa1fa2cae775";
#endif
    
    ATCocosSdk::setDebugLog(true);
    ATCocosSdk::setChannel("test_cocos_channel");
    ATCocosSdk::setSubChannel("test_cocos_sub_channel");

    //custom rule for app
    cocos2d::ValueMap customDict;
    customDict["custom_data_key"] = "custom_data_value";
    ATCocosSdk::setCustomData(customDict);
    
    cocos2d::ValueVector vector;
    vector.push_back(cocos2d::Value(ATCocosSdk::OS_VERSION_NAME));
    vector.push_back(cocos2d::Value(ATCocosSdk::OS_VERSION_CODE));
    vector.push_back(cocos2d::Value(ATCocosSdk::APP_PACKAGE_NAME));
    vector.push_back(cocos2d::Value(ATCocosSdk::APP_VERSION_NAME));
    vector.push_back(cocos2d::Value(ATCocosSdk::APP_VERSION_CODE));

    vector.push_back(cocos2d::Value(ATCocosSdk::BRAND));
    vector.push_back(cocos2d::Value(ATCocosSdk::MODEL));
    vector.push_back(cocos2d::Value(ATCocosSdk::DEVICE_SCREEN_SIZE));
    vector.push_back(cocos2d::Value(ATCocosSdk::MNC));
    vector.push_back(cocos2d::Value(ATCocosSdk::MCC));
    
    vector.push_back(cocos2d::Value(ATCocosSdk::LANGUAGE));
    vector.push_back(cocos2d::Value(ATCocosSdk::TIMEZONE));
    vector.push_back(cocos2d::Value(ATCocosSdk::USER_AGENT));
    vector.push_back(cocos2d::Value(ATCocosSdk::ORIENTATION));
    vector.push_back(cocos2d::Value(ATCocosSdk::NETWORK_TYPE));
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
    vector.push_back(cocos2d::Value(ATCocosSdk::INSTALLER));
    vector.push_back(cocos2d::Value(ATCocosSdk::ANDROID_ID));
    vector.push_back(cocos2d::Value(ATCocosSdk::GAID));
    vector.push_back(cocos2d::Value(ATCocosSdk::MAC));
    vector.push_back(cocos2d::Value(ATCocosSdk::IMEI));
    vector.push_back(cocos2d::Value(ATCocosSdk::OAID));
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS

    vector.push_back(cocos2d::Value(ATCocosSdk::IDFA));
    vector.push_back(cocos2d::Value(ATCocosSdk::IDFV));
#endif

    //隐私上报控制
    ATCocosSdk::deniedUploadDeviceInfo(vector);

    //custom rule for placmenet
    cocos2d::ValueMap plcamentCustomDict;
    plcamentCustomDict["placement_custom_data_key"] = "placement_custom_data_value";
    ATCocosSdk::setPlacementCustomData(rvPlacementId, plcamentCustomDict);

    //check is in EU
    ATCocosSdk::getUserLocation(this);

    CCLOG("DemoMainScene::isEUTraffic %s", ATCocosSdk::isEUTraffic()?"YES":"NO");

    int gdpr_level = ATCocosSdk::getGDPRLevel();
    CCLOG("DemoMainScene::getGDPRLevel %d", gdpr_level);
    if (gdpr_level == ATCocosSdk::GDPR_PERSONALIZED) {
        CCLOG("%s", "DemoMainScene 同意上报隐私数据");
    };
//    ATCocosSdk::setGDPRLevel(0);
    ATCocosSdk::integrationChecking();
    ATCocosSdk::initSDK(appId, appKey);
//    int gdprLevel = ATCocosSdk::getGDPRLevel();

    return true;
}


void DemoMainScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    #endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


void  DemoMainScene::addGDPRButton()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("showgdpr ");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);

    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setTag(1);

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 20) + origin.y));
    this->addChild(button,1);
}


void  DemoMainScene::initLoadNativeAdBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Load NativeAd");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);

    button->setOpacity(100); //继承自node，设置node透明度，0完全透明
    button->setTag(2);
    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 50) + origin.y));

    this->addChild(button,1);
}

void  DemoMainScene::initShowNativeAdBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Show NativeAd");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(3);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10, (visibleSize.height - 50) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initCleanNativeAdBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Clean NativeAd");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);

    button->setOpacity(100); //继承自node，设置node透明度，0完全透明
    button->setTag(4);
    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10 + 50 +10, (visibleSize.height - 50) + origin.y));
    this->addChild(button,1);
}



void  DemoMainScene::initLoadNativeBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Load NativeBanner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(5);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 50 - 30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initShowNativeBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Show NativeBanner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);

    button->setOpacity(100); //继承自node，设置node透明度，0完全透明
    button->setTag(6);
    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10, (visibleSize.height - 50 - 30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initCleanNativeBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Clean NativeBanner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(7);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10 + 50 +10, (visibleSize.height - 50 - 30) + origin.y));
    this->addChild(button,1);
}


/**--------------------------------------------------------- Banner -----------------------------------------------------------------**/
void  DemoMainScene::initLoadBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Load Banner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(8);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 50 - 30 - 30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initShowBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Show Banner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(9);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10, (visibleSize.height - 50 - 30 - 30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initCleanBannerBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Clean Banner");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(10);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10 + 50 +10, (visibleSize.height - 50 - 30 - 30) + origin.y));
    this->addChild(button,1);
}

/**--------------------------------------------------------- Interstitial -----------------------------------------------------------------**/
void  DemoMainScene::initLoadInterstitialBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Load Interstitial");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(11);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 50 - 30 - 30 - 30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initShowInterstitialBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Show Interstitial");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(12);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10, (visibleSize.height - 50 - 30 - 30 -30) + origin.y));
    this->addChild(button,1);
}

/**--------------------------------------------------------- RewardedVideo -----------------------------------------------------------------**/
void  DemoMainScene::initLoadRewardedVideoBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Load Video");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(13);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25, (visibleSize.height - 50 - 30 - 30 -30 -30) + origin.y));
    this->addChild(button,1);
}

void  DemoMainScene::initShowRewardedVideoBtn()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto button = cocos2d::ui::Button::create("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");  //使用图片创建Button
    auto button = cocos2d::ui::Button::create();   //创建一个Button，纹理贴图后面添加
    //button->loadTextures("button/Button01.png", "button/Button01Pressed.png", "button/Button01Disabled.png");
    button->loadTextureNormal("CloseNormal.png");
    button->loadTexturePressed("CloseSelected.png");
    button->loadTextureDisabled("CloseNormal.png");

    button->setPressedActionEnabled(false); //设置启用按钮被按下时的缩放操作

    button->setScale9Enabled(true);   //打开scale9 可以拉伸图片

    button->setTitleText("Show Video");     //设置按钮标题,还有其他函数可以设置颜色，字体大小
    button->setTitleFontSize(6.0);
    button->setTag(14);
    button->setOpacity(100); //继承自node，设置node透明度，0完全透明

    button->addTouchEventListener(CC_CALLBACK_2(DemoMainScene::initClickEvent,this));    //设置按钮的触摸事件和作用目标（继承自Widget）

    button->setContentSize(Size(50, 20));     //设置按钮大小，必须setScale9Enabled(true)，不然没有用
    button->setPosition(Vec2(origin.x + 25 + 50 + 10, (visibleSize.height  - 50 - 30 - 30 -30 -30) + origin.y));
    this->addChild(button,1);
}

void DemoMainScene::initNetworkBtn() {
    
}
//按钮的触摸事件回掉函数
void DemoMainScene::initClickEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)//判断点击类型，钮结束按下的
    {
        int tag = ((cocos2d::ui::Button*)pSender)->getTag();
        switch (tag) {
            case 1: //show gdpr
                ATCocosSdk::showGdprAuthWithListener(this);
                break;
            case 2: //load native
            {
                ATCocosSdk::setNativeAdListener(this, nativePlacementId);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;


                std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 4 / 5)/ATCocosSdk::getScreenScale()));
                cocos2d::ValueMap localExtra;
                localExtra[ATCocosSdk::KEY_WIDTH] = widthStr;
                localExtra[ATCocosSdk::KEY_HEIGHT] = heightStr;
                //for toutiao native express

                ATCocosSdk::loadNativeAd(nativePlacementId, localExtra);
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android

                //for toutiao native express
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;


                std::string widthStr = StringUtils::format("%d", width);
                std::string heightStr = StringUtils::format("%d", width * 4 / 5);
                cocos2d::ValueMap localExtra;
                localExtra[ATCocosSdk::KEY_WIDTH] = widthStr;
                localExtra[ATCocosSdk::KEY_HEIGHT] = heightStr;
                //for toutiao native express

                ATCocosSdk::loadNativeAd(nativePlacementId, localExtra);
#endif

            }

                break;
            case 3: //show native
            {
                Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();

                auto *glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();


                if (ATCocosSdk::isNativeAdReady(nativePlacementId)) {

                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;


                    cocos2d::ValueMap rectDict;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    int ptHight = height/ATCocosSdk::getScreenScale();
                    int parentWidth = width/ATCocosSdk::getScreenScale();
                    int parentHeight = (width * 4/5)/ATCocosSdk::getScreenScale();
                    int appIconSize = (width / 7)/ATCocosSdk::getScreenScale();
                    int padding = (width / 35)/ATCocosSdk::getScreenScale();
                    

                    ATNativeProperty property = ATNativeProperty();
                    property.parent = ATNativeItemProperty(0, ptHight - parentHeight, parentWidth, parentHeight, "#ffffff", "", 0);
                    property.cta = ATNativeItemProperty(parentWidth-appIconSize*2, parentHeight - appIconSize, appIconSize*2, appIconSize, "#2095F1" , "#000000", appIconSize/3);
                    property.icon = ATNativeItemProperty(0, parentHeight - appIconSize, appIconSize,appIconSize ,"clearColor", "",0);
                    property.mainImage = ATNativeItemProperty(padding ,padding, parentWidth-2*padding, parentHeight - appIconSize - 2*padding, "#ffffff", "#000000", 14);
                    property.title = ATNativeItemProperty(appIconSize + padding , parentHeight - appIconSize, parentWidth - 3* appIconSize -2 * padding, appIconSize/2 , "#ffffff" , "#000000", appIconSize/3);
                    property.desc = ATNativeItemProperty(appIconSize + padding , parentHeight - appIconSize/2, parentWidth - 3* appIconSize -2 * padding, appIconSize/2 , "#ffffff" , "#000000", appIconSize/4);
                    
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android

                    int parentWidth = width;
                    int parentHeight = width * 4 / 5;
                    int appIconSize = width / 7;
                    int padding = width / 35;

                    ATNativeProperty property = ATNativeProperty();
                    property.parent = ATNativeItemProperty(0, height - parentHeight, parentWidth, parentHeight, "#ffffff", "", 0);
                    property.cta = ATNativeItemProperty(parentWidth-appIconSize*2, parentHeight - appIconSize, appIconSize*2, appIconSize, "#2095F1" , "#000000", appIconSize/3);
                    property.icon = ATNativeItemProperty(0, parentHeight - appIconSize, appIconSize,appIconSize ,"", "",0);
                    property.mainImage = ATNativeItemProperty(padding ,padding, parentWidth-2*padding, parentHeight - appIconSize - 2*padding, "#ffffff", "#000000", 14);
                    property.title = ATNativeItemProperty(appIconSize + padding , parentHeight - appIconSize, parentWidth - 3* appIconSize -2 * padding, appIconSize/2 , "" , "#000000", appIconSize/3);
                    property.desc = ATNativeItemProperty(appIconSize + padding , parentHeight - appIconSize/2, parentWidth - 3* appIconSize -2 * padding, appIconSize/2 , "#ffffff" , "#000000", appIconSize/4);
//                    property.adLogo = ATNativeItemProperty(0,0,0,0,"#ffffff","#ffffff",14);
//                    property.rating = ATNativeItemProperty(0,0,0,0,"#ffffff","#ffffff",14);
#endif
                    ATCocosSdk::showNativeAd(nativePlacementId, property.toJsonString());
                } else {
                    CCLOG("%s", "ATCocosSdk::isNativeAdReady is false");
                }
            }
                break;
            case 4: //clean native
                ATCocosSdk::removeNativeAd(nativePlacementId);
                break;
            case 5: //load native banner
            {
                ATCocosSdk::setNativeBannerAdListener(this, nativebannerPlacementId);

                cocos2d::ValueMap extra;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;
                
                std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                extra[ATCocosSdk::KEY_WIDTH] = widthStr;
                extra[ATCocosSdk::KEY_HEIGHT] = heightStr;

#endif

                extra["custom_data__key"] = "custom_data_value";

                ATCocosSdk::loadNativeBannerAd(nativebannerPlacementId, extra);
            }

                break;
            case 6: //show native banner
                if (ATCocosSdk::isNativeBannerAdReady(nativebannerPlacementId)) {
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;


                    cocos2d::ValueMap rectDict;
                    cocos2d::ValueMap extraDict;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                    std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/ATCocosSdk::getScreenScale()));


                    rectDict[ATCocosSdk::KEY_POS_X] = "0";
                    rectDict[ATCocosSdk::KEY_POS_Y] = yStr;
                    rectDict[ATCocosSdk::KEY_WIDTH] = widthStr;
                    rectDict[ATCocosSdk::KEY_HEIGHT] = heightStr;

                    rectDict[ATCocosSdk::KEY_MAIN_BG_COLOR] = "#ffffff";
                    rectDict[ATCocosSdk::KEY_REFRESH_INTERVEL] = "5";
                    rectDict[ATCocosSdk::KEY_BUTTON_CLOSE_STATUS] = "true";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_BG] = "#000000";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT] = "12";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR] = "#ffffff";
                    rectDict[ATCocosSdk::KEY_TITLE_FONT] = "12";
                    rectDict[ATCocosSdk::KEY_TITLE_COLOR] = "#000000";
                    rectDict[ATCocosSdk::KEY_TEXT_FONT] = "12";
                    rectDict[ATCocosSdk::KEY_TEXT_COLOR] = "#000000";
                    rectDict[ATCocosSdk::KEY_ADVERTISER_TEXT_FONT] = "10";
                    rectDict[ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR] = "#000000";
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
                    std::string widthStr = StringUtils::format("%d", width);
                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);

                    rectDict[ATCocosSdk::KEY_POS_X] = "0";
                    rectDict[ATCocosSdk::KEY_POS_Y] = yStr;
                    rectDict[ATCocosSdk::KEY_WIDTH] = widthStr;
                    rectDict[ATCocosSdk::KEY_HEIGHT] = heightStr;

                    rectDict[ATCocosSdk::KEY_MAIN_BG_COLOR] = "#ffffff";
                    rectDict[ATCocosSdk::KEY_REFRESH_INTERVEL] = "10000";
                    rectDict[ATCocosSdk::KEY_BUTTON_CLOSE_STATUS] = "false";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_BG] = "#000000";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_TITLE_FONT] = "12";
                    rectDict[ATCocosSdk::KEY_BUTTON_CTA_TITLE_COLOR] = "#ffffff";
                    rectDict[ATCocosSdk::KEY_TITLE_COLOR] = "#000000";
                    rectDict[ATCocosSdk::KEY_TEXT_COLOR] = "#000000";
                    rectDict[ATCocosSdk::KEY_ADVERTISER_TEXT_COLOR] = "#000000";
                    rectDict[ATCocosSdk::KEY_IS_SHOW_CTA] = "true";
                    rectDict[ATCocosSdk::KEY_BANNER_SIZE_TYPE] = "3";

#endif

                    ATCocosSdk::showNativeBannerAd(nativebannerPlacementId, rectDict, extraDict);

                } else {
                    CCLOG("%s", "ATCocosSdk::isNativeBannerAdReady is false");
                }
                break;
            case 7: //clean native banner
                ATCocosSdk::removeNativeBannerAd(nativebannerPlacementId);
                break;
            case 8: //load banner
            {
                ATCocosSdk::setBannerAdListener(this, bannerPlacementId);

                cocos2d:
                ValueMap customDict;


                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
                std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
                std::string widthStr = StringUtils::format("%d", width);
                std::string heightStr = StringUtils::format("%d", width * 50 / 320);
#endif

                customDict[ATCocosSdk::KEY_WIDTH] = widthStr;
                customDict[ATCocosSdk::KEY_HEIGHT] = heightStr;

                customDict[ATCocosSdk::KEY_ADAPTIVE_WIDTH] = widthStr;
                customDict[ATCocosSdk::KEY_ADAPTIVE_ORIENTATION] = ATCocosSdk::ADAPTIVE_ORIENTATION_CURRENT;
//                customDict[ATCocosSdk::KEY_ADAPTIVE_ORIENTATION] = ATCocosSdk::ADAPTIVE_ORIENTATION_PORTRAIT;
//                customDict[ATCocosSdk::KEY_ADAPTIVE_ORIENTATION] = ATCocosSdk::ADAPTIVE_ORIENTATION_LANDSCAPE;

                ATCocosSdk::loadBannerAd(bannerPlacementId, customDict);

            }

                break;

            case 9: //show banner
            {
                if (ATCocosSdk::isBannerAdReady(bannerPlacementId)) {
                    auto glView = Director::getInstance()->getOpenGLView();
                    auto frameSize = glView->getFrameSize();
                    int width = frameSize.width;
                    int height = frameSize.height;



#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
//                    cocos2d::ValueMap rectDict;
//                    std::string widthStr = StringUtils::format("%d", (int)(width/ATCocosSdk::getScreenScale()));
//                    std::string heightStr = StringUtils::format("%d", (int)((width * 50 / 320)/ATCocosSdk::getScreenScale()));
//                    std::string yStr = StringUtils::format("%d", (int)((height - width * 50 / 320- 10)/ATCocosSdk::getScreenScale()));
//
//                    rectDict[ATCocosSdk::KEY_POS_X] = "0";
//                    rectDict[ATCocosSdk::KEY_POS_Y] = yStr;
//                    rectDict[ATCocosSdk::KEY_WIDTH] = widthStr;
//                    rectDict[ATCocosSdk::KEY_HEIGHT] = heightStr;

#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    // android
//                    cocos2d::ValueMap rectDict;
//                    std::string widthStr = StringUtils::format("%d", width);
//                    std::string heightStr = StringUtils::format("%d", width * 150 / 960);
//                    std::string yStr = StringUtils::format("%d", height - width * 150 / 960);
//
//                    rectDict[ATCocosSdk::KEY_POS_X] = "0";
//                    rectDict[ATCocosSdk::KEY_POS_Y] = yStr;
//                    rectDict[ATCocosSdk::KEY_WIDTH] = widthStr;
//                    rectDict[ATCocosSdk::KEY_HEIGHT] = heightStr;
#endif

//                    ATCocosSdk::showBannerAd(bannerPlacementId, rectDict);
                    ATCocosSdk::showBannerAdInPostion(bannerPlacementId, ATCocosSdk::KEY_BOTTOM);
                } else {
                    CCLOG("%s", "ATCocosSdk::isBannerAdReady is false");
                }

            }

                break;

            case 10: //clean banner
                ATCocosSdk::removeBannerAd(bannerPlacementId);
                break;

            case 11: //load interstitial
            {
                ATCocosSdk::setInterstitialAdListener(this, interPlacementId);
                cocos2d::ValueMap extra;
                extra[ATCocosSdk::KEY_USE_REWARDED_VIDEO_AS_INTERSTITIAL] = false;
                ATCocosSdk::loadInterstitialAd(interPlacementId, extra);
            }
                break;
            case 12: //show interstitial
            {
                char *interstitialAdStatusInfo = ATCocosSdk::checkInterstitialAdStatus(interPlacementId);
                CCLOG("DemoMainScene::checkInterstitialAdStatus %s", interstitialAdStatusInfo);

                if (ATCocosSdk::isInterstitialAdReady(interPlacementId)) {
//                    ATCocosSdk::showInterstitialAd(interPlacementId);
                    ATCocosSdk::showInterstitialAdInScenario(interPlacementId,
                                                             "f5e54937b0483d");//show with scenario
                } else {
                    CCLOG("%s", "ATCocosSdk::isInterstitialAdReady is false");
                }
            }
                break;
            case 13: //load rewardedvideo
            {
                ATCocosSdk::setRewardedVideoAdListener(this, rvPlacementId);

                cocos2d::ValueMap extra;
                extra[ATCocosSdk::KEY_USER_ID] = "test_user_id";
                extra[ATCocosSdk::KEY_MEDIA_EXT] = "test_user_data";

                ATCocosSdk::loadRewardedVideoAd(rvPlacementId, extra);
            }
                break;
            case 14: //show rewardedvideo
            {
                char *rewardVideoAdStatusInfo = ATCocosSdk::checkRewardedVideoAdStatus(rvPlacementId);
                CCLOG("DemoMainScene::checkRewardedVideoAdStatus %s", rewardVideoAdStatusInfo);

                if(ATCocosSdk::isRewardedVideoAdReady(rvPlacementId)){
//                    ATCocosSdk::showRewardedVideoAd(rvPlacementId);
                    ATCocosSdk::showRewardedVideoAdInScenario(rvPlacementId, "f5e5492eca9668");//show with scenario
                }else{
                    CCLOG("%s", "ATCocosSdk::isRewardedVideoAdReady is false");
                }
            }
                break;
        }
    }
    
}


#pragma mark -实现各种回调事件
//rewardedVideo listener
void DemoMainScene::onRewardedVideoLoadSuccess(const char * placementId) {
    log("DemoMainScene::onRewardedVideoLoadSuccess %s", placementId);
}

void DemoMainScene::onRewardedVideoLoadFailed(const char * placementId, const char * errorString) {
    log("DemoMainScene::onRewardedVideoLoadFailed %s, error:%s", placementId, errorString);
}

//rewardedVideo delegate with extra

void DemoMainScene::onRewardedVideoDidRewardSuccessWithExtra(const char * placementId,const char * extra) {
    log("DemoMainScene::onRewardedVideoDidRewardSuccessWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onRewardedVideoPlayStartWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onRewardedVideoPlayStartWithExtra %s , %s", placementId, extra);
}

void DemoMainScene::onRewardedVideoPlayEndWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onRewardedVideoPlayEnd %s with extra %s", placementId,extra);
}

void DemoMainScene::onRewardedVideoShowFailWithExtra(const char * placementId, const char * errorString, const char * extra) {
    log("DemoMainScene::onRewardedVideoShowFail %s, error:%s with extra:%s", placementId, errorString,extra);
}

void DemoMainScene::onRewardedVideoCloseWithExtra(const char * placementId, bool isRewarded, const char * extra) {
    log("DemoMainScene::onRewardedVideoClose %s, isRewarded:%s , with extra:%s", placementId, isRewarded?"true":"false",extra);
}

void DemoMainScene::onRewardedVideoClickedWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onRewardedVideoClicked %s with extra %s", placementId,extra);
}



//interstitial listener
void DemoMainScene::onInterstitalLoadSuccess(const char * placementId) {
    log("DemoMainScene::onInterstitalLoadSuccess %s", placementId);
}

void DemoMainScene::onInterstitalLoadFailed(const char * placementId, const char * errorString) {
    log("DemoMainScene::onInterstitalLoadFailed %s, error:%s", placementId, errorString);
}

//interstitial extra
void DemoMainScene::onInterstitalShowWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onInterstitalShowWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onInterstitalCloseWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onInterstitalCloseWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onInterstitalClickedWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onInterstitalClickedWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onInterstitalPlayStartWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onInterstitalPlayStartWithExtra %s with extra %s", placementId,extra);
}
void DemoMainScene::onInterstitalPlayEndWithExtra(const char * placementId, const char * extra) {
    log("DemoMainScene::onInterstitalPlayEndWithExtra %s with extra %s", placementId,extra);
}

//banner listener
void DemoMainScene::onBannerAdLoadSuccess(const char * placementId) {
    log("DemoMainScene::onBannerAdLoadSuccess %s", placementId);
}

void DemoMainScene::onBannerAdLoadFailed(const char * placementId, const char * errorString) {
    log("DemoMainScene::onBannerAdLoadFailed %s, error:%s", placementId, errorString);
}

//banner extra
void DemoMainScene::onBannerShowWithExtra(const char *placementId, const char *extra) {
    log("DemoMainScene::onBannerShowWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onBannerClickedWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onBannerClickedWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onBannerCloseWithExtra(const char *placementId, const char *extra) {
    log("DemoMainScene::onBannerCloseWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onBannerAutoRefreshWithExtra(const char *placementId, const char *extra) {
    log("DemoMainScene::onBannerAutoRefreshWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onBannerAutoRefreshFailWithExtra(const char *placementId, const char *errorString, const char *extra) {
    log("DemoMainScene::onBannerAutoRefreshFailWithExtra %s, error:%s with extra %s", placementId, errorString,extra);
}

//native listener

void DemoMainScene::onNativeAdLoadSuccess(const char * placementId){
    log("DemoMainScene::onNativeAdLoadSuccess %s", placementId);
}

void DemoMainScene::onNativeAdLoadFailed(const char * placementId, const char * errorString){
    log("DemoMainScene::onNativeAdLoadFailed %s, error:%s", placementId, errorString);
}

//native extra
void DemoMainScene::onNativeAdVideoStartWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeAdVideoStartWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeAdVideoEndWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeAdVideoEndWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeAdShowWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeAdShowWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeAdClickWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeAdClickWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeAdCloseButtonTappedWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeAdCloseButtonTappedWithExtra %s with extra %s", placementId,extra);
}
//native banner
void DemoMainScene::onNativeBannerAdLoadSuccess(const char * placementId){
    log("DemoMainScene::onNativeBannerAdLoadSuccess %s", placementId);
}

void DemoMainScene::onNativeBannerAdLoadFailed(const char * placementId, const char * errorString){
    log("DemoMainScene::onNativeBannerAdLoadFailed %s, error:%s", placementId, errorString);
}


//native banner extra
void DemoMainScene::onNativeBannerShowWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeBannerShowWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeBannerClickedWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeBannerClickedWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeBannerAutoRefreshFailWithExtra(const char *placementId, const char *errorString, const char *extra){
    log("DemoMainScene::onNativeBannerAutoRefreshFailWithExtra %s, error:%s with extra %s", placementId, errorString,extra);
}

void DemoMainScene::onNativeBannerCloseWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeBannerCloseWithExtra %s with extra %s", placementId,extra);
}

void DemoMainScene::onNativeBannerAutoRefreshWithExtra(const char *placementId, const char *extra){
    log("DemoMainScene::onNativeBannerAutoRefreshWithExtra %s with extra %s", placementId,extra);
}

//gdpr listener

void DemoMainScene::onGDPRDataConsentSet(int dataConsent){
    log("DemoMainScene::onGDPRDataConsentSet %d",dataConsent);
}

void DemoMainScene::onPageLoadFail(){
    log("DemoMainScene::onPageLoadFail");
}

void DemoMainScene::onUserLocation(int location){

    log("DemoMainScene::onUserLocation %d", location);
    if (location == ATCocosSdk::USER_LOCATION_IN_EU) {
        log("DemoMainScene::onUserLocation 当前位于欧盟地区");
    };
}
