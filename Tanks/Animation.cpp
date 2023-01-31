#include "Animation.h"

void Animation::update(float dt)
{
	if (m_state == animation_state::as_active)
	{
		m_animation_time += dt;
		float change_frame = m_animation_total_time / m_frames_count;
		m_rectSourceSprite.left = m_texture_width * m_frame_id;
		m_rectSourceSprite.top = m_texture_width * m_animation_id;
		m_explosion.setTextureRect(m_rectSourceSprite);

		if (m_animation_time >= m_animation_total_time) {
			m_state = as_nonactive;
			m_frame_id = m_frames_count;
		}

		if (m_animation_time >= change_frame * m_frame_id)
		{
			++m_frame_id;
		}

		m_frame_id = std::min(m_frame_id, m_frames_count - 1);
	}
}

void Animation::play(uint32_t animation_id, const sf::Vector2f& pos, const std::string& name)
{
	m_explosion.setPosition(pos);
	m_explosion.setSize(sf::Vector2f(32.f, 32.f));
	if (!m_texture.loadFromFile(name))
	{
		m_explosion.setFillColor(sf::Color::Red);
	}
	else {
		m_explosion.setTexture(&m_texture);
		m_explosion.setTextureRect(m_rectSourceSprite);
	}
	m_animation_id = animation_id;
	m_state = animation_state::as_active;
	m_start_time = std::chrono::system_clock::now();
	m_frame_id = 0;
	m_animation_time = 0;

}

void Animation::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_explosion);

}

uint32_t Animation::get_frame_id() {

	return m_frame_id;

}

uint32_t Animation::get_animation_id() {

	return m_animation_id;

}
