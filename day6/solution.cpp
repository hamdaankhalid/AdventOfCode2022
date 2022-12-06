#include <string>

int findMarker(std::string filepath) {
  std::ifstream inFile(filepath);
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }

  int marker = -1;
  std::string line;
  while (std::getline(inFile, line)) {
    // keep going through chars till we have come across 4 straight unique chars in a row
    for (auto c : line) {

    }
  }

  return marker;
}
int main() {
  return 0;
}
