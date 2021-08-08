#include "GameRoom.h"
#include "../Controller/ConfigController.h"

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
	bg->setScale(ConfigController::getInstance()->getScale());
	auto desk = Sprite::create("images/Room/bgRoom.png");
	bg->addChild(desk);
	desk->setPosition(bg->getContentSize() / 2);

	//底分
	auto diFen = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1010)
		+"  "+ ConfigController::getInstance()->getWordById(1011)
		+"10"
		, "Arial", 28);
	desk->addChild(diFen);
	diFen->setColor(Color3B(56,117, 8));
	diFen->enableBold();
	diFen->setPosition(Vec2(desk->getContentSize().width/2, desk->getContentSize().height/2+100));

	//游戏准备面板
	auto gamePreparePanel = Node::create();
	gamePreparePanel->setVisible(false);
	desk->addChild(gamePreparePanel);
	createPreparePanel(gamePreparePanel);
	
	//玩家信息--中
	createPlayerInfo(bg, Vec2(102.5f, 126.3f));
	//玩家信息--左
	createPlayerInfo(bg, Vec2(102.5f, bg->getContentSize().height/2));
	//玩家信息--右
	createPlayerInfo(bg, Vec2(bg->getContentSize().width - 102.5f, bg->getContentSize().height / 2));
	
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
	playerMiddleHead->setScale(0.7f);
	playerMiddleHead->setPosition(Vec2(playerMiddleHeadBg->getContentSize().width / 2,
		playerMiddleHeadBg->getContentSize().height / 2 + 14));

	auto playerMiddleName = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1009), "Arial", 16);
	playerMiddleHeadBg->addChild(playerMiddleName);
	playerMiddleName->setPosition(Vec2(playerMiddleHeadBg->getContentSize().width / 2,
		15));

	auto coinIcon = Sprite::create("images/Room/coin.png");
	playerMiddleBg->addChild(coinIcon);
	coinIcon->setScale(0.5f);
	coinIcon->setPosition(Vec2(30, 20));

	auto coin = Label::createWithSystemFont(
		"9999" + ConfigController::getInstance()->getWordById(1013), "Arial", 20);
	playerMiddleBg->addChild(coin);
	coin->setColor(Color3B::YELLOW);
	coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	coin->setPosition(Vec2(50, 25));
}

void GameRoom::createPreparePanel(Node* parent)
{
	//解散房间
	auto destoryRoomBtn = Button::create("images/Room/R_btnDisband.png");
	parent->addChild(destoryRoomBtn);
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
	parent->addChild(startGameBtn);
	startGameBtn->setPosition(Vec2(this->getContentSize().width/2, 150));
}
