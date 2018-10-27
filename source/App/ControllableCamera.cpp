#include "ControllableCamera.hpp"

ControllableCamera::ControllableCamera(unsigned int width, unsigned int height)
    : m_Camera(width, height),
      m_Width(width), m_Height(height),
      m_LastMousePosition(0, 0),
      m_Scale(1.0f, 1.0f),
      m_MousePositionEnabled(false), m_DragWithMouse(false),
      m_Speed(10.0f)
{

}

void ControllableCamera::PollEvents(sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        PollKeyPress(event.key.code);                   break;
    case sf::Event::KeyReleased:
        PollKeyRelease(event.key.code);                 break;
    case sf::Event::MouseWheelScrolled:
        PollMouseWheelScroll(event.mouseWheelScroll);   break;
    case sf::Event::MouseMoved:
        PollMouseMove(event.mouseMove);                 break;
    case sf::Event::MouseButtonPressed:
        PollMouseButtonPress(event.mouseButton);        break;
    case sf::Event::MouseButtonReleased:
        PollMouseButtonRelease(event.mouseButton);      break;
    case sf::Event::Resized:
        Resize(event.size.width, event.size.height);    break;
    }
}

void ControllableCamera::PollKeyPress(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::W:
        m_Camera.Translate(m_Camera.Move::Up, m_Speed); break;
    case sf::Keyboard::S:
        m_Camera.Translate(m_Camera.Move::Down, m_Speed); break;
    case sf::Keyboard::A:
        m_Camera.Translate(m_Camera.Move::Left, m_Speed); break;
    case sf::Keyboard::D:
        m_Camera.Translate(m_Camera.Move::Right, m_Speed); break;
    case sf::Keyboard::LControl:
        m_MousePositionEnabled = true; break;
    }
}

void ControllableCamera::PollKeyRelease(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::LControl:
        m_MousePositionEnabled = false; break;
    }
}

void ControllableCamera::PollMouseWheelScroll(const sf::Event::MouseWheelScrollEvent& wheel)
{
    float oldZoom = m_Camera.GetZoom();
    float newZoom = oldZoom;
    if (wheel.delta < 0)
    {
        newZoom *= 0.95f;
        m_Speed /= 0.95f;
    }
    else
    {
        newZoom /= 0.95f;
        m_Speed *= 0.95f;
    }
    if (m_MousePositionEnabled)
    {
        sf::Vector2f posDiff(wheel.x - m_Width/2.0f, wheel.y - m_Height/2.0f);
        sf::Vector2f offset = posDiff *(1/oldZoom - 1/newZoom);
        offset.x /= m_Scale.x;
        offset.y /= m_Scale.y;
        m_Camera.Translate(offset.x, offset.y);
    }
    m_Camera.SetZoom(newZoom);
}

void ControllableCamera::PollMouseButtonPress(const sf::Event::MouseButtonEvent& mouse)
{
    if (mouse.button == sf::Mouse::Button::Middle)
    {
        m_LastMousePosition.x = mouse.x;
        m_LastMousePosition.y = mouse.y;
        m_DragWithMouse = true;
    }
}

void ControllableCamera::PollMouseButtonRelease(const sf::Event::MouseButtonEvent& mouse)
{
    if (mouse.button == sf::Mouse::Button::Middle)
        m_DragWithMouse = false;
}

void ControllableCamera::PollMouseMove(const sf::Event::MouseMoveEvent& mouse)
{
    if (m_DragWithMouse)
    {
        sf::Vector2i mousePos(mouse.x, mouse.y);
        sf::Vector2f posDiff(mousePos.x-m_LastMousePosition.x, mousePos.y-m_LastMousePosition.y);
        m_LastMousePosition = mousePos;

        sf::Vector2f offset = posDiff / m_Camera.GetZoom();
        m_Camera.Translate(-offset.x, -offset.y);
    }
}


void ControllableCamera::Resize(float x, float y)
{
    m_Scale.x *= x / (float)m_Width;
    m_Scale.y *= y / (float)m_Height;
    m_Width = x;
    m_Height = y;
}

void ControllableCamera::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Camera, states);
}