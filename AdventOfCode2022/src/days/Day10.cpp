#include "aoc.h"

namespace day10
{
  enum class Op
  {
    Addx, Noop
  };
  struct Instruction
  {
    Op op;
    int val;
  };
  REGISTER_DAY(day10, std::vector<Instruction>, int);

  REGISTER_TEST_EXAMPLE(day10, ExampleInput, 1, 13140);
  REGISTER_TEST        (day10, Input,        1, 10760);
  REGISTER_TEST_EXAMPLE(day10, ExampleInput, 2, 124);
  REGISTER_TEST        (day10, Input,        2, 100);

  void Draw(int cycle, int value, Array2D<char>& grid)
  {
		int xPos = cycle % 40;
		int yPos = cycle / 40;
		if(value - 1 <= xPos && xPos <= value + 1)
			grid.Set(xPos, yPos, '#');

  }

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Instruction> instructions;
    while (std::getline(input, str))
    {
			Instruction instruction;
      if (str == "noop")
      {
        instruction.op = Op::Noop;
        instructions.emplace_back(instruction);
      }
      else
      {
        std::stringstream ss{str};
        instruction.op = Op::Addx;
        ss >> "addx" >> instruction.val;
        instructions.emplace_back(instruction);
      }
    }
    return instructions;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    int cycle = 1;
    int currentCycle = 20;
    int value = 1;
    for (auto& instruction : input)
    {
      if (instruction.op == Op::Addx)
      {
        cycle += 2;
        if (cycle > currentCycle)
        {
          sum += currentCycle * value;

          currentCycle += 40;
        }
        value += instruction.val;
      }
      else if(instruction.op == Op::Noop)
      {
        cycle += 1;
        if (cycle > currentCycle)
        {
          sum += currentCycle * value;

          currentCycle += 40;
        }
      }
    }
    return sum;
  }

  OUTPUT2(input)
  {
    Array2D<char> grid{40, 6};
    grid.Fill('.');

    int cycle = 0;
    int value = 1;

    for (auto& instruction : input)
    {
      Draw(cycle, value, grid);
      if (instruction.op == Op::Addx)
      {
        cycle++;
				Draw(cycle, value, grid);
        cycle++;
        value += instruction.val;
      }
      else if(instruction.op == Op::Noop)
      {
        cycle++;
      }
    }
    std::cout << grid << std::endl;

    // Output is text in a grid so do some basic verification on the amount of filled in pixels
    return grid.Count('#');
  }
}
