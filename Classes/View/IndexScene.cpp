#include "IndexScene.h"
#include "../Controller/ConfigController.h"
#include "../Tool/DrawTool.h"


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
	
	createRoomBg = createRoom(bg);
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
	auto createRoom = Button::create("images/index/btnCreateRoom.png");
	parentSprite->addChild(createRoom);
	createRoom->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	createRoom->setPosition(Vec2(
		(parentSprite->getContentSize().width - 2 * createRoom->getContentSize().width - 2 * createRoomPadding) / 2,
		parentSprite->getContentSize().height / 2
	));
	createRoom->addClickEventListener([&](Ref* sender)
		{
			createRoomBg->setVisible(true);
		});

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

Sprite* IndexScene::createRoom(Sprite* parentSprite)
{
	auto bg = Sprite::create("images/createRoom/BG_1280_720.jpg");
	parentSprite->addChild(bg, 3);
	bg->setPosition(parentSprite->getContentSize()/2);

	auto returnIndex = Button::create("images/createRoom/btnBackBlue.png");
	returnIndex->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	bg->addChild(returnIndex);
	returnIndex->setPosition(Vec2(20, bg->getContentSize().height - 50));
	returnIndex->addClickEventListener([bg](Ref* sender)
		{
			bg->setVisible(false);
		});

	auto title = Sprite::create("images/createRoom/textCreateRoomBlue.png");
	bg->addChild(title);
	title->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height-50));

	auto line = Sprite::create("images/createRoom/lineCreateRoom.png");
	bg->addChild(line);
	line->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	line->setPosition(Vec2(325, bg->getContentSize().height - 159));

	//创建房间的选项面板
	DrawNode* rightPanelDraw = DrawNode::create();
	bg->addChild(rightPanelDraw);
	Vec2 originrightPanel(365, bg->getContentSize().height - 159);
	Vec2 destinationrightPanel(bg->getContentSize().width - 40, 200);
	DrawTool::drawRoundRect(rightPanelDraw, originrightPanel,
		destinationrightPanel,
		8, 15, true, Color4F(1, 1, 1, 0.5));

	//创建房间按钮
	auto createRoomBtn = Button::create("images/createRoom/btnGreen.png");
	bg->addChild(createRoomBtn);
	createRoomBtn->setPosition(Vec2((bg->getContentSize().width + line->getPosition().x) / 2, 100));
	auto createRoomText = Sprite::create("images/createRoom/textCreateRoomGreen.png");
	createRoomBtn->addChild(createRoomText);
	createRoomText->setPosition(createRoomBtn->getContentSize() / 2);

	auto leftListBg = Sprite::create("images/createRoom/bgGameTypeA.png");
	bg->addChild(leftListBg);
	leftListBg->setPosition(Vec2(leftListBg->getContentSize().width/2+20, bg->getContentSize().height - 200));
	
	auto leftListText = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1010), "Arial", 40);
	leftListBg->addChild(leftListText);
	leftListText->setPosition(leftListBg->getContentSize()/2);
	leftListText->enableBold();

	auto diFen = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1011), "Arial", 40);
	rightPanelDraw->addChild(diFen);
	diFen->setColor(Color3B(156, 98, 61));
	diFen->setPosition(originrightPanel+
		Vec2(
			diFen->getContentSize().width/2 + 30, 
			-diFen->getContentSize().height/2-30));


	auto radio5 = createRadio(
		rightPanelDraw, 
		diFen->getPosition() + Vec2(120, 0), 
		"5"+ ConfigController::getInstance()->getWordById(1012));

	auto radio10 = createRadio(
		rightPanelDraw,
		diFen->getPosition() + Vec2(420, 0),
		"10" + ConfigController::getInstance()->getWordById(1012));

	auto radio20 = createRadio(
		rightPanelDraw,
		diFen->getPosition() + Vec2(720, 0),
		"20" + ConfigController::getInstance()->getWordById(1012));
	Vector<CheckBox*> cbList;
	cbList.pushBack(radio5);
	cbList.pushBack(radio10);
	cbList.pushBack(radio20);
	groupRadio(cbList);

	return bg;
}

CheckBox* IndexScene::createRadio(Node* parentSprite, Vec2 pos, std::string name)
{
	auto radio = CheckBox::create("images/createRoom/circleNone.png",
		"images/createRoom/circleNone.png",
		"images/createRoom/circleGreen.png",
		"images/createRoom/circleGreen.png",
		"images/createRoom/circleGreen.png");
	radio->setName(name);
	parentSprite->addChild(radio);
	radio->setPosition(pos);

	auto text = Label::createWithSystemFont(name, "Arial", 40);
	text->setColor(Color3B(156, 98, 61));
	parentSprite->addChild(text);
	text->setPosition(radio->getPosition()+Vec2(80, 0));
	return radio;
}

void IndexScene::groupRadio(Vector<CheckBox*> checkBoxs)
{
	for (int i=0; i<checkBoxs.size(); i++)
	{
		checkBoxs.at(i)->addClickEventListener([=](Ref* sender)
			{
				CheckBox* cb = (CheckBox*)sender;
				if (cb->isSelected()==false)
				{
					for (int j=0; j< checkBoxs.size(); j++)
					{
						if (i==j)
						{
							continue;
						}
						checkBoxs.at(j)->setSelected(false);
					}
				}
			});
	}
}
