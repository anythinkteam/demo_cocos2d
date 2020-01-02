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

NSDictionary* parseUnityProperties(NSDictionary *properties) {
    NSMutableDictionary *result = NSMutableDictionary.dictionary;
    result[kParsedPropertiesFrameKey] = [NSString stringWithFormat:@"{{%@, %@}, {%@, %@}}", properties[@"x"], properties[@"y"], properties[@"width"], properties[@"height"]];
    result[kParsedPropertiesBackgroundColorKey] = properties[@"backgroundColor"];
    result[kParsedPropertiesTextColorKey] = properties[@"textColor"];
    result[kParsedPropertiesTextSizeKey] = properties[@"textSize"];

    return result;
}

NSDictionary* parseUnityMetrics(NSDictionary* metrics) {
    NSMutableDictionary *result = NSMutableDictionary.dictionary;
    NSDictionary *keysMap = @{@"appIcon":kNativeAssetIcon, @"mainImage":kNativeAssetMainImage, @"title":kNativeAssetTitle, @"desc":kNativeAssetText, @"adLogo":kNativeAssetSponsorImage, @"cta":kNativeAssetCta};
    [keysMap enumerateKeysAndObjectsUsingBlock:^(id  _Nonnull key, id  _Nonnull obj, BOOL * _Nonnull stop) { result[keysMap[key]] = parseUnityProperties(metrics[key]); }];
    return result;
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
    _advertiserLabel = [UILabel autolayoutLabelFont:[UIFont boldSystemFontOfSize:15.0f] textColor:[UIColor blackColor] textAlignment:NSTextAlignmentLeft];
    [self addSubview:_advertiserLabel];
    
    _titleLabel = [UILabel autolayoutLabelFont:[UIFont boldSystemFontOfSize:18.0f] textColor:[UIColor blackColor] textAlignment:NSTextAlignmentLeft];
    [self addSubview:_titleLabel];
    
    _textLabel = [UILabel autolayoutLabelFont:[UIFont systemFontOfSize:12.0f] textColor:[UIColor blackColor]];
    _textLabel.numberOfLines = 2;
    [self addSubview:_textLabel];
    
    _ctaLabel = [UILabel autolayoutLabelFont:[UIFont systemFontOfSize:15.0f] textColor:[UIColor blackColor]];
    _ctaLabel.textAlignment = NSTextAlignmentCenter;
    [self addSubview:_ctaLabel];
    
    _ratingLabel = [UILabel autolayoutLabelFont:[UIFont systemFontOfSize:15.0f] textColor:[UIColor blackColor]];
    [self addSubview:_ratingLabel];
    
    _iconImageView = [UIImageView autolayoutView];
    _iconImageView.layer.cornerRadius = 4.0f;
    _iconImageView.layer.masksToBounds = YES;
    _iconImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_iconImageView];
    
    _mainImageView = [UIImageView autolayoutView];
    _mainImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_mainImageView];
    
    _sponsorImageView = [UIImageView autolayoutView];
    _sponsorImageView.contentMode = UIViewContentModeScaleAspectFit;
    [self addSubview:_sponsorImageView];
    self.backgroundColor = [UIColor whiteColor];
}

-(NSArray<UIView*>*)clickableViews {
    NSMutableArray *clickableViews = [NSMutableArray arrayWithObjects:_iconImageView, _ctaLabel, nil];
    if (self.mediaView != nil) { [clickableViews addObject:self.mediaView]; }
    return clickableViews;
}

-(void) layoutMediaView {
    self.mediaView.frame = CGRectMake(0, 120.0f, CGRectGetWidth(self.bounds), CGRectGetHeight(self.bounds) - 120.0f);
}

-(void) makeConstraintsForSubviews {
    [super makeConstraintsForSubviews];
    NSDictionary *viewsDict = nil;
    if (self.mediaView != nil) {
        viewsDict = @{@"titleLabel":self.titleLabel, @"textLabel":self.textLabel, @"ctaLabel":self.ctaLabel, @"ratingLabel":self.ratingLabel, @"iconImageView":self.iconImageView, @"mainImageView":self.mainImageView, @"mediaView":self.mediaView, @"advertiserLabel":self.advertiserLabel, @"sponsorImageView":self.sponsorImageView};
    } else {
        viewsDict = @{@"titleLabel":self.titleLabel, @"textLabel":self.textLabel, @"ctaLabel":self.ctaLabel, @"ratingLabel":self.ratingLabel, @"iconImageView":self.iconImageView, @"mainImageView":self.mainImageView, @"advertiserLabel":self.advertiserLabel, @"sponsorImageView":self.sponsorImageView};
    }
    [self addConstraintsWithVisualFormat:@"|[mainImageView]|" options:0 metrics:nil views:viewsDict];
    [self addConstraintsWithVisualFormat:@"V:[iconImageView]-20-[mainImageView]|" options:0 metrics:nil views:viewsDict];
    
    [self addConstraintWithItem:self.iconImageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:self.iconImageView attribute:NSLayoutAttributeHeight multiplier:1.0f constant:.0f];
    
    [self.titleLabel setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    [self addConstraintsWithVisualFormat:@"|-15-[iconImageView(90)]-8-[titleLabel]-8-[sponsorImageView]-15-|" options:NSLayoutFormatAlignAllTop metrics:nil views:viewsDict];
    [self addConstraintsWithVisualFormat:@"V:|-15-[titleLabel]-8-[textLabel]-8-[ctaLabel]-8-[ratingLabel]-8-[advertiserLabel]" options:NSLayoutFormatAlignAllLeading | NSLayoutFormatAlignAllTrailing metrics:nil views:viewsDict];
}

-(void) makeConstraintsDrawVideoAssets {
    NSMutableDictionary<NSString*, UIView*> *viewsDict = [NSMutableDictionary<NSString*, UIView*> dictionary];
    if (self.dislikeButton != nil) { viewsDict[@"dislikeButton"] = self.dislikeButton; }
    if (self.adLabel != nil) { viewsDict[@"adLabel"] = self.adLabel; }
    if (self.logoImageView != nil) { viewsDict[@"logoImageView"] = self.logoImageView; }
    if (self.logoADImageView != nil) { viewsDict[@"logoAdImageView"] = self.logoADImageView; }
    if (self.videoAdView != nil) { viewsDict[@"videoView"] = self.videoAdView; }
    
    if ([viewsDict count] == 5) {
        self.dislikeButton.translatesAutoresizingMaskIntoConstraints = self.adLabel.translatesAutoresizingMaskIntoConstraints = self.logoImageView.translatesAutoresizingMaskIntoConstraints = self.logoADImageView.translatesAutoresizingMaskIntoConstraints = self.videoAdView.translatesAutoresizingMaskIntoConstraints = NO;
        [self addConstraintsWithVisualFormat:@"V:[logoAdImageView]-15-|" options:0 metrics:nil views:viewsDict];
        [self addConstraintsWithVisualFormat:@"|-15-[dislikeButton]-5-[adLabel]-5-[logoImageView]-5-[logoAdImageView]" options:NSLayoutFormatAlignAllCenterY metrics:nil views:viewsDict];
        [self addConstraintsWithVisualFormat:@"|[videoView]|" options:0 metrics:nil views:viewsDict];
        [self addConstraintsWithVisualFormat:@"V:[videoView(height)]|" options:0 metrics:@{@"height":@(CGRectGetHeight(self.bounds) - 120.0f)} views:viewsDict];
    }
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

-(void) loadNativeAdWithPlacementID:(NSString*)placementID customData:(NSDictionary*)customData {
    [[ATAdManager sharedManager] loadADWithPlacementID:placementID extra:@{kExtraInfoNativeAdTypeKey:@(ATGDTNativeAdTypeSelfRendering), kATExtraNativeImageSizeKey:kATExtraNativeImageSize690_388} customData:customData delegate:self];
}

-(BOOL) isNativeAdReadyForPlacementID:(NSString*)placementID {
    return [[ATAdManager sharedManager] nativeAdReadyForPlacementID:placementID];
}

-(void) showNativeAdWithPlacementID:(NSString*)placementID rectDict:(NSDictionary*)rectDict {
    if ([self isNativeAdReadyForPlacementID:placementID]) {
        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
        [button addTarget:self action:@selector(noop) forControlEvents:UIControlEventTouchUpInside];
        button.frame = CGRectMake([rectDict[@"x"] doubleValue], [rectDict[@"y"] doubleValue], [rectDict[@"w"] doubleValue], [rectDict[@"h"] doubleValue]);
        _viewsStorage[placementID] = button;
        
        ATNativeADConfiguration *config = [[ATNativeADConfiguration alloc] init];
        config.ADFrame = button.bounds;
        config.mediaViewFrame = CGRectMake(0, 120.0f, CGRectGetWidth(button.bounds), 300.0f - 120.0f);
        config.delegate = self;
        config.renderingViewClass = [ATCocosNativeAdView class];
        config.rootViewController = [[[[UIApplication sharedApplication] delegate] window] rootViewController];
        
        ATCocosNativeAdView *adview = [[ATAdManager sharedManager] retriveAdViewWithPlacementID:placementID configuration:config];
        adview.ctaLabel.hidden = [adview.nativeAd.ctaText length] == 0;
        if (adview != nil) {
//            if ([adview respondsToSelector:@selector(configureMetrics:)]) {
////                [adview configureMetrics:parsedMetrics];
//                adview.backgroundColor = [UIColor whiteColor];
//            } else {
//                [adview.subviews enumerateObjectsUsingBlock:^(__kindof UIView * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
//                    if ([obj isKindOfClass:[ATCocosNativeAdView class]]) {
////                        [(ATCocosNativeAdView*)obj configureMetrics:parsedMetrics];
//                        *stop = YES;
//                    }
//                }];
//            }
            [button addSubview:adview];
            [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:button];
        }
       
    }
}

-(void) noop {
    
}

-(void) removeNativeAdViewWithPlacementID:(NSString*)placementID {
    
    [_viewsStorage[placementID] removeFromSuperview];
}

-(void) clearCache {
    [[ATAdManager sharedManager] clearCache];
}

#pragma mark - delegate
-(void) didFinishLoadingADWithPlacementID:(NSString *)placementID {
    
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        pDelegate->onNativeAdLoadSuccess(cPlacementId);
    }
}

-(void) didFailToLoadADWithPlacementID:(NSString*)placementID error:(NSError*)error {

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
-(void) didStartPlayingVideoInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    //Drop ad view
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdVideoStartWithExtra(cPlacementId, cExtra);
    }
    
}

-(void) didEndPlayingVideoInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    //Drop ad view
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdVideoEndWithExtra(cPlacementId, cExtra);
    }
    
}

-(void) didClickNativeAdInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
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
    void* callback = [[ATNativeAdWrapper sharedInstance] callbackForKey:placementID];
    
    if (callback != NULL) {
        ATCocosNativeAdListener* pDelegate = (ATCocosNativeAdListener*)callback;
        const char* cPlacementId = [ATCocosUtils cstringFromNSString:placementID];
        const char* cExtra = [ATCocosUtils cstringFromExtraNSDictionary:extra];
        pDelegate->onNativeAdShowWithExtra(cPlacementId, cExtra);
    }
    
}

-(void) didEnterFullScreenVideoInAdView:(ATNativeADView*)adView placementID:(NSString*)placementID extra:(NSDictionary *)extra{
    NSLog(@"ATNativeViewController:: didEnterFullScreenVideoInAdView:placementID:%@", placementID);
}


@end
