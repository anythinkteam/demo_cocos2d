//
//  ATCocosBaseWrapper.m
//  up_sdk_cocos-mobile
//
//  Created by stephen on 7/28/19.
//

#import "ATCocosBaseWrapper.h"
#import "ATCocosUtils.h"


@interface ATCocosBaseWrapper()
@property(nonatomic, readonly) NSMutableDictionary<NSString*, NSValue*> *callbacks;
@property(nonatomic, readonly) dispatch_queue_t callbackAccessQueue;
@end
@implementation ATCocosBaseWrapper
+(instancetype) sharedInstance {
    return nil;
}

-(instancetype) init {
    self = [super init];
    if (self != nil) {
        _callbacks = [NSMutableDictionary<NSString*, NSValue*> new];
        _callbackAccessQueue = dispatch_queue_create("com.AT.CocosPackage", DISPATCH_QUEUE_CONCURRENT);
    }
    return self;
}

-(void) setCallBack:(void*)callback forKey:(NSString *)key {
    __weak ATCocosBaseWrapper* weakSelf = self;
    if (callback != NULL && [key length] > 0)
        dispatch_barrier_async(_callbackAccessQueue, ^{
//             NSLog(@"setCallBack: %@", weakSelf.callbacks);
            [weakSelf.callbacks setObject:[NSValue valueWithPointer:callback] forKey:key];
        });
//    weakSelf.callbacks = callback;
}

-(void) removeCallbackForKey:(NSString *)key {
    __weak ATCocosBaseWrapper* weakSelf = self;
    if ([key length] > 0)
        dispatch_barrier_async(_callbackAccessQueue, ^{
            [weakSelf.callbacks removeObjectForKey:key];
        });
}

-(void*) callbackForKey:(NSString*)key {
    __block void(*callback) = NULL;
    if ([key length] > 0) {
        __weak ATCocosBaseWrapper* weakSelf = self;
//
        dispatch_barrier_sync(_callbackAccessQueue, ^{
//            NSLog(@"callbackForKey:%@", weakSelf.callbacks);
            NSValue* pointer = [weakSelf.callbacks objectForKey:key];
            if(pointer != nil){
                callback = (void*)[pointer pointerValue];
            }

        });
    }
    return callback;
}

@end
