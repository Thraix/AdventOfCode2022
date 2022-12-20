#include "aoc.h"

namespace day19
{
  struct Blueprint
  {
    int oreOreCost;
    int clayOreCost;
    int obsidianOreCost;
    int obsidianClayCost;
    int geodeOreCost;
		int geodeObsidianCost;
  };

  struct Robots
  {
    int ore = 1;
    int clay = 0;
    int obsidian = 0;
    int geode = 0;
  };

  struct Materials
  {
    int ore = 0;
    int clay = 0;
    int obsidian = 0;
    int geode = 0;
  };

  REGISTER_DAY(day19, std::vector<Blueprint>, int);

  REGISTER_TEST_EXAMPLE(day19, ExampleInput, 1, 33);
  REGISTER_TEST        (day19, Input,        1, 600);
  REGISTER_TEST_EXAMPLE(day19, ExampleInput, 2, 3472);
  REGISTER_TEST        (day19, Input,        2, 6000);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Blueprint> blueprints;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Blueprint blueprint;
      int i = 0;
      // Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.
      ss >> "Blueprint" >> i >> ": Each ore robot costs" >> blueprint.oreOreCost >>
        "ore. Each clay robot costs" >> blueprint.clayOreCost >>
        "ore. Each obsidian robot costs" >> blueprint.obsidianOreCost >> "ore and" >> blueprint.obsidianClayCost >> 
        "clay. Each geode robot costs" >> blueprint.geodeOreCost >> "ore and" >> blueprint.geodeObsidianCost;
      blueprints.emplace_back(blueprint);

    }
    return blueprints;
  }
  
  void Mine(const Robots& robots, Materials& materials)
  {
    materials.ore += robots.ore;
    materials.clay += robots.clay;
    materials.obsidian += robots.obsidian;
    materials.geode += robots.geode;
  }

  int Max(const Blueprint& blueprint, Robots robots, Materials materials, int timeLeft)
  {
    if (timeLeft == 0)
      return materials.geode;
    timeLeft--;

    int max = 0;

    int maxOresNeeded = std::max({blueprint.oreOreCost, blueprint.clayOreCost, blueprint.obsidianOreCost, blueprint.geodeOreCost});

    if (materials.ore - robots.ore < blueprint.oreOreCost && materials.ore >= blueprint.oreOreCost && robots.ore < maxOresNeeded)
    {
      Robots newRobots = robots;
      Materials newMaterials = materials;
			Mine(newRobots, newMaterials);
      newRobots.ore++;
      newMaterials.ore -= blueprint.oreOreCost;
      max = std::max(max, Max(blueprint, newRobots, newMaterials, timeLeft));
    }
    if (materials.ore - robots.ore < blueprint.clayOreCost && materials.ore >= blueprint.clayOreCost && robots.clay < blueprint.obsidianClayCost)
    {
      Robots newRobots = robots;
      Materials newMaterials = materials;
			Mine(newRobots, newMaterials);
      newRobots.clay++;
      newMaterials.ore -= blueprint.clayOreCost;
      max = std::max(max, Max(blueprint, newRobots, newMaterials, timeLeft));
    }
    if ((materials.ore - robots.ore < blueprint.obsidianOreCost || materials.clay - robots.clay < blueprint.obsidianClayCost) && 
      materials.ore >= blueprint.obsidianOreCost && materials.clay >= blueprint.obsidianClayCost && robots.obsidian < blueprint.geodeObsidianCost)
    {
      Robots newRobots = robots;
      Materials newMaterials = materials;
			Mine(newRobots, newMaterials);
      newRobots.obsidian++;
      newMaterials.ore -= blueprint.obsidianOreCost;
      newMaterials.clay -= blueprint.obsidianClayCost;
      max = std::max(max, Max(blueprint, newRobots, newMaterials, timeLeft));
    }
    if ((materials.ore - robots.ore < blueprint.geodeOreCost || materials.obsidian - robots.obsidian < blueprint.geodeObsidianCost) && 
      materials.ore >= blueprint.geodeOreCost && materials.obsidian >= blueprint.geodeObsidianCost)
    {
      Robots newRobots = robots;
      Materials newMaterials = materials;
			Mine(newRobots, newMaterials);
      newRobots.geode++;
      newMaterials.ore -= blueprint.geodeOreCost;
      newMaterials.obsidian -= blueprint.geodeObsidianCost;
      max = std::max(max, Max(blueprint, newRobots, newMaterials, timeLeft));
    }
    Mine(robots, materials);
		return std::max(max, Max(blueprint, robots, materials, timeLeft));
  }

  OUTPUT1(input)
  {
    int sum = 0;
    for (int i = 0; i < input.size(); i++)
    {
      sum += (i + 1) * Max(input[i], Robots{}, Materials{}, 24);
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 1;
    for (int i = 0; i < input.size() && i < 3; i++)
    {
      sum *= Max(input[i], Robots{}, Materials{}, 32);
    }
    return sum;
  }
}
