#ifndef __C_BALL_H__
#define __C_BALL_H__

#include "cocos2d.h"
#include "Globals.h"

#include "BodyEditorLoader.h"
class CBall : public cocos2d::CCSprite
{
public:
	CBall(void);
	~CBall(void);

	static CBall* createBallWithFileName(const char* fileName);
	void addPhysicsBody(CCSprite* ballSprite);
	void UpdateBall(float dt);

private:
	BodyEditorLoader loader;
	b2Body* ballBody;
	
};

#endif