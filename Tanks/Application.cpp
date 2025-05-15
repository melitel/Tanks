#include "Application.h"
#include <thread>

std::unique_ptr<Game> Application::m_game = nullptr;

std::unique_ptr<sf::RenderWindow> Application::m_window = nullptr;

const uint32_t Application::m_window_width = 864;
const uint32_t Application::m_window_height = 640;

void Application::run()
{
	m_game = std::make_unique<Game>();
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(m_window_width, m_window_height)), "Tanks");
	m_game->initialize(m_window_width, m_window_height);

	InputEvent inputEvent;

	while (m_window->isOpen())
	{
		//events.mouse_events.clear();
		//events.keyboard_events.clear();

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (m_window->pollEvent(event))
		{			
			Game::game_state currentState = m_game->getGameState();

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					sf::Vector2i pos = sf::Mouse::getPosition(*m_window);
					m_game->input_event(InputKey::Undefined, true, pos, inputEvent, InputEvent::Type::MouseClick);
					m_game->push_input_event(inputEvent);
				}				
			}

			if (event.type == sf::Event::KeyPressed && currentState == 1)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					m_game->input_event(InputKey::W, true, sf::Vector2i(0,0), inputEvent, InputEvent::Type::ButtonClick);					
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					m_game->input_event(InputKey::A, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					m_game->input_event(InputKey::S, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_game->input_event(InputKey::D, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::Q)
				{
					m_game->input_event(InputKey::Q, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					m_game->input_event(InputKey::Space, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
			}			
			
			if (event.type == sf::Event::KeyReleased && currentState == 1)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					m_game->input_event(InputKey::W, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					m_game->input_event(InputKey::A, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					m_game->input_event(InputKey::S, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_game->input_event(InputKey::D, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::Q)
				{
					m_game->input_event(InputKey::Q, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					m_game->input_event(InputKey::Space, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					m_game->push_input_event(inputEvent);
				}
			}

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_window->close();

		}

		//m_game->gather_input(events);
		m_game->process_input();
		m_game->update();
		m_game->draw(m_window);	
		
	}

}


