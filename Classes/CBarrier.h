#pragma once

#include "cocos2d.h"
#include "Globals.h"


#include "BodyEditorLoader.h"
class CBarrier : public cocos2d::CCSprite
{
public:
	CBarrier(void);
	~CBarrier(void);

	static CBarrier* createBarrierWithFileName(const char* fileName);
	void addPhysicsBody(CCSprite* barrierSprite);
	void UpdateBarrier(float dt);
	void setAngle(float angle);
	float getAngle();

private:
	BodyEditorLoader loader;
	b2Body* barrierBody;
	float mAngle;
	
};

