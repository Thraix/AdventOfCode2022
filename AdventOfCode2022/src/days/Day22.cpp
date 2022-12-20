#include "aoc.h"

namespace day22
{
  REGISTER_DAY(day22, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day22, ExampleInput, 1, 0);
  REGISTER_TEST        (day22, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day22, ExampleInput, 2, 0);
  REGISTER_TEST        (day22, Input,        2, 0);

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
