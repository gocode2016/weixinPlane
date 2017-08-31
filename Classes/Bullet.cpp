#include "Bullet .h"

Bullet::Bullet(){

}

Bullet* Bullet::create(BulletType type){

	Bullet* bullet=new Bullet();

	if(bullet&& bullet->init(type)){
		bullet->autorelease();
		return bullet;
	}else{
		delete bullet;
		bullet=NULL;
		return NULL;
	}

}

bool Bullet::init(BulletType type){
	bool isSuccess;

	this->m_type=type;

	switch (type)
	{
	case BULLET_SIGNLE:
		//调用的事init而不是create
		isSuccess=Sprite::initWithSpriteFrameName("bullet1.png");
		
		break;
	case BULLET_DOUBLE:
		isSuccess=Sprite::initWithSpriteFrameName("bullet2.png");
		
		break;
	default:
		isSuccess=false;
		break;
	}

	return isSuccess;
}