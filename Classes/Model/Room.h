#pragma
#include <string>
#include <vector>
#include "User.h"

enum RoomType
{
	Classics = 0,//���䶷����
	Noshuffle,//��ϴ��
};

class Room
{
public:
	Room(long roomId, RoomType roomType, int bottomScore, User players[3], int seat[3]);
	~Room();
public:
	long roomId;//����id
	RoomType roomType;//��������
	int bottomScore;//�׷�
	User players[3];//���
	int seat[3];//��λ
	
};