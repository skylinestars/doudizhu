#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include "../Model/Poker.h"
using namespace std;

class RoomController
{
	
public:
	void createPoker(int* pokersID, std::vector<Poker>& pokers);
	void sortPoker(std::vector<Poker>& pokers);
};