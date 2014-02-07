//
//  WebScene.h
//  test
//
//  Created by imac07 on 13/12/9.
//
//

#ifndef __test__WebScene__
#define __test__WebScene__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FMLayerWebView.h"
#include "StartScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
class WebScene : public cocos2d::CCLayer
{
public:
    virtual bool init(int languageTypes);
    static cocos2d::CCScene* scene(int languageType);
    void menuCloseCallback(CCObject* pSender);
    
    static WebScene* create(int languageTypes);
    
    
//    CREATE_FUNC(WebScene);
    
    FMLayerWebView* web;
    
    const char *webStr;
    
    void playWebMusic();
    void backStartScene();
 
    int typeNum;
    
    
};

#endif /* defined(__test__WebScene__) */
