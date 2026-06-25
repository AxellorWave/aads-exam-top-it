#include <fstream>
#include <iostream>
#include <string>
#include <array.hpp>
#include "person.hpp"

namespace zharov
{
  zharov::Person parseLine(const std::string & str);
}

int main(int argc, char** argv)
{
  zharov::Array< zharov::Person > persons;
  if (argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::string inFile;
  std::string outFile;
  bool hasIn = false;
  bool hasOut = false;
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (arg.size() > 3 && arg.substr(0, 3) == "in:")
    {
      if (hasIn)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inFile = arg.substr(3);
      hasIn = true;
    }
    else if (arg.size() > 4 && arg.substr(0, 4) == "out:")
    {
      if (hasOut)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      outFile = arg.substr(4);
      hasOut = true;
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  std::ifstream file_in;
  std::ofstream file_out;
  std::istream* in = std::addressof(std::cin);
  std::ostream* out = std::addressof(std::cout);
  if (hasIn)
  {
    file_in.open(inFile);
    if (!file_in.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 2;
    }
    in = std::addressof(file_in);
  }
  if (hasOut)
  {
    file_out.open(outFile);
    if (!file_out.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 2;
    }
    out = std::addressof(file_out);
  }

  std::string line;
  while (!std::getline(*in, line).eof())
  {
    if (line.empty())
    {
      continue;
    }
    zharov::Person p = zharov::parseLine(line);
    zharov::pushBack(persons, p);
  }
}


zharov::Person parseLine(const std::string& str)
{}