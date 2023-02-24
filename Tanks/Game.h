#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "ControllableTank.h"
#include "AiTank.h"
#include "Projectile.h"
#include "Animation.h"
#include "Base.h"
#include "BrainAtk.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <cmath>

class Game
{

public:	
	
	std::unique_ptr<TileMap> m_map;

	struct input_event {

		struct mouse_event {

			sf::Vector2i position;
			bool left_button_pressed = false;
			bool right_button_pressed = false;
			bool wheel_button_pressed = false;

		};

		struct keyboard_event
		{
			enum key { k_W, k_A, k_S, k_D, k_Space, k_size };
			key key_pressed;
			bool isPressed = false;
			bool isReleased = false;
		};

		std::vector <mouse_event> mouse_events;
		std::vector <keyboard_event> keyboard_events;

	};	

	input_event events;

	void initialize(uint32_t window_width, uint32_t window_height, std::unique_ptr<sf::RenderWindow>& window);
	void update();
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void gather_input(input_event events);
	void calibrate_pos(sf::Vector2f& tank_position);
	
	~Game();
	enum game_state {
		gs_menu,
		gs_game_start
	};
	game_state m_game_state;

private:

	uint32_t m_game_win_width;
	uint32_t m_game_win_height;

	using input_array = std::array<bool, input_event::keyboard_event::key::k_size>;

	input_array m_input_state;

	Animation m_animation;
	ControllableTank m_player_tank;
	AiTank m_ai_tank;
	Base m_player_base;
	Base m_ai_base;
	BrainAtk m_brain;

	std::vector <Projectile> m_projectile_vector;
	std::vector <AiTank> m_ai_vector;
	float m_projectile_distance = 64;
	
	uint32_t m_tank_offset = 16;	
	
	int count_inputs(input_array inputs);
	uint32_t m_level_rows = 19;
	uint32_t m_level_columns = 27;	
	sf::Texture m_background_tex;
	sf::Texture m_start_button_tex;
	sf::RectangleShape m_menu_background;
	sf::RectangleShape m_game_background;
	sf::RectangleShape m_start_button;

	sf::Vector2f m_tank_movement_direction{ 0.f, 0.f };	
	sf::Vector2f m_projectile_movement_direction{ 0.f, -1.f };

	std::chrono::time_point<std::chrono::system_clock> m_time{ std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> m_start_time{ std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> start_animation_time = std::chrono::system_clock::now();
	std::chrono::duration<float> m_total_time{ 0 };
	std::chrono::duration<float> m_dt{ 0 };
	bool m_first_bullet_shot = false;
	std::chrono::duration<float> m_last_projectile_shot{0};
	

};

