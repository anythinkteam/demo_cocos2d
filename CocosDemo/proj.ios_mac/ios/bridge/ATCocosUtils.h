//
//  ATCocosUtils.h
//  up_sdk_cocos-mobile
//
//  Created by Topon on 2019/7/23.
//

#ifndef ATCocosUtils_h
#define ATCocosUtils_h

#include "cocos2d.h"

@interface ATCocosUtils:NSObject

+ (NSString *)nsstringFromCString:(const char *)cstring;
+ (const char *)cstringFromNSString:(NSString *)nsstring;
+ (NSDictionary *)nsDictionaryFromCCDictionary:(cocos2d::CCDictionary *)ccDictionary;
+ (const char *)cstringFromExtraNSDictionary:(NSDictionary *)dic;

@end

@interface NSDictionary (KAKit)
-(NSString*) jsonString;
-(BOOL)containsObjectForKey:(id)key;
@end

@interface UIColor (Hex)
// 透明度固定为1，以0x开头的十六进制转换成的颜色
+ (UIColor *)colorWithHex:(long)hexColor;
// 0x开头的十六进制转换成的颜色,透明度可调整
+ (UIColor *)colorWithHex:(long)hexColor alpha:(float)opacity;
// 颜色转换三：iOS中十六进制的颜色（以#开头）转换为UIColor
+ (UIColor *) colorWithHexString: (NSString *)color;

@end

#endif /* ATXUtils_hpp */
