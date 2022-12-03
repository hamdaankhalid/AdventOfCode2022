#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include <vector>

/**
 * Your total score is the sum of your scores for each round. 
 * The score for a single round is the score for the shape you
 *  selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus 
 * the score for the outcome of the round (0 if you lost, 3 if 
 * the round was a draw, and 6 if you won).
 * 
 * ME X for Rock, Y for Paper, and Z for Scissors.
 * OPP A for Rock, B for Paper, and C for Scissors. 
 * */

int findScore(std::ifstream& stream) {
  // whatever is on your direct right beat whats on diret left, connect head to tail
  std::vector<std::string> hierarchies { "Z" , "Y" , "X" };

  std::unordered_map<std::string, std::string> opponentMap{
    {"A", "X"},
    {"B", "Y"},
    {"C", "Z"}
  };
  std::unordered_map<std::string, int> myscoreselection{
    {"Z", 3},
    {"Y", 2},
    {"X", 1}
  };

  int score = 0;
  std::string line;
  while (std::getline(stream, line)) {
    // split string by space
    std::stringstream linetostream(line);
    std::string opponent, me;
    std::getline(linetostream, opponent, ' ');
    std::getline(linetostream, me, ' ');
      
    // get score and increment score
    auto opponentMapped = opponentMap.at(opponent);
    
    // index of opponent move
    int opponnetIdx = std::find(hierarchies.begin(), hierarchies.end(), opponentMapped) - hierarchies.begin();
    
    // if I have this index then opponent wins
    int losingIdx = opponnetIdx == hierarchies.size()-1 ? 0 : opponnetIdx+1;
    
    int myIdx = std::find(hierarchies.begin(), hierarchies.end(), me) - hierarchies.begin();
    int resScore;
    if (myIdx == opponnetIdx) { // draw
      resScore = 3;
    } else if (myIdx == losingIdx) {
      resScore = 0;
    } else { // won
      resScore = 6;
    }
    auto s = myscoreselection.at(me) + resScore;
    score += s;
  }

  return score;
}

int findScoreTwo(std::ifstream& stream) {
  // whatever is on your direct right beat whats on diret left, connect head to tail
  std::vector<std::string> hierarchies { "Z" , "Y" , "X" };

  std::unordered_map<std::string, std::string> opponentMap{
    {"A", "X"},
    {"B", "Y"},
    {"C", "Z"}
  };

  std::unordered_map<std::string, int> myscoreselection{
    {"Z", 3},
    {"Y", 2},
    {"X", 1}
  };

  int score = 0;
  std::string line;
  while (std::getline(stream, line)) {
    // split string by space
    std::stringstream linetostream(line);
    std::string opponent, scenario;
    std::getline(linetostream, opponent, ' ');
    std::getline(linetostream, scenario, ' ');
      
    // get score and increment score
    auto opponentMapped = opponentMap.at(opponent);

    // index of opponent move
    int opponnetIdx = std::find(hierarchies.begin(), hierarchies.end(), opponentMapped) - hierarchies.begin();
    
    // if I have this index then opponent wins
    int losingIdx = opponnetIdx == hierarchies.size()-1 ? 0 : opponnetIdx+1;
    
    std::string me;
    int resScore;
    if (scenario == "X") { // LOSE
       me = hierarchies.at(losingIdx);
       resScore = 0;
    } else if (scenario == "Y") { // DRAW
       me = hierarchies.at(opponnetIdx);
       resScore = 3;
    } else { // WIN
      me = opponnetIdx == 0 ? hierarchies.at(hierarchies.size()-1) : hierarchies.at(opponnetIdx-1);
      resScore = 6;
    }

    auto s = myscoreselection.at(me) + resScore;
    score += s;
  }

  return score;
}

int main() {
  std::ifstream inFile("./input.txt");
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }
  std::cout << findScoreTwo(inFile) << std::endl;
}
