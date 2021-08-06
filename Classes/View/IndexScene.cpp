#include "IndexScene.h"
#include "../Controller/ConfigController.h"

Scene* IndexScene::createScene()
{
	return IndexScene::create();
}

bool IndexScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图
	auto bg = Sprite::create("images/index/bgIndex.jpg");
	this->addChild(bg);
	bg->setPosition(origin + visibleSize / 2);
	bg->setScale(ConfigController::getInstance()->getScale());
	//海面
	auto seaBg = Sprite::create("images/index/Xhn_dise.png");
	seaBg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg->addChild(seaBg);
	seaBg->setPosition(Vec2(0, bg->getContentSize().height));

	//头像背景
	auto headBg = Sprite::create("images/index/HallTX.png");
	bg->addChild(headBg);
	headBg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	headBg->setPosition(Vec2(0, bg->getContentSize().height));

	//头像
	auto headImg = Sprite::create("images/index/headWho.png");
	float headPadding = 10;
	float headSize = headBg->getContentSize().height- headPadding*2;
	headImg->setContentSize(Size(headSize, headSize));
	headBg->addChild(headImg);
	headImg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	headImg->setPosition(Vec2(headPadding, headPadding));

	//名字、id
	auto nameLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1009), "Arial", 28);
	headBg->addChild(nameLabel);
	nameLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	nameLabel->setPosition(
		Vec2(headImg->getPositionX()+ headImg->getContentSize().width + 20,  
			headBg->getContentSize().height - headPadding));
	auto idLabel = Label::createWithSystemFont("ID: 123456", "Arial", 28);
	headBg->addChild(idLabel);
	idLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	idLabel->setPosition(
		Vec2(headImg->getPositionX() + headImg->getContentSize().width + 20,
			headBg->getContentSize().height - headPadding - 40));

	//金币、砖石
	createFK(
		Vec2(headBg->getContentSize().width + 40,
		bg->getContentSize().height - headPadding - 30),
		bg,
		MoneyType::Gold
		);
	createFK(
		Vec2(headBg->getContentSize().width + 300,
			bg->getContentSize().height - headPadding -30),
		bg,
		MoneyType::Diamond
	);

	//创建房间、加入房间、俱乐部
	createGameList(bg);
	
	//创建导航
	auto hallBtnDi = Sprite::create("images/index/HallBtnDi.png");
	bg->addChild(hallBtnDi);
	hallBtnDi->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	hallBtnDi->setPosition(Vec2(bg->getContentSize().width, 0));
	auto hallHide = Sprite::create("images/index/HallMoreBtn0.png");
	bg->addChild(hallHide);
	hallHide->setPosition(Vec2(bg->getContentSize().width-95, hallBtnDi->getContentSize().height/2));
	
	auto settingPanel = Sprite::create("images/index/HallFX.png");
	bg->addChild(settingPanel);
	settingPanel->setPosition(Vec2(bg->getContentSize().width - 300, 45));
	auto settingText = Sprite::create("images/index/BtnLabelSetting.png");
	settingPanel->addChild(settingText);
	settingText->setPosition(Vec2(settingPanel->getContentSize().width/2, settingPanel->getContentSize().height/2));

	auto recordPanel = Sprite::create("images/index/HallFX.png");
	bg->addChild(recordPanel);
	recordPanel->setPosition(Vec2(settingPanel->getPosition().x - settingPanel->getContentSize().width + 8, 45));
	auto recordText = Sprite::create("images/index/BtnLabelzj.png");
	recordPanel->addChild(recordText);
	recordText->setPosition(Vec2(settingPanel->getContentSize().width / 2, settingPanel->getContentSize().height / 2));
	return true;
}

void IndexScene::createFK(Vec2 position, Sprite* parentSprite, MoneyType moneyType)
{
	std::string moneyImgPath = "";
	float scale = 0;
	if (moneyType == MoneyType::Gold)
	{
		moneyImgPath = "images/Room/coin.png";
		scale = 1.2f;
	}
	else if (moneyType == MoneyType::Diamond)
	{
		moneyImgPath = "images/index/HallFJewel.png";
		scale = 1.0f;
	}
	auto coinImg = Sprite::create(moneyImgPath);
	parentSprite->addChild(coinImg, 2);
	coinImg->setScale(scale);
	coinImg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	coinImg->setPosition(position);
	auto numBg = Sprite::create("images/index/numBg.png");
	parentSprite->addChild(numBg, 1);
	numBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	numBg->setPosition(Vec2(coinImg->getPosition().x, coinImg->getPosition().y));
	auto coinLabel = Label::createWithSystemFont("9999", "Arial", 28);
	numBg->addChild(coinLabel);
	coinLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	coinLabel->setPosition(Vec2(numBg->getContentSize().width / 2, numBg->getContentSize().height / 2));
	auto coinAdd = Sprite::create("images/index/Btn_Buycsj.png");
	numBg->addChild(coinAdd);
	coinAdd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	coinAdd->setPosition(Vec2(numBg->getContentSize().width, numBg->getContentSize().height / 2));
}

void IndexScene::createGameList(Sprite* parentSprite)
{
	float createRoomPadding = 40;
	auto createRoom = Sprite::create("images/index/btnCreateRoom.png");
	parentSprite->addChild(createRoom);
	createRoom->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	createRoom->setPosition(Vec2(
		(parentSprite->getContentSize().width - 2 * createRoom->getContentSize().width - 2 * createRoomPadding) / 2,
		parentSprite->getContentSize().height / 2
	));

	auto joinRoom = Sprite::create("images/index/btnJoinRoom.png");
	parentSprite->addChild(joinRoom);
	joinRoom->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Size createRoomSize = createRoom->getContentSize();
	joinRoom->setContentSize(createRoomSize);
	joinRoom->setPosition(
		Vec2(
			createRoom->getPosition().x + createRoom->getContentSize().width + createRoomPadding,
			parentSprite->getContentSize().height / 2));

	auto club = Sprite::create("images/index/btnClub.png");
	parentSprite->addChild(club);
	club->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	club->setContentSize(createRoom->getContentSize() - Size(0, 30));
	club->setPosition(Vec2(
		joinRoom->getPosition().x + createRoom->getContentSize().width + createRoomPadding,
		parentSprite->getContentSize().height / 2 - 10));

}
