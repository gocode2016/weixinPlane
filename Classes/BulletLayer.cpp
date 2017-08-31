/** 
*���� �����ӵ�����ʼ���ӵ����˶� 
*/  
#include "BulletLayer.h"
#include "CommData.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
/** 
*�����ӵ�����д���� 
*/  
BulletLayer::BulletLayer(Sprite* heroPlane) {  
	this->heroPlane = heroPlane;  
}  
BulletLayer::~BulletLayer() {  
}  
BulletLayer* BulletLayer::create(Sprite* heroPlane){  
	BulletLayer* pRet = new BulletLayer(heroPlane);  
	if (pRet&&pRet->init()){  
		pRet->autorelease();  
		return pRet;  
	}  
	else{  
		delete pRet;  
		pRet = NULL;  
		return NULL;  
	}  

}  
bool BulletLayer::init() {  
	bool bRet = false;  

	this->m_isDoubleBullet=false;	
	this->m_doubleBulletNumber=0;

	do {  
		CC_BREAK_IF(!Layer::init());  
		//ÿ��0.2S����һ�η����ӵ�����  
		this->schedule(schedule_selector(BulletLayer::createBullet), 0.2f);  
		bRet = true;  
	} while (0);  
	return bRet;  
}  
/** 
*�û���ķ��������ӵ�������ʼ���ӵ����˶����˶�����¼� 
*/  

void BulletLayer::createBullet(float) {

	SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");

	//�ҵ��ɻ�����
	auto PlanePos = heroPlane->getPosition();  

	//�ӵ����о���
	float flyLen = VISIBLE_SIZE.height - PlanePos.y;    

	//�ӻ����д����ӵ�    
	if (this->m_isDoubleBullet)
	{
		//����һ��˫�ӵ���������һ
		this->m_doubleBulletNumber--;
		//��������֮���Զ��л��ص��ӵ�
		if (this->m_doubleBulletNumber <= 0)
		{
			this->m_isDoubleBullet = false;
		}
		float realFlyDuration = flyLen / DOUBLE_BULLET_SPEED;//ʵ�ʷ��е�ʱ��

		//���������ӵ�
		auto leftBullet = Bullet::create(BULLET_DOUBLE);
		leftBullet->setPosition(PlanePos+ Point(-heroPlane->getContentSize().width/3, 0));
		//��ӵ����У��ӵ�������Ⱦ�����ƣ�����
		this->addChild(leftBullet);
		//ͬʱ����ӵ������У��Ա�������������
		this->vecBullet.pushBack(leftBullet);

		//�ӵ����еľ����ʱ�䣬�ӷɻ�����ʼ���е���Ļ����  
		auto actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x-heroPlane->getContentSize().width/3, VISIBLE_SIZE.height));  

		//�ӵ�ִ���궯������к����ص��������Ƴ��ӵ�����  
		auto actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//�ӵ���ʼ�ܶ�  
		leftBullet->runAction(Sequence::create(actionMove, actionDone, NULL));  

		//�����Ҳ���ӵ�
		auto rightBullet = Bullet::create(BULLET_DOUBLE);
		rightBullet->setPosition(PlanePos+ Point(heroPlane->getContentSize().width/3, 0));
		//��ӵ����У��ӵ�������Ⱦ�����ƣ�����
		this->addChild(rightBullet);
		//ͬʱ����ӵ������У��Ա�������������
		this->vecBullet.pushBack(rightBullet);

		//�ӵ����еľ����ʱ�䣬�ӷɻ�����ʼ���е���Ļ����  
		actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x+heroPlane->getContentSize().width/3, VISIBLE_SIZE.height));  

		//�ӵ�ִ���궯������к����ص��������Ƴ��ӵ�����  
		actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//�ӵ���ʼ�ܶ�  
		rightBullet->runAction(Sequence::create(actionMove, actionDone, NULL));  
	}else{

		//�ӻ����д����ӵ�  
		auto spritebullet =Bullet::create(BULLET_SIGNLE);  
		//�������õ��ӵ���ӵ�BatchNode�н���������Ⱦ  
		this->addChild(spritebullet);  
		//�������õ��ӵ���ӵ�����  
		vecBullet.pushBack(spritebullet);  

		Point bulletPos = (Point(PlanePos.x,PlanePos.y + heroPlane->getContentSize().height / 2 + 20));  
		spritebullet->setPosition(bulletPos);  
		spritebullet->setScale(0.8f);  

		float realFlyDuration = flyLen / SIGNLE_BULLET_SPEED;//ʵ�ʷ��е�ʱ��
		//�ӵ����еľ����ʱ�䣬�ӷɻ�����ʼ���е���Ļ����  
		auto actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x, VISIBLE_SIZE.height));  

		//�ӵ�ִ���궯������к����ص��������Ƴ��ӵ�����  
		auto actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//�ӵ���ʼ�ܶ�  
		spritebullet->runAction(Sequence::create(actionMove, actionDone, NULL));  
	}
}
/** 
*�ı��ӵ����� 
*/  
void BulletLayer::changeType(){
	this->m_isDoubleBullet=true;
	this->m_doubleBulletNumber=DOUBLE_BULLET_NUMBER;
}
//�����ͨ�ӵ�
void BulletLayer::shootSignleBullet(float dt) {  
	this->m_isDoubleBullet=false;
	createBullet(0);
}  
//���˫���ӵ�
void BulletLayer::shootDoubleBullet(float dt) { 
	this->m_isDoubleBullet=true;
	createBullet(0);
} 
/** 
* �Ƴ��ӵ������ӵ����������Ƴ�
*/  
void BulletLayer::removeBullet(Node* pNode) {  
	if (NULL == pNode) {  
		return;  
	}  
	Sprite* bullet = (Sprite*)pNode;  
	this->removeChild(bullet, true);  
	vecBullet.eraseObject(bullet);  
}  
/** 
*�����ӵ��б�������л�����ײ��� 
*/  
Vector <Sprite *>& BulletLayer::getBullet(){  
	return vecBullet;  
}  

