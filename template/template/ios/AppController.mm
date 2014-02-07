//
//  templateAppController.mm
//  template
//
//  Created by Mac10 on 14/1/17.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"
#import <MediaPlayer/MediaPlayer.h>
#import "TestFlight.h"
@implementation AppController

@synthesize bannerView_;
@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;
MPMoviePlayerViewController *mp;
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    
    //=====================================
    //畫面縮放
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)   //依UI介面方式 判斷是否為iPad
    {
        //ipad
        //讓Retina上也只用普通大小來顯示.
        [viewController.view setContentScaleFactor:1.0f];
        
    }else if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        //iphone
        [viewController.view setContentScaleFactor:2.4f];
    }else{
        //other
        
    }
    //=====================================
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    //==================================
    //banner
    self.bannerView_ = [GADBannerView alloc];
    CGPoint origin = CGPointMake((self.viewController.view.frame.size.height - 320) / 2, self.viewController.view.frame.size.width - 50);
    bannerView_ = [[[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:origin] autorelease];
    //    bannerView_ = [[GADBannerView alloc] initWithFrame:CGRectMake(0.0, 680.0,960.0,120.0)];
    bannerView_.adUnitID = @"a152d36240e5d07";
    
    [viewController.view addSubview:bannerView_];
    [bannerView_ setRootViewController:viewController];
    
    GADRequest * request = [GADRequest request];
    request.testing = YES;
    [bannerView_ loadRequest:request];
    //===================================
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];

#if 1   //是否播放形象影片.
    
    //插入影片.
    [[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
    [self playOpening];
#else
    
    //原本執行cocos2d-x的命令.
    cocos2d::CCApplication::sharedApplication()->run();
#endif

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}

- (void)playOpening{
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Opening" ofType:@"mp4"];
    
    NSURL *movieURL = [NSURL fileURLWithPath:path];
    
    mp= [[MPMoviePlayerViewController alloc] initWithContentURL:movieURL];
    
    [mp.moviePlayer setMovieSourceType:MPMovieSourceTypeFile];
    [mp.moviePlayer setControlStyle:MPMovieControlStyleNone];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(movieFinishedCallback:)
                                                 name:MPMoviePlayerPlaybackDidFinishNotification
                                               object:[mp moviePlayer]];
    
    [mp.moviePlayer prepareToPlay];
    
    [viewController.view addSubview:mp.view];
    
    //    [mp.view setFrame:CGRectMake(0, 0, 1024, 768)];
    [mp.view setFrame:CGRectMake(0, 0, viewController.view.frame.size.height, viewController.view.frame.size.width)];
    [[mp moviePlayer] play];
}
- (void) movieFinishedCallback:(NSNotification*) aNotification {
    MPMoviePlayerController *player = [aNotification object];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:player];
    
    [player stop];
    
    [mp.view removeFromSuperview];
    
    [mp release];
    
    [[UIApplication sharedApplication] endIgnoringInteractionEvents];
    //執行cocos2d-x
    cocos2d::CCApplication::sharedApplication()->run();
}

@end

