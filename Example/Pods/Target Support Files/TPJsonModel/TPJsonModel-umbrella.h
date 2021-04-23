#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "NSObject+TPJsonModel.h"
#import "NSObject+TPJsonModelExtension.h"
#import "TPJsonClassInfo.h"
#import "TPJsonModel.h"

FOUNDATION_EXPORT double TPJsonModelVersionNumber;
FOUNDATION_EXPORT const unsigned char TPJsonModelVersionString[];

