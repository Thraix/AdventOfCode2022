#include "aoc.h"

namespace day08
{
  REGISTER_DAY(day08, Array2D<int>, int);

  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 1, 21);
  REGISTER_TEST        (day08, Input,        1, 1820);
  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 2, 8);
  REGISTER_TEST        (day08, Input,        2, 385112);

  READ_INPUT(input)
  {
    return Input::ReadDigitsAsArray2D(input);
  }

  OUTPUT1(input)
  {

    // input.Each([&](const Array2D<int>& arr, const Index2D& index) {
    std::set<Index2D> found;
    for (auto it = input.begin(); it != input.end(); it++)
    {
      if (found.count(it.index) > 0)
        continue;
      bool visible = true;
      for (int x = it.index.x - 1; x >= 0; x--)
      {
        if (input.Get(x, it.index.y) >= *it)
        {
          visible = false;
          break;
        }
      }
      if (visible)
      {
        found.emplace(it.index);
        continue;
      }
      visible = true;
      for (int x = it.index.x + 1; x < input.width; x++)
      {
        if (input.Get(x, it.index.y) >= *it)
        {
          visible = false;
          break;
        }
      }
      if (visible)
      {
        found.emplace(it.index);
        continue;
      }
      visible = true;
      for (int y = it.index.y - 1; y >= 0; y--)
      {
        if (input.Get(it.index.x, y) >= *it)
        {
          visible = false;
          break;
        }
      }
      if (visible)
      {
        found.emplace(it.index);
        continue;
      }
      visible = true;
      for (int y = it.index.y + 1; y < input.height; y++)
      {
        if (input.Get(it.index.x, y) >= *it)
        {
          visible = false;
          break;
        }
      }
      if (visible)
      {
        found.emplace(it.index);
        continue;
      }
    };
    return found.size();
  }

  OUTPUT2(input)
  {
    int max = 0;
    for (auto it = input.begin(); it != input.end(); ++it)
    {
      int scenic = 1;
      bool found = false;
      for (int x = it.index.x - 1; x >= 0; x--)
      {
        if (*it <= input.Get(x, it.index.y))
        {
          scenic *= it.index.x - x;
          found = true;
          break;
        }
      }
      if (!found)
        scenic *= it.index.x;
      found = false;
      for (int x = it.index.x + 1; x < input.width; x++)
      {
        if (*it <= input.Get(x, it.index.y))
        {
          scenic *= x - it.index.x;
          found = true;
          break;
        }
      }
      if (!found)
        scenic *= input.width - it.index.x - 1;
      found = false;
      for (int y = it.index.y - 1; y >= 0; y--)
      {
        if (*it <= input.Get(it.index.x, y))
        {
          scenic *= it.index.y - y;
          found = true;
          break;
        }
      }
      if (!found)
        scenic *= it.index.y;
      found = false;
      for (int y = it.index.y + 1; y < input.height; y++)
      {
        if (*it <= input.Get(it.index.x, y))
        {
          scenic *= y - it.index.y;
          found = true;
          break;
        }
      }
      if (!found)
        scenic *= input.height - it.index.y - 1;
      max = std::max(max, scenic);
      
    };
    return  max;
  }
}
