//
//  ATNativeAdWrapper.m
//  UnityContainer
//
//  Created by Martin Lau on 27/07/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import "ATNativeAdWrapper.h"
#import "ATCocosUtils.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkNative/ATAdManager+Native.h>
#import <AnyThinkNative/ATNativeAdConfiguration.h>
#import <AnyThinkNative/ATNativeADView.h>
#import "MTAutolayoutCategories.h"
#include "ATCocosSdk.h"
#include "ATCocosNativeAdListener.h"


static NSString *const kParsedPropertiesFrameKey = @"frame";
static NSString *const kParsedPropertiesBackgroundColorKey = @"background_color";
static NSString *const kParsedPropertiesTextColorKey = @"text_color";
static NSString *const kParsedPropertiesTextSizeKey = @"text_size";

static NSString *const kNativeAssetAdvertiser = @"advertiser_label";
static NSString *const kNativeAssetText = @"text";
static NSString *const kNativeAssetTitle = @"title";
static NSString *const kNativeAssetCta = @"cta";
static NSString *const kNativeAssetRating = @"rating";
static NSString *const kNativeAssetIcon = @"icon";
static NSString *const kNativeAssetMainImage = @"main_image";
static NSString *const kNativeAssetSponsorImage = @"sponsor_image";
static NSString *const kNativeAssetMedia = @"media";

NSDictionary* parseCocosProperties(NSDictionary *properties) {
    NSMutableDictionary *result = NSMutableDictionary.dictionary;
    result[kParsedPropertiesFrameKey] = [NSString stringWithFormat:@"{{%@, %@}, {%@, %@}}", properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_X]], properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_Y]], properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]], properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]]];
    result[kParsedPropertiesBackgroundColorKey] = properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BACKGROUND_COLOR]];
    result[kParsedPropertiesTextColorKey] = properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TEXT_COLOR]];
    result[kParsedPropertiesTextSizeKey] = properties[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TEXT_SIZE]];

    return result;
}

NSDictionary* parseCocosMetrics(NSDictionary* metrics) {
    NSMutableDictionary *result = NSMutableDictionary.dictionary;
    NSDictionary *keysMap = @{[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_ICON]:kNativeAssetIcon, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_MAIN_IMAGE]:kNativeAssetMainImage, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TITLE]:kNativeAssetTitle, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_DESC]:kNativeAssetText, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_AD_LOGO]:kNativeAssetSponsorImage, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_CTA]:kNativeAssetCta};
    [keysMap enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) { result[keysMap[key]] = parseCocosProperties(metrics[key]); }];
    return result;
}

NSDictionary *parseNativeExtraJsonStr(NSString* jsonStr) {
    NSDictionary *extra = nil;
    if (jsonStr != nil) {
        NSDictionary *sizeDict = [NSJSONSerialization JSONObjectWithString:jsonStr options:NSJSONReadingAllowFragments error:nil];
        if ([sizeDict isKindOfClass:[NSDictionary class]]) {
            extra = @{kExtraInfoNativeAdSizeKey:[NSValue valueWithCGSize:CGSizeMake([sizeDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]] doubleValue], [sizeDict[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]] doubleValue])]};
        }
    }
    return extra;
}

@interface ATCocosNativeAdView:ATNativeADView
@property(nonatomic, readonly) UILabel *advertiserLabel;
@property(nonatomic, readonly) UILabel *textLabel;
@property(nonatomic, readonly) UILabel *titleLabel;
@property(nonatomic, readonly) UILabel *ctaLabel;
@property(nonatomic, readonly) UILabel *ratingLabel;
@property(nonatomic, readonly) UIImageView *iconImageView;
@property(nonatomic, readonly) UIImageView *mainImageView;
@property(nonatomic, readonly) UIImageView *sponsorImageView;
-(void) configureMetrics:(NSDictionary<NSString*, NSString*>*)metrics;
@end

@implementation ATCocosNativeAdView
-(void) initSubviews {
    [super initSubviews];
    _advertiserLabel = [UILabel new];
    [self addSubview:_advertiserLabel];
    
    _titleLabel = [UILabel new];
    [self addSubview:_titleLabel];
    
    _textLabel = [UILabel new];
    _textLabel.numberOfLines = 2;
    [self addSubview:_textLabel];
    
    _ctaLabel = [UILabel new];
    _ctaLabel.textAlignment = NSTextAlignmentCenter;
    [self addSubview:_ctaLabel];
    
    _ratingLabel = [UILabel new];
    [self addSubview:_ratingLabel];
    
    _iconImageView = [UIImageView new];
    _iconImageView.layer.cornerRadius = 4.0f;
    _iconImageView.layer.masksToBounds = YES;
    _iconImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_iconImageView];
    
    _mainImageView = [UIImageView new];
    _mainImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_mainImageView];
    
    _sponsorImageView = [UIImageView new];
    _sponsorImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_sponsorImageView];
    self.backgroundColor = [UIColor whiteColor];
}

-(NSArray<UIView*>*)clickableViews {
    NSMutableArray *clickableViews = [NSMutableArray arrayWithObjects:_iconImageView, _ctaLabel, nil];
    if (self.mediaView != nil) { [clickableViews addObject:self.mediaView]; }
    return clickableViews;
}

-(void) configureMetrics:(NSDictionary*)metrics {
    NSDictionary<NSString*, UILabel*> *viewsDict = @{[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TITLE]:_titleLabel, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_CTA]:_ctaLabel, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_DESC]:_textLabel, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_ICON]:_iconImageView, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_MAIN_IMAGE]:_mainImageView, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_PARENT]:self, [ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_RATING]:_ratingLabel};
    [viewsDict enumerateKeysAndObjectsUsingBlock:^(NSString * _Nonnull key, UILabel * _Nonnull obj, BOOL * _Nonnull stop) {
        NSDictionary *metric = metrics[key];
        if ([key isEqualToString:[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_PARENT]]) {
            obj.frame = CGRectMake(0, 0, [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]] doubleValue]);
        }else {
            obj.frame = CGRectMake([metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_X]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_Y]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]] doubleValue]);
        }
        NSString *bgColorStr = metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_BACKGROUND_COLOR]];
        if ([bgColorStr isKindOfClass:[NSString class]]) {
            if ([bgColorStr isEqualToString:@"clearColor"]) {
                obj.backgroundColor = [UIColor clearColor];
            } else {
                obj.backgroundColor = [UIColor colorWithHexString:bgColorStr];
            }
        }
        if ([obj respondsToSelector:@selector(setTextColor:)]) {
            NSString *textColor = metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TEXT_COLOR]];
            if ([textColor isEqualToString:@"clearColor"]) {
                obj.textColor = [UIColor clearColor];
            } else {
                obj.textColor = [UIColor colorWithHexString:textColor];
            }
        }
        
        if ([obj respondsToSelector:@selector(setFont:)]) { obj.font = [UIFont systemFontOfSize:[metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_TEXT_SIZE]] doubleValue]]; }
    }];
    self.mediaView.frame = self.mainImageView.frame;
}

@end

#define CS_ATNativeAdWrapper "ATNativeAdWrapper"
@interface ATNativeAdWrapper()
@property(nonatomic, readonly) NSMutableDictionary<NSString*, UIView*> *viewsStorage;
@end
@implementation ATNativeAdWrapper
+(instancetype)sharedInstance {
    static ATNativeAdWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ATNativeAdWrapper alloc] init];
    });
    return sharedInstance;
}

-(instancetype) init {
    self = [super init];
    if (self != nil) _viewsStorage = [NSMutableDictionary<NSString*, UIView*> new];
    return self;
}

-(void) loadNativeAdWithPlacementID:(NSString*)placementID extra:(NSString*)extraJsonStr {
    NSLog(@"ATNativeAdWrapper::loadNativeAdWithPlacementID:%@ extra:%@", placementID, extraJsonStr);
    NSDictionary *extra = parseNativeExtraJsonStr(extraJsonStr);
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:[extra isKindOfClass:[NSDictionary class]] ? extra : nil delegate:self];
}

-(BOOL) isNativeAdReadyForPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeAdWrapper::isNativeAdReadyForPlacementID:%@", placementID);
    return [[ATAdManager sharedManager] nativeAdReadyForPlacementID:placementID];
}

-(void) showNativeAdWithPlacementID:(NSString*)placementID metrics:(NSString*)metricsJSONString {
    NSLog(@"ATNativeAdWrapper::showNativeAdWithPlacementID:%@ metrics:%@", placementID, metricsJSONString);
    if ([self isNativeAdReadyForPlacementID:placementID]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            NSDictionary *metrics = [NSJSONSerialization JSONObjectWithString:metricsJSONString options:NSJSONReadingAllowFragments error:nil];
            
            UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
            [button addTarget:self action:@selector(noop) forControlEvents:UIControlEventTouchUpInside];
            button.frame = CGRectFromString(parseCocosProperties(metrics[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_PARENT]])[kParsedPropertiesFrameKey]);
            _viewsStorage[placementID] = button;
            
            ATNativeADConfiguration *config = [[ATNativeADConfiguration alloc] init];
            config.ADFrame = button.bounds;
            config.delegate = self;
            config.renderingViewClass = [ATCocosNativeAdView class];
            config.rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
            ATCocosNativeAdView *adView = [[ATAdManager sharedManager] retriveAdViewWithPlacementID:placementID configuration:config];
            adView.ctaLabel.hidden = [adView.nativeAd.ctaText length] == 0;
            NSLog(@"=====title：%@",adView.nativeAd.title);
            if (adView != nil) {
                [button addSubview:adView];
                [adView configureMetrics:metrics];
                [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:button];
                
                @try {
                    NSDictionary *metric = metrics[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_MAIN_IMAGE]];
                    CGRect mainImageFrame = CGRectMake([metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_X]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_POS_Y]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_WIDTH]] doubleValue], [metric[[ATCocosUtils nsstringFromCString:ATCocosSdk::KEY_HEIGHT]] doubleValue]);
                    
                    NSObject *dataObject = [adView valueForKeyPath:@"currentOffer.customObject"];
                    if ([dataObject isKindOfClass:NSClassFromString(@"GDTUnifiedNativeAdDataObject")] && [[dataObject valueForKeyPath:@"isVideoAd"] boolValue]) {
                        //视频广告
                        for (UIView *view in adView.subviews)
                        {
                            if ([NSStringFromClass([view class]) isEqualToString:@"GDTUnifiedNativeAdView"]) {
                                view.frame = mainImageFrame;
                                [adView bringSubviewToFront:view];
                            }
                        }
                    } else if ([dataObject isKindOfClass:NSClassFromString(@"BUNativeExpressAdView")]) {
                        for (UIView *view in adView.subviews)
                        {
                            if ([NSStringFromClass([view class]) isEqualToString:@"BUNativeExpressAdView"]) {
                                view.frame = adView.bounds;
                                [adView bringSubviewToFront:view];
                            }
                        }
                    } else if ([dataObject isKindOfClass:NSClassFromString(@"BUNativeExpressFeedVideoAdView")]) {
                        for (UIView *view in adView.subviews)
                        {
                            if ([NSStringFromClass([view class]) isEqualToString:@"BUNativeExpressFeedVideoAdView"]) {
                                view.frame = adView.bounds;
                                [adView bringSubviewToFront:view];
                            }
                        }
                    } else if ([dataObject isKindOfClass:NSClassFromString(@"GDTNativeExpressAdView")]) {
                        for (UIView *view in adView.subviews)
                        {
                            if ([NSStringFromClass([view class]) isEqualToString:@"UIView"]) {
                                for (UIView *childView in view.subviews)
                                {
                                    if ([NSStringFromClass([childView class]) isEqualToString:@"GDTNativeExpressAdView"]) {
                                        view.frame = adView.bounds;
                                        childView.frame = view.bounds;
                                        [adView bringSubviewToFront:view];
                                    }
                                }
                            }
                        }
                    }
                } @catch (NSException *exception) {
                    //
                } @finally {
                    //
                }
            }
        });
    }
}

-(void) noop {
    
}

-(void) removeNativeAdViewWithPlacementID:(NSString*)placementID {
    NSLog(@"ATNativeAdWrapper::removeNativeAdViewWithPlacementID:%@", placementID);
    [_viewsStorage[placementID] removeFromSuperview];
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

#pragma mark - delegate
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {
    NSLog(@"ATNativeAdWrapper::didFinishLoadingADWithPlacementID:%@", placementID);
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onNativeAdLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {
    NSLog(@"ATNativeAdWrapper::didFailToLoadADWithPlacementID:%@ error:%@", placementID, error);
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        
        NSMutableDictionary *errorDict = [NSMutableDictionary dictionaryWithObject:[NSString stringWithFormat:@"%ld", error.code] forKey:@"code"];
        if ([error.userInfo[NSLocalizedDescriptionKey] length] > 0) {
            errorDict[@"desc"] = error.userInfo[NSLocalizedDescriptionKey];
        } else {
            errorDict[@"desc"] = @"";
        }
        if ([error.userInfo[NSLocalizedFailureReasonErrorKey] length] > 0) {
            errorDict[@"reason"] = error.userInfo[NSLocalizedFailureReasonErrorKey];
        } else {
            errorDict[@"reason"] = @"";
        }
        pDelegate->onNativeAdLoadFailed(cPlacementId, errorDict.jsonString.UTF8String);
    }
}

#pragma mark - delegate with networkID and adsourceID
-(void) didStartPlayingVideoInAdView:(ATNativeADView *)adView placementID:(NSString *)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeAdWrapper::didStartPlayingVideoInAdView: placementID:%@ extra:%@", placementID, extra);
    //Drop ad view
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdVideoStartWithExtra(cPlacementId, cExtra);
    }
}

-(void) didEndPlayingVideoInAdView:(ATNativeADView *)adView placementID:(NSString *)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeAdWrapper::didEndPlayingVideoInAdView: placementID:%@ extra:%@", placementID, extra);
    //Drop ad view
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdVideoEndWithExtra(cPlacementId, cExtra);
    }
}

-(void) didClickNativeAdInAdView:(ATNativeADView *)adView placementID:(NSString *)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeAdWrapper::didClickNativeAdInAdView: placementID:%@ extra:%@", placementID, extra);
    //Drop ad view
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdClickWithExtra(cPlacementId, cExtra);
    }
}

-(void) didShowNativeAdInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeAdWrapper::didShowNativeAdInAdView: placementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdShowWithExtra(cPlacementId, cExtra);
    }
}

-(void) didTapCloseButtonInAdView:(ATNativeADView *)adView placementID:(NSString *)placementID extra:(NSDictionary *)extra {
    NSLog(@"ATNativeAdWrapper::didTapCloseButtonInAdView: placementID:%@ extra:%@", placementID, extra);
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdCloseButtonTappedWithExtra(cPlacementId, cExtra);
    }
}

-(void) didEnterFullScreenVideoInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeViewController:: didEnterFullScreenVideoInAdView:placementID:%@ extra:%@", placementID, extra);
}


@end
