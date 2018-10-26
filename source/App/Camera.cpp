#include "Camera.hpp"
#include <SFML/Graphics.hpp>

Camera::Camera(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height),
      m_Scale(1.0f, 1.0f),
      m_Position(width/2.0f, height/2.0f), m_Origin(width/2.0f, height/2.0f),
      m_MousePositionEnabled(false),
      m_Zoom(1.0f),
      m_Speed(10.0f)
{
    if (!m_Canvas.create(width, height))
        throw std::runtime_error("Couldn't create rendertexture canvas");
}

void Camera::PollEvents(sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        PollKeyPress(event.key.code);
        break;
    case sf::Event::KeyReleased:
        PollKeyRelease(event.key.code);
        break;
    case sf::Event::MouseWheelScrolled:
        PollMouseWheelScroll(event.mouseWheelScroll);
        break;
    case sf::Event::Resized:
        Resize(event.size.width, event.size.height);
        break;
    }
}

void Camera::Resize(float x, float y)
{
    m_Scale.x *= x / (float)m_Width;
    m_Scale.y *= y / (float)m_Height;
    m_Width = x;
    m_Height = y;
}

void Camera::PollKeyPress(sf::Keyboard::Key& key)
{
    switch (key)
    {
    case sf::Keyboard::W:
        m_Origin.y -= m_Speed; break;
    case sf::Keyboard::S:
        m_Origin.y += m_Speed; break;
    case sf::Keyboard::A:
        m_Origin.x -= m_Speed; break;
    case sf::Keyboard::D:
        m_Origin.x += m_Speed; break;
    case sf::Keyboard::LControl:
        m_MousePositionEnabled = true; break;
    }
}

void Camera::PollKeyRelease(sf::Keyboard::Key& key)
{
    switch (key)
    {
    case sf::Keyboard::LControl:
        m_MousePositionEnabled = false; break;
    }
}

void Camera::PollMouseWheelScroll(sf::Event::MouseWheelScrollEvent& wheel)
{
    float oldZoom = m_Zoom;
    if (wheel.delta < 0)
    {
        m_Zoom *= 0.95f;
        m_Speed /= 0.95f;
    }
    else
    {
        m_Zoom *= 1.05f;
        m_Speed /= 1.05f;
    }
    if (m_MousePositionEnabled)
    {
        sf::Vector2f posDiff(wheel.x - m_Width/2.0f, wheel.y - m_Height/2.0f);
        sf::Vector2f offset = posDiff *(1/oldZoom - 1/m_Zoom);
        offset.x /= m_Scale.x;
        offset.y /= m_Scale.y;
        m_Origin += offset;
    }
}

void Camera::Clear(const sf::Color& colour) 
{
    m_Canvas.clear(colour);
}

void Camera::Draw(sf::Drawable& drawable)
{
    m_Canvas.draw(drawable);
}


void Camera::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite canvas(m_Canvas.getTexture());
    canvas.setScale(m_Zoom, m_Zoom);
    canvas.setOrigin(m_Origin);
    canvas.setPosition(m_Position);

    target.draw(canvas, states);
}
