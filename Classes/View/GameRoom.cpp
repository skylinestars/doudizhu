#include "GameRoom.h"
#include "../Controller/ConfigController.h"
#include "../Tool/DrawTool.h"
#include "AudioEngine.h"


Scene* GameRoom::createScene()
{
	return GameRoom::create();
}

bool GameRoom::init()
{
	if (!Scene::init())
	{
		return false;
	}
	middlePokerY = 171;
	pokerWidth = 90;
	pokerSpace = pokerWidth * 5 / 12;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图
	auto bg = Sprite::create("images/Room/bgRoomPlay.png");
	this->addChild(bg);
	bg->setPosition(origin + visibleSize / 2);
	//bg->setScale(ConfigController::getInstance()->getScale());
	auto desk = Sprite::create("images/Room/bgRoom.png");
	bg->addChild(desk);
	desk->setPosition(bg->getContentSize() / 2);

	//房间号
	auto roomId = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1014)
		+ "152698", "Arial", 28);
	desk->addChild(roomId);
	roomId->setColor(Color3B(56, 117, 8));
	roomId->enableBold();
	roomId->setPosition(Vec2(desk->getContentSize().width / 2, desk->getContentSize().height / 2 + 200));

	//底分
	auto diFen = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1010)
		+"  "+ ConfigController::getInstance()->getWordById(1011)
		+"10"
		, "Arial", 28);
	desk->addChild(diFen);
	diFen->setColor(Color3B(56,117, 8));
	diFen->enableBold();
	diFen->setPosition(Vec2(desk->getContentSize().width/2, desk->getContentSize().height/2+150));

	//游戏准备面板
	auto gamePreparePanel = Node::create();
	gamePreparePanel->setVisible(false);
	bg->addChild(gamePreparePanel);
	createPreparePanel(gamePreparePanel);

	//玩家信息--中
	createPlayerInfo(bg, Vec2(70, 126.3f));
	//玩家信息--左
	createPlayerInfo(bg, Vec2(70, bg->getContentSize().height/2+200));
	//玩家信息--右
	createPlayerInfo(bg, Vec2(bg->getContentSize().width - 70, bg->getContentSize().height / 2+200));

	//模拟数据
	std::vector<Poker> myPokers;
	roomController.createPoker(nullptr, myPokers);
	roomController.sortPoker(myPokers);
	//游戏发牌
	shuffleCards(myPokers);

	//叫地主
	auto jiaoDiZhuNode = Node::create();
	this->addChild(jiaoDiZhuNode);

	//抢地主

	//加倍

	//出牌
	
	return true;
}

void GameRoom::createPlayerInfo(Sprite* parent, Vec2 pos)
{
	auto playerMiddleBg = Sprite::create("images/Room/headallbk.png");
	parent->addChild(playerMiddleBg);
	playerMiddleBg->setPosition(pos);

	auto playerMiddleHeadBg = Sprite::create("images/Room/bgSeat.png");
	playerMiddleBg->addChild(playerMiddleHeadBg);
	playerMiddleHeadBg->setScale(1.3f);
	playerMiddleHeadBg->setPosition(Vec2(playerMiddleBg->getContentSize().width / 2,
		playerMiddleBg->getContentSize().height / 2 + 15));

	auto playerMiddleHead = Sprite::create("images/index/headWho.png");
	playerMiddleHeadBg->addChild(playerMiddleHead);
	playerMiddleHead->setScale(0.65f);
	playerMiddleHead->setPosition(Vec2(playerMiddleHeadBg->getContentSize().width / 2,
		playerMiddleHeadBg->getContentSize().height / 2 + 12));

	auto playerMiddleName = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1009), "Arial", 12);
	playerMiddleHeadBg->addChild(playerMiddleName);
	playerMiddleName->setPosition(Vec2(playerMiddleHeadBg->getContentSize().width / 2,
		12));

	auto coinIcon = Sprite::create("images/Room/coin.png");
	playerMiddleBg->addChild(coinIcon);
	coinIcon->setScale(0.5f);
	coinIcon->setPosition(Vec2(30, 20));

	auto coin = Label::createWithSystemFont(
		"9999" + ConfigController::getInstance()->getWordById(1013), "Arial", 20);
	playerMiddleBg->addChild(coin);
	coin->setColor(Color3B::YELLOW);
	coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	coin->setPosition(Vec2(50, 20));
}

void GameRoom::createPreparePanel(Node* parent)
{
	float padding = 20;
	auto jiesanBtn = Button::create("images/Room/longBtnYellow.png");
	parent->addChild(jiesanBtn);
	jiesanBtn->setTitleText(ConfigController::getInstance()->getWordById(1015));
	jiesanBtn->setTitleFontSize(35);
	jiesanBtn->setPosition(
		Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2)
		- Vec2(padding + 121, 0));

	auto startGameBtn = Button::create("images/Room/longBtnBlue.png");
	parent->addChild(startGameBtn);
	startGameBtn->setTitleText(ConfigController::getInstance()->getWordById(1016));
	startGameBtn->setTitleFontSize(35);
	startGameBtn->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
		+ Vec2(padding + 121, 0));
}

void GameRoom::shuffleCards(std::vector<Poker>& myPokers)
{
	auto pokerNode = Node::create();
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("plist/poker.plist");
	int num = 17;
	int length = num - 1;
	float startPosX = this->getContentSize().width / 2;
	Sprite* firstPoker = nullptr;
	float myPokerStartPosX = (this->getContentSize().width - pokerSpace * (num - 1)) / 2;
	for (int i = 0; i < num; i++)
	{
		char str[10];
		sprintf(str, "%d.png", myPokers.at(i).id);
		auto spritePoker = Sprite::createWithSpriteFrameName(str);
		if (i == length)
		{
			firstPoker = spritePoker;
			this->addChild(spritePoker,1);
			spritePoker->setPosition(Vec2(this->getContentSize().width / 2, middlePokerY));
		}
		else
		{
			pokerNode->addChild(spritePoker);
			spritePoker->setPosition(Vec2(startPosX + pokerSpace * i, middlePokerY));
		}
		auto myPokerSprite = Sprite::createWithSpriteFrameName(str);
		myPokersSprite.push_back(myPokerSprite);
		this->addChild(myPokerSprite);
		myPokerSprite->setVisible(false);
		myPokerSprite->setPosition(Vec2(myPokerStartPosX + pokerSpace * i, middlePokerY));
	}
	auto pokerMask = ClippingNode::create();
	DrawNode* drawNode = DrawNode::create();
	Vec2 origin(this->getContentSize().width / 2, middlePokerY+60);
	Vec2 destination(this->getContentSize().width / 2 + 15* pokerSpace + 45, middlePokerY -60);
	DrawTool::drawRoundRect(drawNode, origin, destination, 1, 1, true, Color4F::BLUE);
	pokerMask->setInverted(true);
	pokerMask->setAlphaThreshold(0.0f);
	pokerMask->setStencil(drawNode);
	pokerMask->addChild(pokerNode);
	addChild(pokerMask);
	
	float moveTime = 4;
	auto moveBy = MoveBy::create(moveTime, Vec2(-pokerSpace * 8 , 0));
	pokerNode->runAction(Sequence::createWithTwoActions(moveBy, 
		CallFunc::create([=]()
		{
				for (auto myPokerSprite : myPokersSprite)
				{
					myPokerSprite->setVisible(true);
					pokerAddTouch(myPokerSprite, nullptr);
				}
				pokerNode->removeAllChildren();
				firstPoker->removeFromParent();
			
		})));
	auto moveBy16 = MoveBy::create(moveTime, Vec2(pokerSpace * 8 , 0));
	firstPoker->runAction(moveBy16);
	auto maskNodeNoveBy = MoveBy::create(moveTime, Vec2(pokerSpace * 8, 0));
	drawNode->runAction(maskNodeNoveBy);

	//播放发牌音效
	auto soundEffectID = AudioEngine::play2d("music/room/Special_Dispatch.mp3", false);
	
	//其他玩家发牌
	othersShuffleCards();
}

bool GameRoom::selectPoker(Sprite* poker, const Touch* touch, Event* event)
{
	//中
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("plist/poker.plist");
	int num = 17;
	float startPosX  = (this->getContentSize().width - pokerSpace * (num - 1)) / 2;
	
	for (int i = 0; i < num; i++)
	{
		char str[10];
		sprintf(str, "%d.png", i);
		auto spritePoker = Sprite::createWithSpriteFrameName(str);
		spritePoker->setTag(i);
		this->addChild(spritePoker);
		spritePoker->setPosition(Vec2(startPosX + pokerSpace * i, middlePokerY));
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			return true;
		};

		listener->onTouchMoved = [=](Touch* touch, Event* event)
		{
			if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
			{
				spritePoker->setColor(Color3B(220, 220, 220));
				event->stopPropagation();
			}
		};
		listener->onTouchEnded = [=](Touch* touch, Event* event)
		{

			Vec2 start = touch->getStartLocation();
			Vec2 end = touch->getLocation();
			if (start == end)
			{
				if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
				{
					if (fabs(spritePoker->getPositionY() - middlePokerY) < 0.0001)
					{
						spritePoker->setPositionY(middlePokerY + 20);
					}
					else
					{
						spritePoker->setPositionY(middlePokerY);
					}
					event->stopPropagation();
				}
			}

			if (spritePoker->getColor().equals(Color3B(220, 220, 220)))
			{
				spritePoker->setColor(Color3B::WHITE);
				if (fabs(spritePoker->getPositionY() - middlePokerY) < 0.0001)
				{
					spritePoker->setPositionY(middlePokerY + 20);
				}
				else
				{
					spritePoker->setPositionY(middlePokerY);
				}

			}
			/*if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
			{
				if (fabs(spritePoker->getPositionY() - middlePokerY) < 0.0001)
				{
					spritePoker->setPositionY(middlePokerY + 20);
				}
				else
				{
					spritePoker->setPositionY(middlePokerY);
				}
				event->stopPropagation();
			}*/
		};


		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spritePoker);
	}

	//左
	auto pokerLeft = Sprite::createWithSpriteFrameName("63.png");
	this->addChild(pokerLeft);
	pokerLeft->setScale(0.5f);
	pokerLeft->setPosition(258, 490);
	auto pokerNumLeft = Label::createWithSystemFont("17", "Arial", 40);
	pokerLeft->addChild(pokerNumLeft);
	pokerNumLeft->setColor(Color3B::WHITE);
	pokerNumLeft->setPosition(pokerLeft->getContentSize() / 2);

	//右
	auto pokerRight = Sprite::createWithSpriteFrameName("63.png");
	this->addChild(pokerRight);
	pokerRight->setScale(0.5f);
	pokerRight->setPosition(this->getContentSize().width - 258, 490);
	auto pokerNumRight = Label::createWithSystemFont("17", "Arial", 40);
	pokerRight->addChild(pokerNumRight);
	pokerNumRight->setColor(Color3B::WHITE);
	pokerNumRight->setPosition(pokerLeft->getContentSize() / 2);

	return true;
}

void GameRoom::pokerAddTouch(Sprite* spritePoker, Node* node)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		return true;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
		{
			spritePoker->setColor(Color3B(220, 220, 220));
			event->stopPropagation();
		}
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Vec2 start = touch->getStartLocation();
		Vec2 end = touch->getLocation();
		if (start == end)
		{
			if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
			{
				if (fabs(spritePoker->getPositionY() - middlePokerY) < 0.0001)
				{
					spritePoker->setPositionY(middlePokerY + 20);
				}
				else
				{
					spritePoker->setPositionY(middlePokerY);
				}
				event->stopPropagation();
			}
		}

		if (spritePoker->getColor().equals(Color3B(220, 220, 220)))
		{
			spritePoker->setColor(Color3B::WHITE);
			if (fabs(spritePoker->getPositionY() - middlePokerY) < 0.0001)
			{
				spritePoker->setPositionY(middlePokerY + 20);
			}
			else
			{
				spritePoker->setPositionY(middlePokerY);
			}

		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), spritePoker);
}

void GameRoom::othersShuffleCards()
{
	//左
	pokerLeft = Sprite::createWithSpriteFrameName("63.png");
	this->addChild(pokerLeft);
	pokerLeft->setScale(0.5f);
	pokerLeft->setPosition(258, 490);
	pokerNumLeft = Label::createWithSystemFont("17", "Arial", 40);
	pokerLeft->addChild(pokerNumLeft);
	pokerNumLeft->setColor(Color3B::WHITE);
	pokerNumLeft->setPosition(pokerLeft->getContentSize() / 2);

	//右
	pokerRight = Sprite::createWithSpriteFrameName("63.png");
	this->addChild(pokerRight);
	pokerRight->setScale(0.5f);
	pokerRight->setPosition(this->getContentSize().width - 258, 490);
	pokerNumRight = Label::createWithSystemFont("17", "Arial", 40);
	pokerRight->addChild(pokerNumRight);
	pokerNumRight->setColor(Color3B::WHITE);
	pokerNumRight->setPosition(pokerLeft->getContentSize() / 2);

	othersPokerNum = 0;
	this->schedule(SEL_SCHEDULE(&GameRoom::othersShuffleCardsHandle), 0.23f);
}

void GameRoom::othersShuffleCardsHandle(float dt)
{
	othersPokerNum++;
	char str[10];
	sprintf(str, "%d", othersPokerNum);
	pokerNumLeft->setString(str);
	pokerNumRight->setString(str);
	if (othersPokerNum==17)
	{
		this->unschedule(SEL_SCHEDULE(&GameRoom::othersShuffleCardsHandle));
	}
}

void GameRoom::sortCards()
{

}

void GameRoom::callDiZhuBtn(Node* parentNode)
{


}

void GameRoom::robDiZhuBtn(Node* parentNode)
{
}

void GameRoom::playPokerBtn(Node* parentNode)
{
}


