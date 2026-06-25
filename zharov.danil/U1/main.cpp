#include <fstream>
#include <iostream>
#include <string>
#include <array.hpp>
#include "person.hpp"

namespace zharov
{
  bool parseLine(const std::string& str, Person& p);
}

namespace
{
  bool hasId(const zharov::Array< zharov::Person >& arr, size_t id)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      if (arr.data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }
}

int main(int argc, char** argv)
{
  zharov::Array< zharov::Person > persons = zharov::makeArray< zharov::Person >(10);
  if (argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    zharov::clear(persons);
    return 0;
  }
  std::string inFile;
  std::string outFile;
  bool hasIn = false;
  bool hasOut = false;
  std::istream* in = std::addressof(std::cin);
  std::ostream* out = std::addressof(std::cout);
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (arg.size() > 3 && arg.substr(0, 3) == "in:")
    {
      if (hasIn)
      {
        std::cerr << "Invalid arguments\n";
        zharov::clear(persons);
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
        zharov::clear(persons);
        return 1;
      }
      outFile = arg.substr(4);
      hasOut = true;
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      zharov::clear(persons);
      return 1;
    }
  }
  std::ifstream file_in;
  if (hasIn)
  {
    file_in.open(inFile);
    if (!file_in.is_open())
    {
      std::cerr << "Cannot open file\n";
      zharov::clear(persons);
      return 2;
    }
    in = std::addressof(file_in);
  }

  size_t accepted = 0;
  size_t ignored = 0;
  std::string line;
  while (std::getline(*in, line))
  {
    if (line.empty())
    {
      continue;
    }
    zharov::Person p;
    if (!zharov::parseLine(line, p))
    {
      ++ignored;
      continue;
    }
    if (hasId(persons, p.id))
    {
      ++ignored;
      continue;
    }
    zharov::pushBack(persons, p);
    ++accepted;
  }
  std::ofstream file_out;
  if (hasOut)
  {
    file_out.open(outFile);
    if (!file_out.is_open())
    {
      std::cerr << "Cannot open file\n";
      zharov::clear(persons);
      return 2;
    }
    out = std::addressof(file_out);
  }
  for (size_t i = 0; i < persons.size; ++i)
  {
    *out << persons.data[i].id << " " << persons.data[i].info << "\n";
  }
  if (persons.size == 0)
  {
    *out << "\n";
  }
  std::cerr << accepted << " " << ignored << "\n";
  zharov::clear(persons);
}


bool zharov::parseLine(const std::string& str, Person& p)
{
  size_t pos = 0;
  size_t id = 0;
  try
  {
    id = std::stoul(str, &pos);
  }
  catch (...)
  {
    return false;
  }
  while (pos < str.size() && (str[pos] == ' ' || str[pos] == '\t'))
  {
    ++pos;
  }
  if (pos == str.size())
  {
    return false;
  }
  p.id = id;
  p.info = str.substr(pos);
  return true;
}
