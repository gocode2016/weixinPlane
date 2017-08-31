#pragma once 

#include "cocos2d.h"
#include "CommData.h"

using namespace cocos2d;

class Enemy:public Sprite{

	int m_HP;
	int m_Goal;
	int m_enemySpeed;
	EnemyType m_type;
public:

    Enemy(void);
    ~Enemy(void);
 
	virtual bool init(EnemyType);

	static Enemy* create(EnemyType);

	void down();
	void hit();
	//敌机属性接口
	int getSpeed();
	EnemyType getEnemyType();
	int getHP();
	int getGoal();
	void loseHP();
};
