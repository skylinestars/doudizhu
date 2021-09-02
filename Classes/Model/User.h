#pragma
#include <string>
#include <vector>
#include "Poker.h"

class User
{
public:
	User();
	User(long userId, std::string username, std::string password, std::string headImg,
		std::string nickName, int totalGame, int continuityWin, float winningPercentage,
		long coin);
	~User();
public:
	long userId;//id
	std::string username;//用户名
	std::string password;//密码
	std::string headImg;//头像
	std::string nickName;//昵称
	int totalGame;//总游戏场数
	int continuityWin;//最高连胜
	float winningPercentage;//胜率
	long coin;//金币
	long diamonds;//钻石
};