#include "LoginScene.h"
#include "../Controller/ConfigController.h"
#include "../Tool/DrawTool.h"
#include "cocos/ui/UIEditBox/UIEditBox.h"
#include "cocos/ui/UIScale9Sprite.h"
#include "cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;

LoginScene::~LoginScene()
{
	if (loginController)
	{
		delete loginController;
	}
}

Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

bool LoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	loginController = new LoginController();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//µÇÂ¼±³¾°
	auto* bg = Sprite::create("images/createRoom/BG_1280_720.jpg");
	this->addChild(bg);
	bg->setPosition(origin + visibleSize / 2);
	bg->setScale(ConfigController::getInstance()->getScale());
	//µÇÂ¼Ãæ°å¡¢×¢²áÃæ°å
	DrawNode* loginLayerDraw = DrawNode::create();
	DrawNode* registerLayerDraw = DrawNode::create();
	initLoginScene(loginLayerDraw, registerLayerDraw);
	initRegisterScene(loginLayerDraw, registerLayerDraw);

	return true;
}

void LoginScene::initLoginScene(DrawNode* loginLayerDraw, DrawNode* registerLayerDraw)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//µÇÂ¼Í¼²ã
	float loginLayerHeight = 240;
	float loginLayerWidth = 590;
	Vec2 loginLayerSize(loginLayerWidth, loginLayerHeight);
	this->addChild(loginLayerDraw);
	Vec2 originLoginLayer;
	originLoginLayer.x = origin.x + visibleSize.width / 2 - loginLayerSize.x / 2;
	originLoginLayer.y = origin.y + visibleSize.height / 2 + loginLayerSize.y / 2;
	Vec2 destinationLoginLayer;
	destinationLoginLayer.x = origin.x + visibleSize.width / 2 + loginLayerSize.x / 2;
	destinationLoginLayer.y = origin.y + visibleSize.height / 2 - loginLayerSize.y / 2;
	DrawTool::drawRoundRect(
		loginLayerDraw, originLoginLayer,
		destinationLoginLayer,
		8, 15, true, Color4F(1, 1, 1, 0.5));

	//ÓÃ»§Ãû
	Label* userNameLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1002), "Arial", 32);
	loginLayerDraw->addChild(userNameLabel);
	userNameLabel->setColor(Color3B(156, 98, 61));
	Vec2 userNameLabelPos;
	float leftPadding = 40;
	float space = 30;
	float userNameLabelWidthHalf = userNameLabel->getContentSize().width / 2;
	userNameLabelPos.x = originLoginLayer.x + leftPadding + userNameLabelWidthHalf;
	userNameLabelPos.y = originLoginLayer.y - (loginLayerHeight / 2 - space - userNameLabel->getContentSize().height / 2);
	userNameLabel->setPosition(userNameLabelPos);

	//ÓÃ»§ÃûÊäÈë¿ò
	float editWidth = 320;
	float editHeight = 70;
	float editSpace = 10;
	auto* userNameEdit = ui::EditBox::create(
		Size(editWidth, editHeight),
		Scale9Sprite::create("images/login/loginText.png"));
	userNameEdit->setPosition(
		Vec2(
			userNameLabel->getContentSize().width + editWidth / 2 + editSpace,
			editHeight / 2 - userNameLabel->getContentSize().height / 2));
	userNameLabel->addChild(userNameEdit);
	userNameEdit->setFontColor(Color3B(156, 98, 61));
	userNameEdit->setFontSize(32);
	userNameEdit->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	userNameEdit->setReturnType(EditBox::KeyboardReturnType::DONE);

	//ÃÜÂë±êÇ©
	Label* passwordLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1003), "Arial", 32);
	loginLayerDraw->addChild(passwordLabel);
	passwordLabel->setColor(Color3B(156, 98, 61));
	passwordLabel->setPosition(userNameLabelPos - Vec2(userNameLabelWidthHalf - passwordLabel->getContentSize().width / 2, 2 * space + userNameLabel->getContentSize().height));

	//ÃÜÂëÊäÈë¿ò
	auto* passwordEdit = ui::EditBox::create(
		Size(editWidth, editHeight),
		Scale9Sprite::create("images/login/loginText.png"));
	passwordEdit->setPosition(
		Vec2(
			userNameLabel->getContentSize().width + editWidth / 2 + editSpace,
			editHeight / 2 - userNameLabel->getContentSize().height / 2));
	passwordLabel->addChild(passwordEdit);
	passwordEdit->setFontColor(Color3B(156, 98, 61));
	passwordEdit->setFontSize(32);
	passwordEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
	passwordEdit->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	passwordEdit->setReturnType(EditBox::KeyboardReturnType::DONE);

	//µÇÂ¼°´Å¥
	auto loginBtn = Button::create("images/smrz/B_zhong_huang.png");
	loginLayerDraw->addChild(loginBtn);
	loginBtn->setTitleText(ConfigController::getInstance()->getWordById(1004));
	loginBtn->setScale(0.6f);
	loginBtn->setPosition(Vec2(visibleSize.width / 2 - 130, visibleSize.height - 600));
	loginBtn->setTitleFontSize(50);
	loginBtn->addClickEventListener([=](Ref* sender)
		{
			if (loginController->loginHandle(userNameEdit->getText(), passwordEdit->getText()))
			{
				// µÇÂ¼³É¹¦
			}
			else
			{
				//µÇÂ¼Ê§°Ü
			}
		});

	//×¢²á°´Å¥
	auto registerBtn = Button::create("images/smrz/B_zhong_lv.png");
	loginLayerDraw->addChild(registerBtn);
	registerBtn->setTitleText(ConfigController::getInstance()->getWordById(1005));
	registerBtn->setScale(0.6f);
	registerBtn->setPosition(Vec2(visibleSize.width / 2 + 130, visibleSize.height - 600));
	registerBtn->setTitleFontSize(50);
	registerBtn->addClickEventListener([=](Ref* sender)
	{
			loginLayerDraw->setVisible(false);
			registerLayerDraw->setVisible(true);
			userNameEdit->setText("");
			passwordEdit->setText("");
	});

}

void LoginScene::initRegisterScene(DrawNode* loginLayerDraw, DrawNode* registerLayerDraw)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	registerLayerDraw->setVisible(false);

	//µÇÂ¼Í¼²ã
	float registerLayerHeight = 360;
	float registerLayerWidth = 590;
	Vec2 registerLayerSize(registerLayerWidth, registerLayerHeight);
	this->addChild(registerLayerDraw);
	Vec2 originRegisterLayer;
	originRegisterLayer.x = origin.x + visibleSize.width / 2 - registerLayerSize.x / 2;
	originRegisterLayer.y = origin.y + visibleSize.height / 2 + registerLayerSize.y / 2;
	Vec2 destinationRegisterLayer;
	destinationRegisterLayer.x = origin.x + visibleSize.width / 2 + registerLayerSize.x / 2;
	destinationRegisterLayer.y = origin.y + visibleSize.height / 2 - registerLayerSize.y / 2;
	DrawTool::drawRoundRect(
		registerLayerDraw, originRegisterLayer,
		destinationRegisterLayer,
		8, 15, true, Color4F(1, 1, 1, 0.5));

	//ÓÃ»§Ãû
	Label* userNameLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1002), "Arial", 32);
	registerLayerDraw->addChild(userNameLabel);
	userNameLabel->setColor(Color3B(156, 98, 61));
	Vec2 userNameLabelPos;
	float leftPadding = 40;
	float space = 30;
	float userNameLabelWidthHalf = userNameLabel->getContentSize().width / 2;
	userNameLabelPos.x = originRegisterLayer.x + leftPadding + userNameLabelWidthHalf;
	userNameLabelPos.y = originRegisterLayer.y - (registerLayerHeight - 2 * space - 4 * userNameLabel->getContentSize().height)/2;
	userNameLabel->setPosition(userNameLabelPos);

	//ÃÜÂë±êÇ©
	Label* passwordLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1003), "Arial", 32);
	registerLayerDraw->addChild(passwordLabel);
	passwordLabel->setColor(Color3B(156, 98, 61));
	passwordLabel->setPosition(
		userNameLabelPos - Vec2(
			userNameLabelWidthHalf - passwordLabel->getContentSize().width / 2, 
			2 * space + userNameLabel->getContentSize().height));

	//È·ÈÏÃÜÂë±êÇ©
	Label* passwordOkLabel = Label::createWithSystemFont(
		ConfigController::getInstance()->getWordById(1006), "Arial", 32);
	registerLayerDraw->addChild(passwordOkLabel);
	passwordOkLabel->setColor(Color3B(156, 98, 61));
	passwordOkLabel->setPosition(
		passwordLabel->getPosition() - Vec2(
			passwordLabel->getContentSize().width/2 - passwordOkLabel->getContentSize().width / 2,
			2 * space + userNameLabel->getContentSize().height));


	//ÓÃ»§ÃûÊäÈë¿ò
	float editWidth = 320;
	float editHeight = 70;
	float editSpace = 50;
	auto* userNameEdit = ui::EditBox::create(
		Size(editWidth, editHeight),
		Scale9Sprite::create("images/login/loginText.png"));
	userNameEdit->setPosition(
		Vec2(
			userNameLabel->getContentSize().width + editWidth / 2 + editSpace,
			editHeight / 2 - userNameLabel->getContentSize().height / 2));
	userNameLabel->addChild(userNameEdit);
	userNameEdit->setFontColor(Color3B(156, 98, 61));
	userNameEdit->setFontSize(32);
	userNameEdit->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	userNameEdit->setReturnType(EditBox::KeyboardReturnType::DONE);

	//ÃÜÂëÊäÈë¿ò
	auto* passwordEdit = ui::EditBox::create(
		Size(editWidth, editHeight),
		Scale9Sprite::create("images/login/loginText.png"));
	passwordEdit->setPosition(
		Vec2(
			userNameLabel->getContentSize().width + editWidth / 2 + editSpace,
			editHeight / 2 - userNameLabel->getContentSize().height / 2));
	passwordLabel->addChild(passwordEdit);
	passwordEdit->setFontColor(Color3B(156, 98, 61));
	passwordEdit->setFontSize(32);
	passwordEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
	passwordEdit->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	passwordEdit->setReturnType(EditBox::KeyboardReturnType::DONE);

	//ÃÜÂëÊäÈë¿ò
	auto* passwordOkEdit = ui::EditBox::create(
		Size(editWidth, editHeight),
		Scale9Sprite::create("images/login/loginText.png"));
	passwordOkEdit->setPosition(
		Vec2(
			userNameLabel->getContentSize().width + editWidth / 2 + editSpace,
			editHeight / 2 - userNameLabel->getContentSize().height / 2));
	passwordOkLabel->addChild(passwordOkEdit);
	passwordOkEdit->setFontColor(Color3B(156, 98, 61));
	passwordOkEdit->setFontSize(32);
	passwordOkEdit->setInputFlag(EditBox::InputFlag::PASSWORD);
	passwordOkEdit->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	passwordOkEdit->setReturnType(EditBox::KeyboardReturnType::DONE);

	//·µ»ØµÇÂ¼°´Å¥
	auto loginBtn = Button::create("images/smrz/B_zhong_huang.png");
	registerLayerDraw->addChild(loginBtn);
	loginBtn->setTitleText(ConfigController::getInstance()->getWordById(1007));
	loginBtn->setScale(0.6f);
	loginBtn->setPosition(Vec2(visibleSize.width / 2 - 130, visibleSize.height - 600));
	loginBtn->setTitleFontSize(50);
	loginBtn->addClickEventListener([=](Ref* sender)
	{
		loginLayerDraw->setVisible(true);
		registerLayerDraw->setVisible(false);
		userNameEdit->setText("");
		passwordEdit->setText("");
		passwordOkEdit->setText("");
	});

	//×¢²áµÇÂ¼°´Å¥
	auto registerBtn = Button::create("images/smrz/B_zhong_lv.png");
	registerLayerDraw->addChild(registerBtn);
	registerBtn->setTitleText(ConfigController::getInstance()->getWordById(1008));
	registerBtn->setScale(0.6f);
	registerBtn->setPosition(Vec2(visibleSize.width / 2 + 130, visibleSize.height - 600));
	registerBtn->setTitleFontSize(50);
	registerBtn->addClickEventListener([=](Ref* sender)
		{
			if (loginController->registerHandle(userNameEdit->getText(), passwordEdit->getText(), passwordOkEdit->getText()))
			{
				// ×¢²á³É¹¦ ²¢µÇÂ¼
				// TODO
			}
			else
			{
				//×¢²áÊ§°Ü
				//TODO
			}
		});
}

