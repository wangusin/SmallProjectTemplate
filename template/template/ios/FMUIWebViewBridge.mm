//

//  FMUIWebViewBridge.cpp

//  WebViewDemo

//

//  Created by Yanghui Liu on 12-6-5.

//  Copyright (c) 2012年 FMinutes company. All rights reserved.

//

#import "FMUIWebViewBridge.h"

#import "EAGLView.h"

@implementation FMUIWebViewBridge

- (id)init{
    
    self = [super init];
    
    if (self) {
        
        // init code here.
        count = 0;
        
    }
    
    
    
    return self;
    
}

- (void)dealloc{
    
    [mBackButton release];
    
    [backButton release];
    
    [mWebView release];
    
    [mView release];
    
    [super dealloc];
    
}

   

-(void) setLayerWebView : (FMLayerWebView*) iLayerWebView URLString:(const char*) urlString{
    
    mLayerWebView = iLayerWebView;
    
    cocos2d::CCSize size = mLayerWebView-> getContentSize();
    
    mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, size.width , size.height)];
    
    // create webView
    
    //Bottom size
    
    int wBottomMargin = 0;
    
    int wWebViewHeight = size.height - wBottomMargin;
    
    mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, size.width, wWebViewHeight)];
    
    mWebView.delegate = self;
    
    NSString *urlBase = [NSString stringWithCString:urlString encoding:NSUTF8StringEncoding];
    CCLog("urlString=%s",urlString);
    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlBase ]]];
    
    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are
    
    //create a tool bar for the bottom of the screen to hold the back button
    backButton=[[UIButton alloc] initWithFrame:CGRectMake(0.0, 0.0, 65.0, 60.0)];
    
    [mView addSubview:mWebView];
    [mView addSubview:backButton];
    
    // add the webView to the view
    
    [[EAGLView sharedEGLView] addSubview:mView];
    
    [backButton addTarget:self action:@selector(backClicked:) forControlEvents:UIControlEventTouchUpInside];
}

   

- (void)webViewDidStartLoad:(UIWebView *)thisWebView {
    
}

   

- (void)webViewDidFinishLoad:(UIWebView *)thisWebView{
    
    count++;
    
    [mWebView setUserInteractionEnabled:YES];
    
    mLayerWebView->webViewDidFinishLoad();
    
}

   

- (void)webView:(UIWebView *)thisWebView didFailLoadWithError:(NSError *)error {
    
    if (count == 0) {
        if ([error code] != -999 && error != NULL) { //error -999 happens when the user clicks on something before it's done loading.
            
               
            
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Network Error" message:@"Unable to load the page. Please keep network connection."
                                  
                                                           delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
            
            [alert show];
            
            [alert release];
            
        }
    }
    
}

   

-(void) backClicked:(id)sender {
    
    mWebView.delegate = nil; //keep the webview from firing off any extra messages
    
    //remove items from the Superview...just to make sure they're gone
    [backButton removeFromSuperview];
    
    [mWebView removeFromSuperview];
    
    [mView removeFromSuperview];
    
    mLayerWebView->onBackbuttonClick();
    
}

- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    //Code.....
    
    mWebView.delegate = nil; //keep the webview from firing off any extra messages
    
    //remove items from the Superview...just to make sure they're gone
    [backButton removeFromSuperview];
    
    [mWebView removeFromSuperview];
    
    [mView removeFromSuperview];
    
    mLayerWebView->onBackbuttonClick();
}

@end