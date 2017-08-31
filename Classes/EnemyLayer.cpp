/** 
*���� �����л�����ʼ���л����˶� 
*/  
#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(Sprite* heroPlane) {  
	this->heroPlane = heroPlane; 
	this->upSpeed=0;
}  

EnemyLayer::~EnemyLayer() {  
}  

/** 
*�����л��ľ�̬���� 
*@param heroPlaneΪӢ�۷ɻ� 
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
//���صл��б�  
Vector <Enemy *>& EnemyLayer::getEnemy(){

	return vecEnemy;
}

void EnemyLayer::createEnemyByType(EnemyType type){
	//���ð󶨵л� 
	Enemy* enemy=Enemy::create(type);  

	//�����ʼλ��  
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
	//����ʵ�ʷ��е�ʱ��  
	float realFlyDuration =( VISIBLE_SIZE.height+enemy1Size.height) / (enemy->getSpeed()+this->upSpeed);

	//�л����еľ����ʱ�䣬�ӷɻ�����ʼ���е���Ļ����  
	auto actionMove = MoveTo::create(realFlyDuration,  
		Point(actualX, -enemy1Size.height/2));  

	//�л�ִ���궯������к����ص��������Ƴ��л�����  
	auto actionDone = CallFuncN::create(  
		CC_CALLBACK_1(EnemyLayer::removeEnemy, this));  

	//�л�enemy��ʼ�ܶ�  
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

//�л�����
void EnemyLayer::speedUp(){
	this->upSpeed+=10;
}
//�л���ը  
void EnemyLayer::blowupEnemy(Node* pNode){  
	if (NULL == pNode) {  
		return;  
	}  
	Enemy* enemy = (Enemy*) pNode;  
	vecEnemy.eraseObject(enemy);
}  

//�Ƴ����ܵл�
void EnemyLayer::removeEnemy(Node* pNode) {  
	if (NULL == pNode) {  
		return;  
	}  
	Enemy* enemy = (Enemy*) pNode;

	this->removeChild(enemy);

	vecEnemy.eraseObject(enemy);
}  

//�Ƴ����ܵл�
void EnemyLayer::removeAllEnemy() {  

	vecEnemy.clear();
}  