#pragma once
#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>


class Application
{
public:
	static void run();

private:

	static std::unique_ptr<Game> m_game;

	static std::unique_ptr<sf::RenderWindow> m_window;

	static const uint32_t m_window_width;
	static const uint32_t m_window_height;

};

