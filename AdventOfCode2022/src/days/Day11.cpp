#include "aoc.h"

namespace day11
{

  enum Op
  {
    Add, Mul
  };
  struct Old {};
  struct Monkey
  {
    std::vector<int64_t> items;
    std::variant<int, Old> bin1;
    std::variant<int, Old> bin2;
    int divisible;
    Op op;
    int monkeyTrue;
    int monkeyFalse;
  };

  REGISTER_DAY(day11, std::vector<Monkey>, int64_t);

  REGISTER_TEST_EXAMPLE(day11, ExampleInput, 1, 10605);
  REGISTER_TEST        (day11, Input,        1, 120756);
  REGISTER_TEST_EXAMPLE(day11, ExampleInput, 2, 2713310158);
  REGISTER_TEST        (day11, Input,        2, 39109444654);

  template <typename Func>
  void Round(std::vector<Monkey>& monkeys, std::vector<int64_t>& inspections, Func worryManagement)
  {
		for (int j = 0; j < monkeys.size(); j++)
		{
			for (auto item : monkeys[j].items)
			{
				inspections[j]++;
				int64_t i1 = std::holds_alternative<Old>(monkeys[j].bin1) ? item : std::get<int>(monkeys[j].bin1);
				int64_t i2 = std::holds_alternative<Old>(monkeys[j].bin2) ? item : std::get<int>(monkeys[j].bin2);
				int64_t val;

				if (monkeys[j].op == Op::Add)
					val = i1 + i2;
				else if (monkeys[j].op == Op::Mul)
					val = i1 * i2;
        val = worryManagement(val);
				if (val % monkeys[j].divisible == 0)
				  monkeys[monkeys[j].monkeyTrue].items.emplace_back(val);
				else
					monkeys[monkeys[j].monkeyFalse].items.emplace_back(val);
			}
			monkeys[j].items.clear();
		}

  }

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Monkey> monkeys;
    while (std::getline(input, str))
    {
      Monkey monkey;
      { // items
        std::getline(input, str);
        std::stringstream ss{str};
        ss >> "Starting items: ";
        while (std::getline(ss, str, ','))
          monkey.items.emplace_back(std::stoi(str));
      }
      { // operator
        std::getline(input, str);
        std::stringstream ss{str};
        ss >> "Operation: new = ";
        ss >> str;
        if (str == "old")
          monkey.bin1 = Old{};
        else
          monkey.bin1 = std::stoi(str);
        char c;
        ss >> c;
        if (c == '+')
          monkey.op = Op::Add;
        else if (c == '*')
          monkey.op = Op::Mul;
        ss >> str;
        if (str == "old")
          monkey.bin2 = Old{};
        else
          monkey.bin2 = std::stoi(str);
      }
      { // Test
        std::getline(input, str);
        std::stringstream ss{str};
        ss >> "Test: divisible by " >> monkey.divisible;
      }
      { // True
        std::getline(input, str);
        std::stringstream ss{str};
        ss >> "If true: throw to monkey " >> monkey.monkeyTrue;
      }
      { // False
        std::getline(input, str);
        std::stringstream ss{str};
        ss >> "If false: throw to monkey " >> monkey.monkeyFalse;
      }
			std::getline(input, str);
      monkeys.emplace_back(monkey);
    }
    return monkeys;
  }

  OUTPUT1(input)
  {
    std::vector<int64_t> inspections;
    inspections.resize(input.size());
		std::vector<Monkey> monkeys = input;
    for (int i = 0; i < 20; i++)
    {
      Round(monkeys, inspections, [](int64_t val) { return val / 3; });
    }
    std::sort(inspections.begin(), inspections.end());
    return inspections[inspections.size() - 1] * inspections[inspections.size() - 2];
  }

  OUTPUT2(input)
  {
    std::vector<int64_t> inspections;
    inspections.resize(input.size());
		std::vector<Monkey> monkeys = input;
    int mod = 1;
    for (auto& monkey : monkeys)
    {
      mod *= monkey.divisible;
    }
    for (int i = 0; i < 10000; i++)
    {
      Round(monkeys, inspections, [mod](int64_t val) { return val % mod; });
    }
    std::sort(inspections.begin(), inspections.end());
    return inspections[inspections.size() - 1] * inspections[inspections.size() - 2];
  }
}
