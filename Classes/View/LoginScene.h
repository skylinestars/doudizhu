#pragma once
#include "cocos2d.h"
#include "../Controller/LoginController.h"
using namespace cocos2d;

class LoginScene:Scene
{
public:
	~LoginScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
private:
	void initLoginScene(DrawNode* loginLayerDraw, DrawNode* registerLayerDraw);
	void initRegisterScene(DrawNode* loginLayerDraw, DrawNode* registerLayerDraw);

private:
	LoginController* loginController;
};