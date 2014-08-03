#ifndef __LEVEL_01_H__
#define __LEVEL_01_H__

#include "AppMacros.h"
#include "cocos2d.h"
#include "CBall.h"
#include "Constants.h"
#include "CBarrier.h"
#include "CSoundManager.h"


USING_NS_CC;

class Level01 : public cocos2d::CCLayer
{
public:
	Level01(void);
	~Level01(void);

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
virtual bool init(); 
// there's no 'id' in cpp, so we recommend returning the class instance pointer
static cocos2d::CCScene* scene();
// a selector callback
void menuCloseCallback(CCObject* pSender);
// implement the "static node()" method manually
CREATE_FUNC(Level01);

void tick(float dt);

private:
	CCSprite* pSprite;
	CCLabelTTF* pLabel;
	
	CBall* pBall;
	CBarrier* pBarrier;

	CSoundManager* pSoundManager;
	


	b2World* pworld; 

};

#endif //End of LEVEL_01