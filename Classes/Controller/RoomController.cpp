#include "RoomController.h"

void RoomController::createPoker(int* pokersID, std::vector<Poker>& pokers)
{
	srand((unsigned)time(NULL));
	int pokerID[54];
	for (int i = 0; i < 54; i++)
	{
		pokerID[i] = i;
	}
	for (int i = 0; i < 54; i++)
	{
		int index = rand() % 54;
		int temp = pokerID[i];
		pokerID[i] = pokerID[index];
		pokerID[index] = temp;
	}
	for (int i = 0; i < 17; i++)
	{
		Poker pokerObj;
		if (pokerID[i] == 52 || pokerID[i] == 53)
		{
			pokerObj.faceValue = pokerID[i] + 13;
		}
		else
		{
			pokerObj.faceValue = pokerID[i] % 13 + 1;
		}
		pokerObj.id = pokerID[i];
		if (pokerObj.faceValue==1 || pokerObj.faceValue==2)
		{
			pokerObj.faceValue = pokerObj.faceValue + 13;
		}
		int flowvalue = 0;
		if (pokerID[i] >= 0 && pokerID[i] <= 12)
		{
			flowvalue = 2;
		}
		else if (pokerID[i] >= 13 && pokerID[i] <= 25)
		{
			flowvalue = 4;
		}
		else if (pokerID[i] >= 26 && pokerID[i] <= 38)
		{
			flowvalue = 1;
		}
		else if (pokerID[i] >= 39 && pokerID[i] <= 51)
		{
			flowvalue = 3;
		}
		pokerObj.flowerValue = flowvalue;
		pokers.push_back(pokerObj);
	}
}


void RoomController::sortPoker(std::vector<Poker>& pokers)
{
	if (pokers.empty())
	{
		return;
	}
	int length = pokers.size();
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (pokers.at(i).faceValue < pokers.at(j).faceValue)
			{
				Poker temp = pokers.at(i);
				pokers.at(i) = pokers.at(j);
				pokers.at(j) = temp;
			}
			else if (pokers.at(i).faceValue == pokers.at(j).faceValue)
			{
				if (pokers.at(i).flowerValue < pokers.at(j).flowerValue)
				{
					Poker temp = pokers.at(i);
					pokers.at(i) = pokers.at(j);
					pokers.at(j) = temp;
				}
			}
		}
	}
}