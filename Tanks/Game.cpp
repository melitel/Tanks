#include "Game.h"
#include "FireCommand.h"
#include <sstream>

Game* g_Game = nullptr;
PowerUp* m_life_boost = new LifeBoostPowerUp();
PowerUp* m_speed_boost = new SpeedBoostPowerUp();

void Game::initialize(uint32_t window_width, uint32_t window_height)
{
	m_game_state = gs_menu;

	m_game_win_width = window_width;
	m_game_win_height = window_height;

	initialize_game_menu(window_width, window_height);
}

void Game::initialize_game_menu(uint32_t window_width, uint32_t window_height)
{	
	m_menu_background.setSize(sf::Vector2f((float)m_game_win_width, (float)m_game_win_height));
	m_menu_background.setPosition(sf::Vector2f(0.f, 0.f));
	if (!m_background_tex.loadFromFile("background.jpg"))
	{
		std::cout << "Error";
	}
	m_menu_background.setTexture(&m_background_tex);

	m_start_button.setSize(sf::Vector2f(225.f, 90.f));
	m_start_button.setPosition(sf::Vector2f(310.f, 200.f));
	if (!m_start_button_tex.loadFromFile("startbutton.png"))
	{
		std::cout << "Error";
	}
	m_start_button.setTexture(&m_start_button_tex);
}

void Game::initialize_game_start(uint32_t window_width, uint32_t window_height)
{		
	m_input_state.fill(false);
	m_boosts.clear();
	m_ai_tanks.clear();
	m_map = std::make_unique<TileMap>();
	m_map->read_level_from_file("level.txt");

	if (!m_map->load("tileset.png"))
	{
		std::cout << "Error";
	}

	if (!m_game_font.loadFromFile("arial.ttf"))
	{
		//error::
	}

	m_player_tank.initialize(sf::Vector2f(432.f, 592.f));

	// Attach observers to the tank
	m_player_tank.addObserver(&audioObserver);
	m_player_tank.addObserver(&animationObserver);

	m_ai_tanks.push_back(AiTank("aitank.png", 1, 10, 1, 60.f, 0, AiTank::attack));
	m_ai_tanks.back().initialize(m_ai_spawn_pos[1]);
	m_ai_tanks.push_back(AiTank("aitank.png", 1, 10, 1, 60.f, 0, AiTank::defence));
	m_ai_tanks.back().initialize(m_ai_spawn_pos[0]);

	m_game_background.setSize(sf::Vector2f((float)m_game_win_width, (float)m_game_win_height));
	m_game_background.setPosition(sf::Vector2f(0.f, 0.f));
	m_game_background.setFillColor(sf::Color::Yellow);
	
	m_player_life.setSize(sf::Vector2f(32.f, 32.f));
	m_player_life.setPosition(sf::Vector2f(32.f, 0.f));

	if (!m_life_texture.loadFromFile("heart.png"))
	{
		std::cout << "Error";
	}
	m_player_life.setTexture(&m_life_texture);

	m_life_text.setCharacterSize(25);
	m_life_text.setFillColor(sf::Color::White);
	m_life_text.setPosition(sf::Vector2f(70.f, 0.f));

	uint32_t player_life_count = m_player_tank.get_life();
	// Convert integer to string
	std::stringstream pl;
	pl << player_life_count;
	std::string playerLifeCountString = pl.str();

	m_life_text.setString(playerLifeCountString);
	m_life_text.setFont(m_game_font);

	m_kill_count_icon.setSize(sf::Vector2f(32.f, 32.f));
	m_kill_count_icon.setPosition(sf::Vector2f(760.f, 0.f));
	if (!m_kill_count_texture.loadFromFile("killcount.png"))
	{
		std::cout << "Error";
	}
	m_kill_count_icon.setTexture(&m_kill_count_texture);
	m_kill_count_text.setCharacterSize(25);
	m_kill_count_text.setFillColor(sf::Color::White);
	m_kill_count_text.setPosition(sf::Vector2f(800.f, 0.f));
	m_kill_count_text.setString("0");
	m_kill_count_text.setFont(m_game_font);		

	/*for (int i = 0; i < m_ai_tanks.size(); ++i) {		
		m_ai_tanks[i].initialize(m_ai_spawn_pos[0]);
	}*/
	m_player_base.initialize(sf::Vector2f(432.f, 592.f), "base.png");
	m_ai_base.initialize(sf::Vector2f(432.f, 80.f), "base.png");
	m_player_base.rotate_base(sf::degrees(180.f));	
	
	g_Game = this;
}

void Game::update()
{
	std::chrono::time_point t = std::chrono::system_clock::now();
	m_dt = t - m_time;
	m_time = t;
	m_total_time = t - m_start_time;
	float delta = std::min(m_dt.count(), 1.f / 30.f);	
	int total_time_seconds = std::chrono::duration_cast<std::chrono::seconds>(m_total_time).count();

	sf::FloatRect ai_base_bounds = m_ai_base.get_bounds();
	sf::Vector2f ai_base_position = m_ai_base.get_position();

	sf::FloatRect player_tank_bounds = m_player_tank.get_tank_bounds();
	sf::Vector2f player_tank_position = m_player_tank.get_position();

	sf::FloatRect player_base_bounds = m_player_base.get_bounds();
	sf::Vector2f player_base_position = m_player_base.get_position();

	if (m_game_state == game_state::gs_game_start) {

		m_player_tank.update(delta, 0);		

		if (!m_ai_tanks.empty()) {
			for (int i = 0; i < m_ai_tanks.size(); ++i) {
				m_ai_tanks[i].update(delta, i);
			}
		}

		if (total_time_seconds % 10 == 0 && m_boosts.empty() && total_time_seconds != 0) {
			
			int x = std::rand() % 101;

			if (x % 2 == 0) {
				sf::Vector2f position = random_spawn_point();
				m_boosts.push_back(BoostSprite("speedboost.png", 2, position));
				m_boost_spawn_time = m_total_time;
			}
			else {
				sf::Vector2f position = random_spawn_point();
				m_boosts.push_back(BoostSprite("heart.png", 1, position));
				m_boost_spawn_time = m_total_time;
			}		
		}
		if ((m_total_time - m_boost_spawn_time) >= std::chrono::seconds{ 5 }) {
			m_boosts.clear();
		}

		if (!m_boosts.empty()) {
			sf::FloatRect boost_bounds = m_boosts[0].get_bounds();
			uint32_t boost_id = m_boosts[0].get_boost_id();
		
			if (player_tank_bounds.findIntersection(boost_bounds) && boost_id == 1) {
				m_life_boost->activate(&m_player_tank);
				uint32_t player_life = m_player_tank.get_life();
				// Convert integer to string
				std::stringstream pl;
				pl << player_life;
				std::string playerLifeString = pl.str();
				m_life_text.setString(playerLifeString);
				m_boosts.clear();
			}
			if (player_tank_bounds.findIntersection(boost_bounds) && boost_id == 2) {
				m_speed_boost->activate(&m_player_tank);
				m_boosts.clear();
			}
		}
	}
	if (m_game_state == gs_win) {

		m_win_lose_text.setCharacterSize(75);
		m_win_lose_text.setFillColor(sf::Color::Black);
		m_win_lose_text.setPosition(sf::Vector2f(260.f, 150.f));
		m_win_lose_text.setString("You Won!");
		m_win_lose_text.setFont(m_game_font);

		m_replay_button.setSize(sf::Vector2f(225.f, 70.f));
		m_replay_button.setPosition(sf::Vector2f(310.f, 270.f));
		m_replay_button_tex = &TextureManager::GetTexture("replaybutton.png");
		m_replay_button.setTexture(m_replay_button_tex);
	}

	if (m_game_state == gs_lose) {
		m_win_lose_text.setCharacterSize(75);
		m_win_lose_text.setFillColor(sf::Color::Black);
		m_win_lose_text.setPosition(sf::Vector2f(260.f, 150.f));
		m_win_lose_text.setString("You Lose!");
		m_win_lose_text.setFont(m_game_font);

		m_replay_button.setSize(sf::Vector2f(225.f, 70.f));
		m_replay_button.setPosition(sf::Vector2f(310.f, 270.f));
		m_replay_button_tex = &TextureManager::GetTexture("replaybutton.png");
		m_replay_button.setTexture(m_replay_button_tex);
	}

	for (int j = 0; j < m_commands.size(); ++j) {
	
		m_commands[j]->execute();
	}

	m_commands.clear();

	for (int i = 0; i < m_projectile_vector.size(); i++)
	{
		Projectile& proj = m_projectile_vector[i];
		uint32_t proj_owner_team_id = proj.get_owner_team_id();
		float projectile_distance = proj.get_projectile_distance();

		sf::FloatRect projectile_bounds = m_projectile_vector[i].get_projectile_bounds();		

		calibrate_projectile(proj);

		if (proj_owner_team_id == 1) {
			proj.update(delta);
			projectile_distance = proj.distance_update(delta);
		}
		else {
			proj.update(delta);
			projectile_distance = proj.distance_update(delta);
		}

		if (projectile_distance <= 0)
		{
			delete_projectile(proj);
		}

		for (int j = 0; j < m_ai_tanks.size(); j++) {

			sf::FloatRect ai_tank_bounds = m_ai_tanks[j].get_tank_bounds();
			sf::Vector2f ai_tank_position = m_ai_tanks[j].get_position();			

			if (projectile_bounds.findIntersection(ai_tank_bounds) && proj_owner_team_id == 1) {

				m_animation.play(0, sf::Vector2f(ai_tank_position.x - m_tank_offset, ai_tank_position.y - m_tank_offset), "explosioneffect.png");
				delete_projectile(proj);
				m_player_tank.kill_count();

				uint32_t kills_count = m_player_tank.get_kill_count();

				// Convert integer to string
				std::stringstream ss;
				ss << kills_count;
				std::string killCountString = ss.str();
								
				m_kill_count_text.setString(killCountString);

				if (kills_count < 5) {

					if (m_ai_tanks[j].m_tank_attack_type == AiTank::defence) {
						m_ai_tanks.erase(m_ai_tanks.begin() + j);
						m_ai_tanks.push_back(AiTank("aitank.png", 1, 10, 1, 60.f, 0, AiTank::defence));
						m_ai_tanks.back().initialize(m_ai_spawn_pos[0]);
					}
					else {
						m_ai_tanks.erase(m_ai_tanks.begin() + j);
						m_ai_tanks.push_back(AiTank("aitank.png", 1, 10, 1, 60.f, 0, AiTank::attack));						
						sf::Vector2f position = random_spawn_point();
						m_ai_tanks.back().initialize(sf::Vector2f(position.x + m_tank_offset, position.y + m_tank_offset));
					}
				}
				else {
					m_ai_tanks.erase(m_ai_tanks.begin() + j);
				}
			}
		}

		if (projectile_bounds.findIntersection(ai_base_bounds) && proj_owner_team_id == 1) {
			m_animation.play(0, sf::Vector2f(ai_base_position.x - m_base_offset_x, ai_base_position.y - m_base_offset_y), "explosioneffect.png");
			m_ai_base.modify_life(-1);
			int ai_base_hp = m_ai_base.get_life();
			delete_projectile(proj);
			if (ai_base_hp == 0) {
				m_game_state = gs_win;
			}
		}
		if (projectile_bounds.findIntersection(player_tank_bounds) && proj_owner_team_id == 0) {
			m_player_tank.hitByBullet();
			//m_animation.play(0, sf::Vector2f(player_tank_position.x - m_tank_offset, player_tank_position.y - m_tank_offset), "explosioneffect.png");
			m_player_tank.modify_life(-1);
			uint32_t player_life = m_player_tank.get_life();
			// Convert integer to string
			std::stringstream pl;
			pl << player_life;
			std::string playerLifeString = pl.str();
			m_life_text.setString(playerLifeString);
			delete_projectile(proj);
			if (player_life == 0) {
				m_game_state = gs_lose;
			}
		}
		if (projectile_bounds.findIntersection(player_base_bounds) && proj_owner_team_id == 0) {
			m_animation.play(0, sf::Vector2f(player_base_position.x - m_base_offset_x, player_base_position.y - m_base_offset_y), "explosioneffect.png");
			m_player_base.modify_life(-1);
			int player_base_hp = m_player_base.get_life();
			delete_projectile(proj);
			if (player_base_hp == 0) {
				m_game_state = gs_lose;
			}
		}
	}

	m_animation.update(delta);
}

void Game::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->clear(sf::Color::White);

	if (m_game_state == game_state::gs_menu)
	{		
		window->draw(m_menu_background);
		window->draw(m_start_button);
	}
	if (m_game_state == game_state::gs_game_start)
	{	
		window->draw(*m_map);
		window->draw(m_player_life);
		window->draw(m_kill_count_icon);
		window->draw(m_kill_count_text);
		window->draw(m_life_text);
		if (!m_boosts.empty())
		{
			for (int j = 0; j < m_boosts.size(); ++j)
			{
				m_boosts[j].draw(window);
			}
		}
		m_player_base.draw(window);
		m_ai_base.draw(window);
		m_player_tank.draw(window);
		if (!m_ai_tanks.empty()) {
			for (int i = 0; i < m_ai_tanks.size(); ++i) {
				m_ai_tanks[i].draw(window);
			}			
		}
		m_animation.draw(window);		
	}
	if (m_game_state == gs_win || m_game_state == gs_lose) {
		window->draw(m_menu_background);
		window->draw(m_win_lose_text);
		window->draw(m_replay_button);
	}

	if (!m_projectile_vector.empty())
	{
		for (int i = 0; i < m_projectile_vector.size(); ++i)
		{
			m_projectile_vector[i].draw(window);
		}
	}

	window->display();
}

void Game::process_input()
{
	InputEvent event;
	sf::FloatRect start_bounds = m_start_button.getGlobalBounds();
	sf::FloatRect replay_bounds = m_replay_button.getGlobalBounds();

	// Process the event queue
	while (m_event_queue.hasEvents()) {

		event = m_event_queue.popEvent();

		switch (event.type) {
		case InputEvent::Type::MouseClick:
			// ... Handle mouse click event ...
			if (start_bounds.contains(sf::Vector2f(event.position)))
			{
				m_game_state = gs_game_start;
				initialize_game_start(m_game_win_width, m_game_win_height);
			}
			if (replay_bounds.contains(sf::Vector2f(event.position)))
			{
				m_game_state = gs_menu;	
				initialize_game_menu(m_game_win_width, m_game_win_height);
			}
			break;
		case InputEvent::Type::ButtonClick:
			// ... Handle key pressed event ...
			if (event.buttonType == 0) {
				if (event.buttonPressed == true) {
					m_input_state[input_event::keyboard_event::k_W] = true;
				}
				else {
					m_input_state[input_event::keyboard_event::k_W] = false;
				}
			}
			if (event.buttonType == 1) {
				if (event.buttonPressed == true) {
					m_input_state[input_event::keyboard_event::k_A] = true;
				}
				else {
					m_input_state[input_event::keyboard_event::k_A] = false;
				}
			}
			if (event.buttonType == 2) {
				if (event.buttonPressed == true) {
					m_input_state[input_event::keyboard_event::k_S] = true;
				}
				else {
					m_input_state[input_event::keyboard_event::k_S] = false;
				}
			}
			if (event.buttonType == 3) {
				if (event.buttonPressed == true) {
					m_input_state[input_event::keyboard_event::k_D] = true;
				}
				else {
					m_input_state[input_event::keyboard_event::k_D] = false;
				}
			}
			if (event.buttonType == 4) {
				Command* command;
				command = new FireCommand;
				m_commands.push_back(command);
			}

			break;		
		}
	}
}

int Game::count_inputs(input_array inputs)
{
	int numberOfTrue = 0;

	for (int i=0; i < inputs.size(); ++i)
	{
		if (inputs[i])
		{
			if (i == 4)
			{
				continue;
			}
			else {			
				++numberOfTrue;
			}
		}
	}

	return numberOfTrue;
}

sf::Vector2f Game::random_spawn_point()
{
	sf::Vector2f spawn_point;

	int maxAttempts = 100; // Maximum number of attempts to find a walkable tile
	int attempt = 0;

	float default_x = (13 * 32);
	float default_y = (2 * 32);

	sf::Vector2u tile_size = m_map->get_tile_size();

	do {

		int x = distx(gen);
		int y = disty(gen);
		
		bool walkable = m_map->get_tile_walkable_by_indices(x, y);

		if (walkable) {
			spawn_point.x = x * tile_size.x; // Multiply by tile width to get the actual position
			spawn_point.y = y * tile_size.y; // Multiply by tile height to get the actual position
			spawn_point = sf::Vector2f(spawn_point.x, spawn_point.y);
			break; // Found a walkable tile, exit the loop
		}

		attempt++;
	} while (attempt < maxAttempts);

	// If no walkable tile was found after the maximum number of attempts, spawn at a default position
	if (attempt >= maxAttempts) {
		spawn_point = sf::Vector2f(default_x, default_y); // Set the default spawn position
	}

	return spawn_point;
}


void Game::calibrate_pos(sf::Vector2f& tank_position)
{		
	sf::Vector2f tank_direction = m_player_tank.get_direction();
	sf::Vector2i top_left_corner = m_map->get_tile_coordinates(int(tank_position.x - m_tank_offset), int(tank_position.y - m_tank_offset));
	sf::Vector2i bot_right_corner = m_map->get_tile_coordinates(int(tank_position.x + m_tank_offset), int(tank_position.y + m_tank_offset));
	sf::Vector2i top_right_corner = m_map->get_tile_coordinates(int(tank_position.x + m_tank_offset), int(tank_position.y - m_tank_offset));
	sf::Vector2i bot_left_corner = m_map->get_tile_coordinates(int(tank_position.x - m_tank_offset), int(tank_position.y + m_tank_offset));

	if (tank_direction == sf::Vector2f(0.f, -1.f))
	{
		if (tank_position.y < (0 + m_tank_offset))
		{
			tank_position.y = float(0 + (m_tank_offset + 1));
		}
		else {
			calibrate_position_moving_north_or_west(tank_position.y, top_left_corner, top_right_corner, top_left_corner.y);		
		}
	}
	else if (tank_direction == sf::Vector2f(-1.f, 0.f))
	{
		if (tank_position.x < (0 + m_tank_offset))
		{
			tank_position.x = float(0 + (m_tank_offset + 1));
		}
		else {
			calibrate_position_moving_north_or_west(tank_position.x, top_left_corner, bot_left_corner, top_left_corner.x);
		}
	}
	else if (tank_direction == sf::Vector2f(1.f, 0.f))
	{
		if (tank_position.x > (m_game_win_width - (m_tank_offset + 1)))
		{
			tank_position.x = float(m_game_win_width - (m_tank_offset + 1));
		}
		else {
			calibrate_position_moving_south_or_east(tank_position.x, bot_right_corner, top_right_corner, bot_right_corner.x);
		}
	}
	else if (tank_direction == sf::Vector2f(0.f, 1.f))
	{
		if (tank_position.y > (m_game_win_height - (m_tank_offset + 1)))
		{
			tank_position.y = float(m_game_win_height - (m_tank_offset + 1));
		}
		else {
			calibrate_position_moving_south_or_east(tank_position.y, bot_right_corner, bot_left_corner, bot_right_corner.y);
		}
	}
}

void Game::calibrate_position_moving_north_or_west(float& tank_position_axis, sf::Vector2i corner_1, sf::Vector2i corner_2, int corner_calibrate_axis) {

	bool walkable_left = m_map->get_tile_walkable_by_indices(corner_1.x, corner_1.y);

	if (!walkable_left)
	{
		tank_position_axis = corner_calibrate_axis * 32 + 32 + (m_tank_offset + 1);
	}
	else {

		//checking second corner coordinates position
		bool walkable_right = m_map->get_tile_walkable_by_indices(corner_2.x, corner_2.y);

		if (!walkable_right)
		{
			tank_position_axis = corner_calibrate_axis * 32 + 32 + (m_tank_offset + 1);
		}
	}
}

void Game::calibrate_position_moving_south_or_east(float& tank_position_axis, sf::Vector2i corner_1, sf::Vector2i corner_2, int corner_calibrate_axis) {

	//checking first corner coordinates position
	bool walkable_bot_right = m_map->get_tile_walkable_by_indices(corner_1.x, corner_1.y);

	if (!walkable_bot_right)
	{
		tank_position_axis = corner_calibrate_axis * 32 - (m_tank_offset + 1);
	}
	else
	{
		//checking second corner coordinates position
		bool walkable_bot_left = m_map->get_tile_walkable_by_indices(corner_2.x, corner_2.y);

		if (!walkable_bot_left)
		{
			tank_position_axis = corner_calibrate_axis * 32 - (m_tank_offset + 1);
		}
	}
}

void Game::calibrate_projectile(Projectile& proj)
{
	sf::Vector2f proj_position = proj.get_position();
	bool piercable = m_map->get_tile_pierceable_by_coordinates(proj_position.x, proj_position.y);

	if (!piercable) {
	
		m_animation.play(0, sf::Vector2f(proj_position.x, proj_position.y), "explosioneffect.png");
		delete_projectile(proj);
	}
}

sf::Vector2f Game::get_base_position()
{
	sf::Vector2f base_position = m_player_base.get_position();
	return base_position;
}

sf::Vector2f Game::get_ai_base_position()
{
	sf::Vector2f ai_base_position = m_ai_base.get_position();
	return ai_base_position;
}

sf::Vector2f Game::get_player_position()
{
	sf::Vector2f player_position = m_player_tank.get_position();
	return player_position;
}

void Game::projectile_shoot(Tank& tank)
{
	Projectile projectile(&tank);

	if (!tank.if_first_bullet_shot()) {
		tank.first_bullet_shot();
		tank.last_projectile_shot_time(m_total_time);

		m_projectile_vector.push_back(std::move(projectile));
	}
	else {

		std::chrono::duration<float> m_last_projectile_shot = tank.when_last_projectile_shot();

		if ((m_total_time - m_last_projectile_shot) >= std::chrono::seconds{ 3 }) {

			tank.last_projectile_shot_time(m_total_time);
			m_projectile_vector.push_back(std::move(projectile));
		}
	}
}

void Game::delete_projectile(Projectile& proj)
{
	std::swap(proj, m_projectile_vector.back());
	m_projectile_vector.pop_back();
}

void Game::push_input_event(InputEvent& event)
{
	m_event_queue.pushEvent(event);
}

void Game::input_event(int buttonType, bool buttonPressed, sf::Vector2i pos, InputEvent& event, InputEvent::Type eventType)
{
	event.type = eventType;
	event.buttonType = buttonType;
	event.buttonPressed = buttonPressed;
	event.position = pos;
}

sf::Vector2f Game::separating_axis(const Tank& ai_tank, const Tank& player_tank, sf::Vector2f player_pos) {
	
	sf::Vector2f ai_pos = ai_tank.get_position();
	sf::Vector2f player_dir = player_tank.get_direction();
	sf::Vector2f mtd (0.f, 0.f);
	auto b = ai_tank.get_shape().getGlobalBounds();

	auto check_collision = [&]() {
		sf::Vector2f player_pos_topleft = player_pos - sf::Vector2f(m_tank_offset, m_tank_offset);
		sf::Vector2f ai_pos_topleft = ai_pos - sf::Vector2f(m_tank_offset, m_tank_offset);
		const float tank_size = m_tank_offset * 1.8f;
		sf::FloatRect bounds_player(player_pos_topleft, sf::Vector2f(tank_size, tank_size));
		sf::FloatRect bounds_ai(ai_pos_topleft, sf::Vector2f(tank_size, tank_size));
		
		return bounds_player.findIntersection(bounds_ai);
	};

	if (check_collision()) {
		sf::Vector2f gap = player_pos - ai_pos;
		float dp = player_dir.dot(gap);

		sf::Vector2f projected_vector = player_dir * dp;

		float length = projected_vector.length();
		float overlap = length - m_tank_offset * 2;

		if (overlap < 0) {

			mtd = player_dir * overlap;
		}
	}

	return mtd;
}

Game::~Game()
{
	g_Game = nullptr;
}


