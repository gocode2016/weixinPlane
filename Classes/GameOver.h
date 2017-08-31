#pragma once

#include "cocos2d.h" 

USING_NS_CC;

class GameOverScene : public Layer{

	int m_Score;

public:
	bool init(int );
	//CREATE_FUNC(GameOverScene);
	static GameOverScene *create(int );

	static Scene *createScene(int );

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);  

	void setScore(int);
};
