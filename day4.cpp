#include <iostream>
#include <fstream>

int main()
{
  int count1 = 0;
  int count2 = 0;

  std::ifstream file("input/day4.txt");
  std::string str;

  while (getline(file, str)) {
    // split the string into two parts by comma
    std::string first = str.substr(0, str.find(','));
    std::string second = str.substr(str.find(',') + 1);

    // split the first part into two parts by dash
    int f1 = stoi(first.substr(0, first.find('-')));
    int f2 = stoi(first.substr(first.find('-') + 1));

    // split the second part into two parts by dash
    int s1 = stoi(second.substr(0, second.find('-')));
    int s2 = stoi(second.substr(second.find('-') + 1));

    if ((f1 >= s1 && f2 <= s2) || (s1 >= f1 && s2 <= f2))
      count1++;

    if ((f1 >= s1 && f1 <= s2) || (f2 >= s1 && f2 <= s2) ||
        (s1 >= f1 && s1 <= f2) || (s2 >= f1 && s2 <= f2))
      count2++;
  }

  // print the first and second part
  std::cout << count1 << std::endl;
  std::cout << count2 << std::endl;

  return 0;
}
