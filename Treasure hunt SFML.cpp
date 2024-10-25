
#include <array>
#include <chrono>
#include <iostream>
#include <thread>

#include "SFML/Graphics.hpp"





int main()
{
	sf::Texture texture;
	texture.loadFromFile("asset\\tile_0001.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(3, 3);
	std::array<int, 16>fieldArray = {};
	sf::RenderWindow window(sf::VideoMode(sprite.getGlobalBounds().width * 4 + 150, sprite.getGlobalBounds().height * 4), "SFML Treasure Hunt");

	sf::Texture texture_hole;

	sf::Font font_round_number;
	sf::Font font_end_game;
	sf::Text text_round;
	sf::Text text_end_game;
	sf::Sprite treasure;
	sf::Sprite sprite_hole;
	sf::Event event;


	
	int player_try = 4;
	int chest = 0;
	srand(time(NULL));
	chest = rand() % fieldArray.size();
	font_round_number.loadFromFile("asset\\Super Unicorn.ttf");
	text_round.setFont(font_round_number);
	font_end_game.loadFromFile("asset\\mickey_mouse\\MickeyMouse_PERSONAL_USE_ONLY.otf");
	text_end_game.setFont(font_end_game);

	window.clear();


	while (window.isOpen())
	{
		text_round.setPosition((sprite.getGlobalBounds().width * 4) + 185, 190);
		text_round.setString(std::to_string(player_try));
		text_round.setScale(3, 3);
		text_round.setOrigin(text_round.getGlobalBounds().width, text_round.getGlobalBounds().height);
		window.draw(text_round);

		for (int row_size = 0; row_size < 4;row_size++)//Y
		{
			for (int col_size = 0;col_size < 4;col_size++)//X
			{

				switch (fieldArray[4 * row_size + col_size])
				{
				case 0:

					texture.loadFromFile("asset\\tile_0001.png");
					sprite.setPosition(col_size * 50, row_size * 50);


					window.draw(sprite);

					break;
				case 1:
					texture_hole.loadFromFile("asset\\tile_0024.png");
					sprite_hole.setTexture(texture_hole);

					sprite_hole.setPosition(col_size * 50, row_size * 50);
					sprite_hole.setScale(3, 3);

					window.draw(sprite_hole);
					break;
				case 2:
					texture.loadFromFile("asset\\tile_0135.png");
					treasure.setTexture(texture);

					treasure.setPosition(col_size * 50, row_size * 50);
					treasure.setScale(3, 3);

					window.draw(treasure);
					break;
				}
			}
		}

		static bool chest_find = false;

		if (!chest_find && player_try > 0) {
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					sf::Vector2i mouse_pose = sf::Mouse::getPosition(window);
					int x = mouse_pose.x / (texture.getSize().x * sprite.getScale().x);
					int y = mouse_pose.y / (texture.getSize().y * sprite.getScale().y);

					if (x >= 0 && x < 4 && y >= 0 && y < 4)
					{
						int idx = 4 * y + x;


						if (fieldArray.at(idx) == 0)
						{

							if (idx == chest)
							{
								chest_find = true;
								fieldArray[idx] = 2;
							}
							else
							{

								player_try--;
								fieldArray[idx] = 1;
							}
						}
					}
				}
			}
		}
		else
		{
			if (chest_find)
			{
				text_end_game.setPosition((sprite.getGlobalBounds().width * 4) + 215, 200);
				text_end_game.setString("WIN");
				text_end_game.setFillColor(sf::Color::Yellow);
				text_end_game.setScale(2, 2);
				text_end_game.setOrigin(text_end_game.getGlobalBounds().width, text_end_game.getGlobalBounds().height);
				window.draw(text_end_game);
			}
			else
			{
				text_end_game.setPosition((sprite.getGlobalBounds().width * 4) + 200, 200);
				text_end_game.setString("LOSE");
				text_end_game.setFillColor(sf::Color::Red);
				text_end_game.setScale(2, 2);
				text_end_game.setOrigin(text_end_game.getGlobalBounds().width, text_end_game.getGlobalBounds().height);
				window.draw(text_end_game);
			}

			static int timer_s = 4;
			static double  deltaTime = 1.0;
			static auto previousTime = std::chrono::steady_clock::now();
			auto currentTime = std::chrono::steady_clock::now();
			std::chrono::duration<double>elapsedTime = currentTime - previousTime;
			if (elapsedTime.count() >= deltaTime)
			{
				timer_s--;
				previousTime = currentTime;
			}
			if (timer_s <= 0)
			{
				exit(0);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		window.display();
		window.clear();
	}
}

