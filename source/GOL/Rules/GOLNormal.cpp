#include "GOLNormal.hpp"

namespace gol::rules
{

bool CheckNeighbour(GOLGrid& grid, unsigned int row, unsigned int col)
{
    if (row < 0 || row >= grid.GetHeight()) 
        return false;
    if (col < 0 || col >= grid.GetWidth())
        return false;
    GOLGrid::State state = grid.GetState(row, col);
    if (state == GOLGrid::State::Alive || state == GOLGrid::State::Ressurecting)
        return true;
    return false;
}

int GetTotalNeighbours(GOLGrid& grid, int row, int col)
{
    int totalNeighbours = 0;
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++)
    {
        for (int colOffset = -1; colOffset <= 1; colOffset++)
        {
            if (rowOffset == 0 && colOffset == 0)
                continue;
            if (CheckNeighbour(grid, row+rowOffset, col+colOffset))
                totalNeighbours++;
        }
    }

    return totalNeighbours;
}

GOLGrid::State Default(GOLGrid& grid, unsigned int row, unsigned int col)
{

    bool isAlive = CheckNeighbour(grid, row, col);
    int totalNeighbours = GetTotalNeighbours(grid, row, col);
    if (isAlive)
    {
        if (totalNeighbours <= 1 || totalNeighbours >= 4)
            return GOLGrid::State::Dying;
        return GOLGrid::State::Alive;
    }
    else
    {
        if (totalNeighbours == 3)
            return GOLGrid::State::Ressurecting;
        return GOLGrid::State::Dead;
    }
}

}