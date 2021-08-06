#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__
#include "cocos2d.h"
#include "ui/UILoadingBar.h"

USING_NS_CC;
using namespace ui;

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    /// <summary>
    /// 加载数据回调
    /// </summary>
    /// <param name="pSender">发送者</param>
    void loadingDataCallback(Ref* pSender);
    CREATE_FUNC(LoadingScene);
private:
    /// <summary>
    /// 计算背景图片缩放
    /// </summary>
    /// <param name="bg"></param>
    /// <returns></returns>
    float calcBgScale(Sprite* bg);
   
    //加载条中的数字进度
    Label* _loadingText;
    //加载条
    LoadingBar* _loadingBar;
    //加载条头部
    Sprite* _loadingBarHead;
    //加载条背景宽度
    int _loadingBgWidth;
    //当前加载数量
    int _currentLoadingNum;
    //资源加载总数
    int _totalResource;
    //加载的中文字
    std::string _loadingTextCN;

};

#endif // __LOADING_SCENE_H__
