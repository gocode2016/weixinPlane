#pragma once 

#include "cocos2d.h"

/**
�궨�壺�滻�����ַ���
**/

//���������С
#define VISIBLE_SIZE  Director::getInstance()->getVisibleSize()

//�ӵ������ٶȣ������Լ����ƣ�ÿ�����ߵ�����
#define SIGNLE_BULLET_SPEED  1000
#define DOUBLE_BULLET_SPEED  1500

//ÿ��˫�ӵ����ֵ�����
#define DOUBLE_BULLET_NUMBER 50

//�л��ٶ�
#define SMALL_ENEMY_SPEED 200
#define MIDDLE_ENEMY_SPEED 100
#define BIG_ENEMY_SPEED 50

enum EnemyType
{
	ENEMY_SMALL,
	ENEMY_MIDDLE,
	ENEMY_BIG,
};

enum BulletType
{
	BULLET_SIGNLE,
	BULLET_DOUBLE,
};

enum PropType
{
	PROP_DOUBLE,
	PROP_BOMB,
};