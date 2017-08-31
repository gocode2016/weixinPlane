#pragma once

#include "cocos2d.h"

#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "PropLayer.h"

using namespace cocos2d;

class GameScene: public cocos2d::Layer
{
	Point vec;

	int m_score;  //得分
	int m_speedLevel; //得分匹配速度等级

	bool is_GameOver;//游戏是否结束
	bool is_Movable; //飞机是否可移动

	BulletLayer* mBulletLayer;
	EnemyLayer* mEnemyLayer;
	PropLayer* mPropLayer;
	Sprite* mPlane;
public:

	static Scene* createScene();
	virtual bool init();
	static GameScene* create();
	//初始背景
	void initBackground();
	//初始音效
	void initAudio();
	//初始菜单项
	void initMenu();
	//初始英雄飞机
	void initHeroPlane();

	//暂停
	void pause(Ref *);
	//继续
	void resume(Ref *);

	//主频率更新
	void update(float);
	//更新炸弹标签数据
	void updateBombLabel(float);
	//碰撞检测
	void checkEnemyCrash();//碰撞检测之敌机
	void checkPropCrash();//碰撞检测之道具
};