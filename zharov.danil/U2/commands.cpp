#include "commands.hpp"
#include <io.hpp>
#include <utility>

namespace
{
  bool hasAnonId(const zharov::Array< size_t >& arr, size_t id)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      if (arr.data[i] == id)
      {
        return true;
      }
    }
    return false;
  }

  void selectionSort(zharov::Array< size_t >& arr)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      size_t minIdx = i;
      for (size_t j = i + 1; j < arr.size; ++j)
      {
        if (arr.data[j] < arr.data[minIdx])
        {
          minIdx = j;
        }
      }
      std::swap(arr.data[i], arr.data[minIdx]);
    }
  }
}

void zharov::runAnons(std::ostream& out, std::istream&, const Context& ctx)
{
  Array< size_t > anons = makeArray< size_t >(ctx.meets->size * 2 + 1);
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    size_t id1 = ctx.meets->data[i].id1;
    size_t id2 = ctx.meets->data[i].id2;
    if (!hasId(*ctx.persons, id1) && !hasAnonId(anons, id1))
    {
      pushBack(anons, id1);
    }
    if (!hasId(*ctx.persons, id2) && !hasAnonId(anons, id2))
    {
      pushBack(anons, id2);
    }
  }
  selectionSort(anons);
  for (size_t i = 0; i < anons.size; ++i)
  {
    out << anons.data[i] << "\n";
  }
  clear(anons);
}

void zharov::runDesc(std::ostream&, std::istream&, const Context&)
{}

void zharov::runMeets(std::ostream&, std::istream&, const Context&)
{}

void zharov::runCommons(std::ostream&, std::istream&, const Context&)
{}

void zharov::runLess(std::ostream&, std::istream&, const Context&)
{}

void zharov::runGreater(std::ostream&, std::istream&, const Context&)
{}

void zharov::runOutPersons(std::ostream&, std::istream&, const Context&)
{}

void zharov::runDeanon(std::ostream&, std::istream&, Context&)
{}

void zharov::runRedesc(std::ostream&, std::istream&, Context&)
{}