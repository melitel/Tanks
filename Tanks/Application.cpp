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
	m_game->initialize(m_window_width, m_window_height, m_window);
	//Game::input_event events;
	//Game::input_event::mouse_event input_mouse_event;
	//Game::input_event::keyboard_event input_key_event;	

	//Game::game_state state;
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
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pos = sf::Mouse::getPosition(*m_window);
					m_game->input_event(6, true, pos, inputEvent, InputEvent::Type::MouseClick);
					//inputEvent.type = InputEvent::Type::MouseClick;
					m_game->push_input_event(inputEvent);

					/*input_mouse_event.left_button_pressed = true;
					input_mouse_event.position = sf::Mouse::getPosition(*m_window);
					events.mouse_events.push_back(input_mouse_event);*/
				}				
			}

			if (event.type == sf::Event::KeyPressed && currentState == 1)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					m_game->input_event(0, true, sf::Vector2i(0,0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 0;
					inputEvent.buttonPressed = true;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_W;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					m_game->input_event(1, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 1;
					inputEvent.buttonPressed = true;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_A;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					m_game->input_event(2, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 2;
					inputEvent.buttonPressed = true;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_S;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_game->input_event(3, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 3;
					inputEvent.buttonPressed = true;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_D;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					m_game->input_event(4, true, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 4;
					inputEvent.buttonPressed = true;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_Space;
					input_key_event.isPressed = true;
					input_key_event.isReleased = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
			}			
			
			if (event.type == sf::Event::KeyReleased && currentState == 1)
			{
				if (event.key.code == sf::Keyboard::Key::W)
				{
					m_game->input_event(0, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 0;
					inputEvent.buttonPressed = false;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_W;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					m_game->input_event(1, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 1;
					inputEvent.buttonPressed = false;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_A;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::S)
				{
					m_game->input_event(2, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 2;
					inputEvent.buttonPressed = false;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_S;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_game->input_event(3, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 3;
					inputEvent.buttonPressed = false;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_D;
					input_key_event.isReleased = true;
					input_key_event.isPressed = false;
					events.keyboard_events.push_back(input_key_event);*/
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					m_game->input_event(4, false, sf::Vector2i(0, 0), inputEvent, InputEvent::Type::ButtonClick);
					/*inputEvent.type = InputEvent::Type::ButtonClick;
					inputEvent.buttonType = 4;
					inputEvent.buttonPressed = false;*/
					m_game->push_input_event(inputEvent);

					/*input_key_event.key_pressed = input_key_event.k_Space;
					input_key_event.isPressed = false;
					input_key_event.isReleased = true;
					events.keyboard_events.push_back(input_key_event);	*/			
					
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


