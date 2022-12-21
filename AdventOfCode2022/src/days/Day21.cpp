#include "aoc.h"

namespace day21
{
  enum class Operator
  {
    Add, Mul, Sub, Div

  };
  struct Operation
  {
    std::string lhs;
    std::string rhs;
    Operator op;
  };

  struct Monkey
  {
    std::string name;
    std::variant<int64_t, Operation> yell;

    bool operator<(const Monkey& rhs) const
    {
      return name < rhs.name;
    }
  };
  REGISTER_DAY(day21, std::set<Monkey>, int64_t);

  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 1, 152);
  REGISTER_TEST        (day21, Input,        1, 160274622817992);
  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 2, 301);
  REGISTER_TEST        (day21, Input,        2, 3087390115721);

  READ_INPUT(input)
  {
    std::string str;
    std::set<Monkey> monkeys;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Monkey monkey;
      ss >> monkey.name;
      monkey.name.pop_back(); // remove :

      if (str[6] >= '0' && str[6] <= '9')
      {
        int64_t i;
        ss >> i;
        monkey.yell = i;
      }
      else
      {
        Operation operation;
        char c;
        ss >> operation.lhs;
        ss >> c;
        ss >> operation.rhs;
        if (c == '+') operation.op = Operator::Add;
        if (c == '-') operation.op = Operator::Sub;
        if (c == '*') operation.op = Operator::Mul;
        if (c == '/') operation.op = Operator::Div;
        monkey.yell = operation;
      }
      monkeys.emplace(monkey);
    }
    return monkeys;
  }

  int64_t Resolve(const std::set<Monkey>& monkeys, const std::string& name)
  {
    Monkey findMonkey;
    findMonkey.name = name;
    const Monkey& monkey = *monkeys.find(findMonkey);
    if (std::holds_alternative<int64_t>(monkey.yell))
      return std::get<int64_t>(monkey.yell);

    const Operation& operation = std::get<Operation>(monkey.yell);
    switch (operation.op)
    {
    case Operator::Add:
      return Resolve(monkeys, operation.lhs) + Resolve(monkeys, operation.rhs);
    case Operator::Sub:
      return Resolve(monkeys, operation.lhs) - Resolve(monkeys, operation.rhs);
    case Operator::Mul:
      return Resolve(monkeys, operation.lhs) * Resolve(monkeys, operation.rhs);
    case Operator::Div:
      return Resolve(monkeys, operation.lhs) / Resolve(monkeys, operation.rhs);
    }
    return 0;
  }

  bool HasHuman(const std::set<Monkey>& monkeys, const std::string& name)
  {
    if (name == "humn")
      return true;

    Monkey findMonkey;
    findMonkey.name = name;
    const Monkey& monkey = *monkeys.find(findMonkey);
    if (std::holds_alternative<Operation>(monkey.yell))
    {
      return HasHuman(monkeys, std::get<Operation>(monkey.yell).lhs) ||
             HasHuman(monkeys, std::get<Operation>(monkey.yell).rhs);
    }

    return false;
  }

  int64_t Resolve(const std::set<Monkey>& monkeys, const std::string& name, int64_t result)
  {
    if (name == "humn")
      return result;

    Monkey findMonkey;
    findMonkey.name = name;
    const Monkey& monkey = *monkeys.find(findMonkey);
    if (std::holds_alternative<int64_t>(monkey.yell))
      return std::get<int64_t>(monkey.yell);

    const Operation& operation = std::get<Operation>(monkey.yell);
    if (name == "root")
    {
      if (HasHuman(monkeys, operation.lhs))
      {
        return Resolve(monkeys, operation.lhs, Resolve(monkeys, operation.rhs));
      }
      else
      {
        return Resolve(monkeys, operation.rhs, Resolve(monkeys, operation.lhs));
      }
    }

    if (HasHuman(monkeys, operation.lhs))
    {
      int64_t rhs = Resolve(monkeys, operation.rhs);
      switch (operation.op)
      {
      case Operator::Add:
        return Resolve(monkeys, operation.lhs, result - rhs); // lhs + rhs = result => lhs = result - rhs
      case Operator::Sub:
        return Resolve(monkeys, operation.lhs, result + rhs); // lhs - rhs = result => lhs = result + rhs
      case Operator::Mul:
        return Resolve(monkeys, operation.lhs, result / rhs); // lhs * rhs = result => lhs = result / rhs
      case Operator::Div:
        return Resolve(monkeys, operation.lhs, result * rhs); // lhs / rhs = result => lhs = result * rhs
      }
    }
    else
    {
      int64_t lhs = Resolve(monkeys, operation.lhs);
      switch (operation.op)
      {
      case Operator::Add:
        return Resolve(monkeys, operation.rhs, result - lhs); // lhs + rhs = result => rhs = result - lhs
      case Operator::Sub:
        return Resolve(monkeys, operation.rhs, lhs - result); // lhs - rhs = result => rhs = lhs - result
      case Operator::Mul:
        return Resolve(monkeys, operation.rhs, result / lhs); // lhs * rhs = result => result / lhs
      case Operator::Div:
        return Resolve(monkeys, operation.rhs, lhs * result); // lhs / rhs = result => lhs / result
      }
    }
    return 0;
  }

  OUTPUT1(input)
  {
    return Resolve(input, "root");
  }

  OUTPUT2(input)
  {
    return Resolve(input, "root", 0);
  }
}
