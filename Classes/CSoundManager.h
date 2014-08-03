#pragma once

#include "SimpleAudioEngine.h"

class CSoundManager
{
public:

	void setBackGroundMusic(char* fileName);
	static CSoundManager& getInstance()
	{
		static CSoundManager    instance;
		return instance;
	}
private:
	CSoundManager(void);
	~CSoundManager(void);
};

