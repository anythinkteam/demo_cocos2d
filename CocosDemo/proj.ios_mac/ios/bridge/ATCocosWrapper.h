//
//  ATCocosWrapper.h
//  up_sdk_cocos
//
//  Created by stephen on 7/28/19.
//

#ifndef ATCocosWrapper_h
#define ATCocosWrapper_h

@protocol ATCocosWrapper<NSObject>
+(instancetype) sharedInstance;
@optional
-(void) setCallBack:(void*)callback forKey:(NSString*)key;
-(void) removeCallbackForKey:(NSString*)key;
-(void*) callbackForKey:(NSString*)key;

@end

#endif /* ATCocosWrapper_h */
