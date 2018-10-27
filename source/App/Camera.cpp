#include "Camera.hpp"
#include <SFML/Graphics.hpp>

Camera::Camera(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height),
      m_Position(width/2.0f, height/2.0f), m_Origin(width/2.0f, height/2.0f),
      m_Zoom(1.0f)
{
    if (!m_Canvas.create(width, height))
        throw std::runtime_error("Couldn't create rendertexture canvas");
}

void Camera::SetZoom(float zoom)
{
    if (zoom > 0) 
    {
        m_Zoom = zoom;
    }
}

void Camera::Translate(Move move, float distance)
{
    switch (move)
    {
    case Move::Up:
        m_Origin.y -= distance; 
        break;
    case Move::Down:
        m_Origin.y += distance; 
        break;
    case Move::Left:
        m_Origin.x -= distance; 
        break;
    case Move::Right:
        m_Origin.x += distance; 
        break;
    }
}

void Camera::Translate(float x, float y)
{
    m_Origin.x += x;
    m_Origin.y += y;
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
