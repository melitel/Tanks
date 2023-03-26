#include "AiTank.h"


void AiTank::initialize(const sf::Vector2f& pos, const std::string& name)
{
	Tank::initialize(pos, name);

	m_ai_status = moving_to_enemy_base;

}

void AiTank::change_status(ai_status status)
{	
	m_ai_status = status;
}

void AiTank::update(float dt) {

	sf::Vector2f velocity;
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f goal_coordinates = sf::Vector2f(m_path.back().x, m_path.back().y);
	//tile for left corner
	int tileX_l = (p0.x - m_offset) / 32;
	//tileX for right corner
	int tileX_r = (p0.x + (m_offset - 1)) / 32;
	//tileY top corner
	int tileY_t = (p0.y - m_offset) / 32;
	//tileY bot corner
	int tileY_b = (p0.y + (m_offset - 1)) / 32;

	sf::Vector2f tank_upper_left_coord = sf::Vector2f(tileX_l, tileY_t);
	sf::Vector2f tank_upper_right_coord = sf::Vector2f(tileX_r, tileY_t);
	sf::Vector2f tank_bottom_left_coord = sf::Vector2f(tileX_l, tileY_b);


	for (int i = 0; i < m_path.size(); ++i) {

		sf::Vector2f path_coordinates = sf::Vector2f(m_path[i].x, m_path[i].y);

		if (tank_upper_left_coord == path_coordinates) {
			//aiTank reached base and changes status to "attacking base"
			//fix the player tank offset problem
			if (tank_upper_left_coord.x == goal_coordinates.x && abs(tank_upper_left_coord.y - goal_coordinates.y) <= 2) {
				velocity = sf::Vector2f(0.f, 0.f);
				m_ai_status = attacking;
				break;
			}

			if (tank_upper_left_coord.y == goal_coordinates.y && abs(tank_upper_left_coord.x - goal_coordinates.x) <= 2) {
				velocity = sf::Vector2f(0.f, 0.f);
				m_ai_status = attacking;
				break;
			}


			if (tank_upper_left_coord == goal_coordinates) {

				if (m_path[i - 1].movement_direction == BrainAtk::Node::direction::south || m_path[i - 1].movement_direction == BrainAtk::Node::direction::east) {

					velocity = sf::Vector2f(0.f, 0.f);
					break;
				}
				else if (m_path[i - 1].movement_direction == BrainAtk::Node::direction::north) {

					if (tank_bottom_left_coord == path_coordinates) {

						velocity = sf::Vector2f(0.f, 0.f);
						break;
					}
					else {
						velocity = sf::Vector2f(0.f, -1.f);
					}

				}
				else if (m_path[i - 1].movement_direction == BrainAtk::Node::direction::west) {

					if (tank_upper_right_coord == path_coordinates) {

						velocity = sf::Vector2f(0.f, 0.f);
						break;
					}
					else {
						velocity = sf::Vector2f(-1.f, 0.f);
					}

				}
			}
			else {

				if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::east) {

					if (m_path[i].movement_direction == BrainAtk::Node::direction::north) {

						if (tank_bottom_left_coord == path_coordinates) {

							m_tank.setRotation(sf::degrees(-90.f));
							velocity = sf::Vector2f(1.f, 0.f);
						}
						else {
							velocity = sf::Vector2f(0.f, -1.f);
						}
					}
					else {

						m_tank.setRotation(sf::degrees(-90.f));
						velocity = sf::Vector2f(1.f, 0.f);
					}
				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::west) {

					if (m_path[i].movement_direction == BrainAtk::Node::direction::north) {

						if (tank_bottom_left_coord == path_coordinates) {

							m_tank.setRotation(sf::degrees(90.f));
							velocity = sf::Vector2f(-1.f, 0.f);
						}
						else {

							velocity = sf::Vector2f(0.f, -1.f);
						}

					}
					else {

						m_tank.setRotation(sf::degrees(90.f));
						velocity = sf::Vector2f(-1.f, 0.f);
					}

				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::south) {


					if (m_path[i].movement_direction == BrainAtk::Node::direction::west) {

						if (tank_upper_right_coord == path_coordinates) {

							m_tank.setRotation(sf::degrees(0.f));
							velocity = sf::Vector2f(0.f, 1.f);
						}
						else {

							velocity = sf::Vector2f(-1.f, 0.f);
						}

					}
					//else if (m_path[i].movement_direction == BrainAtk::Node::direction::north) {

					//	if (tank_bottom_left_coord == path_coordinates) {

					//		m_tank.setRotation(sf::degrees(0.f));
					//		velocity = sf::Vector2f(0.f, 1.f);
					//	}
					//	else {

					//		velocity = sf::Vector2f(0.f, -1.f);
					//	}

					//}
					else {

						m_tank.setRotation(sf::degrees(0.f));
						velocity = sf::Vector2f(0.f, 1.f);
					}

				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::north) {

					if (m_path[i].movement_direction == BrainAtk::Node::direction::west) {

						if (tank_upper_right_coord == path_coordinates) {

							m_tank.setRotation(sf::degrees(-180.f));
							velocity = sf::Vector2f(0.f, -1.f);
						}
						else {

							velocity = sf::Vector2f(-1.f, 0.f);
						}
					}
					else {

						m_tank.setRotation(sf::degrees(-180.f));
						velocity = sf::Vector2f(0.f, -1.f);
					}
				}
			}
		}
	}

	sf::Vector2f vel = velocity * m_move_speed;
	sf::Vector2f p1 = p0 + dt * vel;

	m_tank.setPosition(p1);

}

void AiTank::get_path(int start_x, int start_y, int goal_x, int goal_y)
{
	m_path.clear();
	m_path = m_ai_brain.a_star(start_x, start_y, goal_x, goal_y);
}

void AiTank::move_tank(movement_direction direction, float delta){
	
	
}











