#pragma once
#include "GOLGrid.hpp"

namespace gol::rules
{

bool CheckNeighbour(GOLGrid& grid, unsigned int row, unsigned int col);
int GetTotalNeighbours(GOLGrid& grid, int width, int height);
GOLGrid::State Default(GOLGrid& grid, unsigned int width, unsigned int height);

}