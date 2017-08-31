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
  
    //���ݵ������ʹ������� 
	void createPropByType(PropType type);
	void createUFO(float dt);  
    void createBomb(float dt);  
	//�Ƴ�����
	void removeProp(Node* pNode); 
	//ը������+1
	void addBomb();
	//ը������+1
	void useBomb();
	int getBombNumber();
    //���ص����б�  
    Vector <Prop *>& getProps();  
public:  
	//��������
    Vector <Prop *>m_vecProp;  
	//�����Ӣ�۷ɻ�  
    Sprite* m_heroPlane; 
	//ը������
	int m_BombNumber;
};