#include "User.h"

User::User():
	userId(0),
	username(""),
	password(""),
	headImg(""),
	nickName(""),
	totalGame(0),
	continuityWin(0),
	winningPercentage(0.0f),
	coin(0)
{
}

User::User(long userId, std::string username, std::string password, std::string headImg, std::string nickName, int totalGame, int continuityWin, float winningPercentage, long coin)
{
	this->userId = userId;
	this->username = username;
	this->password = password;
	this->headImg = headImg;
	this->nickName = nickName;
	this->totalGame = totalGame;
	this->continuityWin = continuityWin;
	this->winningPercentage = winningPercentage;
	this->coin = coin;
}

User::~User()
{
}
