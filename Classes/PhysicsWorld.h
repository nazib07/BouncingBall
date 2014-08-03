#pragma once

#include <Box2D/Box2D.h>
#include "Constants.h"
class PhysicsWorld : public b2World
{
public:
	static PhysicsWorld& getInstance()
	{
		static PhysicsWorld    instance;
		return instance;
	}

private:
	PhysicsWorld():b2World(GRAVITY){}
	PhysicsWorld(PhysicsWorld const&);              // Don't Implement.
	void operator=(PhysicsWorld const&); // Don't implement
};

