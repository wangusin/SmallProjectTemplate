//
//  StartScene 
//
#ifndef __StartScene__
#define __StartScene__

#include "cocos2d.h"
#include "WebScene.h"
#include "ObjCCalls.h"
#include "MediaPlayerScene.h"
#include "GameScene.h"
using namespace cocos2d;
class StartScene : public cocos2d::CCLayer
{
public:
    ~StartScene();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(StartScene);
    
    //===================================
    int languageType;
    CCString * tempString;
    CCSize tempSize;
    
    CCSprite * sceneSpr;
    CCSprite * bannerSpr;
    CCMenuItemSprite * bannerItem;
    //-----------------------------------
    //App畫面的表現.自行依企畫書設計.
    void createTitle();
    void createLogoSpr();
    
    void createDuckSpr();
    void createUglyDuckSpr();

    
    //---底下修改部份設定即可.
    void createMovieSpr();
    void playMovie();

    void createGameSpr();
    void gotoGame();

    void createMoreSpr();
    void gotoBookStore();
    void LinkURL(CCMenuItem * sender);
    void scheduleBanner();
    
    void createBookSpr();
    void gotoAppStore();
    
    
    
};


#endif /* defined(__StartScene__) */
