//
//  GameScene 
//
#ifndef __template__GameScene__
#define __template__GameScene__

#include "cocos2d.h"
using namespace cocos2d;
class GameScene : public cocos2d::CCLayer
{
public:
    ~GameScene();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    //===================================
    
    //-----------------------------------
    void toNextScene();
};

#endif /* defined(__Cinderella_X__GameScene__) */
