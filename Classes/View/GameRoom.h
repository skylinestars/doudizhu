#pragma once
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "../Model/Poker.h"
#include "../Controller/RoomController.h"

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
	bool selectPoker(Sprite* poker, const Touch* touch, Event* event);
	void pokerAddTouch(Sprite* poker, Node* node);
	void shuffleCards(std::vector<Poker>& myPokers);//发牌动画
	void othersShuffleCards();//其他玩家发牌动画
	void othersShuffleCardsHandle(float dt);
	void sortCards();
	void callDiZhuBtn(Node* parentNode);
	void robDiZhuBtn(Node* parentNode);
	void playPokerBtn(Node* parentNode);
private:
	Sprite* testSprite;
	float middlePokerY;
	float pokerWidth;
	float pokerSpace;
	RoomController roomController;

	std::vector<Sprite*> myPokersSprite;
	Sprite* pokerLeft;
	Sprite* pokerRight;
	Label* pokerNumLeft;
	Label* pokerNumRight;
	int othersPokerNum;
};