#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <tuple>

struct Coord
{
  int x;
  int y;

  bool operator<(const Coord &other) const
  {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }
};

struct Rope
{
  Coord head;
  std::vector<Coord> *body;
};

/**
 * @brief  Moves the segment of the rope relative to the previous segment
 *
 * @param p  The previous segment of the rope
 * @param s  The segment to move
 */
void changeSegmentPos(Coord &p, Coord &s)
{
  int diff[2] = {p.x - s.x, p.y - s.y};
  if (abs(diff[0]) < 2 && abs(diff[1]) < 2)
    return;

  if (p.x > s.x)
    s.x++;
  else if (p.x < s.x)
    s.x--;
  if (p.y > s.y)
    s.y++;
  else if (p.y < s.y)
    s.y--;
}

/**
 * @brief  Moves the body of the rope relative to the head
 *
 * @param r  The rope to move
 */
void changeBodyPos(Rope &r)
{
  for (int i = 0; i < r.body->size(); i++)
  {
    if (i == 0)
      changeSegmentPos(r.head, r.body->data()[i]);
    else
      changeSegmentPos(r.body->data()[i - 1], r.body->data()[i]);
  }
}

/**
 * @brief  Moves the head of the rope and returns the new coordinates of the tail
 *
 * @param r  The rope to move
 * @param dir  The direction to move in
 * @param amount  The amount to move
 * @return  The path of the tail
 */
std::set<Coord> *move(Rope &r, char dir, int amount)
{
  std::set<Coord> *newCoords = new std::set<Coord>();
  for (int i = 0; i < amount; i++)
  {
    switch (dir)
    {
    case 'U':
      r.head.y++;
      break;
    case 'D':
      r.head.y--;
      break;
    case 'L':
      r.head.x--;
      break;
    case 'R':
      r.head.x++;
      break;
    }
    changeBodyPos(r);
    newCoords->insert(r.body->data()[r.body->size() - 1]);
  }
  return newCoords;
}

int main()
{
  std::ifstream file("input/day9.txt");
  std::string line;
  Rope rope1 = {.head = {0, 0}, .body = new std::vector<Coord>(1, {0, 0})};
  Rope rope2 = {.head = {0, 0}, .body = new std::vector<Coord>(9, {0, 0})};
  std::set<Coord> tCoords1, tCoords2;

  while (std::getline(file, line))
  {
    char dir = line[0];
    int amount = std::stoi(line.substr(1));
    std::set<Coord> coords = *move(rope1, dir, amount);
    tCoords1.insert(coords.begin(), coords.end());

    coords = *move(rope2, dir, amount);
    tCoords2.insert(coords.begin(), coords.end());
  }

  std::cout << tCoords1.size() << std::endl;
  std::cout << tCoords2.size() << std::endl;
  return 0;
}