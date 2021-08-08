#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;

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
	Sprite* createRoom(Sprite* parentSprite);
	CheckBox* createRadio(Node* parentSprite, Vec2 pos, std::string name);
	void groupRadio(Vector<CheckBox*> checkBoxs);

private:
	Sprite* createRoomBg;
};