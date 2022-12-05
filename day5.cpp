#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <cctype>

/**
 * @brief  Initialize the stacks with the characters from the string
 *
 * @param charStack  The array of stacks
 * @param str        The string to be processed
 */
void initStacks(std::map<int, std::stack<char>> &charMap, std::string str)
{
  for (int i = 0; i < str.length(); i++)
  {
    if (isalpha(str[i]))
      charMap[i / 4 + 1].push(str[i]);
  }
}

/**
 * @brief  Reverse the stacks
 *
 * @param charStack  The array of stacks
 */
void reverseStacks(std::map<int, std::stack<char>> &charMap)
{
  for (auto it = charMap.begin(); it != charMap.end(); ++it)
  {
    std::stack<char> &stack = it->second;
    std::stack<char> temp;
    while (!it->second.empty())
    {
      temp.push(it->second.top());
      it->second.pop();
    }
    it->second = temp;
  }
}

/**
 * @brief  Print the top of the stacks
 *
 * @param charStack  The array of stacks
 */
void printStackTop(std::map<int, std::stack<char>> &charMap)
{
  for (auto it = charMap.begin(); it != charMap.end(); ++it)
    std::cout << it->second.top();
  std::cout << std::endl;
}

int main()
{
  std::ifstream file("input/day5.txt");
  std::string str;
  std::map<int, std::stack<char>> charStack;
  std::map<int, std::stack<char>> charStack2;

  while (getline(file, str))
  {
    if (isdigit(str[str.length() - 1]))
      break;

    initStacks(charStack, str);
    initStacks(charStack2, str);
  }

  // reverse the stacks
  reverseStacks(charStack);
  reverseStacks(charStack2);

  while (getline(file, str))
  {
    if (str.length() == 0)
      continue;

    std::stringstream ss(str);
    std::string temp;
    std::vector<int> nums;
    std::vector<char> crane;

    while (ss >> temp)
    {
      if (isdigit(temp[0]))
        nums.emplace_back(stoi(temp));
    }

    for (int i = 0; i < nums[0]; i++)
    {
      // part 1 operation
      char c = charStack[nums[1]].top();
      charStack[nums[1]].pop();
      charStack[nums[2]].push(c);

      // part 2 operation
      crane.emplace_back(charStack2[nums[1]].top());
      charStack2[nums[1]].pop();
    }

    // pop the crane back into the stack
    for (int i = crane.size() - 1; i >= 0; i--)
      charStack2[nums[2]].push(crane[i]);
  }

  printStackTop(charStack);
  printStackTop(charStack2);

  return 0;
}
