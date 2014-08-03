#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "AppMacros.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "CParallaxNodeExtras.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "BodyEditorLoader.h"

#define PTM_RATIO 32.0
USING_NS_CC;
using namespace std;
class HelloWorld : public cocos2d::CCLayer
{

	
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	



    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);


	
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	b2World* pworld;
	b2Body* pbodyYellowBall;

	b2Body* pbodyNetPot;

	b2Body* pbodyGround;
	b2Body* pbodyLeftWall;
	b2Body* pbodyRightWall;
	b2Body* pbodyTopWall;
	CCParallaxNodeExtras  *pBackgroundNode; 
	CCSprite* pSprite;
	CCSprite* pNextSprite;
	

public:
	void tick(float dt);
	//From CCLayer.h
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);


public:

	void createCloseButton( CCPoint &origin, CCSize &visibleSize );
	void CreateYellowBallAt(CCPoint position);

	void createGroundWall();
	void createLeftWall();
	void createRightWall();
	void createTopWall();

	void createNetPot();
	
	BodyEditorLoader loader;
	BodyEditorLoader netPotLoader;

	 CCLabelTTF* pLabel;

};

#endif // __HELLOWORLD_SCENE_H__
