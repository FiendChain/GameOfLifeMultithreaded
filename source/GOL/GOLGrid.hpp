#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace gol
{

class GOLGrid: public sf::Drawable
{
    public:
        enum State { Alive, Dead, Dying, Ressurecting };
    private:
        std::vector<sf::Vertex> m_Grid;
        std::vector<State> m_States;
        const unsigned int m_Width, m_Height;
    public:
        GOLGrid(unsigned int width, unsigned int height);
        GOLGrid::State GetState(unsigned int row, unsigned int col) const;
        void SetState(GOLGrid::State state, unsigned int row, unsigned int col);
        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }
        inline unsigned int GetIndex(unsigned int row, unsigned int col) const 
        {  return row*m_Width + col; }
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}