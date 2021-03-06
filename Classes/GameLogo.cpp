#include "GameLogo.h"

Scene* GameLogo::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLogo::create();

	scene->addChild(layer);

	return scene;

}

bool GameLogo::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	this->addLogo();
	return true;
}

void GameLogo::addLogo()
{
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size  visibleSize = Director::getInstance()->getVisibleSize();
	auto logo = Sprite::create("myLogo.png");
	logo->setPosition(originPoint.x + visibleSize.width/2, originPoint.y+visibleSize.height/2);
	logo->setName("logo");
	logo->setOpacity(10);
	this->addChild(logo);
	logo->runAction(Sequence::create(FadeTo::create(2.0f, 255), CallFunc::create(CC_CALLBACK_0(GameLogo::loadRes, this)), nullptr));
}

void  GameLogo::loadRes()
{
	Director::getInstance()->getTextureCache()->addImageAsync("spriteSheet.png", CC_CALLBACK_1(GameLogo::loadImageOver, this));
}


void GameLogo::loadImageOver(Texture2D* texture)
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteSheet.plist", texture);

	this->loadMusic();

	this->startGame();
}

void GameLogo::loadMusic()
{
	DiscJockey::getInstance()->preLoad();
	
}

void GameLogo::startGame()
{

	CallFunc* nextScene = CallFunc::create(std::bind(&GameLogo::nextScene, this));
	this->getChildByName("logo")->runAction(Sequence::create(FadeOut::create(2.0f), nextScene, nullptr));
}


void GameLogo::nextScene()
{
	CommandCenter::getInstance()->goState(GAME_STATE::MENU);
}

void GameLogo::onExit()
{

	Layer::onExit();
	this->stopAllActions();
}

