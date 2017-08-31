/** 
*功能 创建子弹并初始化子弹的运动 
*/  
#include "BulletLayer.h"
#include "CommData.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
/** 
*创建子弹，重写方法 
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
		//每隔0.2S调用一次发射子弹函数  
		this->schedule(schedule_selector(BulletLayer::createBullet), 0.2f);  
		bRet = true;  
	} while (0);  
	return bRet;  
}  
/** 
*用缓存的方法创建子弹，并初始化子弹的运动和运动后的事件 
*/  

void BulletLayer::createBullet(float) {

	SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");

	//找到飞机对象
	auto PlanePos = heroPlane->getPosition();  

	//子弹飞行距离
	float flyLen = VISIBLE_SIZE.height - PlanePos.y;    

	//从缓存中创建子弹    
	if (this->m_isDoubleBullet)
	{
		//创建一次双子弹，计数减一
		this->m_doubleBulletNumber--;
		//次数用完之后，自动切换回单子弹
		if (this->m_doubleBulletNumber <= 0)
		{
			this->m_isDoubleBullet = false;
		}
		float realFlyDuration = flyLen / DOUBLE_BULLET_SPEED;//实际飞行的时间

		//创建左侧的子弹
		auto leftBullet = Bullet::create(BULLET_DOUBLE);
		leftBullet->setPosition(PlanePos+ Point(-heroPlane->getContentSize().width/3, 0));
		//添加到层中，子弹将被渲染（绘制）出来
		this->addChild(leftBullet);
		//同时，添加到集合中，以便后续访问与操作
		this->vecBullet.pushBack(leftBullet);

		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端  
		auto actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x-heroPlane->getContentSize().width/3, VISIBLE_SIZE.height));  

		//子弹执行完动作后进行函数回调，调用移除子弹函数  
		auto actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//子弹开始跑动  
		leftBullet->runAction(Sequence::create(actionMove, actionDone, NULL));  

		//创建右侧的子弹
		auto rightBullet = Bullet::create(BULLET_DOUBLE);
		rightBullet->setPosition(PlanePos+ Point(heroPlane->getContentSize().width/3, 0));
		//添加到层中，子弹将被渲染（绘制）出来
		this->addChild(rightBullet);
		//同时，添加到集合中，以便后续访问与操作
		this->vecBullet.pushBack(rightBullet);

		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端  
		actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x+heroPlane->getContentSize().width/3, VISIBLE_SIZE.height));  

		//子弹执行完动作后进行函数回调，调用移除子弹函数  
		actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//子弹开始跑动  
		rightBullet->runAction(Sequence::create(actionMove, actionDone, NULL));  
	}else{

		//从缓存中创建子弹  
		auto spritebullet =Bullet::create(BULLET_SIGNLE);  
		//将创建好的子弹添加到BatchNode中进行批次渲染  
		this->addChild(spritebullet);  
		//将创建好的子弹添加到容器  
		vecBullet.pushBack(spritebullet);  

		Point bulletPos = (Point(PlanePos.x,PlanePos.y + heroPlane->getContentSize().height / 2 + 20));  
		spritebullet->setPosition(bulletPos);  
		spritebullet->setScale(0.8f);  

		float realFlyDuration = flyLen / SIGNLE_BULLET_SPEED;//实际飞行的时间
		//子弹运行的距离和时间，从飞机处开始运行到屏幕顶端  
		auto actionMove = MoveTo::create(realFlyDuration,  
			Point(PlanePos.x, VISIBLE_SIZE.height));  

		//子弹执行完动作后进行函数回调，调用移除子弹函数  
		auto actionDone = CallFuncN::create(  
			CC_CALLBACK_1(BulletLayer::removeBullet, this));  

		//子弹开始跑动  
		spritebullet->runAction(Sequence::create(actionMove, actionDone, NULL));  
	}
}
/** 
*改变子弹类型 
*/  
void BulletLayer::changeType(){
	this->m_isDoubleBullet=true;
	this->m_doubleBulletNumber=DOUBLE_BULLET_NUMBER;
}
//添加普通子弹
void BulletLayer::shootSignleBullet(float dt) {  
	this->m_isDoubleBullet=false;
	createBullet(0);
}  
//添加双行子弹
void BulletLayer::shootDoubleBullet(float dt) { 
	this->m_isDoubleBullet=true;
	createBullet(0);
} 
/** 
* 移除子弹，将子弹从容器中移除
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
*返回子弹列表，用来与敌机做碰撞检测 
*/  
Vector <Sprite *>& BulletLayer::getBullet(){  
	return vecBullet;  
}  

