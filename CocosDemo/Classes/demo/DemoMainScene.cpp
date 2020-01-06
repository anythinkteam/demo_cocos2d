
#include "DemoMainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
#include "ATCocosSdk.h"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
#include "bridge/ATCocosSdk.h"
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
    
    
    rvPlacementId = "b5b44a02bf08c0";
    interPlacementId = "b5bacad6860972";
    bannerPlacementId = "b5bacacef17717";
    nativePlacementId = "b5b0f55228375a";
    nativebannerPlacementId = "b5c2c6d50e7f44";
    
    
    
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android
    appId = "a5c4ad280995c9";
    appKey = "7b4e37f819dbee652ef79c4506e14288";
    rvPlacementId = "b5c4ad2f0de421";
    interPlacementId = "b5c4ad302ad418";
    bannerPlacementId = "b5c4ad2fa3ab6d";
    nativePlacementId = "b5c4ad2d34576b";
    nativebannerPlacementId = "b5c4ad2d34576b";
#endif
    
    ATCocosSdk::setDebugLog(true);
    ATCocosSdk::setChannel("test_cocos");
    cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
    
    customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
    
    ATCocosSdk::setCustomData(customDict);
    CCLOG("DemoMainScene::isEUTraffic " + ATCocosSdk::isEUTraffic()?"YES":"NO");
    CCLOG("DemoMainScene::getGDPRLevel %d", ATCocosSdk::getGDPRLevel());
    ATCocosSdk::setGDPRLevel(0);
    ATCocosSdk::initSDK(appId, appKey);
    int gdprLevel = ATCocosSdk::getGDPRLevel();

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
        switch (tag)
        {
            case 1: //show gdpr
                ATCocosSdk::showGdprAuthWithListener(this);
                break;
            case 2: //load native
            {
                ATCocosSdk::setNativeAdListener(this, nativePlacementId);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   // IOS
                ATCocosSdk::loadNativeAd(nativePlacementId, NULL);
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // Android

                //for toutiao native express
                auto glView = Director::getInstance()->getOpenGLView();
                auto frameSize = glView->getFrameSize();
                int width = frameSize.width;
                int height = frameSize.height;

                cocos2d::CCDictionary *localDict = cocos2d::CCDictionary::create();
                std::string widthStr = StringUtils::format("%d", width);
                std::string heightStr = StringUtils::format("%d", width *2/ 3);
                localDict->setObject(cocos2d::CCString::create(widthStr), "tt_image_width");
                localDict->setObject(cocos2d::CCString::create(heightStr), "tt_image_height");
                //for toutiao native express

                ATCocosSdk::loadNativeAd(nativePlacementId, localDict);
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
            }
                break;
            case 4: //clean native
                ATCocosSdk::removeNativeAd(nativePlacementId);
                break;
            case 5: //load native banner
            {
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
            }
          
                break;
            case 6: //show native banner
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
                    extraDict->setObject(cocos2d::CCString::create("true"), ATCocosSdk::KEY_BUTTON_CLOSE_STATUS);
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
                break;
            case 7: //clean native banner
                  ATCocosSdk::removeNativeBannerAd(nativebannerPlacementId);
                break;
            case 8: //load banner
            {
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
                
//                #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID   // IOS
//                cocos2d::CCDictionary * customDict = cocos2d::CCDictionary::create();
//                customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
//
//                ATCocosSdk::loadBannerAd(bannerPlacementId, customDict);
//                #endif
              
                customDict->setObject(cocos2d::CCString::create("custom_data_val"), "custom_data_key");
                
                ATCocosSdk::loadBannerAd(bannerPlacementId, customDict);
               
            }
              
                break;
                
            case 9: //show banner
            {
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
              
            }

                break;
                
            case 10: //clean banner
                 ATCocosSdk::removeBannerAd(bannerPlacementId);
                break;
                
            case 11: //load interstitial
                ATCocosSdk::setInterstitialAdListener(this, interPlacementId);
                ATCocosSdk::loadInterstitialAd(interPlacementId, NULL);
                break;
            case 12: //show interstitial
                if(ATCocosSdk::isInterstitialAdReady(interPlacementId)){
                    ATCocosSdk::showInterstitialAd(interPlacementId);
                }else{
                    CCLOG("ATCocosSdk::isInterstitialAdReady is false");
                }
                
                break;
            case 13: //load rewardedvideo
                ATCocosSdk::setRewardedVideoAdListener(this, rvPlacementId);
                ATCocosSdk::loadRewardedVideoAd(rvPlacementId, NULL, NULL);
                break;
            case 14: //show rewardedvideo
                if(ATCocosSdk::isRewardedVideoAdReady(rvPlacementId)){
                    ATCocosSdk::showRewardedVideoAd(rvPlacementId);
                }else{
                    CCLOG("ATCocosSdk::isRewardedVideoAdReady is false");
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
