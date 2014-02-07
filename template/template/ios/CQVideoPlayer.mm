//
//  CQVideoPlayer.cpp
//  pjtAction
//
//  Created by Mac10 on 13/11/26.
//
//

#include "CQVideoPlayer.h"
#import <MediaPlayer/MediaPlayer.h>

static CQVideoPlayer *pSharedVideoPlayer = NULL;

// Keep these pointers to shut everything down in the end
MPMoviePlayerViewController *playerViewController;
MPMoviePlayerController *player;
UIWindow *window;

CQVideoPlayer* CQVideoPlayer::sharedVideoPlayer()
{
    if (! pSharedVideoPlayer)
    {
        pSharedVideoPlayer = new CQVideoPlayer();
        pSharedVideoPlayer->init();
    }
    
    return pSharedVideoPlayer;
}

bool CQVideoPlayer::init()
{
    // Some black magik to hear objC notifications from C++ class
    CFNotificationCenterAddObserver(CFNotificationCenterGetLocalCenter(), this, &notificationHandler,
                                    (CFStringRef)MPMoviePlayerPlaybackDidFinishNotification,  NULL, CFNotificationSuspensionBehaviorDeliverImmediately);
    return true;
}

void CQVideoPlayer::playVideo(const char* strFileName, const char* strExtension)
{
    // Init MPMoviePlayerViewController
    NSString *url = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:strFileName] ofType:[NSString stringWithUTF8String:strExtension]];
    playerViewController = [[MPMoviePlayerViewController alloc] initWithContentURL:[NSURL fileURLWithPath:url]];
    
    // Same thing we're doing in AppController
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    [window addSubview: playerViewController.view];
    [window makeKeyAndVisible];
    
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        [window addSubview: playerViewController.view];
    }
    else
    {
        [window setRootViewController:playerViewController];
    }
    
    // Actually start a video
    player = [playerViewController moviePlayer];
    CGRect r = player.view.frame;
    float offset = (r.size.height - 1024 * r.size.width/768) / 2;
    CCLOG("%f  %f  %f",playerViewController.view.frame.size.height,1024 * r.size.width/768,offset);
    [player.view setFrame:CGRectMake(0, offset, 768 * r.size.width/768, 1024 * r.size.width/768)];
    
    [player prepareToPlay];
    player.scalingMode = MPMovieScalingModeAspectFit;
    player.shouldAutoplay = TRUE;
    //    player.controlStyle = MPMovieControlStyleNone;
    player.controlStyle = MPMovieControlStyleFullscreen;
    [player play];

}

// React to notification
void CQVideoPlayer::notificationHandler(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo)
{
    (static_cast<CQVideoPlayer *>(observer))->videoFinishedCallback();
}

void CQVideoPlayer::videoFinishedCallback()
{
    // Hide video
    [player.view removeFromSuperview];
    [window setHidden:YES];
    [window release];
    [playerViewController release];
    
    // Post a notification to be able to properly react
    CCNotificationCenter::sharedNotificationCenter()->postNotification("VideoPlaybackFinished");
}

CQVideoPlayer::~CQVideoPlayer()
{
    // Remove observer in the end
    CFNotificationCenterRemoveEveryObserver(CFNotificationCenterGetLocalCenter(), this);
}