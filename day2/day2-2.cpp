#include <iostream>
#include <fstream>

/**
 *  @brief  Get the score for the result.
 *  @param first  The enemy's choice (A - Rock, B - Paper, C - Scissors).
 *  @param result  The result of the game (X - Lose, Y - Draw, Z - Win).
 *  @return  The score for the result.
 */
int getScore(char first, char result)
{
  int sum = 0;
  char second;
  int choiceWeight[3] = {1, 2, 3};

  // calculate the score for the result
  switch (result - 'X')
  {
  case 0:
    sum += 0;
    second = (first == 'A') ? 'Z' : (first - 'A' + 'X') - 1;
    break;
  case 1:
    sum += 3;
    second = (first - 'A' + 'X');
    break;
  case 2:
    sum += 6;
    second = (first == 'C') ? 'X' : (first - 'A' + 'X') + 1;
    break;
  }

  // calculate the score for our choice
  sum += choiceWeight[second - 'X'];

  return sum;
}

int main()
{
  std::ifstream input("day2.txt");
  std::string line;
  int total = 0;

  while (getline(input, line))
  {
    total += getScore(line[0], line[2]);
  }

  std::cout << total << std::endl;

  return 0;
}
