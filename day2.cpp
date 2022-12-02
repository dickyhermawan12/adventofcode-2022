#include <iostream>
#include <fstream>

const int choiceWeight[3] = {1, 2, 3};
const int resultWeight[3] = {0, 3, 6};

/**
 *  @brief  Get the score for the result.
 *  @param first  The enemy's choice (A - Rock, B - Paper, C - Scissors).
 *  @param second  The choice that we made (X - Rock, Y - Paper, Z - Scissors).
 *  @return  The score for the result.
 */
int getScorePartOne(char first, char second)
{
  int sum = 0;

  // calculate the score for the result
  switch ((second - 'X') - (first - 'A'))
  {
  case 1:
  case -2:
    sum += resultWeight[2];
    break;
  case 0:
    sum += resultWeight[1];
    break;
  case -1:
  case 2:
    sum += resultWeight[0];
    break;
  }

  // calculate the score for our choice
  sum += choiceWeight[second - 'X'];
  return sum;
}

/**
 *  @brief  Get the score for the result.
 *  @param first  The enemy's choice (A - Rock, B - Paper, C - Scissors).
 *  @param result  The result of the game (X - Lose, Y - Draw, Z - Win).
 *  @return  The score for the result.
 */
int getScorePartTwo(char first, char result)
{
  int sum = 0;
  char second;

  // calculate the score for the result
  int resultIndex = result - 'X';
  sum += resultWeight[resultIndex];

  second = (first - 'A' + 'X');
  switch (resultIndex)
  {
  case 0:
    second = (first == 'A') ? 'Z' : second - 1;
    break;
  case 2:
    second = (first == 'C') ? 'X' : second + 1;
    break;
  }

  // calculate the score for our choice
  sum += choiceWeight[second - 'X'];
  return sum;
}

int main()
{
  std::ifstream input("input/day2.txt");
  std::string line;
  int total[2] = {0};

  while (getline(input, line))
  {
    total[0] += getScorePartOne(line[0], line[2]);
    total[1] += getScorePartTwo(line[0], line[2]);
  }

  std::cout << total[0] << std::endl;
  std::cout << total[1] << std::endl;

  return 0;
}
