/** 
*功能 创建敌机并初始化敌机的运动 
*/  
#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(Sprite* heroPlane) {  
	this->heroPlane = heroPlane; 
	this->upSpeed=0;
}  

EnemyLayer::~EnemyLayer() {  
}  

/** 
*创建敌机的静态方法 
*@param heroPlane为英雄飞机 
*/  
EnemyLayer* EnemyLayer::create(Sprite* heroPlane){  
	EnemyLayer* pRet = new EnemyLayer(heroPlane);  
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
bool EnemyLayer::init() {  
	bool bRet = false;   

	do {  
		CC_BREAK_IF(!Layer::init());  

		this->schedule(schedule_selector(EnemyLayer::addSmallEnemy), 0.8f, -1, 3);
		this->schedule(schedule_selector(EnemyLayer::addMiddleEnemy), 2, -1, 6); 
		this->schedule(schedule_selector(EnemyLayer::addBigEnemy), 20, -1, 12); 
		bRet = true;  
	} while (0);  
	return bRet;  
} 
//返回敌机列表  
Vector <Enemy *>& EnemyLayer::getEnemy(){

	return vecEnemy;
}

void EnemyLayer::createEnemyByType(EnemyType type){
	//调用绑定敌机 
	Enemy* enemy=Enemy::create(type);  

	//随机初始位置  
	Size enemy1Size=enemy->getContentSize();  
	int minX=enemy1Size.width/2;  
	int maxX=VISIBLE_SIZE.width-enemy1Size.width/2;  
	int rangeX=maxX-minX;  
	int actualX=(rand()%rangeX)+minX;  

	enemy->setPosition(Point(actualX,VISIBLE_SIZE.height+enemy1Size.height/2));  
	this->addChild(enemy);  

	this->vecEnemy.pushBack(enemy);   
	//Point enemyPos = (Point(heroPlane->getPositionX(),VISIBLE_SIZE.height));  
	//enemy1->setPosition(enemyPos);  
	enemy->setScale(0.8f);  
	//计算实际飞行的时间  
	float realFlyDuration =( VISIBLE_SIZE.height+enemy1Size.height) / (enemy->getSpeed()+this->upSpeed);

	//敌机运行的距离和时间，从飞机处开始运行到屏幕顶端  
	auto actionMove = MoveTo::create(realFlyDuration,  
		Point(actualX, -enemy1Size.height/2));  

	//敌机执行完动作后进行函数回调，调用移除敌机函数  
	auto actionDone = CallFuncN::create(  
		CC_CALLBACK_1(EnemyLayer::removeEnemy, this));  

	//敌机enemy开始跑动  
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);  
	enemy->runAction(sequence);  
}
void EnemyLayer::addSmallEnemy(float dt){

	createEnemyByType(ENEMY_SMALL);
}
void EnemyLayer::addMiddleEnemy(float dt){

	createEnemyByType(ENEMY_MIDDLE);
}
void EnemyLayer::addBigEnemy(float dt){

	createEnemyByType(ENEMY_BIG);
}

//敌机加速
void EnemyLayer::speedUp(){
	this->upSpeed+=10;
}
//敌机爆炸  
void EnemyLayer::blowupEnemy(Node* pNode){  
	if (NULL == pNode) {  
		return;  
	}  
	Enemy* enemy = (Enemy*) pNode;  
	vecEnemy.eraseObject(enemy);
}  

//移除单架敌机
void EnemyLayer::removeEnemy(Node* pNode) {  
	if (NULL == pNode) {  
		return;  
	}  
	Enemy* enemy = (Enemy*) pNode;

	this->removeChild(enemy);

	vecEnemy.eraseObject(enemy);
}  

//移除单架敌机
void EnemyLayer::removeAllEnemy() {  

	vecEnemy.clear();
}  