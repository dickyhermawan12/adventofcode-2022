#include <iostream>
#include <fstream>

/**
 *  @brief  Get the score for the result.
 *  @param first  The enemy's choice (A - Rock, B - Paper, C - Scissors).
 *  @param second  The choice that we made (X - Rock, Y - Paper, Z - Scissors).
 *  @return  The score for the result.
 */
int getScore(char first, char second)
{
  int sum = 0;
  int choiceWeight[3] = {1, 2, 3};

  // calculate the score for the result
  switch ((second - 'X') - (first - 'A'))
  {
  case 1:
  case -2:
    sum += 6;
    break;
  case 0:
    sum += 3;
    break;
  case -1:
  case 2:
    sum += 0;
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
