#include <iostream>
#include <fstream>

int main()
{
  std::ifstream input("day1.txt");
  std::string line;
  int max = 0;
  int sum = 0;

  while (getline(input, line))
  {
    if (line == "")
    {
      if (sum > max)
      {
        max = sum;
      }
      sum = 0;
      continue;
    }

    int calorie = std::stoi(line);
    sum += calorie;
  }

  std::cout << max << std::endl;

  return 0;
}
