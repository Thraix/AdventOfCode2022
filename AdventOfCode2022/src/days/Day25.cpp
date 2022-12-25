#include "aoc.h"

namespace day25
{
  int64_t Pow(int64_t number, int64_t pow)
  {
    int64_t result = number;
    for (int i = 0; i < pow; i++)
    {
      result *= number;
    }
    return result;
  }

  int64_t ConvertToBase10(const std::string& string)
  {
    int64_t total = 0;
    for (int i = 0; i < string.size(); i++)
    {
      total *= 5;
      if (string[i] == '1') total += 1;
      else if (string[i] == '2') total += 2;
      else if (string[i] == '-') total += -1;
      else if (string[i] == '=') total += -2;
      else if (string[i] == '0') total += 0;
      else std::cout << "Invalid character in " << string << std::endl;
    }
    return total;
  }

  std::string ConvertToBase5(int64_t base10)
  {
    // Convert to base 5
    std::string base5 = "";
    int64_t numbers = log(base10) / log(5) + 1;
    for (int i = 0; i < numbers + 1; i++) base5.push_back('0');
    int64_t base5Max = Pow(5, numbers - 2);

    for (int i = 1; i < base5.size(); i++)
    {
      int64_t val = base10 / base5Max;
      base5[i] = val + '0';
      base10 -= val * base5Max;
      base5Max /= 5;
    }
    return base5;
  }

  std::string ConvertToSNAFU(const std::string& base5)
  {
    std::string snafu = base5;
    for(int i = snafu.size() - 1; i > 0; i--)
    {
      if (snafu[i] == '3') 
      {
        snafu[i] = '=';
        snafu[i - 1] += 1;
      }
      else if(snafu[i] == '4')
      {
        snafu[i] = '-';
        snafu[i - 1] += 1;
      }
      else if(snafu[i] == '5')
      {
        snafu[i] = '0';
        snafu[i - 1] += 1;
      }
    }
    if (snafu[0] == '0') 
      return snafu.substr(1);
    return snafu;
  }

  REGISTER_DAY(day25, std::vector<std::string>, std::string);

  REGISTER_TEST_EXAMPLE(day25, ExampleInput, 1, "2=-1=0");
  REGISTER_TEST        (day25, Input,        1, "2=12-100--1012-0=012");
  REGISTER_TEST        (day25, Input,        2, "");

  READ_INPUT(input)
  {
    return Input::ReadLines(input);
  }

  OUTPUT1(input)
  {
    int64_t base10 = 0;
    for (auto& line : input)
    {
      base10 += ConvertToBase10(line);
    }

    std::string base5 = ConvertToBase5(base10);
    return ConvertToSNAFU(base5);
  }

  OUTPUT2(input)
  {
    std::cout << "  ___                      ___" << std::endl;
    std::cout << " (o o)                    (o o)" << std::endl;
    std::cout << "(  V  ) MERRY CHRISTMAS! (  V  )" << std::endl;
    std::cout << "--m-m----------------------m-m--" << std::endl;
    return "";
  }
}
