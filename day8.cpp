#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief  Checks the surrounding of the current position and counts the number of positions that are not covered.
 *
 * @param grid  The grid to be checked
 * @param x  The x position
 * @param y  The y position
 * @param count  The number of positions that are not covered
 * @param score  The score of the current position
 */
void checkSurrounding(std::vector<std::vector<int>> &grid, int x, int y, int &count, int &score)
{
  if (x == 0 || x == grid.size() - 1 || y == 0 || y == grid[0].size() - 1)
  {
    count++;
    return;
  }

  int localScore = 1;
  int scenicScore = 0;
  int covered = 0;

  // check top to the edge of the grid if it is larger than the current position
  for (int i = x - 1; i >= 0; i--)
  {
    scenicScore++;
    if (grid[i][y] >= grid[x][y])
    {
      covered++;
      break;
    }
  }
  localScore *= scenicScore;
  scenicScore = 0;

  // check bottom to the edge of the grid if it is larger than the current position
  for (int i = x + 1; i < grid.size(); i++)
  {
    scenicScore++;
    if (grid[i][y] >= grid[x][y])
    {
      covered++;
      break;
    }
  }
  localScore *= scenicScore;
  scenicScore = 0;

  // check left to the edge of the grid if it is larger than the current position
  for (int i = y - 1; i >= 0; i--)
  {
    scenicScore++;
    if (grid[x][i] >= grid[x][y])
    {
      covered++;
      break;
    }
  }
  localScore *= scenicScore;
  scenicScore = 0;

  // check right to the edge of the grid if it is larger than the current position
  for (int i = y + 1; i < grid[0].size(); i++)
  {
    scenicScore++;
    if (grid[x][i] >= grid[x][y])
    {
      covered++;
      break;
    }
  }
  localScore *= scenicScore;
  scenicScore = 0;

  if (score < localScore)
  {
    score = localScore;
  }

  if (covered == 4)
    return;
  count++;
}

int main()
{
  std::ifstream file("input/day8.txt");
  std::string line;
  std::vector<std::vector<int>> grid;
  int count = 0;
  int score = 0;

  while (std::getline(file, line))
  {
    std::vector<int> row;

    for (auto &c : line)
    {
      row.push_back(c - '0');
    }

    grid.push_back(row);
  }

  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[0].size(); j++)
    {
      checkSurrounding(grid, i, j, count, score);
    }
  }

  std::cout << count << std::endl;
  std::cout << score << std::endl;

  return 0;
}
