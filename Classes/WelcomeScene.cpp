#include "WelcomeScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool WelcomeScene::init(){

	//�õ�ǰʱ����Ϊ�����������
	srand((unsigned int)time(0));	

	//==============��ʼ����==============
	initCache();

	//==============���ر���==============
	auto spriteBg = Sprite::createWithSpriteFrameName("background.png");//������������1
	spriteBg->setPosition(0,0);//����������1�趨���õ�λ��
	spriteBg->setAnchorPoint(Point(0,0));//����ê
	this->addChild(spriteBg);//����������1����ò�����

	auto spriteCopyRight = Sprite::createWithSpriteFrameName("shoot_copyright.png");//������������1
	spriteCopyRight->setPosition(VISIBLE_SIZE.width/2,
		VISIBLE_SIZE.height/2+spriteCopyRight->getContentSize().height/2);//����������1�趨���õ�λ��
	spriteCopyRight->setAnchorPoint(Point(0.5,0.5));//����ê
	this->addChild(spriteCopyRight);//����������1����ò�����

	//==============������ת==============

	auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");//��������С�ɻ�
	loading->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/4);//������С�ɻ��趨���õ�λ��
	loading->setAnchorPoint(Point(0.5,0.5));//����ê
	this->addChild(loading);//������С�ɻ�����ò�����

	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("LoadingPlane"));
	auto callFunc = CallFunc::create([](){
		//��ת�����Ĵ���
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	loading->runAction(Sequence::create(animate, callFunc, NULL));

	return true;
}

Scene* WelcomeScene::createScene(){

	auto scene =Scene::create();
	auto layer= WelcomeScene::create();

	scene->addChild(layer);

	return scene;
}

//��ʼ������
void WelcomeScene::initCache(){

	//0.0��shoot_background.plist,shoot.plist�ļ����뻺��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	//1.0��������ӵ�����
	Animation *animation;

	//1.1��ӷɻ����ж���

	//1.1.1��ɻ��ķ��ж���
	animation = Animation::create();
	//���ͼƬ���붯��
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	//�л���Ƶ��
	animation->setDelayPerUnit(0.2f);
	//�л���������
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, "HeroPlaneFly");

	//1.1.2��ɻ��ķ��ж���
	animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));			
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, "BigEnemyFly");

	//1.2��ӷɻ���ը����
	//1.2.1С�ͷɻ���ը
	animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		//ƴ���ַ������μ�C�е�printf����
		auto png = StringUtils::format("enemy1_down%d.png", i);
		//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation->addSpriteFrame(spriteFrame);
	}		
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation, "SmallEnemyBlow");

	//1.2.2���ͷɻ���ը
	animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		auto png = StringUtils::format("enemy2_down%d.png", i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "MiddleEnemyBlow");

	//1.2.3���ͷɻ���ը
	animation = Animation::create();
	for (int i = 1; i <= 6; i++)
	{
		auto png = StringUtils::format("enemy3_down%d.png", i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation->addSpriteFrame(spriteFrame);
	}			
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "BigEnemyBlow");

	//1.2.4Ӣ�۷ɻ���ը
	animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		auto png = StringUtils::format("hero_blowup_n%d.png", i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "HeroPlaneBlow");

	//1.3��ӵл����ж���
	//1.3.1���ͷɻ�������
	animation = Animation::create();		
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));		
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "MiddleEnemyHit");

	//1.3.2���ͷɻ�������
	animation = Animation::create();			
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));	
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "BigEnemyHit");

	//1.4�ɻ���������
	animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		auto png = StringUtils::format("game_loading%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(2);
	AnimationCache::getInstance()->addAnimation(animation, "LoadingPlane");


	//==============���������ļ�==============
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");		
	SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("out_porp.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
}