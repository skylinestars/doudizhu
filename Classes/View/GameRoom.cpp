#include "GameRoom.h"
#include "../Controller/ConfigController.h"
#include "../Tool/DrawTool.h"

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
	desk->addChild(gamePreparePanel);
	createPreparePanel(gamePreparePanel);

	//游戏发牌
	shuffleCards();
	//玩家信息--中
	createPlayerInfo(bg, Vec2(70, 126.3f));
	//玩家信息--左
	createPlayerInfo(bg, Vec2(70, bg->getContentSize().height/2+200));
	//玩家信息--右
	createPlayerInfo(bg, Vec2(bg->getContentSize().width - 70, bg->getContentSize().height / 2+200));
	
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
	//解散房间
	auto destoryRoomBtn = Button::create("images/Room/R_btnDisband.png");
	parent->addChild(destoryRoomBtn);
	destoryRoomBtn->setEnabled(false);
	destoryRoomBtn->setPosition(Vec2(950, 150));
	//返回大厅
	auto backIndexBtn = Button::create("images/Room/R_btnBackIndex.png");
	parent->addChild(backIndexBtn);
	backIndexBtn->setPosition(destoryRoomBtn->getPosition() + Vec2(0, 120));
	//复制房间号
	auto copyRoomIdBtn = Button::create("images/Room/btnCopyRoom.png");
	parent->addChild(copyRoomIdBtn);
	copyRoomIdBtn->setPosition(backIndexBtn->getPosition() + Vec2(0, 120));
	copyRoomIdBtn->setScale(
		backIndexBtn->getContentSize().width / copyRoomIdBtn->getContentSize().width,
		backIndexBtn->getContentSize().height / copyRoomIdBtn->getContentSize().height);
	//开始游戏
	auto startGameBtn = Button::create(
		"images/Room/ox_24.png", 
		"", 
		"images/Room/ox_25.png");
	startGameBtn->setVisible(false);
	parent->addChild(startGameBtn);
	startGameBtn->setPosition(Vec2(this->getContentSize().width/2, 150));

	//准备
	auto prepareBtn = Button::create("images/Room/ox_ready.png");
	prepareBtn->setVisible(true);
	parent->addChild(prepareBtn);
	prepareBtn->setPosition(Vec2(this->getContentSize().width / 2, 150));
}

void GameRoom::createPlayGame(Node* parent)
{

}

void GameRoom::shuffleCards()
{

	//中
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("plist/poker.plist");
	float startPosX = 0;
	Vec2 startPos = Vec2(300, 145);
	int num = 17;
	middlePokerY = 171;
	for (int i = 0; i < num; i++)
	{
		char str[10];
		sprintf(str, "%d.png", i);
		auto spritePoker = Sprite::createWithSpriteFrameName(str);
		spritePoker->setTag(i);
		if (startPosX == 0)
		{
			startPosX = this->getContentSize().width / 2 - (5 * num - 3) * spritePoker->getContentSize().width / 24;
		}
		this->addChild(spritePoker);
		
		spritePoker->setPosition(Vec2(startPosX + spritePoker->getContentSize().width * i * 5 / 12, middlePokerY));
		auto listener = EventListenerTouchOneByOne::create();
		Vec2 beginPos;
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			//spritePoker->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
			//log("%f;%f", touch->getLocation().x, touch->getLocation().y);
			//return selectPoker(spritePoker, touch, event);
			
			/*if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
			{

				return true;
			}
			else
			{
				return false;
			}*/
			//beginPos = touch->getLocation();
			return true;

		};
		//ccTouchCallback onTouchMoved;
		//ccTouchCallback onTouchEnded;
		listener->onTouchMoved = [=](Touch* touch, Event* event)
		{
			//log("%f,%f,%f", spritePoker->getColor().r, spritePoker->getColor().g, spritePoker->getColor().b);
			if (spritePoker->getBoundingBox().containsPoint(touch->getLocation()))
			{
				spritePoker->setColor(Color3B(220, 220, 220));
				event->stopPropagation();
			}
		};
		listener->onTouchEnded = [=](Touch* touch, Event* event)
		{
			

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
	pokerLeft->setPosition(258,490);
	auto pokerNumLeft = Label::createWithSystemFont("17", "Arial", 40);
	pokerLeft->addChild(pokerNumLeft);
	pokerNumLeft->setColor(Color3B::WHITE);
	pokerNumLeft->setPosition(pokerLeft->getContentSize()/2);

	//右
	auto pokerRight = Sprite::createWithSpriteFrameName("63.png");
	this->addChild(pokerRight);
	pokerRight->setScale(0.5f);
	pokerRight->setPosition(this->getContentSize().width - 258, 490);
	auto pokerNumRight = Label::createWithSystemFont("17", "Arial", 40);
	pokerRight->addChild(pokerNumRight);
	pokerNumRight->setColor(Color3B::WHITE);
	pokerNumRight->setPosition(pokerLeft->getContentSize() / 2);
		
}

bool GameRoom::selectPoker(Sprite* poker, const Touch* touch, Event* event)
{
	if (poker->getBoundingBox().containsPoint(touch->getLocation())) 
	{

		if (poker->getPositionY() == middlePokerY)
		{
			poker->setPositionY(middlePokerY + 20);
		}
		else
		{
			poker->setPositionY(middlePokerY);
		}
		event->stopPropagation();
		return true;
	}
	else
	{
		return false;
	}	
}

