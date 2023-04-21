#include "AiTank.h"
#include <iostream>
#include "Game.h"

extern Game* g_Game;

void AiTank::initialize(const sf::Vector2f& pos, const std::string& name)
{
	Tank::initialize(pos, name);

	m_ai_status = moving_to_enemy_base;

}

void AiTank::change_status(ai_status status)
{	
	if (m_ai_status != status) {
		std::cout << status << std::endl;
	}
	m_ai_status = status;
}

void AiTank::update(float dt) {

	sf::Vector2f ai_tank_position = m_tank.getPosition();
	sf::Vector2f player_tank_position = g_Game->get_player_position();
	sf::Vector2f player_base_position = g_Game->get_base_position();
	sf::Vector2i ai_tank_tile_coord = sf::Vector2i(((ai_tank_position.x - m_offset) / 32), ((ai_tank_position.y - m_offset) / 32));
	sf::Vector2i player_tank_tile_coord = sf::Vector2i((player_tank_position.x / 32),(player_tank_position.y / 32));
	sf::Vector2i player_base_tile_coord = sf::Vector2i((player_base_position.x / 32),(player_base_position.y / 32));

	processing_state(ai_tank_tile_coord, player_tank_tile_coord, player_base_tile_coord);
	change_state(ai_tank_tile_coord, player_tank_tile_coord, player_base_tile_coord);
	move_controller(dt);
}

void AiTank::get_path(int start_x, int start_y, int goal_x, int goal_y)
{
	m_path.clear();
	m_path = m_ai_brain.a_star(start_x, start_y, goal_x, goal_y);
}

void AiTank::move_tank(movement_direction direction, float delta){
	
	
}

void AiTank::move_controller(float delta)
{	
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f goal_coordinates = sf::Vector2f(m_path.back().x * 32, m_path.back().y * 32);

	sf::Vector2f tank_upper_left_coord = sf::Vector2f((p0.x - m_offset), (p0.y - m_offset));

	float comparison_epsilon = (1.f / 60.f) * m_move_speed;

		sf::Vector2f path_coordinates = sf::Vector2f(m_path[0].x * 32, m_path[0].y * 32);

		if ((abs(tank_upper_left_coord.x - path_coordinates.x) <= comparison_epsilon) && 
			(abs(tank_upper_left_coord.y - path_coordinates.y) <= comparison_epsilon)) {
		
			if ((abs(tank_upper_left_coord.x - goal_coordinates.x) <= comparison_epsilon) &&
				(abs(tank_upper_left_coord.y - goal_coordinates.y) <= comparison_epsilon)) {
			
				m_velocity = sf::Vector2f(0.f, 0.f);
			}
			else {
			
				if (m_path[1].movement_direction == BrainAtk::Node::direction::east) {

					m_tank.setRotation(sf::degrees(-90.f));
					m_velocity = sf::Vector2f(1.f, 0.f);
				}
				else if (m_path[1].movement_direction == BrainAtk::Node::direction::west) {
				
					m_tank.setRotation(sf::degrees(90.f));
					m_velocity = sf::Vector2f(-1.f, 0.f);
				}
				else if (m_path[1].movement_direction == BrainAtk::Node::direction::south) {
				
					m_tank.setRotation(sf::degrees(0.f));
					m_velocity = sf::Vector2f(0.f, 1.f);
				}
				else if (m_path[1].movement_direction == BrainAtk::Node::direction::north) {
				
					m_tank.setRotation(sf::degrees(-180.f));
					m_velocity = sf::Vector2f(0.f, -1.f);
				}
			}
		}	

	sf::Vector2f vel = m_velocity * m_move_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_direction = m_velocity;

	sf::Vector2f mtd = g_Game->separating_axis(g_Game->m_player_tank, g_Game->m_ai_tank, p1);

	m_tank.setPosition(p1 + mtd);
}

void AiTank::processing_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile)
{
	sf::Vector2f player_tank_pos = g_Game->get_player_position();
	sf::Vector2i player_tile_coord = sf::Vector2i(((player_tank_pos.x - m_offset) / 32), ((player_tank_pos.y - m_offset) / 32));

	if (m_ai_status == moving_to_enemy_base) {		

		get_path(ai_tank_tile.x, ai_tank_tile.y, player_base_tile.x, player_base_tile.y);

		//I use floor for base coordinates cause base tiles coordinates are (13.5 , 16.5) and we need to floor them in order to align with tank
		if (ai_tank_tile.x == player_base_tile.x && abs(ai_tank_tile.y - player_base_tile.y) <= 3) {
			
			g_Game->projectile_shoot();
		}
		if (ai_tank_tile.y == player_base_tile.y && abs(ai_tank_tile.x - player_base_tile.x) <= 3) {


			g_Game->projectile_shoot();
		}

	}
	if (m_ai_status == chasing_enemy_tank) {

		get_path(ai_tank_tile.x, ai_tank_tile.y, player_tank_tile.x, player_tank_tile.y);		
		
		if (ai_tank_tile.x == player_tile_coord.x && abs(ai_tank_tile.y - player_tile_coord.y) <= 3) {
			
			sf::Angle rotation = m_tank.getRotation();

			if (ai_tank_tile.y < player_tile_coord.y) {
				if (rotation != sf::degrees(0.f)) {
					m_tank.setRotation(sf::degrees(0.f));
				}
			}
			if (ai_tank_tile.y > player_tile_coord.y) {
				if (rotation != sf::degrees(-180.f)) {
					m_tank.setRotation(sf::degrees(-180.f));
				}
			}
			g_Game->projectile_shoot();
		}
		if (ai_tank_tile.y == player_tile_coord.y && abs(ai_tank_tile.x - player_tile_coord.x) <= 3) {
			
			sf::Angle rotation = m_tank.getRotation();

			if (ai_tank_tile.x < player_tile_coord.x) {
				if (rotation != sf::degrees(-90.f)) {
					m_tank.setRotation(sf::degrees(-90.f));
				}
			}
			if (ai_tank_tile.x > player_tile_coord.x) {
				if (rotation != sf::degrees(90.f)) {
					m_tank.setRotation(sf::degrees(90.f));
				}
			}
			g_Game->projectile_shoot();
		}
		
	}	

}


void AiTank::change_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile)
{
	//switch to chasing player mode
	if (ai_tank_tile.x == player_tank_tile.x && ai_tank_tile.y != player_tank_tile.y) {

		int tile_x = ai_tank_tile.x;

		if (ai_tank_tile.y > player_tank_tile.y) {

			bool view_through = true;

			for (int i = ai_tank_tile.y; i >= player_tank_tile.y; --i) {				

				view_through = g_Game->m_map->get_tile_view_through_by_indices(tile_x, i);

				if (!view_through) {
					break;
				}
			}

			if (view_through) {
				m_ai_status = chasing_enemy_tank;
			}

		}
		if (ai_tank_tile.y < player_tank_tile.y) {

			bool view_through = true;

			for (int i = ai_tank_tile.y; i <= player_tank_tile.y; ++i) {

				view_through = g_Game->m_map->get_tile_view_through_by_indices(tile_x, i);

				if (!view_through) {
					break;
				}
			}

			if (view_through) {

				m_ai_status = chasing_enemy_tank;
			}
		}
	}
	if (ai_tank_tile.y == player_tank_tile.y && ai_tank_tile.x != player_tank_tile.x) {

		int tile_y = ai_tank_tile.y;

		if (ai_tank_tile.x > player_tank_tile.x) {

			bool view_through = true;

			for (int i = ai_tank_tile.x; i >= player_tank_tile.x; --i) {

				view_through = g_Game->m_map->get_tile_view_through_by_indices(i, tile_y);

				if (!view_through) {
					break;
				}
			}

			if (view_through) {

				m_ai_status = chasing_enemy_tank;
			}

		}
		if (ai_tank_tile.x < player_tank_tile.x) {

			bool view_through = true;

			for (int i = ai_tank_tile.x; i <= player_tank_tile.x; ++i) {

				view_through = g_Game->m_map->get_tile_view_through_by_indices(i, tile_y);

				if (!view_through) {
					break;
				}
			}

			if (view_through) {

				m_ai_status = chasing_enemy_tank;
			}
		}
	}
}











