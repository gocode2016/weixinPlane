#pragma once

#include "cocos2d.h"

#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "PropLayer.h"

using namespace cocos2d;

class GameScene: public cocos2d::Layer
{
	Point vec;

	int m_score;  //�÷�
	int m_speedLevel; //�÷�ƥ���ٶȵȼ�

	bool is_GameOver;//��Ϸ�Ƿ����
	bool is_Movable; //�ɻ��Ƿ���ƶ�

	BulletLayer* mBulletLayer;
	EnemyLayer* mEnemyLayer;
	PropLayer* mPropLayer;
	Sprite* mPlane;
public:

	static Scene* createScene();
	virtual bool init();
	static GameScene* create();
	//��ʼ����
	void initBackground();
	//��ʼ��Ч
	void initAudio();
	//��ʼ�˵���
	void initMenu();
	//��ʼӢ�۷ɻ�
	void initHeroPlane();

	//��ͣ
	void pause(Ref *);
	//����
	void resume(Ref *);

	//��Ƶ�ʸ���
	void update(float);
	//����ը����ǩ����
	void updateBombLabel(float);
	//��ײ���
	void checkEnemyCrash();//��ײ���֮�л�
	void checkPropCrash();//��ײ���֮����
};