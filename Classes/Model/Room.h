#pragma
#include <string>
#include <vector>
#include "User.h"

enum RoomType
{
	Classics = 0,//经典斗地主
	Noshuffle,//不洗牌
};

class Room
{
public:
	Room(long roomId, RoomType roomType, int bottomScore, User players[3], int seat[3]);
	~Room();
public:
	long roomId;//房间id
	RoomType roomType;//房间类型
	int bottomScore;//底分
	User players[3];//玩家
	int seat[3];//座位
	
};