#include "aoc.h"

namespace day14
{
  REGISTER_DAY(day14, std::set<Index2D>, int);

  REGISTER_TEST_EXAMPLE(day14, ExampleInput, 1, 24);
  REGISTER_TEST        (day14, Input,        1, 768);
  REGISTER_TEST_EXAMPLE(day14, ExampleInput, 2, 93);
  REGISTER_TEST        (day14, Input,        2, 26686);

  READ_INPUT(input)
  {
    std::string str;
    std::set<Index2D> occupied;
    int sum = 0;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Index2D start;
      ss >> start.x >> "," >> start.y;
      while ((ss >> "->"))
      {
				Index2D next;
				ss >> next.x >> "," >> next.y;
        for (int y = std::min(start.y, next.y); y <= std::max(start.y, next.y); y++)
        {
					for (int x = std::min(start.x, next.x); x <= std::max(start.x, next.x); x++)
					{
            occupied.emplace(Index2D{x, y});
					}
        }
        start = next;
      }
    }
    return occupied;
  }

  OUTPUT1(input)
  {
    int maxY = input.begin()->y;
    for (auto& index : input)
    {
      maxY = std::max(maxY, index.y);
    }
    maxY += 2;
    Array2D<char> grid{maxY * 2 - 1, maxY};
    grid.Fill('.');
    for (auto& index : input)
    {
      grid.Set(index.x - 500 + maxY - 1, index.y, '#');
    }
    while (true)
    {
      Index2D sand{maxY-1, 0};
      while (true)
      { 
        if(sand.y >= maxY - 2)
          return grid.Count('o');
        else if(grid.Get(sand.x, sand.y + 1) == '.')
          sand.y++;
        else if (grid.Get(sand.x - 1, sand.y + 1) == '.')
        {
          sand.x--;
          sand.y++;
        }
        else if (grid.Get(sand.x + 1, sand.y + 1) == '.')
        {
          sand.x++;
          sand.y++;
        }
        else
        {
          grid.Set(sand.x, sand.y, 'o');
          break;
        }
      }
    }
    return 0;
    return 0;
  }

  OUTPUT2(input)
  {
    int maxY = input.begin()->y;
    for (auto& index : input)
    {
      maxY = std::max(maxY, index.y);
    }
    maxY += 2;
    Array2D<char> grid{maxY * 2 - 1, maxY};
    grid.Fill('.');
    for (auto& index : input)
    {
      grid.Set(index.x - 500 + maxY - 1, index.y, '#');
    }
    while (true)
    {
      Index2D sand{maxY-1, 0};
      while (true)
      { 
        if(grid.Get(sand.x, sand.y + 1) == '.')
          sand.y++;
        else if (grid.Get(sand.x - 1, sand.y + 1) == '.')
        {
          sand.x--;
          sand.y++;
        }
        else if (grid.Get(sand.x + 1, sand.y + 1) == '.')
        {
          sand.x++;
          sand.y++;
        }
        else if (sand.y == 0)
        {
          grid.Set(sand.x, sand.y, 'o');
          return grid.Count('o');
        }
        else
        {
          grid.Set(sand.x, sand.y, 'o');
          break;
        }
        if (sand.y + 1 >= maxY)
        {
          grid.Set(sand.x, sand.y, 'o');
          break;
        }
      }
    }
    return 0;
  }
}
