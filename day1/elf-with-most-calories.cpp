#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class PseudoMinHeap
{
  int size;
  std::vector<int> internalarr;

public:
  PseudoMinHeap(int _size) : size(_size) {}

  void add(int i)
  {
    if (internalarr.size() < size) {
      internalarr.push_back(i);
    } 
    else if (internalarr.size() == size && i > internalarr[0]) {
      internalarr[0] = i;
    }
    
    sort(internalarr.begin(), internalarr.end());
  }

  std::vector<int> getTop()
  {
    return internalarr;
  }
};

int elfWithMostCalories(std::string filepath)
{
  int maxElfCalories = -1;
  int elfWithMaxCalories = -1;

  // MIN HEAP OF SZE 3
  PseudoMinHeap heap(3);

  // read the file line by line each line break indicates a new
  std::ifstream inFile(filepath);
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }

  int elfcounter = 1;
  int currElfCalories = 0;
  std::string line;
  while (std::getline(inFile, line))
  {
    // if line is empty compare last elf stats and then reset elfcounter and curr elf calories
    if (line.size() == 0)
    {
      std::cout << "ELF " << elfcounter << " has " << currElfCalories << "\n";
      if (currElfCalories > maxElfCalories)
      {
        maxElfCalories = currElfCalories;
        elfWithMaxCalories = elfcounter;
      }
      heap.add(currElfCalories);
      currElfCalories = 0;
      elfcounter++;
    }
    else
    {
      // otherwise keep accumulating
      int calorieInItem = std::stoi(line);
      currElfCalories += calorieInItem;
    }
  }
      heap.add(currElfCalories);

  if (currElfCalories > maxElfCalories)
  {
    std::cout << "ELF " << elfcounter << " has " << currElfCalories << "\n";
    maxElfCalories = currElfCalories;
    elfWithMaxCalories = elfcounter;
  }

  int maxCals = maxElfCalories;
  auto topthree = heap.getTop();
  int topthreecals = 0;
  for (int i = 0; i < topthree.size(); i++)
  {
    std::cout << topthree.at(i) << std::endl;
    topthreecals += topthree.at(i);
  }
  return topthreecals;
}

int main()
{
  std::cout << elfWithMostCalories("./elf-calories.txt") << std::endl;
  return 0;
}
