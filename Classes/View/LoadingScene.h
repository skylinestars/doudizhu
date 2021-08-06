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
    /// �������ݻص�
    /// </summary>
    /// <param name="pSender">������</param>
    void loadingDataCallback(Ref* pSender);
    CREATE_FUNC(LoadingScene);
private:
    /// <summary>
    /// ���㱳��ͼƬ����
    /// </summary>
    /// <param name="bg"></param>
    /// <returns></returns>
    float calcBgScale(Sprite* bg);
   
    //�������е����ֽ���
    Label* _loadingText;
    //������
    LoadingBar* _loadingBar;
    //������ͷ��
    Sprite* _loadingBarHead;
    //�������������
    int _loadingBgWidth;
    //��ǰ��������
    int _currentLoadingNum;
    //��Դ��������
    int _totalResource;
    //���ص�������
    std::string _loadingTextCN;

};

#endif // __LOADING_SCENE_H__
