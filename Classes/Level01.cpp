#include "Level01.h"

USING_NS_CC;

Level01::Level01(void)
{
}

Level01::~Level01(void)
{
}

CCScene* Level01::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Level01 *layer = Level01::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Level01::init()
{

		
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	pworld =& PhysicsWorld::getInstance(); 


	//Add BackGround Sound
	pSoundManager = &CSoundManager::getInstance();
	pSoundManager->setBackGroundMusic(LEVEL_01_BACKGROUND_MUSIC);
    
     pLabel = CCLabelTTF::create("", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    /*CCSprite* */
	pSprite = CCSprite::create(LEVEL_01_BACKGROUND);

	  // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	// create Ball
	pBall = CBall::createBallWithFileName(LEVEL_01_BALL);
	pBall->setPosition(LEVEL_01_BALL_POS);
	pBall->addPhysicsBody(pBall);
	this->addChild(pBall, LEVEL_01_BALL_LAYER);

	// create Barrier
	pBarrier = CBarrier::createBarrierWithFileName(LEVEL_01_BARRIER);
	pBarrier->setPosition(LEVEL_01_BARRIER_POS);
	pBarrier->setAngle(LEVEL_01_BARRIER_ANGLE_IN_DEGREES);
	pBarrier->addPhysicsBody(pBarrier);
	this->addChild(pBarrier, LEVEL_01_BARRIER_LAYER);


	this->schedule(schedule_selector(Level01::tick),1/60);

	return true;
}


void Level01::tick(float dt)
{
	
	pworld->Step(dt, 10, 10);
	pBall->UpdateBall(dt);

}