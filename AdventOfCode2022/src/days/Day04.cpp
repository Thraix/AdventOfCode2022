#include "aoc.h"

namespace day04
{
  struct Range
  {
    int left = 0;
    int right = 0;

  };
  struct Pair
  {
    Range r1;
    Range r2;
  };

  REGISTER_DAY(day04, std::vector<Pair>, int);

  REGISTER_TEST_EXAMPLE(day04, ExampleInput, 1, 2);
  REGISTER_TEST        (day04, Input,        1, 477);
  REGISTER_TEST_EXAMPLE(day04, ExampleInput, 2, 4);
  REGISTER_TEST        (day04, Input,        2, 830);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Pair> pairs;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Pair pair;
      ss >> pair.r1.left >> "-" >> pair.r1.right >> ",";
      ss >> pair.r2.left >> "-" >> pair.r2.right;
      pairs.emplace_back(pair);
    }
    return pairs;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    for (auto& pair : input)
    {
      if ((pair.r1.left >= pair.r2.left && pair.r1.right <= pair.r2.right) || (pair.r2.left >= pair.r1.left && pair.r2.right <= pair.r1.right))
      {
        sum++;
      }
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    for (auto& pair : input)
    {
      if (pair.r1.left <= pair.r2.right && pair.r1.right >= pair.r2.left)
      {
        sum++;
      }
    }
    return sum;
  }
}
