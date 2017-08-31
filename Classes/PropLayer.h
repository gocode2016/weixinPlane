#pragma once

#include "cocos2d.h" 
#include "CommData.h"
#include "Prop.h"

using namespace cocos2d;  

class PropLayer: public Layer{

public:
	PropLayer(Sprite* heroPlane);  
    ~PropLayer();  
    virtual bool init();  
  
    static PropLayer* create(Sprite* heroPlane); 
  
    //根据道具类型创建道具 
	void createPropByType(PropType type);
	void createUFO(float dt);  
    void createBomb(float dt);  
	//移除道具
	void removeProp(Node* pNode); 
	//炸弹数量+1
	void addBomb();
	//炸弹数量+1
	void useBomb();
	int getBombNumber();
    //返回道具列表  
    Vector <Prop *>& getProps();  
public:  
	//道具容器
    Vector <Prop *>m_vecProp;  
	//传入的英雄飞机  
    Sprite* m_heroPlane; 
	//炸弹数量
	int m_BombNumber;
};