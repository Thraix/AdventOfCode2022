#include "aoc.h"

namespace day06
{
  REGISTER_DAY(day06, std::string, int);

  REGISTER_TEST_EXAMPLE(day06, ExampleInput, 1, 7);
  REGISTER_TEST        (day06, Input,        1, 1658);
  REGISTER_TEST_EXAMPLE(day06, ExampleInput, 2, 19);
  REGISTER_TEST        (day06, Input,        2, 2260);

  int GetPosition(const std::string& str, int length)
  {
    for (int i = length - 1; i < str.size(); i++)
    {
      std::set<char> s;
      for (int j = i - length + 1; j <= i; j++)
      {
        s.emplace(str[j]);
      }
      if (s.size() == length)
        return i + 1;
    }
    return 0;

  }

  READ_INPUT(input)
  {
    std::string str;
    std::getline(input, str);
    return str;
  }

  OUTPUT1(input)
  {
    return GetPosition(input, 4);
  }

  OUTPUT2(input)
  {
    return GetPosition(input, 14);
  }
}
