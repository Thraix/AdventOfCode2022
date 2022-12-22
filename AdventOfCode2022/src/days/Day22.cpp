#include "aoc.h"

namespace day22
{

  struct Input
  {
    Array2D<char> grid;
    std::string directions;
  };

	bool Between(int x, int bound1, int bound2)
	{
    if (bound1 < bound2)
      return x >= bound1 && x <= bound2;
    else
      return x <= bound1 && x >= bound2;
	}

  REGISTER_DAY(day22, Input, int);

  REGISTER_TEST_EXAMPLE(day22, ExampleInput, 1, 6032);
  REGISTER_TEST        (day22, Input,        1, 89224);
  REGISTER_TEST        (day22, Input,        2, 136182);

  struct State
  {
    Index2D pos;
    Index2D facing;
  };

  struct Edge
  {
    Index2D from1;
    Index2D to1;
    Index2D facing1;
    Index2D from2;
    Index2D to2;
    Index2D facing2;

    Edge(Index2D from1, Index2D to1, Index2D facing1, Index2D from2,Index2D to2, Index2D facing2)
      : from1{from1}, to1{to1}, facing1{facing1}, from2{from2}, to2{to2}, facing2{facing2}
    {}

    void CalcTransition(Index2D& pos, Index2D& facing)
    {
      if (facing == facing1 && Between(pos.x, from1.x, to1.x) && Between(pos.y, from1.y, to1.y))
      {
        facing.x = -facing2.x;
        facing.y = -facing2.y;
        Index2D diff1 = pos - from1;
        int offset = std::max(std::abs(diff1.x), std::abs(diff1.y));
        Index2D diff2 = to2 - from2;
        diff2.x = Helper::Sign(diff2.x);
        diff2.y = Helper::Sign(diff2.y);
        pos.x = from2.x + offset * diff2.x;
        pos.y = from2.y + offset * diff2.y;

      }
      else
      {
        facing.x = -facing1.x;
        facing.y = -facing1.y;
        Index2D diff2 = pos - from2;
        int offset = std::max(std::abs(diff2.x), std::abs(diff2.y));
        Index2D diff1 = to1 - from1;
        diff1.x = Helper::Sign(diff1.x);
        diff1.y = Helper::Sign(diff1.y);
        pos.x = from1.x + offset * diff1.x;
        pos.y = from1.y + offset * diff1.y;
      }
    }


    bool operator==(const State& state) const
    {
      return (state.facing == facing1 && Between(state.pos.x, from1.x, to1.x) && Between(state.pos.y, from1.y, to1.y)) ||
						 (state.facing == facing2 && Between(state.pos.x, from2.x, to2.x) && Between(state.pos.y, from2.y, to2.y));
    }
  };

  READ_INPUT(input)
  {
    Input in;
    std::string str;
    int max = 0;
    std::vector<std::string> vector;
    while (std::getline(input, str))
    {
      if (str.empty())
        break;
      vector.emplace_back(str);
      max = std::max(max, (int)str.size());
    }

    in.grid = Array2D<char>{max, (int)vector.size()};
    in.grid.Fill(' ');
    for (int i = 0; i < vector.size(); i++)
    {
      for(int j = 0; j < vector[i].size(); j++)
      {
        in.grid.Set(j, i, vector[i][j]);
      }
    }

    std::getline(input, in.directions);
    return in;
  }

  OUTPUT1(input)
  {
    State state;
    state.facing = Index2D{1, 0};

    for (int i = 0; i < input.grid.width; i++)
    {
      if (input.grid.Get(i, 0) != ' ')
      {
        state.pos = {i, 0};
        break;
      }
    }
    int i = 0;
    while (i < input.directions.size())
    {
      if (input.directions[i] >= '0' && input.directions[i] <= '9')
      {
        int amount = std::stoi(&input.directions[i]);
        while (input.directions[i] >= '0' && input.directions[i] <= '9') i++;

        for (int j = 0; j < amount; j++)
        {
          Index2D oldPos = state.pos;
          state.pos = state.pos + state.facing;
          if (input.grid.GetMod(state.pos.x, state.pos.y) == '#')
          {
            state.pos = oldPos;
            break;
          }
          else if (input.grid.GetMod(state.pos.x, state.pos.y) == ' ')
          {
            while (input.grid.GetMod(state.pos.x, state.pos.y) == ' ')
            {
              state.pos = state.pos + state.facing;
            }
            if (input.grid.GetMod(state.pos.x, state.pos.y) == '#')
            {
              state.pos = oldPos;
              break;
            }
          }
        }
        state.pos.x = ((state.pos.x % input.grid.width) + input.grid.width) % input.grid.width;
        state.pos.y = ((state.pos.y % input.grid.height) + input.grid.height) % input.grid.height;
      }
      else
      {
        if (input.directions[i] == 'R')
        {
          int tmp = state.facing.x;
          state.facing.x = -state.facing.y;
          state.facing.y = tmp;
        }
        else
        {
          int tmp = state.facing.x;
          state.facing.x = state.facing.y;
          state.facing.y = -tmp;
        }
        i++;
      }
    }
    int face = 0;
    if (state.facing == Index2D{0, 1}) face = 1;
    if (state.facing == Index2D{-1, 0}) face = 2;
    if (state.facing == Index2D{0, -1}) face = 3;
    return (state.pos.y + 1) * 1000 + 4 * (state.pos.x + 1) + face;
  }

  OUTPUT2(input)
  {
    State state;
    state.facing = Index2D{1, 0};
    std::vector<Edge> edges;
		edges.emplace_back(Index2D{50, 50}, Index2D{50, 99}, Index2D{-1, 0}, Index2D{0, 100}, Index2D{49, 100}, Index2D{0, -1});
		edges.emplace_back(Index2D{50, 0}, Index2D{50, 49}, Index2D{-1, 0}, Index2D{0, 149}, Index2D{0, 100}, Index2D{-1,  0});
		edges.emplace_back(Index2D{100, 49}, Index2D{149, 49}, Index2D{0, 1}, Index2D{99, 50}, Index2D{99, 99}, Index2D{1, 0});
		edges.emplace_back(Index2D{50, 149}, Index2D{99, 149}, Index2D{0, 1}, Index2D{49, 150}, Index2D{49, 199}, Index2D{1, 0});
		edges.emplace_back(Index2D{50, 0}, Index2D{99, 0}, Index2D{0, -1}, Index2D{0, 150}, Index2D{0, 199}, Index2D{-1, 0});
		edges.emplace_back(Index2D{99, 100}, Index2D{99, 149}, Index2D{1, 0}, Index2D{149, 49}, Index2D{149, 0}, Index2D{1, 0});
		edges.emplace_back(Index2D{100, 0}, Index2D{149, 0}, Index2D{0, -1}, Index2D{0, 199}, Index2D{49, 199}, Index2D{0, 1});

    for (int i = 0; i < input.grid.width; i++)
    {
      if (input.grid.Get(i, 0) != ' ')
      {
        state.pos = {i, 0};
        break;
      }
    }
    int i = 0;
    while (i < input.directions.size())
    {
      if (input.directions[i] >= '0' && input.directions[i] <= '9')
      {
        int amount = std::stoi(&input.directions[i]);
        while (input.directions[i] >= '0' && input.directions[i] <= '9') i++;

        for (int j = 0; j < amount; j++)
        {
          Index2D oldPos = state.pos;
          Index2D oldFacing = state.facing;
          state.pos = state.pos + state.facing;
					state.pos.x = ((state.pos.x % input.grid.width) + input.grid.width) % input.grid.width;
					state.pos.y = ((state.pos.y % input.grid.height) + input.grid.height) % input.grid.height;
          if (input.grid.Get(state.pos.x, state.pos.y) == '#')
          {
            state.pos = oldPos;
            break;
          }
          else if (input.grid.Get(state.pos.x, state.pos.y) == ' ')
          {
            state.pos = oldPos;
            auto it = std::find(edges.begin(), edges.end(), state);
            if (it != edges.end())
            {
              it->CalcTransition(state.pos, state.facing);
              if (input.grid.Get(state.pos.x, state.pos.y) == '#')
              {
                state.pos = oldPos;
                state.facing = oldFacing;
                break;
              }
            }
            else
            {
              std::cout << "Not found: state.pos: " << state.pos << " state.facing: " << state.facing << std::endl;
              return 0;
            }
          }
        }
      }
      else
      {
        if (input.directions[i] == 'R')
        {
          int tmp = state.facing.x;
          state.facing.x = -state.facing.y;
          state.facing.y = tmp;
        }
        else
        {
          int tmp = state.facing.x;
          state.facing.x = state.facing.y;
          state.facing.y = -tmp;
        }
        i++;
      }
    }
    int face = 0;
    if (state.facing == Index2D{0, 1}) face = 1;
    if (state.facing == Index2D{-1, 0}) face = 2;
    if (state.facing == Index2D{0, -1}) face = 3;
    return (state.pos.y + 1) * 1000 + 4 * (state.pos.x + 1) + face;
  }
}
