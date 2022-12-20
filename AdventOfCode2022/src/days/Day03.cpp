#include "aoc.h"

namespace day03
{
  REGISTER_DAY(day03, std::vector<std::string>, int);

  REGISTER_TEST_EXAMPLE(day03, ExampleInput, 1, 157);
  REGISTER_TEST        (day03, Input,        1, 7811);
  REGISTER_TEST_EXAMPLE(day03, ExampleInput, 2, 70);
  REGISTER_TEST        (day03, Input,        2, 2639);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<std::string> backpacks;
    while (std::getline(input, str))
    {
      backpacks.emplace_back(str);
    }
    return backpacks;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    for (auto& backpack : input)
    {
      std::set<char> s1;
      std::set<char> s2;
      for (int i = 0; i < backpack.size(); i++)
      {
        if (i < backpack.size() / 2)
        {
          s1.emplace(backpack[i]);
        }
        else
        {
          s2.emplace(backpack[i]);
        }
      }
      std::set<char> intersection = Helper::GetIntersection(s1, s2);
      for (auto c : intersection)
      {
        if (c >= 'A' && c <= 'Z') sum += c - 'A' + 27;
        else sum += c - 'a' + 1;
      }
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    for (int i = 0; i < input.size() - 2; i += 3)
    {
      std::set<char> s1;
      std::set<char> s2;
      std::set<char> s3;
      for (int j = 0; j < input[i].size(); j++)
      {
				s1.emplace(input[i][j]);
      }
      for (int j = 0; j < input[i + 1].size(); j++)
      {
				s2.emplace(input[i + 1][j]);
      }
      for (int j = 0; j < input[i + 2].size(); j++)
      {
				s3.emplace(input[i + 2][j]);
      }
      std::set<char> intersection = Helper::GetIntersection(std::vector<std::set<char>>{s1, s2, s3});
      for (auto c : intersection)
      {
        if (c >= 'A' && c <= 'Z') sum += c - 'A' + 27;
        else sum += c - 'a' + 1;
      }
    }
    return sum;
  }
}
