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
  
    //����Ӣ�۷ɻ������ӵ�  
    static BulletLayer* create(Sprite* heroPlane);  
  
    //�Ƴ�������Ļ���ӷ�Χ���ӵ�������ײ����ӵ����  
    void removeBullet(Node* pNode);  
  
    //�����ӵ��������н����ӵ�����Ⱦ���ӵ��ķ��ж�����Ĭ��Ϊ���ӵ�  
	void createBullet(float);
	void shootSignleBullet(float dt);  
    void shootDoubleBullet(float dt);  
	//�л��ӵ�����
	void changeType();

    //�����ӵ��б�  
    Vector <Sprite *>& getBullet();  
public:  
	//�ӵ�����
    Vector <Sprite *>vecBullet;  
	//�����Ӣ�۷ɻ�  
    Sprite* heroPlane;  
	//�Ƿ��л���˫�ӵ�
	bool m_isDoubleBullet;	
	//˫�ӵ��ķ������
	int m_doubleBulletNumber;

};  