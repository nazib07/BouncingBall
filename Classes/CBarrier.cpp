#include "CBarrier.h"


CBarrier::CBarrier(void):mAngle(0.0f)
{
	loader.SetFilePath(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("Barrier.json"));
}


CBarrier::~CBarrier(void)
{
}


CBarrier* CBarrier::createBarrierWithFileName(const char* fileName)
{

	CBarrier* barrier = new CBarrier();

	if(barrier && barrier->initWithFile(fileName))
	{
		barrier->autorelease();

		return barrier;
	}
	CC_SAFE_DELETE(barrier);
	return NULL;
}
void CBarrier::UpdateBarrier(float dt)
{
	for(b2Body *b = PhysicsWorld::getInstance().GetBodyList(); b; b=b->GetNext()) 
	{    
        if (b->GetUserData() != NULL) 
		{
			CBarrier *barrierData = (CBarrier *)b->GetUserData();
			if(b->GetType() == b2_dynamicBody && barrierData)
			{			
				barrierData->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				barrierData->setRotation (-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}

        }        
    }
}

void CBarrier::addPhysicsBody(CCSprite* barrierSprite)
{ 
		// Create barrier body and shape

	

	b2BodyDef barrierBodyDef;
	barrierBodyDef.type = b2_staticBody;
	barrierBodyDef.position.Set(barrierSprite->getPosition().x/PTM_RATIO, barrierSprite->getPosition().y/PTM_RATIO);
	barrierBodyDef.angle = CC_DEGREES_TO_RADIANS(mAngle);
	barrierBodyDef.userData = barrierSprite;
	barrierBody= PhysicsWorld::getInstance().CreateBody(&barrierBodyDef);
	barrierSprite->setRotation(-1*CC_RADIANS_TO_DEGREES(barrierBody->GetAngle()));
	//b2CircleShape circle;
	//circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef barrierShapeDef;
	//barrierShapeDef.shape = &circle;
	barrierShapeDef.density = 1.0f;
	barrierShapeDef.friction = 0.2f;
	barrierShapeDef.restitution = 0.8f;
	//pbodyYellowbarrier->CreateFixture(&barrierShapeDef);
	loader.attachFixture(barrierBody, "Name", barrierShapeDef, 50/PTM_RATIO);
}

void CBarrier::setAngle(float angle)
{
	mAngle = angle;
}
float CBarrier::getAngle()
{
	return mAngle;
}