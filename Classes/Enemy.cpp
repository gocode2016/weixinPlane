#include "Enemy.h" 
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Enemy::Enemy(void)  
{  
	m_HP=0;//生命值  
	m_enemySpeed=0;
}  


Enemy::~Enemy(void)  
{  

} 

int Enemy::getSpeed(){
	return m_enemySpeed;
}

int Enemy::getHP(){
	return m_HP;
}

int Enemy::getGoal(){
	return m_Goal;
}

EnemyType Enemy::getEnemyType(){
	return m_type;
}

void Enemy::loseHP(){
    m_HP--;
}

bool Enemy::init(EnemyType e){

	bool isSuccess;

	this->m_type=e;

	switch (e)
	{
	case ENEMY_SMALL:
		//调用的事init而不是create
		isSuccess=Sprite::initWithSpriteFrameName("enemy1.png");
		this->m_enemySpeed = SMALL_ENEMY_SPEED;
		this->m_HP = 1;
		this->m_Goal = 10;
		break;
	case ENEMY_MIDDLE:
		isSuccess=Sprite::initWithSpriteFrameName("enemy2.png");
		this->m_enemySpeed = MIDDLE_ENEMY_SPEED;
		this->m_HP = 4;
		this->m_Goal = 50;
		break;
	case ENEMY_BIG:
		isSuccess=Sprite::initWithSpriteFrameName("enemy3_n1.png");
		this->m_enemySpeed = BIG_ENEMY_SPEED;
		this->m_HP = 8;
		this->m_Goal = 100;
		{
			//大飞机的飞行动画
			this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("BigEnemyFly")));
		}
		break;
	default:
		isSuccess=false;
		break;
	}

	return isSuccess;
}

Enemy* Enemy::create(EnemyType e){
	auto enemy = new Enemy();
	if(enemy &&enemy->init(e))
	{
		enemy->autorelease();
		return enemy;
	}else{
		delete enemy;
		enemy = NULL;
		return NULL;
	}
}

void Enemy::down(){

	//获取爆炸动画并执行
	Animation *animation;

	switch (m_type)
	{
	case ENEMY_SMALL:
		SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
		animation = AnimationCache::getInstance()->getAnimation("SmallEnemyBlow");
		break;
	case ENEMY_MIDDLE:
		SimpleAudioEngine::getInstance()->playEffect("enemy2_down.mp3");
		animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyBlow");
		break;
	case ENEMY_BIG:
		SimpleAudioEngine::getInstance()->playEffect("enemy3_down.mp3");
		animation = AnimationCache::getInstance()->getAnimation("BigEnemyBlow");
		break;
	default:
		break;
	}

	//this->runAction(Animate::create(animation));
	auto callFunc = CallFuncN::create([](Node *node){
		node->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create( Animate::create(animation), callFunc, NULL));

}

void Enemy::hit(){
	//获取中弹动画并执行
	Animation *animation;

	switch (m_type)
	{
	case ENEMY_MIDDLE:
		animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyHit");
		break;
	case ENEMY_BIG:
		animation = AnimationCache::getInstance()->getAnimation("BigEnemyHit");
		break;
	default:
		break;
	}

	this->runAction(Animate::create(animation));
}