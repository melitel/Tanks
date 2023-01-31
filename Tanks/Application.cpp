#include "Application.h"

std::unique_ptr<Game> Application::m_game = nullptr;

std::unique_ptr<sf::RenderWindow> Application::m_window = nullptr;

const uint32_t Application::m_window_width = 864;
const uint32_t Application::m_window_height = 608;

void Application::run()
{
	m_game = std::make_unique<Game>();
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(m_window_width, m_window_height)), "Tanks");
	m_game->initialize(m_window_width, m_window_height, m_window);
	Game::input_event events;
	Game::input_event::mouse_event input_mouse_event;
	Game::input_event::keyboard_event input_key_event;	

	while (m_window->isOpen())
	{
		events.mouse_events.clear();
		events.keyboard_events.clear();

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (m_window->pollEvent(event))
		{			

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					input_mouse_event.left_button_pressed = true;
					input_mouse_event.position = sf::Mouse::getPosition(*m_window);
					events.mouse_events.push_back(input_mouse_event);

				}				
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					input_key_event.key_pressed = input_key_event.k_W;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					input_key_event.key_pressed = input_key_event.k_A;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					input_key_event.key_pressed = input_key_event.k_S;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					input_key_event.key_pressed = input_key_event.k_D;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					input_key_event.key_pressed = input_key_event.k_Space;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);
				}
			}			
			
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					input_key_event.key_pressed = input_key_event.k_W;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					input_key_event.key_pressed = input_key_event.k_A;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					input_key_event.key_pressed = input_key_event.k_S;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					input_key_event.key_pressed = input_key_event.k_D;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					input_key_event.key_pressed = input_key_event.k_Space;
					input_key_event.isPressed = false;
					input_key_event.isReleased = true;
					events.keyboard_events.push_back(input_key_event);
				}
			}

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_window->close();

		}

		m_game->gather_input(events);
		m_game->update();
		m_game->draw(m_window);
		
	}

}
