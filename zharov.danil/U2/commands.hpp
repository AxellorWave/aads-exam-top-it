#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <ostream>
#include <array.hpp>
#include <person.hpp>

namespace zharov
{
  struct Context
  {
    Array< Person >* persons;
    Array< Meet >* meets;
  };

  using Cmd = void (*)(std::ostream&, std::istream&, Context&);

  void cmdAnons(std::ostream&, std::istream&, Context&);
  void cmdDeanon(std::ostream&, std::istream&, Context&);
  void cmdRedesc(std::ostream&, std::istream&, Context&);
  void cmdDesc(std::ostream&, std::istream&, Context&);
  void cmdMeets(std::ostream&, std::istream&, Context&);
  void cmdCommons(std::ostream&, std::istream&, Context&);
  void cmdLess(std::ostream&, std::istream&, Context&);
  void cmdGreater(std::ostream&, std::istream&, Context&);
  void cmdOutPersons(std::ostream&, std::istream&, Context&);
}

#endif
