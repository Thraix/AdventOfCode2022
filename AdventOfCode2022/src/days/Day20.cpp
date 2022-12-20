#include "aoc.h"

namespace day20
{
  REGISTER_DAY(day20, std::vector<int>, int64_t);

  REGISTER_TEST_EXAMPLE(day20, ExampleInput, 1, 3);
  REGISTER_TEST        (day20, Input,        1, 988);
  REGISTER_TEST_EXAMPLE(day20, ExampleInput, 2, 1623178306);
  REGISTER_TEST        (day20, Input,        2, 7768531372516);

  READ_INPUT(input)
  {
    return Input::ReadInts(input);
  }

  OUTPUT1(input)
  {
    int sum = 0;
    std::vector<std::pair<int, int>> newList;
    for (int i = 0; i < input.size(); i++)
    {
      newList.emplace_back(input[i], i);
    }
    for (int i = 0; i < input.size(); i++)
    {
      auto it = std::find_if(newList.begin(), newList.end(), [i](auto& p) { return p.second == i; });
      int distance = std::distance(newList.begin(), it);
      if (input[i] == 0) continue;
      int newPos = (distance + input[i]) % ((int)input.size() - 1);
      if (newPos < 0) newPos += (int)newList.size() - 1;
      std::pair<int, int> p = *it;
      newList.erase(it);
      newList.insert(newList.begin() + newPos, p);
    }
    // std::sort(newList.begin(), newList.end(), [](auto& p1, auto& p2) { return p1.second < p2.second; });
    auto it = std::find_if(newList.begin(), newList.end(), [](const std::pair<int, int>& p1) { return p1.first == 0; });
    int pos = std::distance(newList.begin(), it);
    return newList[(pos + 1000) % input.size()].first + newList[(pos + 2000) % input.size()].first + newList[(pos + 3000) % input.size()].first;
  }

  OUTPUT2(input)
  {
    int sum = 0;
		std::vector<std::pair<int64_t, int>> newList;
		for (int i = 0; i < input.size(); i++)
		{
			newList.emplace_back((int64_t)input[i] * (int64_t)811589153, i);
		}
    for (int j = 0; j < 10; j++)
    {
      for (int i = 0; i < input.size(); i++)
      {
        auto it = std::find_if(newList.begin(), newList.end(), [i](auto& p) { return p.second == i; });
        int oldPos = std::distance(newList.begin(), it);
        if (it->first == 0) continue;
        int newPos = (oldPos + it->first) % ((int64_t)input.size() - 1);
        if (newPos < 0) newPos += (int64_t)newList.size() - 1;
        std::pair<int64_t, int> p = *it;
        newList.erase(it);
        newList.insert(newList.begin() + newPos, p);
      }
    }
    // std::sort(newList.begin(), newList.end(), [](auto& p1, auto& p2) { return p1.second < p2.second; });
    auto it = std::find_if(newList.begin(), newList.end(), [](const std::pair<int64_t, int>& p1) { return p1.first == 0; });
    int pos = std::distance(newList.begin(), it);
    return newList[(pos + 1000) % input.size()].first + newList[(pos + 2000) % input.size()].first + newList[(pos + 3000) % input.size()].first;
  }
}
