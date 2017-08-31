#include "GameOver.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


void GameOverScene::setScore(int score){

	this->m_Score=score;

}

bool GameOverScene::init(int score){
	if ( !Layer::init() )
	{
		return false;
	}
	//������������
	auto listener = EventListenerKeyboard::create();  
  
	listener->onKeyReleased = CC_CALLBACK_2(GameOverScene::onKeyReleased, this);  
  
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);  

	this->m_Score=score;

	//==============��ʼ��Ч==============
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game_over.mp3");
	//==============��ʼ����==============
	auto spriteBg = Sprite::createWithSpriteFrameName("gameover.png");
	spriteBg->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height);//�����������趨���õ�λ��
	spriteBg->setAnchorPoint(Point(0.5,1));
	this->addChild(spriteBg);//�������������ò�����


	//==============��ʾ����==============
	auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", m_Score));
	lblScore->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height-450);
	this->addChild(lblScore);
	lblScore->setColor(Color3B(120, 120, 120));

	//�������ļ��ж�ȡ��ʷ��ߵ÷֣����û���򷵻�Ĭ��ֵ0
	auto highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE", 0);
	auto lblHighScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", highScore));
	lblHighScore->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	lblHighScore->setPosition(150, VISIBLE_SIZE.height-40);
	this->addChild(lblHighScore);
	lblHighScore->setColor(Color3B(120, 120, 120));

	//�����ȡ������߷�û�е�ǰ�ĵ÷�ֵ��
	//��ô��������ߵ÷���д�뵽�����ļ���
	if (highScore<m_Score)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("achievement.mp3");

		highScore = m_Score;

		UserDefault::getInstance()->setIntegerForKey("HIGHSCORE", highScore);

		lblHighScore->setString(StringUtils::format("%d", highScore));
	}

	//==============���¿�ʼ��ť==============
	auto spriteBack = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto menuItemBack = MenuItemSprite::create(spriteBack, spriteBack, [](Ref *){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");

		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	float x = VISIBLE_SIZE.width - spriteBack->getContentSize().width/2-20;
	menuItemBack->setPosition(VISIBLE_SIZE.width/2, spriteBack->getContentSize().height/2+20);

	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

GameOverScene* GameOverScene::create(int score) {

	auto gameOver = new GameOverScene();
	if (gameOver && gameOver->init(score))
	{
		gameOver->autorelease();
		return gameOver;
	}
	delete gameOver;
	gameOver = NULL;
	return NULL;
}

Scene* GameOverScene::createScene(int score){

	auto scene =Scene::create();

	auto layer= GameOverScene::create(score);

	scene->addChild(layer);

	return scene;
}


void  GameOverScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){  
  
    switch (keycode){  
  
    case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:  
  
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH: 

	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_TAB: 
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  
  
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");  
  
        return;  
  
#endif  
  
        Director::getInstance()->end();  
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
  
        exit(0);  
  
#endif  
  
        break;  
  
    default:  
  
        break;  
  
    }  
}  