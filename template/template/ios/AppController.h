//
//  templateAppController.h
//  template
//
//  Created by Mac10 on 14/1/17.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//
#include "GADBannerView.h"
@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView * bannerView_;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;
@property (nonatomic, retain)GADBannerView * bannerView_;

@end

