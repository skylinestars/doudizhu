#pragma
#include <string>

class User
{
public:
	User();
	User(long userId, std::string username, std::string password, std::string headImg,
		std::string nickName, int totalGame, int continuityWin, float winningPercentage,
		long coin);
	~User();
public:
	long userId;
	std::string username;
	std::string password;
	std::string headImg;
	std::string nickName;
	int totalGame;
	int continuityWin;
	float winningPercentage;
	long coin;
};