#include "aoc.h"

namespace day21
{
  REGISTER_DAY(day21, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 1, 0);
  REGISTER_TEST        (day21, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 2, 0);
  REGISTER_TEST        (day21, Input,        2, 0);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<int> vector;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
    }
    return vector;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    return sum;
  }
}
