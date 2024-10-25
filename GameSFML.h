#ifndef GAME_H
#define GAME_H

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

#include "GameHunt.h"
#include "SFML/Graphics.hpp"

class GameSfml
{
public:
	GameSfml();
	void DrawTry();
	void DrawMap();
	void CheckItemOfClick();
	void Event();
	bool GameEnd();

	void GameLoop();
private:
	GameHunt game_hunt_;

	sf::RenderWindow window_;

	sf::Texture texture_;
	sf::Texture texture_hole_;

	sf::Sprite sprite_;
	sf::Sprite treasure_;
	sf::Sprite sprite_hole_;
	
	sf::Font font_round_number_;
	sf::Font font_end_game_;
	sf::Text text_round_;
	sf::Text text_end_game_;
	
	sf::Event event_;

	int timer_s_ = 3;
	double delta_time_ = 1.0;
	std::chrono::time_point<std::chrono::steady_clock> previous_time_ = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> current_time_;
	std::chrono::duration<double>elapsed_time_;
};

#endif // GAME_H
