#include "aoc.h"

namespace day24
{
  struct World
  {
    const Array2D<char> world;
    Array2D<char> up;
    Array2D<char> down;
    Array2D<char> left;
    Array2D<char> right;
    World(const Array2D<char>& world)
      : world{world}
    {
      up = Array2D<char>{world.width, world.height};
      down = Array2D<char>{world.width, world.height};
      left = Array2D<char>{world.width, world.height};
      right = Array2D<char>{world.width, world.height};
      up.Fill('.');
      down.Fill('.');
      right.Fill('.');
      left.Fill('.');
      for (auto it = world.begin(); it != world.end(); ++it)
      {
        if (*it == '^') up.Set(it.index.x, it.index.y, '^');
        if (*it == 'v') down.Set(it.index.x, it.index.y, 'v');
        if (*it == '>') right.Set(it.index.x, it.index.y, '>');
        if (*it == '<') left.Set(it.index.x, it.index.y, '<');
      }
    }
  };
  struct State
  {
    Index2D pos;
    int depth;
    int vert;
    int hor;

    bool operator<(const State& rhs) const
    {
      if (pos != rhs.pos)
        return pos < rhs.pos;
      if (vert != rhs.vert)
        return vert < rhs.vert;
      return hor < rhs.hor;
    }
  };

  REGISTER_DAY(day24, World, int);

  REGISTER_TEST_EXAMPLE(day24, ExampleInput, 1, 18);
  REGISTER_TEST        (day24, Input,        1, 299);
  REGISTER_TEST_EXAMPLE(day24, ExampleInput, 2, 54);
  REGISTER_TEST        (day24, Input,        2, 899);

  READ_INPUT(input)
  {
    return World{ Input::ReadArray2D(input) };
  }

  void Step(World& world)
  {
    Array2D<char> upCpy = world.up;
    world.up.Fill('.');
    for(auto it = upCpy.begin(); it != upCpy.end(); ++it)
    {
      if (*it == '^') {
        int y = it.index.y - 1;
        if(y == 0)
          world.up.Set(it.index.x, world.up.height - 2, '^');
        else
          world.up.Set(it.index.x, it.index.y - 1, '^');
      }
    }

    Array2D<char> downCpy = world.down;
    world.down.Fill('.');
    for(auto it = downCpy.begin(); it != downCpy.end(); ++it)
    {
      if (*it == 'v') {
        int y = it.index.y + 1;
        if(y == world.down.height - 1)
          world.down.Set(it.index.x, 1, 'v');
        else
          world.down.Set(it.index.x, it.index.y + 1, 'v');
      }
    }

    Array2D<char> rightCpy = world.right;
    world.right.Fill('.');
    for(auto it = rightCpy.begin(); it != rightCpy.end(); ++it)
    {
      if (*it == '>') {
        int x = it.index.x + 1;
        if(x == world.right.width - 1)
          world.right.Set(1, it.index.y, '>');
        else
          world.right.Set(it.index.x + 1, it.index.y, '>');
      }
    }

    Array2D<char> leftCpy = world.left;
    world.left.Fill('.');
    for(auto it = leftCpy.begin(); it != leftCpy.end(); ++it)
    {
      if (*it == '<') {
        int x = it.index.x - 1;
        if(x == 0)
          world.left.Set(world.left.width - 2, it.index.y, '<');
        else
          world.left.Set(it.index.x - 1, it.index.y, '<');
      }
    }
  }

  int PathFind(World& world, const Index2D& from, const Index2D& to)
  {
    std::set<State> visited;
    int lastDepth = -1;
    std::queue<State> queue;
    State initialState;
    initialState.pos = from;
    initialState.depth = 0;
    initialState.vert = 0;
    initialState.hor = 0;
    queue.emplace(initialState);
    visited.emplace(initialState);
    while (!queue.empty())
    {
      State state = queue.front();
      queue.pop();
      if (state.pos == to) 
      { 
        return state.depth; 
      }
      if (lastDepth != state.depth)
      {
        Step(world);
        lastDepth = state.depth;
      }

      std::vector<Index2D> moves{Index2D{0, 0}, Index2D{1, 0}, Index2D{-1, 0}, Index2D{0, 1}, Index2D{0, -1}};
      for(auto& move : moves)
      {
        Index2D newPos = state.pos + move;
        if (!world.world.IsInside(newPos)) continue;
        if (world.world.Get(newPos) == '#') continue;
        if (world.up.Get(newPos) == '^') continue;
        if (world.down.Get(newPos) == 'v') continue;
        if (world.left.Get(newPos) == '<') continue;
        if (world.right.Get(newPos) == '>') continue;
        State newState;
        newState.pos = newPos;
        newState.depth = state.depth + 1;
        newState.vert = state.vert + 1;
        newState.hor = state.hor + 1;
        if (newState.vert == world.world.height - 2) newState.vert = 0;
        if (newState.hor == world.world.width - 2) newState.hor = 0;
        if (visited.count(newState) > 0) continue;
        visited.emplace(newState);
        queue.emplace(newState);
      }
    }
    return 0;
  }

  OUTPUT1(input)
  {
    World world = input;
    return PathFind(world, Index2D{1, 0}, Index2D{world.world.width - 2, world.world.height - 1});
  }

  OUTPUT2(input)
  {
    World world = input;
    int path1 = PathFind(world, Index2D{1, 0}, Index2D{world.world.width - 2, world.world.height - 1});
    int path2 = PathFind(world, Index2D{world.world.width - 2, world.world.height - 1}, Index2D{1, 0});
    int path3 = PathFind(world, Index2D{1, 0}, Index2D{world.world.width - 2, world.world.height - 1});

    return path1 + path2 + path3 + 2;
  }
}
