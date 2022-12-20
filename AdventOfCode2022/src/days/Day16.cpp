#include "aoc.h"

namespace day16
{
  struct Node
  {
    std::string name;
    int flowrate;
    std::set<std::string> paths;
    bool operator<(const Node& rhs) const
    {
      return name < rhs.name;
    }
  };

  std::vector<std::pair<int, std::string>> Branch(const std::set<Node>& nodes, const std::string& str)
  {
    Node n;
    n.name = str;
    const Node& node = *nodes.find(n);
    std::vector<std::pair<int, std::string>> branches;
    for (auto& path : node.paths)
    {
      branches.emplace_back(1, path);
    }
    return branches;
  }

  int GetDistance(const std::set<Node>& nodes, const std::string& from, const std::string& to, std::map<std::string, int>& distances) {
    std::string s = from + to;
    if (to < from)
      s = to + from;
		auto it = distances.find(s);
		int distance = 0;
		if (it != distances.end())
			distance = it->second;
		else
		{
			distance = Helper::Dijkstras(from, [&nodes](const std::string& str) { return Branch(nodes, str); }, [to](const std::string& str) { return str == to; });
			distances.emplace(s, distance);
		}
    return distance;
  }

  int FindMax(const std::set<Node>& nodes, std::map<std::string, int>& distances, const std::string& currentNode, const std::set<std::string>& visit, int timeLeft, int pressure)
  {
    if (timeLeft < 0)
      return 0;
    if (visit.empty())
      return pressure;
    int max = pressure;
    for (auto& node : visit)
    {
      Node newNode;
      newNode.name = node;
      std::set<std::string> newVisit = visit;
      int newTimeLeft = timeLeft - (GetDistance(nodes, currentNode, node, distances) + 1);
      int newPressure = pressure + newTimeLeft * nodes.find(newNode)->flowrate;
      newVisit.erase(node);

      max = std::max(max, FindMax(nodes, distances, node, newVisit, newTimeLeft, newPressure));
    }
    return max;
  }

  void FindMax(const std::set<Node>& nodes, std::map<std::string, int>& distances, const std::string& currentNode, const std::set<std::string>& visit, int timeLeft, int pressure, int currentBits, std::vector<int>& best, const std::map<std::string, int>& nodeIndex)
  {
    if (timeLeft < 0)
      return;
		best[currentBits] = std::max(best[currentBits], pressure);
    for (auto& node : visit)
    {
      Node newNode;
      newNode.name = node;
      std::set<std::string> newVisit = visit;
      int newTimeLeft = timeLeft - (GetDistance(nodes, currentNode, node, distances) + 1);
      int newPressure = pressure + newTimeLeft * nodes.find(newNode)->flowrate;
      newVisit.erase(node);

      int bits = currentBits | (1 << (nodeIndex.find(node)->second));

      FindMax(nodes, distances, node, newVisit, newTimeLeft, newPressure, bits, best, nodeIndex);
    }
  }

  std::pair<std::set<std::string>, std::set<std::string>> Split(const std::vector<std::string>& nodes, int bits)
  {
    std::pair<std::set<std::string>, std::set<std::string>> pairs;
    for (int i = 0; i < nodes.size(); i++)
    {
      if (bits & 1)
        pairs.first.emplace(nodes[i]);
      else
        pairs.second.emplace(nodes[i]);
      bits >>= 1;
    }
    return pairs;
  }

  REGISTER_DAY(day16, std::set<Node>, int);

  REGISTER_TEST_EXAMPLE(day16, ExampleInput, 1, 1651);
  REGISTER_TEST        (day16, Input,        1, 1775);
  REGISTER_TEST_EXAMPLE(day16, ExampleInput, 2, 1707);
  REGISTER_TEST        (day16, Input,        2, 2351);

  READ_INPUT(input)
  {
    std::string str;
    std::set<Node> nodes;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Node node;
      ss >> "Valve" >> node.name >> "has flow rate=" >> node.flowrate >> "; tunnel";
      if (ss.peek() == 's') 
        ss >> "s lead to valves";
      else
        ss >> "leads to valve";
      while (std::getline(ss, str, ','))
      {
        if (str.front() == ' ') str = str.substr(1);
        node.paths.emplace(str);
      }
      nodes.emplace(node);
    }
    return nodes;
  }

  OUTPUT1(input)
  {
    std::map<std::string, int> distances;
    std::set<std::string> nodes;
    for (auto& node : input)
    {
      if(node.flowrate != 0)
				nodes.emplace(node.name);
    }

    return FindMax(input, distances, "AA", nodes, 30, 0);
  }

  OUTPUT2(input)
  {
    if(true) { 
      std::map<std::string, int> distances;
			std::map<std::string, int> nodeIndices;
			std::set<std::string> nodes;
			int i = 0;
			for (auto& node : input)
			{
				if (node.flowrate != 0)
				{
					nodes.emplace(node.name);
					nodeIndices.emplace(node.name, i++);
				}
			}
			std::vector<int> best;
			best.resize(1 << nodes.size());

			FindMax(input, distances, "AA", nodes, 26, 0, 0, best, nodeIndices);
			int mask = (1 << nodes.size()) - 1;
			int max = 0;
			for (int i = 0; i < best.size(); i++)
			{
        int max2 = 0;
        for(int j = 0; j < best.size(); j++)
        {
          if ((j | ((~i) & mask)) == ((~i) & mask))
          {
            max2 = std::max(max2, best[j]);
          }
        }
				max = std::max(max, best[i] + max2);
			}
			return max;
    }
  }
}
