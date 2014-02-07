//PrinceMessage.mm (.mm means its objective-c++?  Which means you can access it in c++?  This file can combine c++ and objective c?)
#include "ObjCCalls.h"
#import "../cocos2dx/platform/ios/EAGLView.h" 
#import "AppController.h"

bool ObjCCalls::OpenURL(const char *url)
{
    NSString *nsurl = [NSString stringWithUTF8String:url];
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:nsurl]])
    {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:nsurl]];
        return true;
    }

    return false;
}

void ObjCCalls::hideBanner()
{
    AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
    [app.bannerView_ setHidden:true];
}
void ObjCCalls::showBanner()
{
    AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
    [app.bannerView_ setHidden:false];
}

