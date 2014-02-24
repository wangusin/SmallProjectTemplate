#import <Foundation/Foundation.h>

#import <CoreLocation/CoreLocation.h>

#import <UIKit/UIKit.h>

   

#import "FMLayerWebView.h"

   

@interface FMUIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>{
    
    FMLayerWebView * mLayerWebView;
    
    UIView    *mView;
    
    UIWebView *mWebView;
    
    UIButton *backButton;
    
    UIBarButtonItem *mBackButton;
    
    int count;
    
}

   

-(void) setLayerWebView : (FMLayerWebView*) iLayerWebView URLString:(const char*) urlString;

-(void) backClicked:(id)sender;

   

@end