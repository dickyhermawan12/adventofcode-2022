#include <iostream>
#include <fstream>

/**
 *  @brief  Rank the array sorted from largest to smallest.
 *  @param arr  The array of numbers.
 *  @param max  New obtained number that is introduced to the array.
 */
void shiftRank(int arr[], int max)
{
  arr[2] = max;
  for (int i = 0; i < 3; i++)
  {
    for (int j = i + 1; j < 3; j++)
    {
      if (arr[i] < arr[j])
      {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

/**
 *  @brief  Sum of the three largest numbers.
 *  @param arr  The array of numbers.
 *  @return  The sum of the three largest numbers.
 */
int getSum(int arr[])
{
  int sum = 0;
  for (int i = 0; i < 3; i++)
  {
    sum += arr[i];
  }
  return sum;
}

int main()
{
  std::ifstream input("day1.txt");
  std::string line;
  int sum = 0;
  int arr[3] = {0, 0, 0};

  while (getline(input, line))
  {
    if (line == "")
    {
      if (sum > arr[2])
      {
        shiftRank(arr, sum);
      }
      sum = 0;
      continue;
    }

    int calorie = std::stoi(line);
    sum += calorie;
  }

  std::cout << arr[0] << std::endl;
  std::cout << getSum(arr) << std::endl;

  return 0;
}
