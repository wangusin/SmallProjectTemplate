//
//  MediaPlayerScene 
//
#ifndef __Cinderella_X__MediaPlayerScene__
#define __Cinderella_X__MediaPlayerScene__

#include "cocos2d.h"
#include "StartScene.h";
#include "CQVideoPlayer.h"
using namespace cocos2d;
class MediaPlayerScene : public cocos2d::CCLayer
{
public:
    ~MediaPlayerScene();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(const char * fileName);
    static cocos2d::CCScene* scene(const char * fileName);

    static MediaPlayerScene * create(const char * fileName);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
//    CREATE_FUNC(MediaPlayerScene);
    
    //===================================
    
    //-----------------------------------
    void toNextScene();
};

#endif /* defined(__Cinderella_X__MediaPlayerScene__) */
