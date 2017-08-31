#include "WelcomeScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool WelcomeScene::init(){

	//用当前时间作为随机数的种子
	srand((unsigned int)time(0));	

	//==============初始缓存==============
	initCache();

	//==============加载背景==============
	auto spriteBg = Sprite::createWithSpriteFrameName("background.png");//创建背景精灵1
	spriteBg->setPosition(0,0);//给背景精灵1设定放置的位置
	spriteBg->setAnchorPoint(Point(0,0));//设置锚
	this->addChild(spriteBg);//将背景精灵1加入该层里面

	auto spriteCopyRight = Sprite::createWithSpriteFrameName("shoot_copyright.png");//创建背景精灵1
	spriteCopyRight->setPosition(VISIBLE_SIZE.width/2,
		VISIBLE_SIZE.height/2+spriteCopyRight->getContentSize().height/2);//给背景精灵1设定放置的位置
	spriteCopyRight->setAnchorPoint(Point(0.5,0.5));//设置锚
	this->addChild(spriteCopyRight);//将背景精灵1加入该层里面

	//==============场景跳转==============

	auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");//创建加载小飞机
	loading->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/4);//给加载小飞机设定放置的位置
	loading->setAnchorPoint(Point(0.5,0.5));//设置锚
	this->addChild(loading);//将加载小飞机加入该层里面

	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("LoadingPlane"));
	auto callFunc = CallFunc::create([](){
		//跳转场景的代码
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

//初始化缓存
void WelcomeScene::initCache(){

	//0.0将shoot_background.plist,shoot.plist文件导入缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	//1.0将动画添加到缓存
	Animation *animation;

	//1.1添加飞机飞行动画

	//1.1.1大飞机的飞行动画
	animation = Animation::create();
	//添加图片参与动画
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	//切换的频率
	animation->setDelayPerUnit(0.2f);
	//切换的周期数
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, "HeroPlaneFly");

	//1.1.2大飞机的飞行动画
	animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));			
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(animation, "BigEnemyFly");

	//1.2添加飞机爆炸动画
	//1.2.1小型飞机爆炸
	animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		//拼接字符串，参见C中的printf函数
		auto png = StringUtils::format("enemy1_down%d.png", i);
		//根据精灵帧名称从精灵帧缓存中获取精灵帧
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation->addSpriteFrame(spriteFrame);
	}		
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(animation, "SmallEnemyBlow");

	//1.2.2中型飞机爆炸
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

	//1.2.3大型飞机爆炸
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

	//1.2.4英雄飞机爆炸
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

	//1.3添加敌机击中动画
	//1.3.1中型飞机被击中
	animation = Animation::create();		
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));		
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "MiddleEnemyHit");

	//1.3.2大型飞机被击中
	animation = Animation::create();			
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));	
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "BigEnemyHit");

	//1.4飞机加载启动
	animation = Animation::create();
	for (int i = 1; i < 4; i++)
	{
		auto png = StringUtils::format("game_loading%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(2);
	AnimationCache::getInstance()->addAnimation(animation, "LoadingPlane");


	//==============加载声音文件==============
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