#pragma once
#include "../View/LoadingScene.h"


class LoadingController
{

public:

	/// <summary>
	/// 初始化数据
	/// </summary>
	/// <param name="loadingScene">加载场景</param>
	void initData(LoadingScene* loadingScene);
	/// <summary>
	/// 获取资源总数
	/// </summary>
	/// <returns></returns>
	int getTotalResource(){ return _totalResource; }

private:
	int _totalResource;
};