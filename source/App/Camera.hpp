#pragma once

#include <SFML/Graphics.hpp>

class Camera: public sf::Drawable
{
    private:
        sf::RenderTexture m_Canvas;
        unsigned int m_Width, m_Height;
        sf::Vector2f m_Position, m_Origin, m_Scale;
        bool m_MousePositionEnabled, m_DragWithMouse;
        sf::Vector2i m_LastMousePosition;
        float m_Zoom, m_Speed;
    public:
        Camera(unsigned int width, unsigned int height);
        void PollEvents(sf::Event& event);
        void Clear(const sf::Color& colour);
        void Draw(sf::Drawable& drawable);
        void Resize(float x, float y);
    private:
        void PollKeyPress(sf::Keyboard::Key& key);
        void PollKeyRelease(sf::Keyboard::Key& key);
        void PollMouseWheelScroll(sf::Event::MouseWheelScrollEvent& wheel);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};