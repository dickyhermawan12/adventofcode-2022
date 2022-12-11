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

void changeSegmentPos(Coord &h, Coord &t)
{
  int diff[2] = {h.x - t.x, h.y - t.y};
  if (abs(diff[0]) < 2 && abs(diff[1]) < 2)
    return;

  if (h.x > t.x)
    t.x++;
  else if (h.x < t.x)
    t.x--;
  if (h.y > t.y)
    t.y++;
  else if (h.y < t.y)
    t.y--;
}

void changeBodyPos(Rope &s)
{
  for (int i = 0; i < s.body->size(); i++)
  {
    if (i == 0)
      changeSegmentPos(s.head, s.body->data()[i]);
    else
      changeSegmentPos(s.body->data()[i - 1], s.body->data()[i]);
  }
}

std::set<Coord> *move(Rope &s, char dir, int amount)
{
  std::set<Coord> *newCoords = new std::set<Coord>();
  for (int i = 0; i < amount; i++)
  {
    switch (dir)
    {
    case 'U':
      s.head.y++;
      break;
    case 'D':
      s.head.y--;
      break;
    case 'L':
      s.head.x--;
      break;
    case 'R':
      s.head.x++;
      break;
    }
    changeBodyPos(s);
    newCoords->insert(s.body->data()[s.body->size() - 1]);
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

  std::cout << "Number of unique coordinates: " << tCoords1.size() << std::endl;
  std::cout << "Number of unique coordinates: " << tCoords2.size() << std::endl;
  return 0;
}