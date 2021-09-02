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
	std::string username;//�û���
	std::string password;//����
	std::string headImg;//ͷ��
	std::string nickName;//�ǳ�
	int totalGame;//����Ϸ����
	int continuityWin;//�����ʤ
	float winningPercentage;//ʤ��
	long coin;//���
	long diamonds;//��ʯ
};