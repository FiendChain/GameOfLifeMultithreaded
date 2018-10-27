#pragma once

#include <SFML/Graphics.hpp>

class Camera: public sf::Drawable
{
    public:
        enum Move { Up, Down, Left, Right };
    private:
        sf::RenderTexture m_Canvas;
        unsigned int m_Width, m_Height;
        sf::Vector2f m_Position, m_Origin;
        float m_Zoom;
    public:
        Camera(unsigned int width, unsigned int height);
        void Clear(const sf::Color& colour);
        void Draw(sf::Drawable& drawable);
        void SetZoom(float zoom);
        inline float GetZoom() const { return m_Zoom; }
        void Translate(Move move, float distance);
        void Translate(float x, float y);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};