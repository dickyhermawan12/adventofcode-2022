#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct File
{
  std::string name;
  long long size;
};

struct Directory
{
  std::string name;
  long long size;
  Directory *parent;
  std::vector<Directory *> children;
  std::vector<File *> files;
};

/**
 * @brief  Finds the size of the directory.
 *
 * @param dir  The directory to be checked
 * @return  The size of the directory
 */
long long findSize(Directory *dir)
{
  long long sum = 0;

  for (auto &file : dir->files)
  {
    sum += file->size;
  }

  for (auto &child : dir->children)
  {
    sum += findSize(child);
  }

  dir->size = sum;
  return sum;
}

/**
 * @brief  Finds the size of the directories that are smaller than 100000.
 *
 * @param dir  The directory to be checked
 * @param sum  The sum of the sizes of the directories
 */
void findSmall(Directory *dir, long long &sum)
{
  if (dir->size < 100000)
  {
    sum += dir->size;
  }

  for (auto &child : dir->children)
  {
    findSmall(child, sum);
  }
}

/**
 * @brief  Finds the directories that are larger than the deficit.
 *
 * @param dir  The directory to be checked
 * @param dirs  The vector of directories
 * @param deficit  The deficit
 */
void findLarge(Directory *dir, std::vector<Directory *> &dirs, long long deficit)
{
  if (dir->size + deficit > 0)
  {
    dirs.push_back(dir);
  }

  for (auto &child : dir->children)
  {
    findLarge(child, dirs, deficit);
  }
}

int main()
{
  std::ifstream input("input/day7.txt");
  std::string line;
  Directory *root = new Directory({"/", 0, nullptr, {}, {}});
  Directory *current = root;
  long long sum = 0;
  std::vector<Directory *> dirs;
  const long long MAX_SIZE = 70000000;
  const long long NEEDED_SIZE = 30000000;

  while (getline(input, line))
  {
    std::string command = line.substr(0, line.find(" "));

    if (command == "$")
    {
      std::string arg1 = line.substr(line.find("$") + 2, 2);

      if (arg1 == "cd")
      {
        std::string arg2 = line.substr(line.find("$ cd") + 5);

        if (arg2 == "..")
        {
          current = current->parent;
        }
        else
        {
          for (auto &child : current->children)
          {
            if (child->name == arg2)
            {
              current = child;
              break;
            }
          }
        }
      }
    }
    else
    {
      if (command == "dir")
      {
        std::string arg1 = line.substr(line.find("dir") + 4);
        Directory *newDir = new Directory({arg1, 0, current, {}, {}});
        current->children.push_back(newDir);
      }
      else
      {
        std::string size = line.substr(0, line.find(" "));
        std::string name = line.substr(line.find(" ") + 1);
        long long sizeNum = std::stoll(size);

        File *newFile = new File({name, sizeNum});
        current->files.push_back(newFile);
      }
    }
  }

  findSize(root);
  findSmall(root, sum);
  findLarge(root, dirs, MAX_SIZE - NEEDED_SIZE - root->size);
  std::sort(dirs.begin(), dirs.end(), [](Directory *a, Directory *b)
            { return a->size < b->size; });
  std::cout << sum << std::endl;
  std::cout << dirs[0]->size << std::endl;

  return 0;
}
