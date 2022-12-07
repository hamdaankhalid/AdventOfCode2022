#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>


int findIdxOfLastOccurrence(std::vector<char>& v, char tofind) {
  for (int i = v.size() - 1; i > -1; i--) {
    if (v.at(i) == tofind) {
      return i;
    }
  }

  return -1;
}


int findMarker(std::string filepath, int uniqueSize) {
  std::ifstream inFile(filepath);
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }

  int marker = -1;

  std::string line;
  std::getline(inFile, line);

  std::vector<char> currentmarkers;  

  for (int r = 0; r < line.size(); r++) {
    for (auto c : currentmarkers) {
        std::cout << c << ",";
      }
      std::cout << "\n";

    if (currentmarkers.size() == uniqueSize) {
      return r;
    }
    auto found = findIdxOfLastOccurrence(currentmarkers, line.at(r));
    if (found != -1) {
      currentmarkers.erase(currentmarkers.begin(), currentmarkers.begin() + found + 1);
    }
    currentmarkers.push_back(line.at(r));
    
  }

  return marker;
}


int main() {
  std::cout << findMarker("input.txt", 14) << std::endl;
  return 0;
}
