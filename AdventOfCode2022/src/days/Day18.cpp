#include "aoc.h"

namespace day18
{
  REGISTER_DAY(day18, Array3D<char>, int);

  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 1, 64);
  REGISTER_TEST        (day18, Input,        1, 4504);
  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 2, 58);
  REGISTER_TEST        (day18, Input,        2, 2556);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Index3D> indices;
    Index3D min;
    Index3D max;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Index3D index;
      ss >> index.x >> "," >> index.y >> "," >> index.z;
      if (!min.IsValid())
        min = index;
      if (!max.IsValid())
        max = index;
      min.x = std::min(min.x, index.x);
      min.y = std::min(min.y, index.y);
      min.z = std::min(min.z, index.z);
      max.x = std::max(max.x, index.x);
      max.y = std::max(max.y, index.y);
      max.z = std::max(max.z, index.z);
      indices.emplace_back(index);
    }
    Array3D<char> grid{max.x - min.x + 3, max.y - min.y + 3, max.z - min.z + 3};
    grid.Fill('.');
    for (auto& index : indices)
    {
      grid.Set(index.x - min.x + 1, index.y - min.y + 1, index.z - min.z + 1, '#');
    }

    return grid;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    std::vector<Index3D> neighbors{Index3D{-1, 0, 0}, Index3D{1, 0, 0}, Index3D{0, -1, 0}, Index3D{0, 1, 0}, Index3D{0, 0, -1}, Index3D{0, 0, 1}};
    for (auto it = input.begin(); it != input.end(); ++it)
    {
      if (*it != '#') continue;
			sum += neighbors.size();

			for (auto& neighbor : neighbors)
			{
				Index3D i = it.index + neighbor;
				if (input.IsInside(i) && input.Get(i) == '#') sum--;
			}
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    std::set<Index3D> visited;
    std::stack<Index3D> stack;
    stack.emplace(Index3D{0, 0, 0});
    std::vector<Index3D> neighbors{Index3D{-1, 0, 0}, Index3D{1, 0, 0}, Index3D{0, -1, 0}, Index3D{0, 1, 0}, Index3D{0, 0, -1}, Index3D{0, 0, 1}};
    while (!stack.empty())
    {
      Index3D index = stack.top();
      stack.pop();

      for(auto& neighbor : neighbors)
      {
        Index3D i = index + neighbor;
        if (input.IsInside(i))
        {
          if(visited.count(i) == 0 && input.Get(i) == '.')
          {
            visited.emplace(i);
            stack.emplace(i);
          }
        }
      }
    }
    for (auto& index : visited)
    {
      for (auto& neighbor : neighbors)
      {
        Index3D i = index + neighbor;
        if (input.IsInside(i) && input.Get(i) == '#')
        {
          sum++;
        }
      }
    }
    return sum;
  }
}
