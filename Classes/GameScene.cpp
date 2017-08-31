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

	//==============��ʼ����==============
	initBackground();

	//==============��ʼ��Ϸ��Ч==============
	initAudio();

	//==============��ʼ�ҷ��ɻ�==============
	initHeroPlane();

	//==============����ӵ�==============
	BulletLayer* mBulletLayer = BulletLayer::create(this->mPlane); 
	this->mBulletLayer=mBulletLayer;
	this->addChild(mBulletLayer,1);  

	//==============��ӵл�==============
	EnemyLayer* mEnemyLayer = EnemyLayer::create(this->mPlane);
	this->mEnemyLayer=mEnemyLayer;
	this->addChild(mEnemyLayer,1);  

	//==============��ӵ���==============
	PropLayer* mPropLayer=PropLayer::create(this->mPlane);
	this->mPropLayer=mPropLayer;
	this->addChild(mPropLayer,1);  

	//==============��ʼMenu��Label==============
	initMenu();

	this->scheduleUpdate();

	return true;
}

//��ʼ����
void GameScene::initBackground(){
	auto spBg1 = Sprite::createWithSpriteFrameName("background.png");//������������1
	spBg1->setPosition(0,0);//����������1�趨���õ�λ��
	spBg1->setAnchorPoint(Point(0,0));//����ê
	spBg1->getTexture()->setAliasTexParameters();//���������
	this->addChild(spBg1,1,11);//����������1����ò�����


	auto spBg2 = Sprite::createWithSpriteFrameName("background.png");//������������2
	spBg2->setPosition(0,0);//����������2�趨���õ�λ��
	spBg2->setAnchorPoint(Point(0,0));//����ê
	spBg2->getTexture()->setAliasTexParameters();//���������
	this->addChild(spBg2,1,12);//����������2����ò�����

}

//��ʼ��Ч
void GameScene::initAudio(){

	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3", true);
}

//��ʼӢ�۷ɻ�
void GameScene::initHeroPlane(){

	auto spPlane = Sprite::createWithSpriteFrameName("hero1.png");//�����ɻ�����
	auto planeSize = spPlane->getContentSize();
	//spPlane->setPosition(size.width/2,spPlane->getContentSize().height/2);
	spPlane->setPosition(VISIBLE_SIZE.width/2,planeSize.height/2);
	spPlane->setAnchorPoint(Point(0.5,0.5));//����ê
	this->addChild(spPlane,1,21);//���ɻ��������ò�����

	this->mPlane=spPlane;

	//ִ�з��ж���
	spPlane->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("HeroPlaneFly")));


	//��Ӵ����¼�
	this->setTouchEnabled(true);  
	//�������㴥��������
	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *){
		auto location=touch->getLocation();
		//���㴥������ɻ������������
		this->vec=spPlane->getPosition()-location;
		//�Ƿ�ѡ�зɻ�
		return spPlane->getBoundingBox().containsPoint(location) && is_Movable;
	};
	listener->onTouchMoved = [=](Touch *touch, Event *){
		//���¼���ɻ�λ��
		auto location=touch->getLocation()+this->vec;

		auto planeSize=spPlane->getContentSize();
		//��Ե���
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
		//���λ����������
		this->vec=Point::ZERO;
	};
	//�󶨼����¼�
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spPlane);
}

//��ʼMenu��Label
void GameScene::initMenu(){
	//==============��ʾ����==============
	//�̶�����ѡ����ϵͳ����
	auto lblScore = Label::createWithSystemFont("Score:", "Arial", 36);
	lblScore->setPosition(40, VISIBLE_SIZE.height-40);
	lblScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblScore->setColor(Color3B::BLACK);
	this->addChild(lblScore, 5);	//����������ɫ
	//��ֵ��仯��ѡ�������ṩ��fnt�����ļ�
	auto lblScoreNumber = Label::createWithBMFont("font.fnt", "0");
	lblScoreNumber->setPosition(lblScore->getContentSize().width + 45, VISIBLE_SIZE.height-40);
	lblScoreNumber->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblScoreNumber->setColor(Color3B::BLACK);
	this->addChild(lblScoreNumber, 5, 31);
	//=============���½���ʾը����=============
	auto spriteBomb = Sprite::createWithSpriteFrameName("bomb.png");

	//==============���ը������==============
	auto menuItemBomb = MenuItemSprite::create(spriteBomb, spriteBomb, [=](Ref *){

		SimpleAudioEngine::getInstance()->playEffect("use_bomb.mp3");

		//������ը��ͼ��ʱ������ȫ���ɻ��ı�ը���Ƿ�
		this->mPropLayer->useBomb();
		//�����˸������½���ʾ
		this->updateBombLabel(0);

		//���ٵл����������еĵл�������ռ���
		for (auto enemy : this->mEnemyLayer->getEnemy())
		{
			enemy->down();
			//�ۼӷ�ֵ��������ʾ
			this->m_score += enemy->getGoal();
		}
		this->mEnemyLayer->removeAllEnemy();
		//���·�ֵ��ʾ
		lblScoreNumber->setString(StringUtils::format("%d", this->m_score));
	});

	menuItemBomb->setPosition(40, 40);
	menuItemBomb->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//�˵����ֱ����ӵ�������Ⱦ����Ҫ�˵��������з�װ
	auto menu = Menu::create();
	menu->addChild(menuItemBomb, 5 ,51);
	//Ĭ�ϲ˵������������룬���ﲻ���㶨λ���������㣬�ò˵����Լ���λ
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5, 41);	//ע��Zorder

	//ը������仯��ѡ�������ṩ��fnt����
	auto lblBombCount = Label::createWithBMFont("font.fnt", "X0");
	lblBombCount->setPosition(menuItemBomb->getContentSize().width+45, 40);
	lblBombCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblBombCount->setColor(Color3B::BLACK);
	this->addChild(lblBombCount, 5, 32);

	this->updateBombLabel(0);
	//===========��ͣ��ť===========
	auto pauseNor = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto pausePressed = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	//CC_CALLBACK_1��ʾ��װһ��ֻ��һ�������ĺ���������Ϊ��1.����ȫ�����������޶����� 2.���ú����Ķ���
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
	this->is_Movable = false;	//���ô����ı���

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

	//���ñ�������

	spBg1->setPositionY(spBg1->getPositionY()- 3);
	//��spBg2����spBg1�ƶ�
	spBg2->setPositionY(spBg1->getPositionY()+spBg1->getContentSize().height);
	if(spBg2->getPositionY()<=0)
	{
		spBg1->setPositionY(0);
	}

	//==============�ٶȼ��=============
	if(m_score/500 > m_speedLevel){

		m_speedLevel=m_score/500;

		this->mEnemyLayer->speedUp();
	}

	//==============��ײ���=============

	//�ӵ���л�����ײ
	checkEnemyCrash();

	//������Ӣ�۵���ײ
	checkPropCrash();
}

//���µ��߱�ǩ����
void GameScene::updateBombLabel(float) {
	//���ҵ��˵�����ͨ���˵��ҵ�����˵���
	auto menu = this->getChildByTag(41);
	auto item = menu->getChildByTag(51);
	//��ñ�ǩ��˼��ΪʲôҪǿ������ת��
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
		//�����˸���ը����
		lbl->setString(StringUtils::format("X%d",bombCount));
	}
}

//��ײ���֮�ӵ���л�
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

				vRemoveBullets.pushBack(bullet);//�Ѵ�ɾ���ӵ�����Vector  
				this->mBulletLayer->removeChild(bullet);
				//���HP>1
				if (enemy->getHP()>1)//��ΪEnemy�����˲�ͬ����ֵ   
				{  
					enemy->loseHP(); 
					enemy->hit();
				}  
				//���HP==1,�Ƴ�enemy  
				else if(enemy->getHP()==1)//ֻʣһ������ʱ������ײ�͹ҵ���  
				{  
					enemy->loseHP();
					enemy->down();
					//�ۼӷ��Ӳ�����label����ʾ
					this->m_score += enemy->getGoal();
					auto lbl = (Label *) this->getChildByTag(31);
					lbl->setString(StringUtils::format("%d", this->m_score));


					vRemoveEnemy.pushBack(enemy);//�Ѵ�ɾ���л�����Vector 

				}  
				//��ʱ���ڵл���ը�����׶�,�л�δ��ʧ���ӵ����д򵽵Ļ��ᣬ���Բ����м��  
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
	
	//����Ѿ���ײ���ӵ��ͷɻ�
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

//��ײ���֮�ɻ������
void GameScene::checkPropCrash(){
	Vector<Prop*> removableUfos;
	for (auto ufo : this->mPropLayer->getProps())
	{
		if (ufo->getBoundingBox().intersectsRect(this->mPlane->getBoundingBox()))
		{

			removableUfos.pushBack(ufo);
			switch (ufo->getType())
			{
				//������ӵ����߾��л��ӵ�
			case PROP_DOUBLE:
				SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
				this->removeChild(ufo);
				this->mBulletLayer->changeType();
				break;
				//�����ը�����߾͸������½ǵ���ʾ
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