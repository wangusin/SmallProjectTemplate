//
//  WebScene.cpp
//  test
//
//  Created by imac07 on 13/12/9.
//
//

#include "WebScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;


CCScene* WebScene::scene(int languageType)
{
    CCScene *scene = CCScene::create();
    
    WebScene *layer = WebScene::create(languageType);
    
    scene->addChild(layer);
    
    
    
    return scene;
}



WebScene* WebScene::create(int languageType) {
    
    WebScene *webScene = new WebScene();
    
    if (webScene->init(languageType))
    {
    
        webScene->autorelease();
        //here write your code to initialize everything
    } else
        webScene = NULL;
    
    return webScene;
    
}


bool WebScene::init(int languageType)
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    switch (languageType)
    {
        case 0:
            webStr="http://www.happybook.com.tw/bookshelf/ipad/indexTw.html";
            break;
        case 1:
            webStr="http://www.happybook.com.tw/bookshelf/ipad/indexCn.html";
            break;
        case 2:
            webStr="http://www.happybook.com.tw/bookshelf/ipad/indexEn.html";
            break;
        default:
            break;
    }

    web = FMLayerWebView::create(webStr,this,callfunc_selector(WebScene::backStartScene),callfunc_selector(WebScene::playWebMusic));
    
    web->setPosition(CCPointZero);
    
    addChild(web);
    
    
    
    
    return true;
}

void WebScene::playWebMusic()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Bookshelf.mp3", true);
}

void WebScene::backStartScene()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *toScene=StartScene::scene();
    
    CCDirector::sharedDirector()->replaceScene(toScene);
}

void WebScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}