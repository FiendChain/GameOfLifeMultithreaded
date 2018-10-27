#pragma once

#include "Camera.hpp"

class ControllableCamera: public sf::Drawable
{
    private:
        Camera m_Camera;
        bool m_MousePositionEnabled, m_DragWithMouse;
        sf::Vector2i m_LastMousePosition;
        sf::Vector2f m_Scale;
        unsigned int m_Width, m_Height;
        float m_Speed;
    public:
        ControllableCamera(unsigned int width, unsigned int height);
        inline void Clear(const sf::Color& colour) { m_Camera.Clear(colour); }
        inline void Draw(sf::Drawable& drawable) { m_Camera.Draw(drawable); }
        void PollEvents(sf::Event& event);
    private:
        void Resize(float x, float y);
    private:
        void PollKeyPress(sf::Keyboard::Key key);
        void PollKeyRelease(sf::Keyboard::Key key);
        void PollMouseWheelScroll(const sf::Event::MouseWheelScrollEvent& wheel);
        void PollMouseButtonPress(const sf::Event::MouseButtonEvent& mouse);
        void PollMouseButtonRelease(const sf::Event::MouseButtonEvent& mouse);
        void PollMouseMove(const sf::Event::MouseMoveEvent& mouse);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};