#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "ControllableTank.h"
#include "AiTank.h"
#include "Projectile.h"
#include "Animation.h"
#include "Base.h"
#include "BoostSprite.h"
#include "SpeedBoostPowerUp.h"
#include "LifeBoostPowerUp.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <cmath>
#include <random>
#include "Command.h"
#include "AnimationObserver.h"
#include "AudioObserver.h"
#include "InputEventQueue.h"
#include "InputKeys.h"

class Game
{

public:
	Game() :
		m_life_text(m_game_font),
		m_kill_count_text(m_game_font),
		m_win_lose_text(m_game_font),
		m_teleport_timer_text(m_game_font)
		{}
	std::unique_ptr<TileMap> m_map;
	std::vector <AiTank> m_ai_tanks;
	std::vector <BoostSprite> m_boosts;
	Animation m_animation;
	uint32_t m_level_rows = 20;
	uint32_t m_level_columns = 27;	

	struct input_event {

		struct mouse_event {

			sf::Vector2i position;
			bool left_button_pressed = false;
			bool right_button_pressed = false;
			bool wheel_button_pressed = false;

		};

		struct keyboard_event
		{
			InputKey key_pressed;
			bool isPressed = false;
			bool isReleased = false;
		};

		std::vector <mouse_event> mouse_events;
		std::vector <keyboard_event> keyboard_events;

	};

	input_event events;

	sf::Vector2f get_base_position();
	sf::Vector2f get_ai_base_position();
	sf::Vector2f get_player_position();
	ControllableTank& get_player_tank() { return m_player_tank; }
	sf::Vector2f separating_axis(const Tank& ai_tank, const Tank& player_tank, sf::Vector2f player_pos);
	
	void initialize(uint32_t window_width, uint32_t window_height);
	void initialize_game_menu(uint32_t window_width, uint32_t window_height);
	void initialize_game_start(uint32_t window_width, uint32_t window_height);
	void update();
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void process_input();
	void calibrate_pos(sf::Vector2f& tank_position);
	void calibrate_position_moving_north_or_west(float& tank_position_axis, sf::Vector2i corner_1, sf::Vector2i corner_2, int corner_calibrate_axis);
	void calibrate_position_moving_south_or_east(float& tank_position_axis, sf::Vector2i corner_1, sf::Vector2i corner_2, int corner_calibrate_axis);
	void calibrate_projectile(Projectile& proj);
	void projectile_shoot(Tank& tank);
	void delete_projectile(Projectile& proj);
	void push_input_event(InputEvent &event);
	void input_event(InputKey buttonType, bool buttonPressed, sf::Vector2i pos, InputEvent& event, InputEvent::Type eventType);
	void teleport();
	void update_teleport_timer();
	void initialize_teleport_timer();

	~Game();
	enum game_state {
		gs_menu,
		gs_game_start,
		gs_win,
		gs_lose
	};
	game_state m_game_state;
	using input_array = std::array<bool, to_index(InputKey::Size)>;
	input_array m_input_state;
	int count_inputs(input_array inputs);
	game_state getGameState() const {
		return m_game_state;
	}

private:

	AudioObserver audioObserver;
	AnimationObserver animationObserver;
	InputEventQueue m_event_queue;
		
	uint32_t m_game_win_width;
	uint32_t m_game_win_height;

	std::vector <Command*> m_commands;
	ControllableTank m_player_tank;	

	Base m_player_base{ 5, 1 };
	Base m_ai_base{ 5, 0 };

	std::vector <Projectile> m_projectile_vector;
	
	std::vector <sf::Vector2f> m_ai_spawn_pos{sf::Vector2f((13*32) + 16, (2*32) + 16), 
		sf::Vector2f((2 * 32) + 16, (8 * 32) + 16), 
		sf::Vector2f((20 * 32) + 16, (13 * 32) + 16) };
	
	float m_tank_offset = 16;
	float m_base_offset_x = 24;
	float m_base_offset_y = 28;	
	
	sf::Texture m_background_tex;
	sf::Texture m_start_button_tex;
	sf::RectangleShape m_menu_background;
	sf::RectangleShape m_game_background;
	sf::RectangleShape m_start_button;
	sf::RectangleShape m_player_life;
	sf::Texture m_life_texture;
	sf::Text m_life_text;
	sf::RectangleShape m_kill_count_icon;
	sf::Texture m_kill_count_texture;
	sf::Text m_kill_count_text;
	sf::Text m_win_lose_text;
	sf::Text m_teleport_timer_text;
	sf::RectangleShape m_replay_button;
	sf::Texture* m_replay_button_tex;
	sf::Font m_game_font;

	bool m_teleport_available = true;
	const std::uint32_t m_teleport_cooldown = 10;
	std::chrono::system_clock::time_point m_teleport_start_time{};
	std::chrono::time_point<std::chrono::system_clock> m_time{ std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> m_start_time{ std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> start_animation_time = std::chrono::system_clock::now();
	std::chrono::duration<float> m_total_time{ 0 };
	std::chrono::duration<float> m_dt{ 0 };
	std::chrono::duration<float> m_boost_spawn_time{ 0 };
	//bool m_first_bullet_shot = false;
	bool m_first_ai_bullet_shot = false;
	//std::chrono::duration<float> m_last_projectile_shot{0};
	std::chrono::duration<float> m_last_ai_projectile_shot{ 0 };
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen{ rd() }; // seed the generator
	std::uniform_int_distribution<> distx{ 1, 26 }; // define the range
	std::uniform_int_distribution<> disty{ 1, 19 }; // define the range
	sf::Vector2f random_spawn_point();
};

