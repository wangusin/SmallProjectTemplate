//
//  MediaPlayerScene 
//

#include "MediaPlayerScene.h"
#include "SimpleAudioEngine.h"


#define AnimationSpeed 1.0f/12.0f

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MediaPlayerScene::scene(const char * fileName)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MediaPlayerScene *layer = MediaPlayerScene::create(fileName);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MediaPlayerScene::~MediaPlayerScene(){
    CCLog("Exit MediaPlayerScene Scene");
}
MediaPlayerScene* MediaPlayerScene::create(const char * fileName) {
    
    MediaPlayerScene *mediaPlayerScene = new MediaPlayerScene();
    
    if (mediaPlayerScene->init(fileName))
    {
        
        mediaPlayerScene->autorelease();
        //here write your code to initialize everything
    } else
        mediaPlayerScene = NULL;
    
    return mediaPlayerScene;
    
}

// on "init" you need to initialize your instance
bool MediaPlayerScene::init(const char * fileName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //////////////////////////////
    
    
    CCLabelTTF* pLabel = CCLabelTTF::create("MediaPlayerScene", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    

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
    checkZoneItem->setTarget(this, menu_selector(MediaPlayerScene::toNextScene));
    
    
    CQVideoPlayer::sharedVideoPlayer()->playVideo(fileName, "mp4");
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MediaPlayerScene::toNextScene), "VideoPlaybackFinished", NULL);

    return true;
}

#pragma mark -
void MediaPlayerScene::toNextScene(){
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    
    //CCTransitionScene *rescene=NULL;
    CCScene *toScene=StartScene::scene();
    //rescene=CCTransitionFade::create(1.5, toScene, ccBLACK);
    CCDirector::sharedDirector()->replaceScene(toScene);
}