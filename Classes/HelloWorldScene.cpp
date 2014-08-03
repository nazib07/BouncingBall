#include "HelloWorldScene.h"

#define COCOS2D_DEBUG 1


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	loader.SetFilePath(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("YellowBall.json"));
	netPotLoader.SetFilePath(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("netpot.json"));
	
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();



	///////////////////////////////////////////////////////////nazib edit//////////////////////////////////////////////////////
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	//bool b = this->isTouchEnabled();
	//this->setTouchEnabled(true);
	// b = this->isTouchEnabled();

	//========================================[create yellow ball sprite]================================
	CCSprite* pSpriteYellowBall;
	pSpriteYellowBall = CCSprite::create("YellowBall.png");
	pSpriteYellowBall->setPosition(ccp(100,300));
	this->addChild(pSpriteYellowBall,1);
	//====================================================================================================
	





	//========================================[Create world]==============================================
	b2Vec2 gravity = b2Vec2(0.0f,-9.8f);
	pworld = new b2World(gravity);
	//====================================================================================================


	//========================================[Create YellowBall Body]====================================

	// Create ball body and shape
	b2BodyDef yellowBallBodyDef;
	yellowBallBodyDef.type = b2_dynamicBody;
	yellowBallBodyDef.position.Set(100/PTM_RATIO, 300/PTM_RATIO);
	yellowBallBodyDef.userData = pSpriteYellowBall;
	pbodyYellowBall= pworld->CreateBody(&yellowBallBodyDef);

	//b2CircleShape circle;
	//circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef ballShapeDef;
	//ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	//pbodyYellowBall->CreateFixture(&ballShapeDef);
	loader.attachFixture(pbodyYellowBall, "Name", ballShapeDef, 50/PTM_RATIO);

	//====================================================================================================



	//////////////////////////////////////////////////////////////////////////
	
	//create netpot sprite
	createNetPot();


	//////////////////////////////////////////////////////////////////////////
	


	createGroundWall();
	createLeftWall();
	createRightWall();
	createTopWall();

	createCloseButton(origin, visibleSize);


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
     pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    /*CCSprite* */
	pSprite = CCSprite::create("BackGround.png");
	pNextSprite = CCSprite::create("BackGround.png");

    // position the sprite on the center of the screen
   // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(pSprite, 0);

	//=============================================[Parallax Node]=========================================================


	
	pBackgroundNode = CCParallaxNodeExtras::node(); 
	this->addChild(pBackgroundNode, -1);

	 CCPoint bgSpeed = ccp(0.05, 0.05);

	 pBackgroundNode->addChild(pSprite, 0, bgSpeed, ccp(0,visibleSize.height/2) ); 
	 pBackgroundNode->addChild(pNextSprite, 0, bgSpeed, ccp( pSprite->getContentSize().width,visibleSize.height/2));


	 //====================================================================================================================

	this->schedule(schedule_selector(HelloWorld::tick),1/60);

	// CCDirector::sharedDirector() -> getTouchDispatcher() -> addStandardDelegate( this, 0 );
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::tick(float dt) {
 

	//=================================
	CCPoint backgroundScrollVert = ccp(-2000, 0);
	pBackgroundNode->setPosition(ccpAdd(pBackgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));

	CCArray *BackGrounds = CCArray::createWithCapacity(2);
	BackGrounds->addObject(pSprite);
	BackGrounds->addObject(pNextSprite);
	for ( int ii = 0; ii < BackGrounds->count(); ii++ ) {
		CCSprite * BackGround = (CCSprite *)(BackGrounds->objectAtIndex(ii));
		float xPosition = pBackgroundNode->convertToWorldSpace(BackGround->getPosition()).x;
		float size = BackGround->getContentSize().width;
		if ( xPosition < -size/2 ) {
			pBackgroundNode->incrementOffset(ccp(BackGround->getContentSize().width*2,0),BackGround); 
		}                                   
	}
 

	//===================================

    pworld->Step(dt, 10, 10);
    for(b2Body *b = pworld->GetBodyList(); b; b=b->GetNext()) {    
        if (b->GetUserData() != NULL) {

			if(b->GetType() == b2_dynamicBody)
			{  
				CCSprite *ballData = (CCSprite *)b->GetUserData();
				ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
					b->GetPosition().y * PTM_RATIO));
				ballData->setRotation (-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}

			/*else if(b->GetType() == b2_staticBody)
			{
				CCSprite *ballData = (CCSprite *)b->GetUserData();
				ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
					b->GetPosition().y * PTM_RATIO));
				ballData->setRotation (-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}*/
        }        
    }
 
}






bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint p = pTouch->getLocation();
	
	
	if(p.y > 200)
	 {
		 CreateYellowBallAt(p);
	}
	else
	{
		//Apply impulse to all dynamic bodies

		for(b2Body *b = pworld->GetBodyList();b; b = b->GetNext())
		{

			if(b->GetType() == b2_dynamicBody)
			{

				b2Vec2 bodypos = b->GetWorldCenter();


				b2Vec2 impulse =    b2Vec2(bodypos.x*PTM_RATIO - p.x, bodypos.y*PTM_RATIO-p.y) ;

				float val = impulse.x*impulse.x + impulse.y*impulse.y;
				val = val/1000;

				impulse = b2Vec2(impulse.x/val, impulse.y/val);

				b->ApplyLinearImpulse(impulse, bodypos);


			
				
				
				
				cout<<"Bodypos:   x:  "<<bodypos.x<<"  y:  "<<bodypos.y<<endl;
				cout<<"Touchpos:   x:  "<<p.x<<"  y:  "<<p.y<<endl;
				cout<<"impulse:   x:  "<<impulse.x<<"  y:  "<<impulse.y<<endl;
			}
		}
	}
	return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}
void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){}


void HelloWorld::CreateYellowBallAt(CCPoint position)
{
	b2Body* yellowBody;
	//========================================[create yellow ball sprite]================================
	CCSprite* pSpriteYellowBall;
	pSpriteYellowBall = CCSprite::create("YellowBall.png");
	pSpriteYellowBall->setPosition(ccp(position.x,position.y));
	this->addChild(pSpriteYellowBall,1);
	//====================================================================================================
	


	//========================================[Create YellowBall Body]====================================

	// Create ball body and shape
	b2BodyDef yellowBallBodyDef;
	yellowBallBodyDef.type = b2_dynamicBody;
	yellowBallBodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
	yellowBallBodyDef.userData = pSpriteYellowBall;
	yellowBody= pworld->CreateBody(&yellowBallBodyDef);

	b2CircleShape circle;
	//circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef ballShapeDef;
	//ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.001f;
	//yellowBody->CreateFixture(&ballShapeDef);
	loader.attachFixture(yellowBody, "Name", ballShapeDef, 50/PTM_RATIO);

	//====================================================================================================

}


void HelloWorld::createCloseButton( CCPoint &origin, CCSize &visibleSize )
{
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
}



void HelloWorld::createGroundWall()
{
	//========================================[create ground sprite]======================================
	CCSprite* pSpriteGround;
	pSpriteGround = CCSprite::create("Ground.png");
	pSpriteGround->setPosition(ccp(512,50));
	this->addChild(pSpriteGround,1);
	//====================================================================================================


	//========================================[Create Ground Body]====================================

	// Create ball body and shape
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	//groundBodyDef.position.Set(512/PTM_RATIO, 50/PTM_RATIO);
	groundBodyDef.userData = pSpriteGround;
	pbodyGround= pworld->CreateBody(&groundBodyDef);

	b2Vec2 groundVertices[4] = {
		b2Vec2(0/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(1024/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(1024/PTM_RATIO,100/PTM_RATIO),
		b2Vec2(0/PTM_RATIO,100/PTM_RATIO)
	};
	b2PolygonShape ground;

	ground.Set(groundVertices, 4);

	/*circle.m_radius = 26.0/PTM_RATIO;*/

	b2FixtureDef groundShapeDef;
	groundShapeDef.shape = &ground;
	groundShapeDef.density = 1.0f;
	groundShapeDef.friction = 0.2f;
	groundShapeDef.restitution = 0.5f;
	pbodyGround->CreateFixture(&groundShapeDef);

	//====================================================================================================
}

void HelloWorld::createLeftWall()
{
	//========================================[create ground sprite]======================================
	//CCSprite* pSpriteLeftWall;
	//pSpriteLeftWall = CCSprite::create("Ground.png");
	//pSpriteLeftWall->setPosition(ccp(512,50));
	//this->addChild(pSpriteLeftWall,1);
	//====================================================================================================


	//========================================[Create Ground Body]====================================

	// Create ball body and shape
	b2BodyDef leftWallBodyDef;
	leftWallBodyDef.type = b2_staticBody;
	//groundBodyDef.position.Set(512/PTM_RATIO, 50/PTM_RATIO);
	//leftWallBodyDef.userData = pSpriteLeftWall;
	pbodyLeftWall= pworld->CreateBody(&leftWallBodyDef);

	b2Vec2 leftWallVertices[4] = {
		b2Vec2(-10/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(0/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(0/PTM_RATIO,768/PTM_RATIO),
		b2Vec2(-10/PTM_RATIO,768/PTM_RATIO)
	};
	b2PolygonShape leftWall;

	leftWall.Set(leftWallVertices, 4);

	/*circle.m_radius = 26.0/PTM_RATIO;*/

	b2FixtureDef leftWallShapeDef;
	leftWallShapeDef.shape = &leftWall;
	leftWallShapeDef.density = 1.0f;
	leftWallShapeDef.friction = 0.2f;
	leftWallShapeDef.restitution = 0.8f;
	pbodyGround->CreateFixture(&leftWallShapeDef);

	//====================================================================================================
}

void HelloWorld::createRightWall()
{

	//========================================[create ground sprite]======================================
	//CCSprite* pSpriteRightWall;
	//pSpriteRightWall = CCSprite::create("Ground.png");
	//pSpriteRightWall->setPosition(ccp(512,50));
	//this->addChild(pSpriteRightWall,1);
	//====================================================================================================


	//========================================[Create Ground Body]====================================

	// Create ball body and shape
	b2BodyDef rightWallBodyDef;
	rightWallBodyDef.type = b2_staticBody;
	//groundBodyDef.position.Set(512/PTM_RATIO, 50/PTM_RATIO);
	//rightWallBodyDef.userData = pSpriteRightWall;
	pbodyRightWall= pworld->CreateBody(&rightWallBodyDef);

	b2Vec2 rightWallVertices[4] = {
		b2Vec2(1024/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(1034/PTM_RATIO,0/PTM_RATIO),
		b2Vec2(1034/PTM_RATIO,768/PTM_RATIO),
		b2Vec2(1024/PTM_RATIO,768/PTM_RATIO)
	};
	b2PolygonShape rightWall;

	rightWall.Set(rightWallVertices, 4);

	/*circle.m_radius = 26.0/PTM_RATIO;*/

	b2FixtureDef rightWallShapeDef;
	rightWallShapeDef.shape = &rightWall;
	rightWallShapeDef.density = 1.0f;
	rightWallShapeDef.friction = 0.2f;
	rightWallShapeDef.restitution = 0.8f;
	pbodyGround->CreateFixture(&rightWallShapeDef);

	//====================================================================================================

}

void HelloWorld::createTopWall()
{


	//========================================[create ground sprite]======================================
	//CCSprite* pSpriteTopWall;
	//pSpriteTopWall = CCSprite::create("Ground.png");
	//pSpriteTopWall->setPosition(ccp(512,50));
	//this->addChild(pSpriteTopWall,1);
	//====================================================================================================


	//========================================[Create Ground Body]====================================

	// Create ball body and shape
	b2BodyDef topWallBodyDef;
	topWallBodyDef.type = b2_staticBody;
	//groundBodyDef.position.Set(512/PTM_RATIO, 50/PTM_RATIO);
	//topWallBodyDef.userData = pSpriteTopWall;
	pbodyTopWall= pworld->CreateBody(&topWallBodyDef);

	b2Vec2 topWallVertices[4] = {
		b2Vec2(0/PTM_RATIO,768/PTM_RATIO),
		b2Vec2(1024/PTM_RATIO,768/PTM_RATIO),
		b2Vec2(1024/PTM_RATIO,778/PTM_RATIO),
		b2Vec2(0/PTM_RATIO,778/PTM_RATIO)
	};
	b2PolygonShape topWall;

	topWall.Set(topWallVertices, 4);

	/*circle.m_radius = 26.0/PTM_RATIO;*/

	b2FixtureDef topWallShapeDef;
	topWallShapeDef.shape = &topWall;
	topWallShapeDef.density = 1.0f;
	topWallShapeDef.friction = 0.2f;
	topWallShapeDef.restitution = 0.8f;
	pbodyGround->CreateFixture(&topWallShapeDef);

	//====================================================================================================

}

void HelloWorld::createNetPot()
{
	CCSprite* pSpriteNetPot;
	pSpriteNetPot = CCSprite::create("netpot.png");
	pSpriteNetPot->setPosition(ccp(600,300));
	this->addChild(pSpriteNetPot,1);


	//create netpot body

	b2BodyDef netPotBodyDef;
	netPotBodyDef.type = b2_staticBody;
	netPotBodyDef.position.Set((600-120)/PTM_RATIO, (300-120)/PTM_RATIO);
	netPotBodyDef.userData = pSpriteNetPot;
	pbodyNetPot= pworld->CreateBody(&netPotBodyDef);

	//b2CircleShape circle;
	//circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef netPotShapeDef;
	//ballShapeDef.shape = &circle;
	netPotShapeDef.density = 1.0f;
	netPotShapeDef.friction = 1.0f;
	netPotShapeDef.restitution = 0.001f;
	//pbodyYellowBall->CreateFixture(&ballShapeDef);
	netPotLoader.attachFixture(pbodyNetPot, "netPot", netPotShapeDef, 240/PTM_RATIO);
}
