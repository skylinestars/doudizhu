#include "Room.h"

Room::Room(long roomId, RoomType roomType, int bottomScore, User players[3], int seat[3])
{
	this->roomId = roomId;
	this->roomType = roomType;
	this->bottomScore = bottomScore;
}

Room::~Room()
{
}
