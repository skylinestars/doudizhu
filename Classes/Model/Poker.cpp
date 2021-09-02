#include "Poker.h"

Poker::Poker():id(-1), faceValue(-1), flowerValue(-1)
{
}

Poker::Poker(int id, int faceValue, int flowerValue)
{
	this->id = id;
	this->faceValue = faceValue;
	this->flowerValue = flowerValue;
}
