#include "aoc.h"

namespace day23
{
  REGISTER_DAY(day23, Array2D<char>, int);

  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 1, 110);
  REGISTER_TEST        (day23, Input,        1, 4254);
  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 2, 20);
  REGISTER_TEST        (day23, Input,        2, 992);

  READ_INPUT(input)
  {
    return Input::ReadArray2D(input);
  }


  void Reset(Array2D<char>& grid, const Index2D& pos)
  {
    char c = grid.Get(pos);
    if (c == '1') grid.Set(pos.x, pos.y + 1, '0');
    if (c == '2') grid.Set(pos.x, pos.y - 1, '0');
    if (c == '3') grid.Set(pos.x + 1, pos.y, '0');
    if (c == '4') grid.Set(pos.x - 1, pos.y, '0');
    grid.Set(pos.x, pos.y, '.');
  }

  OUTPUT1(input)
  {
    Array2D<char> grid{input.width * 3, input.height * 3};
    Array2D<char> moves{input.width * 3, input.height * 3};
    grid.Fill('.');
    moves.Fill('.');
    for(auto it = input.begin(); it != input.end(); ++it)
    {
      grid.Set(input.width + it.index.x, input.height + it.index.y, *it);
    }

    for (int i = 0; i < 10; i++)
    {
      for(auto it = grid.begin(); it != grid.end(); ++it)
      {
        if (*it != '#')
          continue;

        if (grid.GetNeighbors('#', it.index.x, it.index.y) == 0)
        {
          moves.Set(it.index.x, it.index.y, '0');
        }
        else
        {
          int up = 0;
          if (grid.Get(it.index.x, it.index.y - 1) == '#') up++;
          if (grid.Get(it.index.x - 1, it.index.y - 1) == '#') up++;
          if (grid.Get(it.index.x + 1, it.index.y - 1) == '#') up++;
          int down = 0;
          if (grid.Get(it.index.x, it.index.y + 1) == '#') down++;
          if (grid.Get(it.index.x - 1, it.index.y + 1) == '#') down++;
          if (grid.Get(it.index.x + 1, it.index.y + 1) == '#') down++;
          int left = 0;
          if (grid.Get(it.index.x - 1, it.index.y) == '#') left++;
          if (grid.Get(it.index.x - 1, it.index.y - 1) == '#') left++;
          if (grid.Get(it.index.x - 1, it.index.y + 1) == '#') left++;
          int right = 0;
          if (grid.Get(it.index.x + 1, it.index.y) == '#') right++;
          if (grid.Get(it.index.x + 1, it.index.y - 1) == '#') right++;
          if (grid.Get(it.index.x + 1, it.index.y + 1) == '#') right++;

          std::vector<int> neighs{up, down, left, right};
          std::vector<Index2D> dirs{Index2D{it.index.x, it.index.y - 1}, Index2D{it.index.x, it.index.y + 1}, Index2D{it.index.x - 1, it.index.y}, Index2D{it.index.x + 1, it.index.y}};
          std::vector<char> val{'1', '2', '3', '4'};

          bool set = false;
          for (int j = 0; j < 4; j++)
          {
            if (neighs[(i + j) % 4] == 0)
            {
              Index2D index = dirs[(i + j) % 4];
              char c = moves.Get(index);
              if (c != '.')
              {
                moves.Set(it.index.x, it.index.y, '0');
                Reset(moves, index);
              }
              else
              {
                moves.Set(index.x, index.y, val[(i + j) % 4]);
              }
              set = true;
              break;
            }
          }
          if(!set)
          {
            moves.Set(it.index.x, it.index.y, '0');
          }
        }
      }

      grid.Fill('.');
      for (auto it = moves.begin(); it != moves.end(); ++it)
      {
        if (*it != '.')
        {
          grid.Set(it.index.x, it.index.y, '#');
        }
      }
      moves.Fill('.');
    }

    Index2D min{grid.width, grid.height};
    Index2D max{0, 0};
    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
      if (*it == '#')
      {
        min.x = std::min(min.x, it.index.x);
        min.y = std::min(min.y, it.index.y);
        max.x = std::max(max.x, it.index.x);
        max.y = std::max(max.y, it.index.y);
      }
    }

    return (max.x - min.x + 1) * (max.y - min.y + 1) - grid.Count('#');
  }

  OUTPUT2(input)
  {
    Array2D<char> grid{input.width * 3, input.height * 3};
    Array2D<char> moves{input.width * 3, input.height * 3};
    grid.Fill('.');
    moves.Fill('.');
    for(auto it = input.begin(); it != input.end(); ++it)
    {
      grid.Set(input.width + it.index.x, input.height + it.index.y, *it);
    }

    bool moved = true;
    int i = 0;
    while (moved)
    {
      for(auto it = grid.begin(); it != grid.end(); ++it)
      {
        if (*it != '#')
          continue;

        if (grid.GetNeighbors('#', it.index.x, it.index.y) == 0)
        {
          moves.Set(it.index.x, it.index.y, '0');
        }
        else
        {
          int up = 0;
          if (grid.Get(it.index.x, it.index.y - 1) == '#') up++;
          if (grid.Get(it.index.x - 1, it.index.y - 1) == '#') up++;
          if (grid.Get(it.index.x + 1, it.index.y - 1) == '#') up++;
          int down = 0;
          if (grid.Get(it.index.x, it.index.y + 1) == '#') down++;
          if (grid.Get(it.index.x - 1, it.index.y + 1) == '#') down++;
          if (grid.Get(it.index.x + 1, it.index.y + 1) == '#') down++;
          int left = 0;
          if (grid.Get(it.index.x - 1, it.index.y) == '#') left++;
          if (grid.Get(it.index.x - 1, it.index.y - 1) == '#') left++;
          if (grid.Get(it.index.x - 1, it.index.y + 1) == '#') left++;
          int right = 0;
          if (grid.Get(it.index.x + 1, it.index.y) == '#') right++;
          if (grid.Get(it.index.x + 1, it.index.y - 1) == '#') right++;
          if (grid.Get(it.index.x + 1, it.index.y + 1) == '#') right++;

          std::vector<int> neighs{up, down, left, right};
          std::vector<Index2D> dirs{Index2D{it.index.x, it.index.y - 1}, Index2D{it.index.x, it.index.y + 1}, Index2D{it.index.x - 1, it.index.y}, Index2D{it.index.x + 1, it.index.y}};
          std::vector<char> val{'1', '2', '3', '4'};

          bool set = false;
          for (int j = 0; j < 4; j++)
          {
            if (neighs[(i + j) % 4] == 0)
            {
              Index2D index = dirs[(i + j) % 4];
              char c = moves.Get(index);
              if (c != '.')
              {
                moves.Set(it.index.x, it.index.y, '0');
                Reset(moves, index);
              }
              else
              {
                moves.Set(index.x, index.y, val[(i + j) % 4]);
              }
              set = true;
              break;
            }
          }
          if(!set)
          {
            moves.Set(it.index.x, it.index.y, '0');
          }
        }
      }

      grid.Fill('.');
      moved = false;
      for (auto it = moves.begin(); it != moves.end(); ++it)
      {
        if (*it != '.')
        {
          grid.Set(it.index.x, it.index.y, '#');
          if (*it != '0') moved = true;
        }
      }
      moves.Fill('.');
      i++;
    }

    Index2D min{grid.width, grid.height};
    Index2D max{0, 0};
    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
      if (*it == '#')
      {
        min.x = std::min(min.x, it.index.x);
        min.y = std::min(min.y, it.index.y);
        max.x = std::max(max.x, it.index.x);
        max.y = std::max(max.y, it.index.y);
      }
    }
    return i;
  }
}
