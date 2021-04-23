//
//  NSObject+TPJsonModelExtension.m
//  TPJsonModel
//
//  Created by Topredator on 2021/4/23.
//

#import "NSObject+TPJsonModelExtension.h"

static id TPJsonObject(id json) {
    if (!json) return nil;
    if ([json isKindOfClass:[NSArray class]]) return json;
    if ([json isKindOfClass:[NSMutableDictionary class]]) return json;
    if ([json isKindOfClass:[NSString class]]) {
        json = [(NSString *)json dataUsingEncoding: NSUTF8StringEncoding];
    }
    if ([json isKindOfClass:[NSData class]]) {
        return [NSJSONSerialization JSONObjectWithData:json options:kNilOptions error:NULL];
    }
    return nil;
}

@implementation NSArray (TPJsonModelExtension)

+ (instancetype)tp_modelWithJSON:(id)json {
    json = TPJsonObject(json);
    if ([json isKindOfClass:[NSMutableArray class]]) {
        return [json copy];
    }
    if ([json isKindOfClass:[NSArray class]]) {
        return json;
    }
    return nil;
}

+ (instancetype)tp_modelWithDictionary:(NSDictionary *)dictionary {
    return nil;
}

@end

@implementation NSMutableArray (TPJsonModelExtension)

+ (instancetype)tp_modelWithJSON:(id)json {
    json = TPJsonObject(json);
    if ([json isKindOfClass:[NSArray class]]) {
        return [json mutableCopy];
    }
    return nil;
}

@end

@implementation NSDictionary (TPJsonModelExtension)

+ (instancetype)tp_modelWithJSON:(id)json {
    json = TPJsonObject(json);
    if ([json isKindOfClass:[NSMutableDictionary class]]) {
        return [json copy];
    }
    else if ([json isKindOfClass:[NSDictionary class]]) {
        return json;
    }
    return nil;
}

+ (instancetype)tp_modelWithDictionary:(NSDictionary *)dictionary {
    if ([dictionary isKindOfClass:[NSMutableDictionary class]]) {
        return [dictionary copy];
    }
    else if ([dictionary isKindOfClass:[NSDictionary class]]) {
        return dictionary;
    }
    return nil;
}

@end

@implementation NSMutableDictionary (TPJsonModelExtension)

+ (instancetype)tp_modelWithJSON:(id)json {
    json = TPJsonObject(json);
    if ([json isKindOfClass:[NSDictionary class]]) {
        return [json mutableCopy];
    }
    return nil;
}

+ (instancetype)tp_modelWithDictionary:(NSDictionary *)dictionary {
    if ([dictionary isKindOfClass:[NSDictionary class]]) {
        return [dictionary mutableCopy];
    }
    return nil;
}

@end

@implementation NSObject (TPJsonModelExtension)
- (void)encodeWithCoder:(NSCoder *)aCoder {
    return [self tp_modelEncodeWithCoder:aCoder];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [self init];
    return [self tp_modelInitWithCoder:aDecoder];
}
@end
