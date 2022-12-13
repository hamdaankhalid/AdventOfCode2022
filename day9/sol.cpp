#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>


struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

enum Direction
{
  U = 1,
  D = -1,
  L = -1,
  R = 1
};

class RopeBoard {

  const std::unordered_map<char, Direction> dirtransform = {
      {'U', Direction::U},
      {'D', Direction::D},
      {'L', Direction::L},
      {'R', Direction::R}};

  std::unordered_set<std::pair<int, int>, pair_hash> visitedByTail = {{0, 0}};

public:
  int GetTailVisitedSiteNum()
  {
    return visitedByTail.size();
  }


  void MoveHead(char dir, int steps, std::pair<int, int>& head, std::vector<std::pair<int, int>>& tails)
  {
    
    std::cout << "--------" << dir << ", " << steps << "-------------\n";
    Direction offset = dirtransform.at(dir);
    for (int i = 0; i < steps; i++)
    {
      if (dir == 'U' || dir == 'D')
      {
        // offset manipulates row dir
        head.first += offset;
      }
      else
      {
        // offset manipulates in col dir
        head.second += offset;
      }

      std::cout << "Head " << head.first << ", " << head.second << std::endl;


      std::pair<int, int> currhead = head;
      int j = 1;
      for (std::pair<int,int>& tail : tails) {
        MoveTailAccordingToHead(currhead, tail);
        std::cout << "Tail " << j << " " << tail.first << ", " << tail.second << std::endl;
        currhead = tail;
        j++;
      }

      // insert new pos in hashset
      visitedByTail.insert(tails[tails.size()-1]);
    }
  }

private:
  
  void MoveTailAccordingToHead(std::pair<int, int>& head, std::pair<int, int>& tail) {
    if (tail.second == head.second && head.first - tail.first == 2)
      {
        tail.first += 1;
      }
      else if (tail.second == head.second && head.first - tail.first == -2)
      {
        tail.first -= 1;
      }
      else if (tail.first == head.first && head.second - tail.second == 2)
      { // head and tail are horizontally 2 steps apart
        tail.second += 1;
      }
      else if (tail.first == head.first && head.second - tail.second == -2)
      {
        tail.second -= 1;
      }
      // diagonal cases
      else if (head.first != tail.first && head.second != tail.second)
      {
        MoveTailDiagonalOffset(head, tail);
      }
  }

  void MoveTailDiagonalOffset(std::pair<int, int> &head, std::pair<int, int> &tail)
  {
    // 2 above 2 right
    if (tail.first + 2 == head.first && tail.second + 2 == head.second)
    {
      tail.first += 1;
      tail.second += 1;
    }
    // upper right 1 col and 2 rows diff
    if (tail.first + 2 == head.first && tail.second + 1 == head.second)
    {
      tail.first += 1;
      tail.second += 1;
    }
    // upper right 2 cols and 1 row diff
    else if (tail.first + 1 == head.first && tail.second + 2 == head.second)
    {
      tail.first += 1;
      tail.second += 1;
    }
    // bottom right 1 col and 2 rows diff
    else if (tail.first - 2 == head.first && tail.second + 1 == head.second)
    {
      tail.first -= 1;
      tail.second += 1;
    }
    // bottom right 2 cols and 1 row diff
    else if (tail.first - 1 == head.first && tail.second + 2 == head.second)
    {
      tail.first -= 1;
      tail.second += 1;
    }
    if (tail.first + 2 == head.first && tail.second - 1 == head.second)
    {
      tail.first += 1;
      tail.second -= 1;
    }
    // 2 Below 2 right
    if (tail.first - 2 == head.first && tail.second + 2 == head.second)
    {
      tail.first -= 1;
      tail.second += 1;
    }
    // upper left 1 col and 2 rows diff
    if (tail.first + 2 == head.first && tail.second - 1 == head.second)
    {
      tail.first += 1;
      tail.second -= 1;
    }
    // upper left 2 cols and 1 row diff
    else if (tail.first + 1 == head.first && tail.second - 2 == head.second)
    {
      tail.first += 1;
      tail.second -= 1;
    }
    // bottom left 1 col and 2 rows diff
    else if (tail.first - 2 == head.first && tail.second - 1 == head.second)
    {
      tail.first -= 1;
      tail.second -= 1;
    }
    // bottom left 2 cols and 1 row diff
    else if (tail.first - 1 == head.first && tail.second - 2 == head.second)
    {
      tail.first -= 1;
      tail.second -= 1;
    }
    // 2 above 2 left
    if (tail.first + 2 == head.first && tail.second - 2 == head.second)
    {
      tail.first += 1;
      tail.second -= 1;
    }
    // 2 below 2 left
    if (tail.first - 2 == head.first && tail.second - 2 == head.second)
    {
      tail.first -= 1;
      tail.second -= 1;
    }
  }
};

int part1(std::ifstream& stream)
{
  RopeBoard rb;
  std::string line;
  std::pair<int, int> head = {0,0};
  std::pair<int, int> tail = {0,0};
  std::vector<std::pair<int, int>> tails(1, tail);
  while (std::getline(stream, line))
  {
    char dir = line.at(0);
    int steps = std::stoi(line.substr(1, line.size()));
    rb.MoveHead(dir, steps, head, tails);
  }

  return rb.GetTailVisitedSiteNum();
}

int part2(std::ifstream& stream)
{
  RopeBoard rb;
  std::pair<int, int> head = {0,0};
  std::pair<int, int> tail = {0,0};

  // 0 of first know and 9 is last know 123..9
  std::vector<std::pair<int, int>> tails(9, tail);

  std::string line;
  while (std::getline(stream, line))
  {
    char dir = line.at(0);
    int steps = std::stoi(line.substr(1, line.size()));
    rb.MoveHead(dir, steps, head, tails);
  }

  return rb.GetTailVisitedSiteNum();
}

int main()
{
  std::ifstream inFile("./input.txt");
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }

  // int res1 = part1(inFile);

  std::cout << "############### \n";

  int res2 = part2(inFile);

  // std::cout << "PART 1: " << res1 << std::endl;
  std::cout << "PART 2: " << res2 << std::endl;
  return 0;
}
