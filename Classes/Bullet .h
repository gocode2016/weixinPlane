#pragma once 

#include "cocos2d.h"
#include "CommData.h"

using namespace cocos2d;

class Bullet : public Sprite{

public:
	Bullet();

	static Bullet *create(BulletType type);

	bool init(BulletType type);

private:
	BulletType m_type;
};
