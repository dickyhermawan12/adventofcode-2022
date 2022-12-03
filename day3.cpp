#include <iostream>
#include <fstream>

// binary search tree of characters
struct Node
{
  char data;
  Node *left;
  Node *right;
};

/**
 * @brief  Create a new node.
 *
 * @param data  The character to insert
 * @return  The root of the binary search tree
 */
Node *newNode(char data)
{
  Node *node = new Node;
  node->data = data;
  node->left = nullptr;
  node->right = nullptr;
  return node;
}

/**
 * @brief  Inserts a character into the binary search tree
 *
 * @param *node  The root of the binary search tree
 * @param data  The character to insert
 * @return  The root of the binary search tree
 */
Node *insert(Node *node, char data)
{
  if (node == nullptr)
    return newNode(data);
  if (data < node->data)
    node->left = insert(node->left, data);
  else if (data > node->data)
    node->right = insert(node->right, data);
  return node;
}

/**
 * @brief  Finds a character in the binary search tree
 *
 * @param *node  The root of the binary search tree
 * @param data  The character to find
 * @return  True if the character is found, false otherwise
 */
bool find(Node *node, char data)
{
  if (node == nullptr)
    return false;
  if (data < node->data)
    return find(node->left, data);
  else if (data > node->data)
    return find(node->right, data);
  return true;
}

/**
 * @brief  Creates a binary search tree from a string
 *
 * @param str  The string to create the binary search tree from
 * @return  The root of the binary search tree
 */
Node *createTree(std::string str)
{
  Node *root = nullptr;
  for (int i = 0; i < str.length(); i++)
  {
    root = insert(root, str[i]);
  }
  return root;
}

/**
 * @brief  Returns the priority of the character
 *
 * @param data  The character
 * @return  The priority of the character
 */
int priority(char data)
{
  switch (data)
  {
  case 'a' ... 'z':
    return data - 'a' + 1;
  default:
    return data - 'A' + 27;
  }
}

/**
 * @brief  Checks any first character in the string is in the binary search tree
 *
 * @param node  The root of the binary search tree
 * @param str  The string to check
 * @return  The first character in the string that is in the binary search tree or 0 if none
 */
char check(Node *node, std::string str)
{
  for (int i = 0; i < str.length(); i++)
  {
    if (find(node, str[i]))
      return str[i];
  }
  return 0;
}

// record of binary search tree of previous lines
struct PreviousData
{
  Node *prev;
  std::string sameChars;
  int cycle;

  PreviousData()
  {
    deleteData();
  }

  void deleteData()
  {
    prev = nullptr;
    sameChars = "";
    cycle = 1;
  }
};

int main()
{
  std::ifstream input("input/day3.txt");
  std::string line;
  int sum = 0;
  int sum2 = 0;
  PreviousData previousData;

  while (getline(input, line))
  {
    int pos = line.length() / 2;
    std::string first = line.substr(0, pos);
    std::string second = line.substr(pos);

    // create a binary search tree
    Node *root = createTree(first);

    // check if one of the characters is in the tree
    sum += priority(check(root, second));

    // check the same characters in the previous line
    switch (previousData.cycle)
    {
    case 1:
      previousData.prev = createTree(line);
      previousData.cycle++;
      break;
    case 2:
      // return all the characters in the string that are found in the tree
      for (int i = 0; i < line.length(); i++)
      {
        if (find(previousData.prev, line[i]))
          previousData.sameChars += line[i];
      }
      previousData.cycle++;
      break;
    case 3:
      previousData.prev = createTree(previousData.sameChars);
      sum2 += priority(check(previousData.prev, line));
      previousData.deleteData();
      break;
    }
  }

  std::cout << sum << std::endl;
  std::cout << sum2 << std::endl;
  return 0;
}
