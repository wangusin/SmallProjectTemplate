//
//  StartScene 
//

#include "StartScene.h"
#include "SimpleAudioEngine.h"


#define AnimationSpeed 1.0f/12.0f

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
StartScene::~StartScene(){
    CCLog("Exit StartScene Scene");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //////////////////////////////
    
    
    CCUserDefault *dataRecord = CCUserDefault::sharedUserDefault();
//    if (!dataRecord->getBoolForKey("DATA_IS_FILE_EXISTED")) {
    
        //取得系統語言.
        const char* plistPath = "InfoPlist.strings";
        const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("InfoPlist.strings", plistPath);
        CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(fullPath);
        CCString* languageInit = dynamic_cast<CCString*>(plistDic->objectForKey("LanguageInit"));
        //        CCLog("LanguageInit = %d", languageInit->intValue());
        dataRecord->setIntegerForKey("Record_Language", languageInit->intValue());   //語言類別.

        dataRecord -> setBoolForKey("DATA_IS_FILE_EXISTED", true);
        dataRecord->flush();
//    }
    //取得語言與是否注音
    languageType = dataRecord->getIntegerForKey("Record_Language");

    
    //------------------------------------------------------------------------
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("startscene11.plist");
    
    
    //背景底圖
    CCLabelTTF* pLabel = CCLabelTTF::create("StartScene", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    
    //設定物件呈現區. 1024x768的範圍.
    CCRect RectSize1 = CCRectMake(0, 0, 1024, 768);
    sceneSpr = CCSprite::create();
    sceneSpr->setTextureRect(RectSize1);
    sceneSpr->setOpacity(100);
    
    sceneSpr -> setPosition(ccp(size.width / 2, size.height / 2));
    this -> addChild(sceneSpr, 5);

    //=====廣告設定=====
    ObjCCalls* objc = new ObjCCalls();
    objc -> showBanner();
//    objc -> hideBanner();

    
//    //=====畫面表現設計=====
//
    //TODO:畫面表現 需依企劃書修改表現內容.
    //故事標題.
    this -> createTitle();
    this -> createLogoSpr();
    
    //物件動態.
    this -> createDuckSpr();
    this -> createUglyDuckSpr();
    
    
    
    //=====基本功能設計=====
    //TODO:基本共通功能 依需求調整座標位置及url目標.
    //看動畫.
    this -> createMovieSpr();
    
    //玩遊戲.
    this -> createGameSpr();
    
    //更多App.
    this -> createMoreSpr();
    
    //力豆圖. (至App Store)
    this -> createBookSpr();

    
    
    return true;
}

#pragma mark -
#pragma mark 故事標題
void StartScene::createTitle()
{
    tempString = CCString::createWithFormat("title%04d.png",languageType + 1);
    CCSprite * title1 = CCSprite::createWithSpriteFrameName(tempString -> getCString());
    title1 -> setPosition(ccp(206.48,486.80));
    sceneSpr -> addChild(title1,5);
    title1 -> setScale(0.7);

    
    tempString = CCString::createWithFormat("title%04d.png",languageType + 3);
    CCSprite * title2 = CCSprite::createWithSpriteFrameName(tempString -> getCString());
    title2 -> setPosition(ccp(369.17,564.63));
    sceneSpr -> addChild(title2,5);
    title2 -> setScale(0.7);

    
    tempString = CCString::createWithFormat("title%04d.png",languageType + 5);
    CCSprite * title3 = CCSprite::createWithSpriteFrameName(tempString -> getCString());
    title3 -> setPosition(ccp(547.00,570.65));
    sceneSpr -> addChild(title3,5);
    title3 -> setScale(0.7);
    
    
    title1 -> runAction(CCSequence::create(CCDelayTime::create(1),CCScaleTo::create(0.5, 1),CCScaleTo::create(0.5, 0.7),NULL));
    title2 -> runAction(CCSequence::create(CCDelayTime::create(2),CCScaleTo::create(0.5, 1),CCScaleTo::create(0.5, 0.7),NULL));
    title3 -> runAction(CCSequence::create(CCDelayTime::create(3),CCScaleTo::create(0.5, 1),CCScaleTo::create(0.5, 0.7),NULL));
}
void StartScene::createLogoSpr()
{
    
    CCSprite * logoSpr = CCSprite::createWithSpriteFrameName("logo.png");
    logoSpr -> setPosition(ccp(83.67, 597.76));
    sceneSpr -> addChild(logoSpr);
    
    
    tempString = CCString::createWithFormat("logo2%04d.png",languageType+1);
    CCSprite * logoSpr2 = CCSprite::createWithSpriteFrameName(tempString -> getCString());
    logoSpr2 -> setPosition(ccp(296.41, 637.70));
    sceneSpr -> addChild(logoSpr2,5);
    
}
#pragma mark 物件動態
void StartScene::createDuckSpr()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite * duckSprR = CCSprite::createWithSpriteFrameName("yellow duck0001.png");
    duckSprR -> setPosition(ccp(671.86, 82.22));
    sceneSpr -> addChild(duckSprR,5);
    duckSprR -> setRotation(-10);
    duckSprR -> setAnchorPoint(ccp(0.5, 0));
    
    CCSprite * duckSprL = CCSprite::createWithSpriteFrameName("yellow duck0002.png");
    duckSprL -> setPosition(ccp(217.5, 71.2));
    sceneSpr -> addChild(duckSprL,10);
    duckSprL -> setRotation(15);
    duckSprL -> setAnchorPoint(ccp(0.5, 0));
    
    CCSprite * duckSprM = CCSprite::createWithSpriteFrameName("yellow duck0003.png");
    duckSprM -> setPosition(ccp(512.14, 189.25));
    sceneSpr -> addChild(duckSprM,10);
    
    CCSprite * hightSpr = CCSprite::createWithSpriteFrameName("hight.png");
    hightSpr -> setPosition(ccp(size.width / 2, 150));
    sceneSpr -> addChild(hightSpr,20);
    
    duckSprR -> runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.8, 20),CCRotateBy::create(0.8, -20),NULL)));
    duckSprL -> runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(1, -15),CCRotateBy::create(1, 15),NULL)));
}
void StartScene::createUglyDuckSpr()
{
    CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSprite * UglyDuckSpr = CCSprite::createWithSpriteFrameName("Ugly little duck0001.png");
    UglyDuckSpr -> setPosition(ccp(373.22, 273.09));
    sceneSpr -> addChild(UglyDuckSpr,5);
    
    
    CCAnimation * uglyduckAnimation = CCAnimation::create();
    for (int i = 1; i <= 75; i++) {
        tempString= CCString::createWithFormat("Ugly little duck%04d.png",i);
        uglyduckAnimation -> addSpriteFrame(cache -> spriteFrameByName(tempString -> getCString()));
    }
    uglyduckAnimation -> setDelayPerUnit(AnimationSpeed);
    
    CCAction * uglyduckAction = CCRepeatForever::create(CCAnimate::create(uglyduckAnimation));
    
    UglyDuckSpr -> runAction(uglyduckAction);
    
    CCSprite * eggSpr = CCSprite::createWithSpriteFrameName("Ugly little duck0076.png");
    eggSpr -> setPosition(ccp(373.22, 273.09));
    sceneSpr -> addChild(eggSpr,6);
    
    ccBezierConfig bezierCon;
    bezierCon.controlPoint_1 = CCPointMake(200,500);
    bezierCon.controlPoint_2 = CCPointMake(50, 500);
    bezierCon.endPosition = CCPointMake(-70, 150);
    eggSpr -> runAction(CCRepeatForever::create(CCSequence::create(
                                                                   CCDelayTime::create(0.41),
                                                                   CCSpawn::create(
                                                                                   CCRotateTo::create(1, 180),
                                                                                   CCBezierTo::create(1, bezierCon),
                                                                                   NULL),
                                                                   CCDelayTime::create(4.84),
                                                                   CCRotateTo::create(0, 0),
                                                                   CCMoveTo::create(0, ccp(373.22,273.09)),
                                                                   NULL)));
    
    
}
#pragma mark -
#pragma mark -
#pragma mark 看動畫
void StartScene::createMovieSpr()
{
    CCLabelTTF* playMediaLabel = CCLabelTTF::create("播放影片", "Thonburi", 20);
    playMediaLabel->setPosition(ccp(703.75, 531.73));
    sceneSpr->addChild(playMediaLabel,1);

    CCRect checkZoneSize = CCRectMake(0, 0, 300, 200);
    CCSprite *checkZoneSpr = CCSprite::create();
    checkZoneSpr->setTextureRect(checkZoneSize);
    checkZoneSpr->setOpacity(0);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    CCMenu *checkZoneMenu = CCMenu::createWithItem(checkZoneItem);
    checkZoneMenu->setPosition(ccp(703.75, 531.73));
    sceneSpr->addChild(checkZoneMenu,5);
    checkZoneItem->setTarget(this, menu_selector(StartScene::playMovie));
        
}
void StartScene::playMovie()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    //帶入影片名稱
    //CCTransitionScene *rescene=NULL;
    CCScene *toScene=MediaPlayerScene::scene("Opening");//movieName
    //rescene=CCTransitionFade::create(1.5, toScene, ccBLACK);
    CCDirector::sharedDirector()->replaceScene(toScene);
}
#pragma mark -
#pragma mark 玩遊戲
void StartScene::createGameSpr()
{
    CCLabelTTF* playGameLabel = CCLabelTTF::create("玩遊戲", "Thonburi", 20);
    playGameLabel->setPosition(ccp(870.49, 451.87));
    sceneSpr->addChild(playGameLabel,1);
    
    CCRect checkZoneSize = CCRectMake(0, 0, 300, 200);
    CCSprite *checkZoneSpr = CCSprite::create();
    checkZoneSpr->setTextureRect(checkZoneSize);
    checkZoneSpr->setOpacity(0);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    CCMenu *checkZoneMenu = CCMenu::createWithItem(checkZoneItem);
    checkZoneMenu->setPosition(ccp(870.49, 451.87));
    sceneSpr->addChild(checkZoneMenu,5);
    checkZoneItem->setTarget(this, menu_selector(StartScene::gotoGame));
    
}
void StartScene::gotoGame()
{
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    
    //CCTransitionScene *rescene=NULL;
    CCScene *toScene=GameScene::scene();
    //rescene=CCTransitionFade::create(1.5, toScene, ccBLACK);
    CCDirector::sharedDirector()->replaceScene(toScene);
}
#pragma mark -
#pragma mark 更多App
void StartScene::createMoreSpr()
{
    
    //更多App Button
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* MoreAppLabel = CCLabelTTF::create("更多ＡＰＰ", "Thonburi", 20);
    MoreAppLabel->setPosition(ccp(794.69, 121.34));
    sceneSpr->addChild(MoreAppLabel,1);
    
    CCRect checkZoneSize = CCRectMake(0, 0, 300, 200);
    CCSprite *checkZoneSpr = CCSprite::create();
    checkZoneSpr->setTextureRect(checkZoneSize);
    checkZoneSpr->setOpacity(0);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    CCMenu *checkZoneMenu = CCMenu::createWithItem(checkZoneItem);
    checkZoneMenu->setPosition(ccp(794.69, 121.34));
    sceneSpr->addChild(checkZoneMenu,5);
    checkZoneItem->setTarget(this, menu_selector(StartScene::gotoBookStore));

    

    
}
void StartScene::gotoBookStore()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
    
    //CCTransitionScene *rescene=NULL;
    CCScene *toScene=WebScene::scene(languageType);
    //rescene=CCTransitionFade::create(1.5, toScene, ccBLACK);
    CCDirector::sharedDirector()->replaceScene(toScene);
}
#pragma mark -
#pragma mark 力豆圖(至App Strore)
void StartScene::createBookSpr()
{
    CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSprite * bookSpr = CCSprite::create("link_bookcase btn0001.png");
    tempSize = bookSpr -> boundingBox().size;
    
    CCSprite * beansSpr = CCSprite::create("link_bookcase btn0002.png");
    beansSpr -> setPosition(ccp(tempSize.width / 2, tempSize.height / 2));
    bookSpr -> addChild(beansSpr);
    
    CCMenuItemSprite * bookItem = CCMenuItemSprite::create(bookSpr, NULL, this, menu_selector(StartScene::gotoAppStore));
    CCMenu * bookMenu = CCMenu::createWithItem(bookItem);
    bookMenu -> setPosition(ccp(880.73, 586.81));
    sceneSpr -> addChild(bookMenu,5);
}
void StartScene::gotoAppStore()
{
    ObjCCalls* objc = new ObjCCalls();
    objc->OpenURL("https://itunes.apple.com/tw/artist/pan-asia-cultural/id552873453?l=zh&mt=8") ;
}