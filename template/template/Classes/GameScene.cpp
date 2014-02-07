//
//  GameScene 
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "ObjCCalls.h"
#define AnimationSpeed 1.0f/12.0f

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
GameScene::~GameScene(){
    CCLog("Exit GameScene Scene");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //////////////////////////////
    
    
    CCLabelTTF* pLabel = CCLabelTTF::create("GameScene", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    //=====廣告設定=====
    ObjCCalls* objc = new ObjCCalls();
//    objc -> showBanner();
    objc -> hideBanner();

    //---
    CCLabelTTF* startLabel = CCLabelTTF::create("回到首頁", "Thonburi", 20);
    startLabel->setPosition(ccp(512, 384));
    this->addChild(startLabel,1);
    
    CCRect checkZoneSize = CCRectMake(0, 0, 300, 200);
    CCSprite *checkZoneSpr = CCSprite::create();
    checkZoneSpr->setTextureRect(checkZoneSize);
    checkZoneSpr->setOpacity(0);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    CCMenu *checkZoneMenu = CCMenu::createWithItem(checkZoneItem);
    checkZoneMenu->setPosition(ccp(512,384));
    this->addChild(checkZoneMenu,5);
    checkZoneItem->setTarget(this, menu_selector(GameScene::toNextScene));
    
    return true;
}

#pragma mark -
void GameScene::toNextScene(){
    CCLOG("To OutVillage");
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    // create a scene. it's an autorelease object
    CCScene *pScene = StartScene::scene();
    
    // replace
    pDirector->replaceScene(CCTransitionFade::create(0.5f, pScene,ccWHITE));
}