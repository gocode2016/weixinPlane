#pragma once

#include "cocos2d.h"  
#include "Bullet .h"

using namespace cocos2d;    

class BulletLayer : public cocos2d::Layer  
{  
public:  
    BulletLayer(Sprite* heroPlane);  
    ~BulletLayer();  
    virtual bool init();  
  
    //根据英雄飞机创建子弹  
    static BulletLayer* create(Sprite* heroPlane);  
  
    //移除超出屏幕可视范围的子弹或者碰撞后的子弹清除  
    void removeBullet(Node* pNode);  
  
    //发射子弹，在其中进行子弹的渲染和子弹的飞行动作，默认为单子弹  
	void createBullet(float);
	void shootSignleBullet(float dt);  
    void shootDoubleBullet(float dt);  
	//切换子弹类型
	void changeType();

    //返回子弹列表  
    Vector <Sprite *>& getBullet();  
public:  
	//子弹容器
    Vector <Sprite *>vecBullet;  
	//传入的英雄飞机  
    Sprite* heroPlane;  
	//是否切换到双子弹
	bool m_isDoubleBullet;	
	//双子弹的发射次数
	int m_doubleBulletNumber;

};  