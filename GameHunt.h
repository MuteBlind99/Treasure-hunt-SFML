#pragma once
#include <array>


class GameHunt
{
public:
	std::array<int, 16>field_array_ = {};
	bool chest_find_ = false;
	void RandPosChest();
	void SubPlayerTry() { player_try_--; }
	int PlayerTry() const { return player_try_; }
	int Chest() const { return chest_; }
private:
	int player_try_ = 8;
	int chest_ = 0;
};

