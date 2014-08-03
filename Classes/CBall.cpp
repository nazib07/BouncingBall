#include "CBall.h"


CBall::CBall(void)
{
    string str =  cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("YellowBall.json");
	loader.SetFilePath(str);
}


CBall::~CBall(void)
{
}


CBall* CBall::createBallWithFileName(const char* fileName)
{

	CBall* ball = new CBall();

	if(ball && ball->initWithFile(fileName))
	{
		ball->autorelease();

		return ball;
	}
	CC_SAFE_DELETE(ball);
	return NULL;
}
void CBall::UpdateBall(float dt)
{
	for(b2Body *b = PhysicsWorld::getInstance().GetBodyList(); b; b=b->GetNext()) 
	{    
        if (b->GetUserData() != NULL) 
		{
			CBall *ballData = (CBall *)b->GetUserData();
			if(b->GetType() == b2_dynamicBody && ballData)
			{			
				ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				ballData->setRotation (-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}

        }        
    }
}

void CBall::addPhysicsBody(CCSprite* ballSprite)
{ 
		// Create ball body and shape
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(ballSprite->getPosition().x/PTM_RATIO, ballSprite->getPosition().y/PTM_RATIO);
	ballBodyDef.userData = ballSprite;
	ballBody= PhysicsWorld::getInstance().CreateBody(&ballBodyDef);

	//b2CircleShape circle;
	//circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef ballShapeDef;
	//ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	//pbodyYellowBall->CreateFixture(&ballShapeDef);
	loader.attachFixture(ballBody, "Name", ballShapeDef, 50/PTM_RATIO);
}