#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class GameRoom : Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameRoom);

private:
	void createPlayerInfo(Sprite* parent, Vec2 pos);
	void createPreparePanel(Node* parent);
	void createPlayGame(Node* parent);
	void shuffleCards();
	bool selectPoker(Sprite* poker, const Touch* touch, Event* event);
	Sprite* testSprite;
	float middlePokerY;
};