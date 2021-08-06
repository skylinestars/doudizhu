#include "LoadingController.h"
#include "ui/UILayout.h"
#include "ui/UILoadingBar.h"
#include "AudioEngine.h"

void LoadingController::initData(LoadingScene* loadingScene)
{
    _totalResource = 4;
    Director::getInstance()->getTextureCache()->addImageAsync(
        "images/test/11.png",
        CC_CALLBACK_1(LoadingScene::loadingDataCallback, loadingScene));
    Director::getInstance()->getTextureCache()->addImageAsync(
        "images/test/22.png",
        CC_CALLBACK_1(LoadingScene::loadingDataCallback, loadingScene));
    Director::getInstance()->getTextureCache()->addImageAsync(
        "images/test/33.png",
        CC_CALLBACK_1(LoadingScene::loadingDataCallback, loadingScene));
    AudioEngine::preload("music/test.mp3", [loadingScene](boolean success)
    {
            loadingScene->loadingDataCallback(loadingScene);
        
    });
   

}
