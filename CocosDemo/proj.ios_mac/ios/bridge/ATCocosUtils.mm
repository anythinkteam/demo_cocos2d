//
//  ATCocosUtils.mm
//  up_sdk_cocos-mobile
//
//  Created by Topon on 2019/7/23.
//

#include "ATCocosUtils.h"

#include "cocos2d.h"

@implementation ATCocosUtils

#define isKindOfClass(obj,class) (dynamic_cast<class*>(obj) != NULL)

+ (NSString *)nsstringFromCString:(const char *)cstring {
    if (cstring == NULL) {
        return NULL;
    }
    
    NSString * nsstring = [[NSString alloc] initWithBytes:cstring length:strlen(cstring) encoding:NSUTF8StringEncoding];
    return [nsstring autorelease];
}
+ (const char *)cstringFromNSString:(NSString *)nsstring {
    
    if (nsstring == NULL) {
        return NULL;
    }
    
    return [nsstring UTF8String];
}
+ (const char *)cstringFromExtraNSDictionary:(NSDictionary *)dic {
    const char* extra = [ATCocosUtils cstringFromNSString:[NSString stringWithFormat:@"adsourceId: %@, networkId: %@",dic[@"ad_source_id"],dic[@"network_firm_id"]]];
    return extra;
}
+ (NSDictionary *)nsDictionaryFromCCDictionary:(cocos2d::CCDictionary *)ccDictionary {
    if (ccDictionary == NULL) {
        return NULL;
    } else if (ccDictionary->allKeys() == NULL) {
        return NULL;
    } else if (ccDictionary->allKeys()->count() <= 0) {
        return NULL;
    }
    
    CCLOG("1");
    
    NSMutableDictionary *nsDict = [NSMutableDictionary dictionaryWithCapacity:ccDictionary->allKeys()->count()];
    
    CCLOG("2");
    
    for (int i = 0; i < ccDictionary->allKeys()->count(); i++) {
        CCLOG("3");
        
        cocos2d::CCObject* obj = ccDictionary->objectForKey(((cocos2d::CCString *)ccDictionary->allKeys()->objectAtIndex(i))->getCString());
        NSObject* nsObject;
        if(isKindOfClass(obj, cocos2d::CCDictionary))
        {
            nsObject = @"Dictionary";
        }
        else if(isKindOfClass(obj, cocos2d::CCArray))
        {
            nsObject = @"Array";
        }
        else if (isKindOfClass(obj, cocos2d::CCString))
        {
            const char* cstring = ((cocos2d::CCString*)obj)->getCString();
            nsObject = [[[NSString alloc] initWithBytes:cstring length:strlen(cstring) encoding:NSUTF8StringEncoding] autorelease];
        }
        else if (isKindOfClass(obj, cocos2d::CCInteger))
        {
            nsObject = [NSString stringWithFormat:@"%d", ((cocos2d::CCInteger*)obj)->getValue()];
        }
        else
        {
            nsObject = @"Unknown Object";
        }
        [nsDict setValue:nsObject forKey:[ATCocosUtils nsstringFromCString:((cocos2d::CCString *)ccDictionary->allKeys()->objectAtIndex(i))->getCString()]];
    }
    
    return nsDict;
}


@end


@implementation NSDictionary (KAKit)
-(NSString*) jsonString {
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:self
                                                       options:(NSJSONWritingOptions)NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (!jsonData) {
        return @"{}";
    } else {
        return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
}

-(BOOL)containsObjectForKey:(id)key {
    return [self.allKeys containsObject:key];
}
@end

@implementation UIColor (Hex)
// 透明度固定为1，以0x开头的十六进制转换成的颜色
+ (UIColor*) colorWithHex:(long)hexColor;
{
    return [UIColor colorWithHex:hexColor alpha:1.];
}
// 0x开头的十六进制转换成的颜色,透明度可调整
+ (UIColor *)colorWithHex:(long)hexColor alpha:(float)opacity
{
    float red = ((float)((hexColor & 0xFF0000) >> 16))/255.0;
    float green = ((float)((hexColor & 0xFF00) >> 8))/255.0;
    float blue = ((float)(hexColor & 0xFF))/255.0;
    return [UIColor colorWithRed:red green:green blue:blue alpha:opacity];
}
// 颜色转换三：iOS中十六进制的颜色（以#开头）转换为UIColor
+ (UIColor *) colorWithHexString: (NSString *)color
{
    NSString *cString = [[color stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) {
        return [UIColor clearColor];
    }
    
    // 判断前缀并剪切掉
    if ([cString hasPrefix:@"0X"])
        cString = [cString substringFromIndex:2];
    if ([cString hasPrefix:@"#"])
        cString = [cString substringFromIndex:1];
    if ([cString length] != 6)
        return [UIColor clearColor];
    
    // 从六位数值中找到RGB对应的位数并转换
    NSRange range;
    range.location = 0;
    range.length = 2;
    
    //R、G、B
    NSString *rString = [cString substringWithRange:range];
    
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f) green:((float) g / 255.0f) blue:((float) b / 255.0f) alpha:1.0f];
}
@end
