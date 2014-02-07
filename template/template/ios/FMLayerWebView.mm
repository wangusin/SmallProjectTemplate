//

//  FMLayerWebView.mm

//  WebViewDemo

//

//  Created by Yanghui Liu on 12-6-5.

//  Copyright (c) 2012年 FMinutes company. All rights reserved.

//


#include "FMLayerWebView.h"

#include "FMUIWebViewBridge.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;



static FMUIWebViewBridge *g_FMUIWebViewBridge=nil;

FMLayerWebView::FMLayerWebView()
{
    target = NULL;
    closeWebViewCallbackFunc = NULL;
    openWebViewCallbackFunc = NULL;
}

FMLayerWebView::~FMLayerWebView(){
    
    target = NULL;
    closeWebViewCallbackFunc = NULL;
    openWebViewCallbackFunc = NULL;
    
    [g_FMUIWebViewBridge release];
    
}

FMLayerWebView* FMLayerWebView::create(const char *urlString, CCObject *target, SEL_CallFunc closeWebViewCallbackFunc, SEL_CallFunc openWebViewCallbackFunc)
{
    FMLayerWebView *pRet = new FMLayerWebView();
    if (pRet && pRet->init(urlString, target, closeWebViewCallbackFunc, openWebViewCallbackFunc))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void FMLayerWebView::webViewDidFinishLoad(){
    
}


void FMLayerWebView::onBackbuttonClick(){
    
    if (target && closeWebViewCallbackFunc) {
        (target->*closeWebViewCallbackFunc)();
    }
    
    this->removeFromParentAndCleanup(true);
    
}

   

bool FMLayerWebView::init(const char* urlString, CCObject *target, SEL_CallFunc closeWebViewCallbackFunc, SEL_CallFunc openWebViewCallbackFunc){
    
    if ( !CCLayer::init() ){
        
        return false;
        
    }
    
    this->target = target;
    this->closeWebViewCallbackFunc = closeWebViewCallbackFunc;
    this->openWebViewCallbackFunc = openWebViewCallbackFunc;
    
    g_FMUIWebViewBridge = [[FMUIWebViewBridge alloc] init];
    
    [g_FMUIWebViewBridge setLayerWebView : this URLString:urlString];
    
    if (target && openWebViewCallbackFunc) {
        (target->*openWebViewCallbackFunc)();
    }
    
    return true;
    
}