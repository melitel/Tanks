#include "ControllableTank.h"
#include "Game.h"

extern Game* g_Game;

int first_button_index = -2;
int second_button_index = -2;
int third_button_index = -2;

void ControllableTank::initialize(const sf::Vector2f& pos)
{
	Tank::initialize(pos);
	m_life = 3;
	m_first_bullet_shot = false;
	m_kills_count = 0;
}

void ControllableTank::update(float dt, int tank_i)
{
	move_controller(dt);
}

void ControllableTank::move_controller(float delta)
{
	Game::input_event::keyboard_event input_key_event;

	int inputs_count = g_Game->count_inputs(g_Game->m_input_state);

	if (inputs_count == 0)
	{
		first_button_index = -2;
	}
	if (inputs_count == 1) {

		second_button_index = -2;

		if (g_Game->m_input_state[to_index(InputKey::W)] == true)
		{
			first_button_index = 0;
			move_tank(ControllableTank::movement_direction::up, delta);
		}
		if (g_Game->m_input_state[to_index(InputKey::A)] == true)
		{
			first_button_index = 1;
			move_tank(ControllableTank::movement_direction::left, delta);
		}
		if (g_Game->m_input_state[to_index(InputKey::S)] == true)
		{
			first_button_index = 2;
			move_tank(ControllableTank::movement_direction::down, delta);
		}
		if (g_Game->m_input_state[to_index(InputKey::D)] == true)
		{
			first_button_index = 3;
			move_tank(ControllableTank::movement_direction::right, delta);

		}
	}
	if (inputs_count == 2) {

		int true_found = -1;
		int action_to_do = -1;

		if (first_button_index >= 0 && second_button_index >= 0 && third_button_index >= 0)
		{
			if (!g_Game->m_input_state[first_button_index])
			{
				first_button_index = second_button_index;
				second_button_index = third_button_index;
				third_button_index = -2;
				action_to_do = second_button_index;
			}
			else if (!g_Game->m_input_state[second_button_index])
			{
				second_button_index = third_button_index;
				third_button_index = -2;
				action_to_do = second_button_index;
			}
			else if (!g_Game->m_input_state[third_button_index])
			{
				third_button_index = -2;
				action_to_do = second_button_index;
			}
		}
		else
		{
			for (int i = 0; i < g_Game->m_input_state.size(); ++i)
			{
				if (g_Game->m_input_state[i])
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
			move_tank(ControllableTank::movement_direction::up, delta);
		}
		if (action_to_do == 1)
		{
			move_tank(ControllableTank::movement_direction::left, delta);
		}
		if (action_to_do == 2)
		{
			move_tank(ControllableTank::movement_direction::down, delta);
		}
		if (action_to_do == 3)
		{
			move_tank(ControllableTank::movement_direction::right, delta);
		}

	}
	if (inputs_count > 2) {

		int true_found = -1;

		for (int i = 0; i < g_Game->m_input_state.size(); ++i)
		{
			if (g_Game->m_input_state[i])
			{
				true_found = i;

				if (true_found != first_button_index && true_found != second_button_index) {

					third_button_index = true_found;
				}
			}
		}

		//change button index to 2nd button pressed, so when 3d button released to continue moving in second button direction
		move_tank(ControllableTank::movement_direction::stop, delta);
	}
}

void ControllableTank::move_tank(movement_direction direction, float delta)
{
	switch (direction) {
	case up:
		m_direction = sf::Vector2f(0.f, -1.f);
		rotate_tank(sf::degrees(0.f));
		break;
	case left:
		m_direction = sf::Vector2f(-1.f, 0.f);
		rotate_tank(sf::degrees(-90.f));
		break;
	case right:
		m_direction = sf::Vector2f(1.f, 0.f);
		rotate_tank(sf::degrees(90.f));
		break;
	case down:
		m_direction = sf::Vector2f(0.f, 1.f);
		rotate_tank(sf::degrees(180.f));
		break;
	case stop:
		m_direction = sf::Vector2f(0.f, 0.f);
		break;
	default:
		// handle invalid status value
		m_direction = sf::Vector2f(0.f, 0.f);
		break;
	}

	sf::Vector2f mtd(0.f, 0.f);
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f vel = m_direction * m_move_speed;
	sf::Vector2f p1 = p0 + (delta * vel);

	if (!g_Game->m_ai_tanks.empty()) {

		for (int i = 0; i < g_Game->m_ai_tanks.size(); ++i) {
			mtd = g_Game->separating_axis(g_Game->m_ai_tanks[i], g_Game->get_player_tank(), p1);
			p1 = p1 + mtd;
			g_Game->calibrate_pos(p1);
			m_tank.setPosition(p1);
		}
	}
	else {
		p1 = p1 + mtd;
		g_Game->calibrate_pos(p1);
		m_tank.setPosition(p1);
	}
}

bool ControllableTank::if_first_bullet_shot()
{
	return m_first_bullet_shot;
}

void ControllableTank::first_bullet_shot()
{
	m_first_bullet_shot = true;
}

void ControllableTank::last_projectile_shot_time(std::chrono::duration<float> time)
{
	m_last_projectile_shot = time;
}

std::chrono::duration<float> ControllableTank::when_last_projectile_shot()
{
	return m_last_projectile_shot;
}


