#pragma once

#include "cocos2d.h" 

using namespace cocos2d;

class WelcomeScene : public Layer{

public:
	bool init();
	CREATE_FUNC(WelcomeScene);

	static Scene *createScene();

	void initCache();
};
