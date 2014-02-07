//
//  CQVideoPlayer.h
//  pjtAction
//
//  Created by Mac10 on 13/11/26.
//
//

#ifndef __pjtAction__CQVideoPlayer__
#define __pjtAction__CQVideoPlayer__

#include <iostream>
#include <cocos2d.h>
#include <CoreFoundation/CoreFoundation.h>

USING_NS_CC;

class CQVideoPlayer
{
public:
    
    bool init();
    static CQVideoPlayer* sharedVideoPlayer();
    ~CQVideoPlayer();
    
    void playVideo(const char* strFileName, const char* strExtension);
    
    static void notificationHandler(CFNotificationCenterRef center, void *observer,
                                    CFStringRef name, const void *object, CFDictionaryRef userInfo);
    void videoFinishedCallback();
};

#endif  // __CQVIDEOPLAYER_H__