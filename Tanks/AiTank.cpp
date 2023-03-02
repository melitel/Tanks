#include "AiTank.h"


void AiTank::update(float dt) {

	//move_tank(sf::Vector2f(0.f, 1.f), dt);

}

void AiTank::get_path(int start_x, int start_y, int goal_x, int goal_y)
{
	m_path.clear();
	m_path = m_ai_brain.a_star(start_x, start_y, goal_x, goal_y);
}

void AiTank::move_tank(const sf::Vector2f& velocity, float delta){

	sf::Vector2f new_velocity;
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f goal_coordinates = sf::Vector2f(m_path.back().x, m_path.back().y);
	//tile for left corner
	int tileX_l = (p0.x - m_offset) / 32;
	//tileX for right corner
	int tileX_r = (p0.x + (m_offset -1)) / 32;
	//tileY top corner
	int tileY_t = (p0.y - m_offset) / 32;
	//tileY bot corner
	int tileY_b = (p0.y + (m_offset-1)) / 32;

	sf::Vector2f tank_upper_left_coord = sf::Vector2f(tileX_l, tileY_t);
	sf::Vector2f tank_upper_right_coord = sf::Vector2f(tileX_r, tileY_t);
	sf::Vector2f tank_bottom_left_coord = sf::Vector2f(tileX_l, tileY_b);

	for (int i = 0; i < m_path.size() - 1 ; ++i) {		
		
		sf::Vector2f path_coordinates = sf::Vector2f(m_path[i].x, m_path[i].y);

			if (tank_upper_left_coord == path_coordinates) {
			
				if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::east) {

					new_velocity = sf::Vector2f(1.f, 0.f);
				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::west) {

					new_velocity = sf::Vector2f(-1.f, 0.f);

				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::south) {

					new_velocity = sf::Vector2f(0.f, -1.f);
				}
				else if (m_path[i + 1].movement_direction == BrainAtk::Node::direction::north) {

					if (m_path[i].movement_direction == BrainAtk::Node::direction::west) {
						
						if (tank_upper_right_coord == path_coordinates) {
							
							new_velocity = sf::Vector2f(0.f, 1.f);
						}
						else {

							new_velocity = sf::Vector2f(-1.f, 0.f);							
						}
					
					}
					else {
					
						new_velocity = sf::Vector2f(0.f, 1.f);
					}
					
				}			
			}	
	}

	if (tank_upper_left_coord == goal_coordinates) {
		
		new_velocity = sf::Vector2f(0.f, 0.f);
	
	}
	
	sf::Vector2f vel = new_velocity * m_move_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	
	m_tank.setPosition(p1);
}






