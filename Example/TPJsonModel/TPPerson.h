//
//  TPPerson.h
//  TPJsonModel_Example
//
//  Created by Topredator on 2021/4/23.
//  Copyright © 2021 Topredator. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TPWork.h"
#import <TPJsonModel/TPJsonModel.h>
NS_ASSUME_NONNULL_BEGIN

@interface TPPerson : NSObject <TPJsonModel>
@property (nonatomic, copy) NSString *req_name;
@property (nonatomic, copy) NSString *personId;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSInteger age;
@property (nonatomic, copy) NSString *sex;
@property (nonatomic, strong) TPWork *work;
@end

NS_ASSUME_NONNULL_END
