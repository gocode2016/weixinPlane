#include "Prop.h"

Prop::Prop(void){
}
Prop::~Prop(void){
}
//���ص�������
PropType Prop::getType(){
	return m_type;
}

bool Prop::init(PropType e){

	bool isSuccess;

	this->m_type=e;

	switch (e)
	{
	case PROP_DOUBLE:
		//���õ���init������create
		isSuccess=Sprite::initWithSpriteFrameName("ufo1.png");
		break;
	case PROP_BOMB:
		isSuccess=Sprite::initWithSpriteFrameName("bomb.png");
		break;
	default:
		isSuccess=false;
		break;
	}

	return isSuccess;
}

Prop* Prop::create(PropType e){
	auto prop = new Prop();
	if(prop &&prop->init(e))
	{
		prop->autorelease();
		return prop;
	}else{
		delete prop;
		prop = NULL;
		return NULL;
	}
}