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
  
    //����Ӣ�۷ɻ������л�
    static EnemyLayer* create(Sprite* heroPlane);  
	//ͨ�����ʹ����л�
	void createEnemyByType(EnemyType);
	//��ӵл�
	void addSmallEnemy(float dt); 
	void addMiddleEnemy(float dt); 
	void addBigEnemy(float dt); 
	//�л�����
	void speedUp();
	//�л���ը
	void blowupEnemy(Node* pNode);  
	//��������л�
	void removeEnemy(Node* pNode);  
	//������ел�
	void removeAllEnemy();
	//���صл��б�  
    Vector <Enemy *>& getEnemy(); 
public: 

    Vector <Enemy *> vecEnemy;//�л�����  
    Sprite* heroPlane;//�����Ӣ�۷ɻ�  

	int upSpeed;
};  