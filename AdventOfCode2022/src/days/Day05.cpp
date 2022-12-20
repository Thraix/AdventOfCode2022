#include "aoc.h"

namespace day05
{
  struct Move
  {
    int from;
    int count;
    int to;
  };

  struct Instructions
  {
    std::vector<std::deque<char>> stacks;
    std::vector<Move> moves;
  };

  REGISTER_DAY(day05, Instructions, std::string);

  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 1, "CMZ");
  REGISTER_TEST        (day05, Input,        1, "JCMHLVGMG");
  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 2, "MCD");
  REGISTER_TEST        (day05, Input,        2, "LVMRWSSPZ");

  READ_INPUT(input)
  {
    std::string str;
    Instructions instructions;
    while (std::getline(input, str))
    {
      if (Helper::StartsWith(str, "move"))
      {
        std::stringstream ss{str};
        Move move;
        ss >> "move" >> move.count >> "from" >> move.from >> "to" >> move.to;
        instructions.moves.emplace_back(move);
      }
      else if(!str.empty())
      {
				for (int i = 1; i < str.size(); i += 4)
				{
					int index = (i - 1) / 4;
					if (instructions.stacks.size() <= index) instructions.stacks.emplace_back(std::deque<char>{});
          if(str[i] >= 'A' && str[i] <= 'Z')
						instructions.stacks[index].emplace_front(str[i]);
				}
			}
    }
    return instructions;
  }

  OUTPUT1(input)
  {
    Instructions instructions = input;
    for (auto& move : instructions.moves)
    {
      for (int i = 0; i < move.count; i++)
      {
        instructions.stacks[move.to - 1].emplace_back(instructions.stacks[move.from - 1].back());
        instructions.stacks[move.from - 1].pop_back();
      }
    }
    std::stringstream ss;
    for (auto& stack : instructions.stacks)
    {
      ss << stack.back();
    }
    return ss.str();
  }

  OUTPUT2(input)
  {
    Instructions instructions = input;
    for (auto& move : instructions.moves)
    {
      std::vector<char> chars;
      for (int i = 0; i < move.count; i++)
      {
        chars.emplace_back(instructions.stacks[move.from - 1].back());
        instructions.stacks[move.from - 1].pop_back();
      }
      for (auto it = chars.rbegin(); it != chars.rend(); it++)
      {
        instructions.stacks[move.to - 1].emplace_back(*it);
      }
    }
    std::stringstream ss;
    for (auto& stack : instructions.stacks)
    {
      ss << stack.back();
    }
    return ss.str();
  }
}
