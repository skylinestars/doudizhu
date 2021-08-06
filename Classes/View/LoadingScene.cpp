#include "LoadingScene.h"
#include "../Controller/ConfigController.h"
#include "../Controller/LoadingController.h"
#include <thread>
#include "cocos/2d/CCLabel.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace ui;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

bool LoadingScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    _totalResource = 0;
    _currentLoadingNum = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //加载背景图
    auto bg = Sprite::create("images/loading/loading.jpg");
    this->addChild(bg);
    bg->setPosition(origin + visibleSize / 2);
    float visibleRatio = visibleSize.height / visibleSize.width;
    float scale = calcBgScale(bg);
    ConfigController::getInstance()->setScale(scale);
    bg->setScale(scale);

    //数字加载进度显示
    _loadingTextCN = ConfigController::getInstance()->getWordById(1001);
    _loadingText = Label::createWithSystemFont(
        _loadingTextCN +"(0%)",
        "Arial", 40);
    _loadingText->setColor(Color3B::BLACK);
    bg->addChild(_loadingText);
    Vec2 loadingTextPosition;
    loadingTextPosition.x = bg->getContentSize().width / 2;
    loadingTextPosition.y = bg->getContentSize().height * 0.2f;
    _loadingText->setPosition(origin + loadingTextPosition);
   
    //加载加载条
    //加载条背景
    auto loadingBg = Sprite::create("images/loading/T_jindutiao_di.png");
    bg->addChild(loadingBg);
    Vec2 loadingBgPosition;
    loadingBgPosition.x = bg->getContentSize().width / 2;
    loadingBgPosition.y = bg->getContentSize().height * 0.12f;
    loadingBg->setPosition(origin + loadingBgPosition);
    //加载条
    _loadingBar = LoadingBar::create("images/loading/T_jindutiao_lv.png");
    bg->addChild(_loadingBar);
    _loadingBar->setPosition(origin + loadingBgPosition);
    _loadingBar->setDirection(LoadingBar::Direction::LEFT);
    _loadingBar->setPercent(0);
    //加载条头部
    _loadingBarHead = Sprite::create("images/loading/Icon_saizi.png");
    _loadingBar->addChild(_loadingBarHead);
    _loadingBgWidth = loadingBg->getContentSize().width;
    _loadingBarHead->setPosition(Vec2(0,loadingBg->getContentSize().height/2));
    //加载控制器
    LoadingController loadingController;
    loadingController.initData(this);
    _totalResource = loadingController.getTotalResource();
    return true;
}

void LoadingScene::loadingDataCallback(Ref* ref)
{
    _currentLoadingNum++;
    int percent = (int)(((float)_currentLoadingNum / _totalResource) * 100);
    std::string loadingText(_loadingTextCN);
    loadingText.append("(");
    loadingText.append(std::to_string(percent));
    loadingText.append("%)");
    _loadingText->setString(loadingText);
    _loadingBar->setPercent(percent);
    _loadingBarHead->setPositionX(_loadingBgWidth * ((float)percent / 100));
    if (percent>=100)
    {
        auto scene = LoginScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

float LoadingScene::calcBgScale(Sprite* bg)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float bgWidth = bg->getTextureRect().getMaxX();
    float bgHeight = bg->getTextureRect().getMaxY();
    float bgImgScale = bgHeight / bgWidth;
    float scale = 0;
    if ((visibleSize.height / visibleSize.width) > bgImgScale)
    {
        //按照宽缩放
        scale = visibleSize.width / bgWidth;
    }
    else
    {
        scale = visibleSize.height / bgHeight;
    }
    return scale;
}

