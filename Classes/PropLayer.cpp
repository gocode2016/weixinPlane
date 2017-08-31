#include "PropLayer.h"

PropLayer::PropLayer(Sprite* heroPlane){
	this->m_heroPlane = heroPlane;  
}
PropLayer::~PropLayer(){

}
bool PropLayer::init(){

	bool bRet = false;  

	this->m_BombNumber=0;

	do {  
		CC_BREAK_IF(!Layer::init());  

		this->schedule(schedule_selector(PropLayer::createUFO), 12, -1, 12);
		this->schedule(schedule_selector(PropLayer::createBomb), 30, -1, 20);
		bRet = true;  
	} while (0);  
	return bRet;  

}

PropLayer* PropLayer::create(Sprite* heroPlane){
	PropLayer* pRet = new PropLayer(heroPlane);  
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

void PropLayer::createPropByType(PropType type){

	Prop* prop=Prop::create(type);

	//设置随机水平位置坐标
	float minX = prop->getContentSize().width/2;
	float maxX = VISIBLE_SIZE.width-minX;
	float x = rand() % (int)(maxX-minX)+minX;
	float y = VISIBLE_SIZE.height+prop->getContentSize().height/2;
	prop->setPosition(x, y);
	this->addChild(prop);
	this->m_vecProp.pushBack(prop);
	//移动道具（下-上-下-销毁）
	auto move1 = MoveBy::create(0.5f, Point(0, -300));
	auto move2 = MoveBy::create(0.5f, Point(0, 300));
	//多移动1/2个长度，防止在执行销毁过程中被飞机采集
	auto move3 = MoveTo::create(1.2f, Point(x, -prop->getContentSize().height));
	auto callFunc = CallFuncN::create([](Node *node){
		node->removeFromParentAndCleanup(true);
	});
	prop->runAction(Sequence::create(move1, move2, move3, callFunc, NULL));
}
void PropLayer::createUFO(float dt){
	createPropByType(PROP_DOUBLE);
}    
void PropLayer::createBomb(float dt){
	createPropByType(PROP_BOMB);
}
void PropLayer::removeProp(Node* pNode){

	Prop* prop = (Prop*) pNode;

	this->removeChild(prop);

	m_vecProp.eraseObject(prop);
}
//返回道具列表  
Vector <Prop *>& PropLayer::getProps(){

	return m_vecProp;
}

void PropLayer::addBomb(){
	this->m_BombNumber++;
}
void PropLayer::useBomb(){
	this->m_BombNumber--;
}

int PropLayer::getBombNumber(){
	return this->m_BombNumber;
}