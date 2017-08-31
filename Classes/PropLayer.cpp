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

	//�������ˮƽλ������
	float minX = prop->getContentSize().width/2;
	float maxX = VISIBLE_SIZE.width-minX;
	float x = rand() % (int)(maxX-minX)+minX;
	float y = VISIBLE_SIZE.height+prop->getContentSize().height/2;
	prop->setPosition(x, y);
	this->addChild(prop);
	this->m_vecProp.pushBack(prop);
	//�ƶ����ߣ���-��-��-���٣�
	auto move1 = MoveBy::create(0.5f, Point(0, -300));
	auto move2 = MoveBy::create(0.5f, Point(0, 300));
	//���ƶ�1/2�����ȣ���ֹ��ִ�����ٹ����б��ɻ��ɼ�
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
//���ص����б�  
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