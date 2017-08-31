#include "GameScene.h"
#include "GameOver.h"
#include "CommData.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* GameScene::createScene(){

	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init(){

	if ( !Layer::init() )
	{
		return false;
	}
	this->m_score=0;
	this->m_speedLevel=0;
	this->is_GameOver=true;
	this->is_Movable=true;

	//==============初始背景==============
	initBackground();

	//==============初始游戏音效==============
	initAudio();

	//==============初始我方飞机==============
	initHeroPlane();

	//==============添加子弹==============
	BulletLayer* mBulletLayer = BulletLayer::create(this->mPlane); 
	this->mBulletLayer=mBulletLayer;
	this->addChild(mBulletLayer,1);  

	//==============添加敌机==============
	EnemyLayer* mEnemyLayer = EnemyLayer::create(this->mPlane);
	this->mEnemyLayer=mEnemyLayer;
	this->addChild(mEnemyLayer,1);  

	//==============添加道具==============
	PropLayer* mPropLayer=PropLayer::create(this->mPlane);
	this->mPropLayer=mPropLayer;
	this->addChild(mPropLayer,1);  

	//==============初始Menu和Label==============
	initMenu();

	this->scheduleUpdate();

	return true;
}

//初始背景
void GameScene::initBackground(){
	auto spBg1 = Sprite::createWithSpriteFrameName("background.png");//创建背景精灵1
	spBg1->setPosition(0,0);//给背景精灵1设定放置的位置
	spBg1->setAnchorPoint(Point(0,0));//设置锚
	spBg1->getTexture()->setAliasTexParameters();//消除抗锯齿
	this->addChild(spBg1,1,11);//将背景精灵1加入该层里面


	auto spBg2 = Sprite::createWithSpriteFrameName("background.png");//创建背景精灵2
	spBg2->setPosition(0,0);//给背景精灵2设定放置的位置
	spBg2->setAnchorPoint(Point(0,0));//设置锚
	spBg2->getTexture()->setAliasTexParameters();//消除抗锯齿
	this->addChild(spBg2,1,12);//将背景精灵2加入该层里面

}

//初始音效
void GameScene::initAudio(){

	//播放背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3", true);
}

//初始英雄飞机
void GameScene::initHeroPlane(){

	auto spPlane = Sprite::createWithSpriteFrameName("hero1.png");//创建飞机精灵
	auto planeSize = spPlane->getContentSize();
	//spPlane->setPosition(size.width/2,spPlane->getContentSize().height/2);
	spPlane->setPosition(VISIBLE_SIZE.width/2,planeSize.height/2);
	spPlane->setAnchorPoint(Point(0.5,0.5));//设置锚
	this->addChild(spPlane,1,21);//将飞机精灵加入该层里面

	this->mPlane=spPlane;

	//执行飞行动作
	spPlane->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("HeroPlaneFly")));


	//添加触屏事件
	this->setTouchEnabled(true);  
	//创建单点触摸监听器
	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *){
		auto location=touch->getLocation();
		//计算触摸点与飞机中心相对向量
		this->vec=spPlane->getPosition()-location;
		//是否选中飞机
		return spPlane->getBoundingBox().containsPoint(location) && is_Movable;
	};
	listener->onTouchMoved = [=](Touch *touch, Event *){
		//从新计算飞机位置
		auto location=touch->getLocation()+this->vec;

		auto planeSize=spPlane->getContentSize();
		//边缘检测
		if (location.x<planeSize.width/2)  
		{  
			location.x=planeSize.width/2;   
		}  
		if (location.x>VISIBLE_SIZE.width-planeSize.width/2)  
		{  
			location.x=VISIBLE_SIZE.width-planeSize.width/2;  
		}  
		if (location.y<planeSize.height/2)  
		{  
			location.y=planeSize.height/2;  
		}  
		if (location.y>VISIBLE_SIZE.height-planeSize.height/2)  
		{  
			location.y=VISIBLE_SIZE.height-planeSize.height/2;  
		}  

		spPlane->setPosition(location);

	};
	listener->onTouchEnded = [=](Touch *touch, Event *){
		//相对位置向量清零
		this->vec=Point::ZERO;
	};
	//绑定监听事件
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spPlane);
}

//初始Menu和Label
void GameScene::initMenu(){
	//==============显示分数==============
	//固定内容选用了系统字体
	auto lblScore = Label::createWithSystemFont("Score:", "Arial", 36);
	lblScore->setPosition(40, VISIBLE_SIZE.height-40);
	lblScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblScore->setColor(Color3B::BLACK);
	this->addChild(lblScore, 5);	//设置字体颜色
	//分值会变化，选用了它提供的fnt字体文件
	auto lblScoreNumber = Label::createWithBMFont("font.fnt", "0");
	lblScoreNumber->setPosition(lblScore->getContentSize().width + 45, VISIBLE_SIZE.height-40);
	lblScoreNumber->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblScoreNumber->setColor(Color3B::BLACK);
	this->addChild(lblScoreNumber, 5, 31);
	//=============左下角显示炸弹数=============
	auto spriteBomb = Sprite::createWithSpriteFrameName("bomb.png");

	//==============添加炸弹按键==============
	auto menuItemBomb = MenuItemSprite::create(spriteBomb, spriteBomb, [=](Ref *){

		SimpleAudioEngine::getInstance()->playEffect("use_bomb.mp3");

		//当触摸炸弹图标时，触发全屏飞机的爆炸并记分
		this->mPropLayer->useBomb();
		//别忘了更新左下角显示
		this->updateBombLabel(0);

		//销毁敌机集合中所有的敌机，并清空集合
		for (auto enemy : this->mEnemyLayer->getEnemy())
		{
			enemy->down();
			//累加分值并更新显示
			this->m_score += enemy->getGoal();
		}
		this->mEnemyLayer->removeAllEnemy();
		//更新分值显示
		lblScoreNumber->setString(StringUtils::format("%d", this->m_score));
	});

	menuItemBomb->setPosition(40, 40);
	menuItemBomb->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//菜单项不可直接添加到层中渲染，需要菜单容器进行封装
	auto menu = Menu::create();
	menu->addChild(menuItemBomb, 5 ,51);
	//默认菜单的坐标中中央，这里不方便定位，所以置零，让菜单项自己定位
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5, 41);	//注意Zorder

	//炸弹数会变化，选用类它提供的fnt字体
	auto lblBombCount = Label::createWithBMFont("font.fnt", "X0");
	lblBombCount->setPosition(menuItemBomb->getContentSize().width+45, 40);
	lblBombCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblBombCount->setColor(Color3B::BLACK);
	this->addChild(lblBombCount, 5, 32);

	this->updateBombLabel(0);
	//===========暂停按钮===========
	auto pauseNor = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto pausePressed = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	//CC_CALLBACK_1表示封装一个只有一个参数的函数，参数为（1.函数全名（含类名限定）， 2.调用函数的对象）
	auto menuItemPause = MenuItemSprite::create(pauseNor, pausePressed, CC_CALLBACK_1(GameScene::pause, this));
	menuItemPause->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
	menuItemPause->setPosition(Point(VISIBLE_SIZE)-Point(20, 20));
	menuItemPause->setTag(52);

	auto resumeNor = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto resumePressed = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto menuItemResume = MenuItemSprite::create(resumeNor, resumePressed, CC_CALLBACK_1(GameScene::resume, this));
	menuItemResume->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
	menuItemResume->setPosition(Point(VISIBLE_SIZE)-Point(20, 20));
	menuItemResume->setVisible(false);
	menuItemResume->setTag(53);

	auto menu1 = Menu::create(menuItemPause, menuItemResume, NULL);
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1, 5, 42);
}

void GameScene::pause(Ref *) {
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");

	auto menu = this->getChildByTag(42);
	auto itemPause = menu->getChildByTag(52);
	auto itemResume = menu->getChildByTag(53);

	itemPause->setVisible(false);
	itemResume->setVisible(true);
	this->is_Movable = false;	//禁用触摸的变量

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->pause();
	//Director::sharedDirector()->pause();
}

void GameScene::resume(Ref *) {
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");

	auto menu = this->getChildByTag(42);
	auto itemPause = menu->getChildByTag(52);
	auto itemResume = menu->getChildByTag(53);

	itemPause->setVisible(true);
	itemResume->setVisible(false);
	this->is_Movable = true;

	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->resume();
	//Director::sharedDirector()->resume();
}

GameScene* GameScene::create(){

	GameScene* pRet = new GameScene();
	if(pRet&& pRet->init()){
		pRet->autorelease();
		return pRet;
	}
	else{
		delete pRet;
		pRet=NULL;
		return NULL;
	}

}

void GameScene::update(float)
{
	auto spBg1 = this->getChildByTag(11);
	auto spBg2 = this->getChildByTag(12);
	auto spriteHero = this->getChildByTag(21);

	//设置背景滚动

	spBg1->setPositionY(spBg1->getPositionY()- 3);
	//让spBg2跟着spBg1移动
	spBg2->setPositionY(spBg1->getPositionY()+spBg1->getContentSize().height);
	if(spBg2->getPositionY()<=0)
	{
		spBg1->setPositionY(0);
	}

	//==============速度检测=============
	if(m_score/500 > m_speedLevel){

		m_speedLevel=m_score/500;

		this->mEnemyLayer->speedUp();
	}

	//==============碰撞检测=============

	//子弹与敌机的碰撞
	checkEnemyCrash();

	//道具与英雄的碰撞
	checkPropCrash();
}

//更新道具标签数据
void GameScene::updateBombLabel(float) {
	//先找到菜单，再通过菜单找到精灵菜单项
	auto menu = this->getChildByTag(41);
	auto item = menu->getChildByTag(51);
	//获得标签，思考为什么要强制类型转换
	auto lbl = (Label *)this->getChildByTag(32);

	auto bombCount=this->mPropLayer->getBombNumber();

	if (bombCount <= 0)
	{
		item->setVisible(false);
		lbl->setVisible(false);
	} else if (bombCount == 1)
	{
		item->setVisible(true);
		lbl->setVisible(false);
	} else {
		item->setVisible(true);
		lbl->setVisible(true);
		//别忘了更新炸弹数
		lbl->setString(StringUtils::format("X%d",bombCount));
	}
}

//碰撞检测之子弹与敌机
void GameScene::checkEnemyCrash(){

	auto hero = this->mPlane;

	Vector<Sprite*> vRemoveBullets;
	Vector<Enemy*> vRemoveEnemy;

	for(auto enemy : this->mEnemyLayer->getEnemy())
	{
		for(auto bullet : this->mBulletLayer->getBullet())
		{
			if(enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
			{

				vRemoveBullets.pushBack(bullet);//把待删除子弹放入Vector  
				this->mBulletLayer->removeChild(bullet);
				//如果HP>1
				if (enemy->getHP()>1)//因为Enemy设置了不同生命值   
				{  
					enemy->loseHP(); 
					enemy->hit();
				}  
				//如果HP==1,移除enemy  
				else if(enemy->getHP()==1)//只剩一条命的时候，再碰撞就挂掉了  
				{  
					enemy->loseHP();
					enemy->down();
					//累加分钟并更新label的显示
					this->m_score += enemy->getGoal();
					auto lbl = (Label *) this->getChildByTag(31);
					lbl->setString(StringUtils::format("%d", this->m_score));


					vRemoveEnemy.pushBack(enemy);//把待删除敌机放入Vector 

				}  
				//此时处在敌机爆炸动画阶段,敌机未消失，子弹还有打到的机会，所以不进行检测  
				else ;  
			}
		}


		if ( this->is_GameOver && enemy->getBoundingBox().intersectsRect(hero->getBoundingBox()))
		{
			this->is_GameOver=false;
			this->is_Movable=false;

			enemy->down();

			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("HeroPlaneBlow"));
			auto callFunc = CallFunc::create([=](){
				auto scene = GameOverScene::createScene(this->m_score);
				Director::getInstance()->replaceScene(scene);
			});
			hero->stopAllActions();
			hero->runAction(Sequence::create(animate, callFunc, NULL));
		}


	}
	
	//清除已经碰撞的子弹和飞机
	for(auto bullet:vRemoveBullets)
	{
		this->mBulletLayer->removeBullet(bullet);
	}
	vRemoveBullets.clear();

	for(auto enemy : vRemoveEnemy)
	{
		this->mEnemyLayer->blowupEnemy(enemy);
	}
	vRemoveEnemy.clear();
}

//碰撞检测之飞机与道具
void GameScene::checkPropCrash(){
	Vector<Prop*> removableUfos;
	for (auto ufo : this->mPropLayer->getProps())
	{
		if (ufo->getBoundingBox().intersectsRect(this->mPlane->getBoundingBox()))
		{

			removableUfos.pushBack(ufo);
			switch (ufo->getType())
			{
				//如果是子弹道具就切换子弹
			case PROP_DOUBLE:
				SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
				this->removeChild(ufo);
				this->mBulletLayer->changeType();
				break;
				//如果是炸弹道具就更新左下角的显示
			case PROP_BOMB:
				{
					SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
					this->mPropLayer->addBomb();
					this->updateBombLabel(0);
				}
				break;
			default:
				break;
			}
		}
	}
	for(auto ufo : removableUfos) {
		this->mPropLayer->removeProp(ufo);
	}
	removableUfos.clear(); 

}