#pragma once
#include "cocos2d.h"

using namespace cocos2d;
enum MoneyType 
{ 
	Gold=0,
	Diamond
};
class IndexScene :Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IndexScene);

private:
	void createFK(Vec2 position, Sprite* parentSprite, MoneyType moneyType);
	void createGameList(Sprite* parentSprite);
};