#include "GameHunt.h"

#include <ctime>


void GameHunt::RandPosChest()
{
	srand(time(NULL));
	chest_ = rand() % field_array_.size();
}
