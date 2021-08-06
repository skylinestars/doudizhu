#pragma once
#include "../View/LoadingScene.h"


class LoadingController
{

public:

	/// <summary>
	/// ��ʼ������
	/// </summary>
	/// <param name="loadingScene">���س���</param>
	void initData(LoadingScene* loadingScene);
	/// <summary>
	/// ��ȡ��Դ����
	/// </summary>
	/// <returns></returns>
	int getTotalResource(){ return _totalResource; }

private:
	int _totalResource;
};