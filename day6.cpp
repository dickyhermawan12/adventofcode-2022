#include <iostream>
#include <fstream>
#include <queue>
#include <set>

struct Signal
{
  bool isFound;
  int charIndex;
  int marker;
  std::queue<char> q;

  Signal()
  {
    isFound = false;
    charIndex = -1;
  }
};

/**
 * @brief  Checks if there are duplicate characters in the queue.
 *
 * @param q  The queue to be checked
 * @param size  The size of the queue
 * @return  True if there are duplicates, false otherwise
 */
bool duplicateExists(std::queue<char> &q, int size)
{
  std::set<char> s;
  for (int i = 0; i < size; i++)
  {
    char c = q.front();
    s.insert(c);
    q.pop();
    q.push(c);
  }

  if (s.size() == size)
    return false;

  return true;
}

/**
 * @brief  Modifies the signal.
 *
 * @param signal  The signal to be modified
 * @param c  The character to be added to the queue
 */
void modifySignal(Signal &signal, char c)
{
  signal.charIndex++;
  if (signal.q.size() >= signal.marker)
  {
    if (!duplicateExists(signal.q, signal.marker))
      signal.isFound = true;
    signal.q.pop();
  }
  signal.q.push(c);
}

int main()
{
  std::ifstream input("input/day6.txt");
  char c;
  Signal packet, message;
  packet.marker = 4;
  message.marker = 14;

  while (input.get(c))
  {
    if (!packet.isFound)
      modifySignal(packet, c);

    if (!message.isFound)
      modifySignal(message, c);

    if (packet.isFound && message.isFound)
      break;
  }

  std::cout << packet.charIndex << std::endl;
  std::cout << message.charIndex << std::endl;
  return 0;
}
