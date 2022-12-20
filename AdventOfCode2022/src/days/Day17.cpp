#include "aoc.h"

namespace day17
{
  Array2D<char> block1{4, 1, {'#', '#', '#', '#'}};
  Array2D<char> block2{3, 3, {'.', '#', '.', '#', '#', '#', '.', '#', '.'}};
  Array2D<char> block3{3, 3, {'#', '#', '#', '.', '.', '#', '.', '.', '#'}};
  Array2D<char> block4{1, 4, {'#', '#', '#', '#'}};
  Array2D<char> block5{2, 2, {'#', '#', '#', '#'}};
  std::vector<Array2D<char>> blocks{block1, block2, block3, block4, block5};

  bool Overlap(const Array2D<char>& grid, const Array2D<char>& block, int xOffset, int yOffset)
  {
		for (int y = 0; y < block.height; y++)
		{
			for (int x = 0; x < block.width; x++)
			{
				if (block.Get(x, y) == '#' && grid.Get(x + xOffset, y + yOffset) == '#')
				{
          return true;
				}

			}
		}
    return false;
  }

  void Set(Array2D<char>& grid, const Array2D<char>& block, int xOffset, int yOffset)
  {
		for (int y = 0; y < block.height; y++)
		{
			for (int x = 0; x < block.width; x++)
			{
				if (block.Get(x, y) == '#')
				{
          grid.Set(x + xOffset, y + yOffset, '#');
				}
			}
		}
  }

  void Print(const Array2D<char>& grid, int height)
  {
    for (int y = height; y >= 0; y--) 
    {
      for (int x = 0; x < grid.width; x++) 
      {
        std::cout << grid.Get(x, y);
      }
      std::cout << std::endl;
    }
		std::cout << std::endl;
  }

  REGISTER_DAY(day17, std::string, int64_t);

  REGISTER_TEST_EXAMPLE(day17, ExampleInput, 1, 3068);
  REGISTER_TEST        (day17, Input,        1, 3065);
  // REGISTER_TEST_EXAMPLE(day17, ExampleInput, 2, 0);
  REGISTER_TEST        (day17, Input,        2, 1562536022966);

  READ_INPUT(input)
  {
    std::string str;
    std::getline(input, str);
    return str;
  }

  OUTPUT1(input)
  {
    int j = 0;
    int index = 0;
    Array2D<char> grid{7, 4044};
    grid.Fill('.');
    int top = 0;
    int piece = 0;
    for (int i = 0; i < 2022; i++)
    {
      Array2D<char> block = blocks[piece];
      piece++;
      piece %= blocks.size();

      int x = 2;
      int y = top + 3;
      while (true)
      {
        if (input[index++] == '>')
        {
          x++;
          if (x + block.width > 7)
            x--;
          else if (Overlap(grid, block, x, y))
						x--;
        }
        else
        {
          x--;
          if (x < 0)
            x++;
          else if (Overlap(grid, block, x, y))
						x++;
        }
				index %= input.size();
        y--;
        if (y < 0 || Overlap(grid, block, x, y))
        {
          y++;
          Set(grid, block, x, y);
          top = std::max(top, y + block.height);
          break;
        }
      }
      j++;
    }
    return top;
  }

  OUTPUT2(input)
  {
    int blockIndex = 0;
    int index = 0;
    Array2D<char> grid{7, 10000};
    grid.Fill('.');
    int top = 0;
    int piece = 0;
    std::map<std::pair<int, int>, std::pair<int, int>> state;
    int loopStart = 0;
    int loopStartHeight = 0;
    int loopSize = 0;
    int loopTopDiff = 0;
    std::pair<int, int> loop;

    int64_t total = 1000000000000;
    for (int64_t i = 0; i < total; i++)
    {
      Array2D<char> block = blocks[piece];
      piece++;
      piece %= blocks.size();

      int x = 2;
      int y = top + 3;
      while (true)
      {
        if (input[index++] == '>')
        {
          x++;
          if (x + block.width > 7)
            x--;
          else if (Overlap(grid, block, x, y))
						x--;
        }
        else
        {
          x--;
          if (x < 0)
            x++;
          else if (Overlap(grid, block, x, y))
						x++;
        }
				index %= input.size();
        y--;
        if (y < 0 || Overlap(grid, block, x, y))
        {
          y++;
          Set(grid, block, x, y);
          top = std::max(top, y + block.height);
          if(loopStart == 0)
          {
						bool found = true;
						for (int x = 0; x < grid.width; x++)
						{
							if (grid.Get(x, top - 1) != '#')
							{
								found = false;
								break;
							}
						}
						if (found)
						{
							auto it = state.find({piece, index});
							if (it != state.end())
							{
								loopStart = it->second.first;
								loopStartHeight = it->second.second;
								loopSize = blockIndex - it->second.first;
								loopTopDiff = top - it->second.second;
								int64_t fastForward = (total - loopStart) / loopSize;
								fastForward = fastForward * loopSize + loopStart;
								i = fastForward;
							}
							state.emplace(std::pair<int, int>{piece, index}, std::pair<int, int>{blockIndex, top});
						}
          }
          break;
        }
      }
      blockIndex++;
    }
    return top - loopTopDiff + (total - loopStart) / loopSize * loopTopDiff;
  }
}
