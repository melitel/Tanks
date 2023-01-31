#include "Game.h"

Game* g_Game = nullptr;

void Game::initialize(uint32_t window_width, uint32_t window_height, std::unique_ptr<sf::RenderWindow> &window)
{
	m_input_state.fill(false);
	m_tank_movement_direction = sf::Vector2f(0.f, 0.f);
	
	m_game_win_width = window_width;
	m_game_win_height = window_height;
	m_map = std::make_unique<TileMap>();
	m_game_state = gs_menu;

	m_menu_background.setSize(sf::Vector2f((float)m_game_win_width, (float)m_game_win_height));
	m_menu_background.setPosition(sf::Vector2f(0.f, 0.f));
	if (!m_background_tex.loadFromFile("background.jpg"))
	{
		std::cout << "Error";
	}
	m_menu_background.setTexture(&m_background_tex);

	m_game_background.setSize(sf::Vector2f((float)m_game_win_width, (float)m_game_win_height));
	m_game_background.setPosition(sf::Vector2f(0.f, 0.f));
	m_game_background.setFillColor(sf::Color::Yellow);

	m_start_button.setSize(sf::Vector2f(225.f, 90.f));
	m_start_button.setPosition(sf::Vector2f(310.f, 200.f));
	if (!m_start_button_tex.loadFromFile("startbutton.png"))
	{
		std::cout << "Error";
	}
	m_start_button.setTexture(&m_start_button_tex);		

	m_map->read_level_from_file("level.txt");

	if (!m_map->load("tileset.png"))
	{
		std::cout << "Error";
	}

	m_player_tank.initialize(sf::Vector2f(432.f, 560.f), "commontankup.png");
	m_ai_tank.initialize(sf::Vector2f(432.f, 48.f), "aitank.png");
	
	g_Game = this;

}

int first_button_index = -2;
int second_button_index = -2;
int third_button_index = -2;

void Game::update()
{
	std::chrono::time_point t = std::chrono::system_clock::now();
	m_dt = t - m_time;
	m_time = t;
	m_total_time = t - m_start_time;
	float delta = std::min(m_dt.count(), 1.f / 30.f);

	int inputs_count = count_inputs(m_input_state);

	if (inputs_count == 0)
	{
		first_button_index = -2;
	}
	if (inputs_count == 1) {
		
		second_button_index = -2;
		
		if (m_input_state[input_event::keyboard_event::k_W] == true) 
		{
			first_button_index = 0;

			if (m_tank_movement_direction == sf::Vector2f(-1.f, 0.f) || m_tank_movement_direction == sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(0.f));
			}
			
			m_tank_movement_direction = sf::Vector2f(0.f, -1.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (m_input_state[input_event::keyboard_event::k_A] == true)
		{
			first_button_index = 1;

			if (m_tank_movement_direction != sf::Vector2f(-1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(-90.f));
			}			

			m_tank_movement_direction = sf::Vector2f(-1.f, 0.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (m_input_state[input_event::keyboard_event::k_S] == true)
		{
			first_button_index = 2;

			if (m_tank_movement_direction == sf::Vector2f(-1.f, 0.f) || m_tank_movement_direction == sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(0.f));
			}			

			m_tank_movement_direction = sf::Vector2f(0.f, 1.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (m_input_state[input_event::keyboard_event::k_D] == true)
		{
			first_button_index = 3;

			if (m_tank_movement_direction != sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(90.f));
			}			

			m_tank_movement_direction = sf::Vector2f(1.f, 0.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
	}
	if (inputs_count == 2) {

		int true_found = -1;
		int action_to_do = -1;

		if (first_button_index >= 0 && second_button_index >= 0 && third_button_index >= 0)
		{
			if (!m_input_state[first_button_index])
			{
				first_button_index = second_button_index;
				second_button_index = third_button_index;
				third_button_index = -2;
				action_to_do = second_button_index;
			}
			else if (!m_input_state[second_button_index])
			{
				second_button_index = third_button_index;
				third_button_index = -2;
				action_to_do = second_button_index;
			}
			else if (!m_input_state[third_button_index])
			{
				third_button_index = -2;
				action_to_do = second_button_index;
			}
			
		}
		else 
		{
			for (int i = 0; i < m_input_state.size(); ++i)
			{
				if (m_input_state[i])
				{
					true_found = i;

					if (true_found != first_button_index) {
						action_to_do = true_found;
						second_button_index = action_to_do;

					}
				}
			}
		}		

		if (action_to_do == 0) 
		{
			if (m_tank_movement_direction == sf::Vector2f(-1.f, 0.f) || m_tank_movement_direction == sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(0.f));
			}

			m_tank_movement_direction = sf::Vector2f(0.f, -1.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (action_to_do == 1)
		{			
			if (m_tank_movement_direction != sf::Vector2f(-1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(-90.f));
			}
			
			m_tank_movement_direction = sf::Vector2f(-1.f, 0.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (action_to_do == 2)
		{	
			if (m_tank_movement_direction == sf::Vector2f(-1.f, 0.f) || m_tank_movement_direction == sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(0.f));
			}

			m_tank_movement_direction = sf::Vector2f(0.f, 1.f);
			m_projectile_movement_direction = m_tank_movement_direction;
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		if (action_to_do == 3)
		{		
			if (m_tank_movement_direction != sf::Vector2f(1.f, 0.f))
			{
				m_player_tank.rotate_tank(sf::degrees(90.f));
			}

			m_tank_movement_direction = sf::Vector2f(1.f, 0.f);
			m_player_tank.move_tank(m_tank_movement_direction, delta);
		}
		
	}
	if (inputs_count > 2) {

		int true_found = -1;

		for (int i = 0; i < m_input_state.size(); ++i)
		{
			if (m_input_state[i])
			{
				true_found = i;

				if (true_found != first_button_index && true_found != second_button_index) {
					
					third_button_index = true_found;

				}
			}
		}

		//change button index to 2nd button pressed, so when 3d button released to continue moving in second button direction
		m_player_tank.move_tank(sf::Vector2f(0.f, 0.f), delta);
	}

	m_animation.update(delta);
	
	if (!m_projectile_vector.empty())
	{
		m_projectile_distance = 64;

		for (int i = 0; i < m_projectile_vector.size();)
		{
			Projectile& proj = m_projectile_vector[i];
			proj.update(m_projectile_movement_direction, delta);			
			m_projectile_distance = proj.distance_update(m_projectile_movement_direction, delta);
			sf::FloatRect projectile_bounds = m_projectile_vector[i].get_projectile_bounds();
			sf::FloatRect ai_tank_bounds = m_ai_tank.get_tank_bounds();
			sf::Vector2f ai_tank_position = m_ai_tank.get_position();
			
			if (m_projectile_distance <= 0)
			{
				std::swap(proj, m_projectile_vector.back());
				
				m_projectile_vector.pop_back();
			}
			else if (projectile_bounds.findIntersection(ai_tank_bounds)) {
				
				m_animation.play(0, sf::Vector2f(ai_tank_position.x - m_tank_offset, ai_tank_position.y - m_tank_offset), "explosioneffect.png");
				std::swap(proj, m_projectile_vector.back());
				m_projectile_vector.pop_back();
			}
			else {
				
				i++;
			
			}
			
			
			
		}
		
	}

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
		m_player_tank.draw(window);
		m_ai_tank.draw(window);
		m_animation.draw(window);
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

void Game::gather_input(input_event events)
{	
	sf::FloatRect start_bounds = m_start_button.getGlobalBounds();
	
	if (!events.mouse_events.empty() && m_game_state == gs_menu)
	{
		for (int i = 0; i < events.mouse_events.size(); ++i)
		{
			if (events.mouse_events[i].left_button_pressed)
			{
				if (start_bounds.contains((sf::Vector2f)(events.mouse_events[i].position)))
				{
					m_game_state = gs_game_start;
				}
			}
		}
	}
	

	if (!events.keyboard_events.empty() && m_game_state == gs_game_start)
	{		

		for (int i = 0; i < events.keyboard_events.size(); ++i)
		{
			if (events.keyboard_events[i].isPressed && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_W)
			{				
				m_input_state[input_event::keyboard_event::k_W] = true;			
			}
			if (events.keyboard_events[i].isPressed && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_D)
			{
				m_input_state[input_event::keyboard_event::k_D] = true;
			}
			if (events.keyboard_events[i].isPressed && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_A)
			{
				m_input_state[input_event::keyboard_event::k_A] = true;
			}
			if (events.keyboard_events[i].isPressed && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_S)
			{
				m_input_state[input_event::keyboard_event::k_S] = true;
			}
			if (events.keyboard_events[i].isPressed && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_Space)
			{
				Projectile projectile(&m_player_tank);
				m_projectile_vector.push_back(std::move(projectile));
			}
			if (events.keyboard_events[i].isReleased && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_W)
			{
				m_input_state[input_event::keyboard_event::k_W] = false;
			}
			if (events.keyboard_events[i].isReleased && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_A)
			{
				m_input_state[input_event::keyboard_event::k_A] = false;
			}
			if (events.keyboard_events[i].isReleased && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_S)
			{
				m_input_state[input_event::keyboard_event::k_S] = false;
			}
			if (events.keyboard_events[i].isReleased && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_D)
			{
				m_input_state[input_event::keyboard_event::k_D] = false;
			}
			if (events.keyboard_events[i].isReleased && events.keyboard_events[i].key_pressed == input_event::keyboard_event::k_Space)
			{
				m_input_state[input_event::keyboard_event::k_Space] = false;
			}
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

void Game::calibrate_pos(sf::Vector2f& tank_position)
{		
	bool tile_walkable = false;
	sf::Vector2f tile_coordinates;

	if (m_tank_movement_direction == sf::Vector2f(0.f, -1.f))
	{
		//checking top left corner coordinates position
		tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x - m_tank_offset), (tank_position.y - m_tank_offset));
		tile_coordinates = m_map->get_tile_coordinates((tank_position.x - m_tank_offset), (tank_position.y - m_tank_offset));
		
		if (!tile_walkable)
		{
			tank_position.y = tile_coordinates.y*32 + 32 + m_tank_offset;
		}
		else {
			//checking top right corner coordinates position
			tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x + m_tank_offset), (tank_position.y - m_tank_offset));

			if (!tile_walkable)
			{
				tank_position.y = tile_coordinates.y * 32 + 32 + m_tank_offset;
			}		
		}
	}
	else if (m_tank_movement_direction == sf::Vector2f(-1.f, 0.f))
	{
		//checking top left corner coordinates position
		tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x - m_tank_offset), (tank_position.y - m_tank_offset));
		tile_coordinates = m_map->get_tile_coordinates((tank_position.x - m_tank_offset), (tank_position.y - m_tank_offset));

		if (!tile_walkable)
		{
			tank_position.x = tile_coordinates.x * 32 + 32 + m_tank_offset;
		}
		else {
			//checking bottom left corner coordinates position
			tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x - m_tank_offset), (tank_position.y + m_tank_offset));

			if (!tile_walkable)
			{
				tank_position.x = tile_coordinates.x * 32 + 32 + m_tank_offset;
			}
		}
	}
	else if (m_tank_movement_direction == sf::Vector2f(1.f, 0.f))
	{
		//checking bottom right corner coordinates position
		tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x + m_tank_offset), (tank_position.y + m_tank_offset));
		tile_coordinates = m_map->get_tile_coordinates((tank_position.x + m_tank_offset), (tank_position.y + m_tank_offset));

		if (!tile_walkable)
		{
			tank_position.x = tile_coordinates.x * 32 - m_tank_offset;
		}
		else {
			//checking top right corner coordinates position
			tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x + m_tank_offset), (tank_position.y - m_tank_offset));

			if (!tile_walkable)
			{
				tank_position.x = tile_coordinates.x * 32 - m_tank_offset;
			}
		}

	}
	else if (m_tank_movement_direction == sf::Vector2f(0.f, 1.f))
	{
		//checking bottom right corner coordinates position
		tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x + m_tank_offset), (tank_position.y + m_tank_offset));
		tile_coordinates = m_map->get_tile_coordinates((tank_position.x + m_tank_offset), (tank_position.y + m_tank_offset));

		if (!tile_walkable)
		{
			tank_position.y = tile_coordinates.y * 32 - m_tank_offset;
		}
		else {
			//checking bottom left corner coordinates position
			tile_walkable = m_map->get_tile_walkable_by_coordinates((tank_position.x - m_tank_offset), (tank_position.y + m_tank_offset));

			if (!tile_walkable)
			{
				tank_position.y = tile_coordinates.y * 32 - m_tank_offset;
			}
		}
	}

	if (tank_position.y < (0 + m_tank_offset))
	{
		tank_position.y = 0 + m_tank_offset;
	}
	if (tank_position.x > (m_game_win_width - m_tank_offset))
	{
		tank_position.x = m_game_win_width - m_tank_offset;
	}
	if (tank_position.x < (0 + m_tank_offset))
	{
		tank_position.x = 0 + m_tank_offset;
	}
	if(tank_position.y > (m_game_win_height - m_tank_offset))
	{
		tank_position.y = m_game_win_height - m_tank_offset;
	}

}

Game::~Game()
{
	g_Game = nullptr;
}


