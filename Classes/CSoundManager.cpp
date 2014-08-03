#include "CSoundManager.h"


CSoundManager::CSoundManager(void)
{
}


CSoundManager::~CSoundManager(void)
{
}

void CSoundManager::setBackGroundMusic(char* fileName)
{
	if(fileName != NULL)
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fileName, true);  
}
