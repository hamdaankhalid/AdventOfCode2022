#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <memory>

class Directo
{

public:
  std::vector<std::shared_ptr<Directo>> children;
  std::string name;
  std::unordered_map<std::string, long int> directoectfiles;

  Directo(std::string &n) : name(n) {}

  long int Size(std::unordered_map<std::string, long int> &childSizeMemo)
  {
    if (childSizeMemo.find(name) != childSizeMemo.end())
    {
      return childSizeMemo[name];
    }

    long int childrensizes = 0;
    
    for (auto child : children)
    {
      long int size = size = child->Size(childSizeMemo);
      childrensizes += size;
    }
    long int directoectsizes = 0;
    for (auto pair : directoectfiles)
    {
      directoectsizes += pair.second;
    }
    childSizeMemo[name] = childrensizes + directoectsizes;
    return childSizeMemo[name];
  }

  void AddChild(std::shared_ptr<Directo> directo)
  {
    children.push_back(directo);
  }

  void AddDirectoectFile(std::string &filename, long int size)
  {
    directoectfiles.insert({filename, size});
  }
};

struct ParsedFileLine
{
  std::string filename;
  long int filesize;

  static ParsedFileLine FromLine(std::string line)
  {
    std::string filesize = "";
    bool addFileName = false;
    std::string filename = "";
    for (auto c : line)
    {
      if (c == ' ')
      {
        addFileName = true;
      }
      else if (addFileName)
      {
        filename += c;
      }
      else
      {
        filesize += c;
      }
    }

    ParsedFileLine res;
    res.filename = filename;
    res.filesize = std::stol(filesize);

    return res;
  }
};

class Result
{
public:
  long int part1(std::ifstream &stream, int threshold)
  {
    char command = '$';
    std::string goback = "..";

    std::unordered_map<std::string, std::shared_ptr<Directo>> nodeLookup;

    std::deque<std::shared_ptr<Directo>> directoStack;

    std::string line;
    while (std::getline(stream, line)) {
      // std::cout << line << std::endl;
      if (line.at(0) == command && line.at(2) == 'c')
      {
        if (line.substr(5, 7) == goback)
        {
          directoStack.pop_back();
        }
        else
        {
          auto directoName = line.substr(5, line.size() - 5);
          if (nodeLookup.find(directoName) == nodeLookup.end())
          {
            auto newDirecto = std::make_shared<Directo>(directoName);
            nodeLookup.insert({directoName, newDirecto});
          }
          auto r = nodeLookup[directoName];
          directoStack.push_back(r);
        }
      }
      else if (line.at(0) == command && line.at(2) == 'l')
      { // skip ls
        continue;
      }
      else
      {
        auto currDirecto = directoStack.back();

        if (line.substr(0, 3) != "dir")
        {

          auto details = ParsedFileLine::FromLine(line);
          currDirecto->AddDirectoectFile(details.filename, details.filesize);
        }
        else
        {
          auto directoName = line.substr(4, line.size() - 4);
          if (nodeLookup.find(directoName) == nodeLookup.end())
          {
            auto dir = std::make_shared<Directo>(directoName);
            currDirecto->AddChild(dir);
            nodeLookup.insert({directoName, dir});
          }
          else
          {
            auto dir = nodeLookup[directoName];
            currDirecto->AddChild(dir);
          }
        }
      }

      // std::cout << directoStack.back()->name << std::endl;
    }

    directoStack.clear();
    // Perform querying
    std::unordered_map<std::string, long int> childSizeMemo;
    long int res = 0;
    for (auto pair : nodeLookup)
    {
      long int size = pair.second->Size(childSizeMemo);
      if (size <= threshold)
      {
        res += size;
      }
    }

    return res;
  }
};

int main()
{
  std::ifstream inFile("./input.txt");
  if (inFile.fail())
  {
    std::cout << "Failed to open file" << std::endl;
    inFile.close();
    return -1;
  }

  std::unique_ptr<Result> resultcalc;
  auto res = resultcalc->part1(inFile, 100000);

  std::cout << "Part 1: " << res << std::endl;
  return 0;
}
