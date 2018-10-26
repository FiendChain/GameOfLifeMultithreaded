#include "GOLGrid.hpp"
#include <SFML/Graphics.hpp>

namespace gol
{

GOLGrid::GOLGrid(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height),
      m_Grid(width*height),
      m_States(width*height)
{
    for (unsigned int row = 0; row < m_Height; row++)
        for (unsigned int col = 0; col < m_Width; col++)
        {
            m_Grid.at(GetIndex(row, col)).position = sf::Vector2f((float)col, (float)row);
            SetState(State::Dead, row, col);
        }
}

GOLGrid::State GOLGrid::GetState(unsigned int row, unsigned int col) const
{
    return m_States.at(GetIndex(row, col)); 
}

void GOLGrid::SetState(GOLGrid::State state, unsigned int row, unsigned int col)
{
    unsigned int index = GetIndex(row, col);
    auto& vertex = m_Grid.at(index);
    m_States.at(index) = state;
    switch (state)
    {
    case State::Dead:
        vertex.color = sf::Color::Black;
        break;
    case State::Alive:
        vertex.color = sf::Color::White;
        break;
    case State::Dying:
        vertex.color = sf::Color::Red;
        break;
    case State::Ressurecting:
        vertex.color = sf::Color::Green;
        break;
    default:
        vertex.color = sf::Color::Yellow;
    }
}

void GOLGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Grid.data(), m_Grid.size(), sf::Points, states);
}
 
}