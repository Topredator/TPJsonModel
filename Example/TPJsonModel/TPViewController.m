//
//  TPViewController.m
//  TPJsonModel
//
//  Created by Topredator on 04/23/2021.
//  Copyright (c) 2021 Topredator. All rights reserved.
//

#import "TPViewController.h"
#import "TPPerson.h"
@interface TPViewController ()

@end

@implementation TPViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSDictionary *dic = @{@"id" : @"123",
                          @"name" : @"Topredator",
                          @"age" : @(18),
                          @"sex" : @"男",
                          @"work" : @{@"name" : @"学天教育", @"address" : @"杭州市下城区城建大厦"}
    };
    
    TPPerson *person = [TPPerson tp_modelWithJSON:dic];
    person.req_name = @"测试试一下";
    NSLog(@"person Object = %@", person);
    NSLog(@"person = %@", [person tp_modelToJSONObject]);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
