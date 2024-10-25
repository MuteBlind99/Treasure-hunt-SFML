#include "GameSFML.h"

GameSfml::GameSfml()
{
	texture_.loadFromFile("asset\\tile_0001.png");
	sprite_.setTexture(texture_);
	sprite_.setScale(3, 3);
	window_.create(sf::VideoMode(sprite_.getGlobalBounds().width * 4 + 150, sprite_.getGlobalBounds().height * 4), "SFML Treasure Hunt");
	
	font_round_number_.loadFromFile("asset\\Super Unicorn.ttf");
	text_round_.setFont(font_round_number_);

	font_end_game_.loadFromFile("asset\\mickey_mouse\\MickeyMouse_PERSONAL_USE_ONLY.otf");
	text_end_game_.setFont(font_end_game_);

	game_hunt_.RandPosChest();
}

void GameSfml::DrawTry()
{
	text_round_.setPosition((sprite_.getGlobalBounds().width * 4) + 185, 190);
	text_round_.setString(std::to_string(game_hunt_.PlayerTry()));
	text_round_.setScale(3, 3);
	text_round_.setOrigin(text_round_.getGlobalBounds().width, text_round_.getGlobalBounds().height);
	window_.draw(text_round_);
}

void GameSfml::DrawMap()
{
	for (int row_size = 0; row_size < 4; row_size++)//Y
	{
		for (int col_size = 0; col_size < 4; col_size++)//X
		{

			switch (game_hunt_.field_array_[4 * row_size + col_size])
			{
			case 0:

				texture_.loadFromFile("asset\\tile_0001.png");
				sprite_.setPosition(col_size * 50, row_size * 50);


				window_.draw(sprite_);

				break;
			case 1:
				texture_hole_.loadFromFile("asset\\tile_0024.png");
				sprite_hole_.setTexture(texture_hole_);

				sprite_hole_.setPosition(col_size * 50, row_size * 50);
				sprite_hole_.setScale(3, 3);

				window_.draw(sprite_hole_);
				break;
			case 2:
				texture_.loadFromFile("asset\\tile_0135.png");
				treasure_.setTexture(texture_);

				treasure_.setPosition(col_size * 50, row_size * 50);
				treasure_.setScale(3, 3);

				window_.draw(treasure_);
				break;
			}

		}

	}
}

void GameSfml::CheckItemOfClick()
{
	sf::Vector2i mouse_pose = sf::Mouse::getPosition(window_);
	int x = mouse_pose.x / (texture_.getSize().x * sprite_.getScale().x);
	int y = mouse_pose.y / (texture_.getSize().y * sprite_.getScale().y);

	if (x >= 0 && x < 4 && y >= 0 && y < 4)
	{
		int idx = 4 * y + x;


		if (game_hunt_.field_array_.at(idx) == 0)
		{

			if (idx == game_hunt_.Chest())
			{
				game_hunt_.chest_find_ = true;
				game_hunt_.field_array_[idx] = 2;
			}
			else
			{

				game_hunt_.SubPlayerTry();
				game_hunt_.field_array_[idx] = 1;
			}
		}

	}
}

void GameSfml::Event()
{
	while (window_.pollEvent(event_))
	{
		if (event_.type == sf::Event::Closed)
		{
			window_.close();
		}

		if (event_.type == sf::Event::MouseButtonReleased)
		{
			CheckItemOfClick();

		}
	}
}

bool GameSfml::GameEnd()
{
	while (window_.pollEvent(event_))
	{
		if (event_.type == sf::Event::Closed)
		{
			window_.close();
		}
	}

	if (game_hunt_.chest_find_)
	{
		text_end_game_.setPosition((sprite_.getGlobalBounds().width * 4) + 200, 200);
		text_end_game_.setString("WIN");
		text_end_game_.setFillColor(sf::Color::Yellow);
		text_end_game_.setScale(2, 2);
		text_end_game_.setOrigin(text_end_game_.getGlobalBounds().width, text_end_game_.getGlobalBounds().height);
		window_.draw(text_end_game_);
	}
	else
	{
		text_end_game_.setPosition((sprite_.getGlobalBounds().width * 4) + 200, 200);
		text_end_game_.setString("LOSE");
		text_end_game_.setFillColor(sf::Color::Red);
		text_end_game_.setScale(2, 2);
		text_end_game_.setOrigin(text_end_game_.getGlobalBounds().width, text_end_game_.getGlobalBounds().height);
		window_.draw(text_end_game_);
	}

	current_time_ = std::chrono::steady_clock::now();
	elapsed_time_ = current_time_ - previous_time_;
	if (elapsed_time_.count() >= delta_time_)
	{
		timer_s_--;
		previous_time_ = current_time_;
	}
	if (timer_s_ <= 0)
	{
		exit(0);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void GameSfml::GameLoop()
{
	while (window_.isOpen())
	{
		window_.clear();

		DrawTry();

		DrawMap();

		if (!game_hunt_.chest_find_ && game_hunt_.PlayerTry() > 0) {
			Event();
		}
		else
		{
			GameEnd();
		}

		window_.display();
	}
}
