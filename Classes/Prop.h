#pragma once 

#include "cocos2d.h"
#include "CommData.h"

using namespace cocos2d;

class Prop: public Sprite{

	PropType m_type;

public :
	Prop(void);
    ~Prop(void);
 
	virtual bool init(PropType);

	static Prop* create(PropType);
	//返回道具类型
	PropType getType();
};