//

//  FMLayerWebView.h

//  WebViewDemo

//

//  Created by Yanghui Liu on 12-6-5.

//  Copyright (c) 2012年 FMinutes company. All rights reserved.

//  

#ifndef WebViewDemo_FMLayerWebView_h

#define WebViewDemo_FMLayerWebView_h


#include "CCCommon.h"

#include "cocos2d.h"

USING_NS_CC;

class FMLayerWebView : public CCLayer{
    
public:
    
    FMLayerWebView();
    
    ~FMLayerWebView();
    
    virtual bool init(const char* urlString, CCObject *target, SEL_CallFunc closeWebViewCallbackFunc, SEL_CallFunc openWebViewCallbackFunc);
    
    static FMLayerWebView* create(const char* urlString, CCObject *target, SEL_CallFunc closeWebViewCallbackFunc, SEL_CallFunc openWebViewCallbackFunc);
    
    void webViewDidFinishLoad();
    
    void onBackbuttonClick();
    
private:
    
    int mWebViewLoadCounter;
    
    CCObject *target;
    SEL_CallFunc closeWebViewCallbackFunc;
    SEL_CallFunc openWebViewCallbackFunc;
    
};

   

#endif