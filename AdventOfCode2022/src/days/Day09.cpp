#include "aoc.h"

namespace day09
{
  struct Instruction
  {
    char dir;
    int amount;
  };
  REGISTER_DAY(day09, std::vector<Instruction>, int);

  REGISTER_TEST_EXAMPLE(day09, ExampleInput, 1, 88);
  REGISTER_TEST        (day09, Input,        1, 6011);
  REGISTER_TEST_EXAMPLE(day09, ExampleInput, 2, 36);
  REGISTER_TEST        (day09, Input,        2, 2419);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Instruction> instructions;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Instruction ins;
      ss >> ins.dir >> ins.amount;
      instructions.emplace_back(ins);
    }
    return instructions;
  }

  OUTPUT1(input)
  {
    std::set<Index2D> visited;
    Index2D headPos{0, 0};
    Index2D tailPos{0, 0};
    visited.emplace(tailPos);
    for (auto& ins : input)
    {
      for (int i = 0; i < ins.amount; i++)
      {
        switch (ins.dir)
        {
        case 'R':
          headPos.x++;
          break;
        case 'U':
          headPos.y++;
          break;
        case 'L':
          headPos.x--;
          break;
        case 'D':
          headPos.y--;
          break;
        }
        Index2D diff = headPos - tailPos;
        if (std::abs(diff.x) > 1)
        {
          tailPos.x = headPos.x + (diff.x < 0 ? 1 : -1);
          tailPos.y = headPos.y;
          visited.emplace(tailPos);
        }
        else if(std::abs(diff.y) > 1)
        {
          tailPos.x = headPos.x;
          tailPos.y = headPos.y + (diff.y < 0 ? 1 : -1);
          visited.emplace(tailPos);
				}
      }
    }
    return visited.size();
  }

  OUTPUT2(input)
  {
    std::set<Index2D> visited;
    std::vector<Index2D> bodyPos;
    bodyPos.resize(10);
    std::fill(bodyPos.begin(), bodyPos.end(), Index2D{0, 0});
    visited.emplace(Index2D{0, 0});
    for (auto& ins : input)
    {
      for (int i = 0; i < ins.amount; i++)
      {
        switch (ins.dir)
        {
        case 'R':
          bodyPos[0].x++;
          break;
        case 'U':
          bodyPos[0].y++;
          break;
        case 'L':
          bodyPos[0].x--;
          break;
        case 'D':
          bodyPos[0].y--;
          break;
        }
        for (int i = 1; i < bodyPos.size(); i++)
        {
					Index2D diff = bodyPos[i - 1] - bodyPos[i];
					if (std::abs(diff.x) > 1)
					{
						bodyPos[i].x += diff.x < 0 ? -1 : 1;
            if(std::abs(diff.y) >= 1)
							bodyPos[i].y += diff.y < 0 ? -1 : 1;
					}
					else if(std::abs(diff.y) > 1)
					{
						if (std::abs(diff.x) >= 1)
							bodyPos[i].x += diff.x < 0 ? -1 : 1;
						bodyPos[i].y += diff.y < 0 ? -1 : 1;
					}
        }
				visited.emplace(bodyPos.back());
      }
    }
    return visited.size();
  }
}
