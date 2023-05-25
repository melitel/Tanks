#include "AiTank.h"
#include <iostream>
#include "Game.h"

extern Game* g_Game;

void AiTank::initialize(const sf::Vector2f& pos)
{
	Tank::initialize(pos);
	m_goal_def_switch = 1;
	m_first_ai_bullet_shot = false;

	if (m_tank_attack_type == attack) {
		m_ai_status = moving_to_enemy_base;	
	}
	if (m_tank_attack_type == defence) {
		m_ai_status = defending_base;
	}
}

void AiTank::change_status(ai_status status)
{	
	if (m_ai_status != status) {
		std::cout << status << std::endl;
	}
	m_ai_status = status;
}

void AiTank::update(float dt, int tank_i) {

	sf::Vector2f ai_tank_position = m_tank.getPosition();
	sf::Vector2f player_tank_position = g_Game->get_player_position();
	sf::Vector2f player_base_position = g_Game->get_base_position();
	sf::Vector2f ai_base_pos = g_Game->get_ai_base_position();
	sf::Vector2i ai_tank_tile_coord = sf::Vector2i(int ((ai_tank_position.x - m_offset) / 32), int ((ai_tank_position.y - m_offset) / 32));
	sf::Vector2i player_tank_tile_coord = sf::Vector2i(int (player_tank_position.x / 32),int (player_tank_position.y / 32));
	sf::Vector2i player_base_tile_coord = sf::Vector2i(int (player_base_position.x / 32),int (player_base_position.y / 32));
	sf::Vector2i ai_base_tile_coord = sf::Vector2i(int(ai_base_pos.x / 32), int(ai_base_pos.y / 32));

	processing_state(ai_tank_tile_coord, player_tank_tile_coord, player_base_tile_coord, tank_i);
	change_state(ai_tank_tile_coord, player_tank_tile_coord, player_base_tile_coord, ai_base_tile_coord);
	move_controller(dt, tank_i);
}

void AiTank::get_path(int start_x, int start_y, int goal_x, int goal_y, int tank_i)
{
	m_path.clear();
	m_path = m_ai_brain.a_star(start_x, start_y, goal_x, goal_y, tank_i);
}

void AiTank::move_tank(movement_direction direction, float delta){
	
	
}

void AiTank::move_controller(float delta, int tank_i)
{	
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f goal_coordinates = sf::Vector2f(float(m_path.back().x * 32), float (m_path.back().y * 32));

	sf::Vector2f tank_upper_left_coord = sf::Vector2f((p0.x - m_offset), (p0.y - m_offset));

	float comparison_epsilon = (1.f / 60.f) * m_move_speed;

		sf::Vector2i path_coordinates = sf::Vector2i(m_path[0].x * 32, m_path[0].y * 32);

		if ((abs(tank_upper_left_coord.x - path_coordinates.x) <= comparison_epsilon) && 
			(abs(tank_upper_left_coord.y - path_coordinates.y) <= comparison_epsilon)) {						
			
				if ((abs(tank_upper_left_coord.x - goal_coordinates.x) <= comparison_epsilon) &&
					(abs(tank_upper_left_coord.y - goal_coordinates.y) <= comparison_epsilon)) {

					if (m_ai_status == defending_base) {

						if (m_goal_def_switch == 1) {
							m_goal_def_switch = 2;
						}
						else {
							m_goal_def_switch = 1;
						}
					}
					else {
					
						m_velocity = sf::Vector2f(0.f, 0.f);
					}
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

	sf::Vector2f mtd = g_Game->separating_axis(g_Game->m_player_tank, g_Game->m_ai_tanks[tank_i], p1);
	
	if (g_Game->m_ai_tanks.size() > 1) {
		
		sf::Vector2f mtd_ai(0.f, 0.f);

		if (tank_i == 0) {		
			mtd_ai = g_Game->separating_axis(g_Game->m_ai_tanks[1], g_Game->m_ai_tanks[tank_i], p1);
		}
		if (tank_i == 1) {
			mtd_ai = g_Game->separating_axis(g_Game->m_ai_tanks[0], g_Game->m_ai_tanks[tank_i], p1);
		}

		m_tank.setPosition(p1 + mtd + mtd_ai);
	}
	else {
		m_tank.setPosition(p1 + mtd);
	}
}

void AiTank::processing_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile, int tank_i)
{
	sf::Vector2f ai_base_pos = g_Game->get_ai_base_position();
	sf::Vector2i ai_base_tile = sf::Vector2i(int(ai_base_pos.x / 32), int(ai_base_pos.y / 32));
	sf::Vector2f player_tank_pos = g_Game->get_player_position();
	//sf::Vector2i player_tile_coord = sf::Vector2i(int ((player_tank_pos.x - m_offset) / 32), int ((player_tank_pos.y - m_offset) / 32));

	if (m_ai_status == moving_to_enemy_base) {		

		get_path(ai_tank_tile.x, ai_tank_tile.y, player_base_tile.x, player_base_tile.y, tank_i);

		//I use floor for base coordinates cause base tiles coordinates are (13.5 , 16.5) and we need to floor them in order to align with tank
		if (ai_tank_tile.x == player_base_tile.x && abs(ai_tank_tile.y - player_base_tile.y) <= 3) {
			sf::Angle rotation = m_tank.getRotation();

			if (rotation != sf::degrees(0.f)) {
				m_tank.setRotation(sf::degrees(0.f));
			}

			g_Game->projectile_shoot(g_Game->m_ai_tanks[tank_i]);
		}
		if (ai_tank_tile.y == player_base_tile.y && abs(ai_tank_tile.x - player_base_tile.x) <= 3) {
			
			sf::Angle rotation = m_tank.getRotation();

			if (ai_tank_tile.x < player_base_tile.x) {
				if (rotation != sf::degrees(-90.f)) {
					m_tank.setRotation(sf::degrees(-90.f));
				}
			}
			if (ai_tank_tile.x > player_tank_tile.x) {
				if (rotation != sf::degrees(90.f)) {
					m_tank.setRotation(sf::degrees(90.f));
				}
			}
			g_Game->projectile_shoot(g_Game->m_ai_tanks[tank_i]);
		}
	}
	if (m_ai_status == chasing_enemy_tank) {

		get_path(ai_tank_tile.x, ai_tank_tile.y, player_tank_tile.x, player_tank_tile.y, tank_i);
		
		if (ai_tank_tile.x == player_tank_tile.x && abs(ai_tank_tile.y - player_tank_tile.y) <= 3) {
			
			sf::Angle rotation = m_tank.getRotation();

			if (ai_tank_tile.y < player_tank_tile.y) {
				if (rotation != sf::degrees(0.f)) {
					m_tank.setRotation(sf::degrees(0.f));
				}
			}
			if (ai_tank_tile.y > player_tank_tile.y) {
				if (rotation != sf::degrees(-180.f)) {
					m_tank.setRotation(sf::degrees(-180.f));
				}
			}
			g_Game->projectile_shoot(g_Game->m_ai_tanks[tank_i]);
		}
		if (ai_tank_tile.y == player_tank_tile.y && abs(ai_tank_tile.x - player_tank_tile.x) <= 3) {
			
			sf::Angle rotation = m_tank.getRotation();

			if (ai_tank_tile.x < player_tank_tile.x) {
				if (rotation != sf::degrees(-90.f)) {
					m_tank.setRotation(sf::degrees(-90.f));
				}
			}
			if (ai_tank_tile.x > player_tank_tile.x) {
				if (rotation != sf::degrees(90.f)) {
					m_tank.setRotation(sf::degrees(90.f));
				}
			}
			g_Game->projectile_shoot(g_Game->m_ai_tanks[tank_i]);
		}		
	}
	if (m_ai_status == defending_base) {

		if (m_goal_def_switch == 1) {
			get_path(ai_tank_tile.x, ai_tank_tile.y, 0, ai_base_tile.y + 2, tank_i);
		}
		if (m_goal_def_switch == 2) {
			get_path(ai_tank_tile.x, ai_tank_tile.y, (g_Game->m_level_columns - 1), ai_base_tile.y + 2, tank_i);
		}
	}
}


void AiTank::change_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile, sf::Vector2i ai_base_tile)
{
	//switch to chasing player mode from moving_to_base state	
	
		if (ai_tank_tile.x == player_tank_tile.x && ai_tank_tile.y != player_tank_tile.y) {

			if (m_ai_status == moving_to_enemy_base) {
			
				if (abs(ai_tank_tile.y - player_tank_tile.y) < abs(ai_tank_tile.y - player_base_tile.y)) {
		
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
				else {
					m_ai_status = moving_to_enemy_base;
				}
			}
			if (m_ai_status == defending_base) {				

				if (abs(player_tank_tile.y - ai_base_tile.y) < abs(player_tank_tile.y - player_base_tile.y)) {

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
				else {
					m_ai_status = defending_base;
				}
			}
		}


		if (ai_tank_tile.y == player_tank_tile.y && ai_tank_tile.x != player_tank_tile.x) {

			if (m_ai_status == moving_to_enemy_base) {
			
				if (abs(ai_tank_tile.x - player_tank_tile.x) < abs(ai_tank_tile.x - player_base_tile.x)) {
		
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
				else {
					m_ai_status = moving_to_enemy_base;
				}
			}
			if (m_ai_status == defending_base) {
			
				if (abs(player_tank_tile.y - ai_base_tile.y) < abs(player_tank_tile.y - player_base_tile.y)) {
					
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
				else {
					m_ai_status = defending_base;
				}			
			}
		}
}

bool AiTank::if_first_bullet_shot()
{
	return m_first_ai_bullet_shot;
}

void AiTank::first_bullet_shot()
{
	m_first_ai_bullet_shot = true;
}

void AiTank::last_projectile_shot_time(std::chrono::duration<float> time)
{
	m_last_ai_projectile_shot = time;
}

std::chrono::duration<float> AiTank::when_last_projectile_shot()
{
	return m_last_ai_projectile_shot;
}













