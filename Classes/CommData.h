#pragma once 

#include "cocos2d.h"

/**
宏定义：替换定义字符串
**/

//可视区域大小
#define VISIBLE_SIZE  Director::getInstance()->getVisibleSize()

//子弹运行速度，可以自己控制，每秒所走的像素
#define SIGNLE_BULLET_SPEED  1000
#define DOUBLE_BULLET_SPEED  1500

//每次双子弹出现的数量
#define DOUBLE_BULLET_NUMBER 50

//敌机速度
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