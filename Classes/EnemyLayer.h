#pragma once

#include "cocos2d.h"  
#include "Enemy.h"
#include "CommData.h"

using namespace cocos2d;  

class EnemyLayer : public cocos2d::Layer  
{  
public:  
    EnemyLayer(Sprite* heroPlane);  
    ~EnemyLayer();  
    virtual bool init();  
  
    //根据英雄飞机创建敌机
    static EnemyLayer* create(Sprite* heroPlane);  
	//通过类型创建敌机
	void createEnemyByType(EnemyType);
	//添加敌机
	void addSmallEnemy(float dt); 
	void addMiddleEnemy(float dt); 
	void addBigEnemy(float dt); 
	//敌机加速
	void speedUp();
	//敌机爆炸
	void blowupEnemy(Node* pNode);  
	//清除单个敌机
	void removeEnemy(Node* pNode);  
	//清除所有敌机
	void removeAllEnemy();
	//返回敌机列表  
    Vector <Enemy *>& getEnemy(); 
public: 

    Vector <Enemy *> vecEnemy;//敌机容器  
    Sprite* heroPlane;//传入的英雄飞机  

	int upSpeed;
};  