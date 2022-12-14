#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

int getNumFromInstruction(std::string& line) {
  return std::stoi(line.substr(5, line.size()));
}


class Display {
  std::vector<std::vector<char> > screen;
  
  public:
  Display() {
    std::vector<char> row(40, '.');
    std::vector<std::vector<char> > display(6, row);
    screen = display;
  }

  void Set(int spriteplacement, int cycle) {
    int row = (cycle % 7)-1;

    screen[row][spriteplacement-1] = cycle == spriteplacement-1 ? '#' : screen[row][spriteplacement-1];
    screen[row][spriteplacement] = cycle == spriteplacement ? '#' : screen[row][spriteplacement];
    screen[row][spriteplacement+1] = cycle == spriteplacement+1 ? '#' : screen[row][spriteplacement+1];

  }

  void Print() {
    for (auto d : screen) {
      for (auto c : d) {
        std::cout<< c;
      }
      std::cout << "\n";
    }
  }
};

int sol(std::ifstream& stream)
{

  Display d;
  int cycle = 1;
  int x = 1;
  
  std::unordered_map<int, int> processingqueue;

  int twenty;
  int sixty;
  int hundred;
  int oneforty;
  int oneighty;
  int twotwenty;


  std::string line;
  while (std::getline(stream, line)) {
    int k = 1;
    
    if (line.at(0) != 'n') {
      // Take the addx, and put it in processing holders 
      int futureCycle = cycle+1;
      int val = getNumFromInstruction(line);
      processingqueue[futureCycle] = val;
      k = 2;
    }

    for (int i = 0; i < k; i++) {
      std::cout << "During Cycle " << cycle << " X is "<< x << std::endl;
      
      // PART 2:
      // BASED on curr register place sprint on a vector of 0 - 39
      d.Set(x, cycle);
      
      if (cycle == 20) {
        twenty = x;
      } else if (cycle == 60) {
        sixty = x;
      } else if (cycle == 100) {
        hundred = x;
      } else if (cycle == 140) {
        oneforty = x;
      } else if (cycle == 180) {
        oneighty = x;
      } else if (cycle == 220) {
        twotwenty = x;
      }


      if (processingqueue.find(cycle) != processingqueue.end()) {
        x += processingqueue.at(cycle);
        processingqueue.erase(cycle);
      }
      cycle++;
    }
    
  }
    d.Print();

  // int maxCycle;
  // for (auto kv : processingqueue) {
  //   maxCycle = std::max(maxCycle, kv.first);
  // }

  // for (int i = cycle; i <= maxCycle; i++) {
  //   if (processingqueue.find(i) != processingqueue.end()) {
  //     x += processingqueue.at(i);
  //   }
  //   std::cout << "At End of Cycle " << i << " X is "<< x << std::endl;
  // }

  return 20*twenty + 60*sixty + 100*hundred + 140*oneforty + 180*oneighty + 220*twotwenty;
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

  int res1 = sol(inFile);
  std::cout << res1 << std::endl;

}
