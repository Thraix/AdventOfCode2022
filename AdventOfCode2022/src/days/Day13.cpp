#include "aoc.h"

namespace day13
{
  struct Node
  {
    std::variant<int, std::vector<Node>> nodes;

    bool operator==(const Node& rhs) const
    {
      return nodes == rhs.nodes;
    }

    bool operator<(const Node& rhs) const
    {
      if (std::holds_alternative<int>(nodes) && std::holds_alternative<int>(rhs.nodes))
      {
        return std::get<int>(nodes) < std::get<int>(rhs.nodes);
      }
      else
      {
        if (std::holds_alternative<int>(nodes))
        {
          Node node;
          node.nodes = std::vector<Node>{Node{std::get<int>(nodes)}};
          return node < rhs;
        }
        else if(std::holds_alternative<int>(rhs.nodes))
        {
          Node node;
          node.nodes = std::vector<Node>{Node{std::get<int>(rhs.nodes)}};
          return *this < node;
        }
        else
        {
          const std::vector<Node>& lhsNodes = std::get<std::vector<Node>>(nodes);
          const std::vector<Node>& rhsNodes = std::get<std::vector<Node>>(rhs.nodes);
          for (int i = 0; i < std::min(lhsNodes.size(), rhsNodes.size()); i++)
          {
            if (lhsNodes[i] < rhsNodes[i])
            {
              return true;
            }
            else if(rhsNodes[i] < lhsNodes[i])
            {
              return false;
            }
          }
          return lhsNodes.size() < rhsNodes.size();
        }
      }
    }
  };
  REGISTER_DAY(day13, std::vector<Node>, int);

  REGISTER_TEST_EXAMPLE(day13, ExampleInput, 1, 13);
  REGISTER_TEST        (day13, Input,        1, 5843);
  REGISTER_TEST_EXAMPLE(day13, ExampleInput, 2, 140);
  REGISTER_TEST        (day13, Input,        2, 26289);

  void ParseTree(const std::string& str, int& index, Node& parent)
  {
    std::vector<Node> nodes{};
    while (index < str.size())
    {
      if (str[index] == '[')
      {
        index++;
        Node node;
        ParseTree(str, index, node);
        nodes.emplace_back(node);
        index++;
      }
      else if(str[index] >= '0' && str[index] <= '9')
      {
        Node node;
        node.nodes = std::stoi(str.substr(index));
        nodes.emplace_back(node);
        while (str[index] >= '0' && str[index] <= '9') index++;
      }
      else
      {
        break;
      }
      if (str[index] != ',') break;
      index++;
    }
    parent.nodes = nodes;
  }

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Node> trees;
    while (std::getline(input, str))
    {
      if (str.empty()) continue;
      Node root;
      int index = 1;
      ParseTree(str, index, root);
      trees.emplace_back(root);
    }
    return trees;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    for (int i = 0; i < input.size(); i += 2)
    {
      if(input[i] < input[i + 1])
          sum += i / 2 + 1;
    }
    return sum;
  }

  OUTPUT2(input)
  {
    std::vector<Node> nodes = input;
    Node key1 = Node{std::vector<Node>{Node{2}}};
    Node key2 = Node{std::vector<Node>{Node{6}}};
    nodes.emplace_back(key1);
    nodes.emplace_back(key2);
    std::sort(nodes.begin(), nodes.end());
    auto it1 = std::find(nodes.begin(), nodes.end(), key1);
    auto it2 = std::find(nodes.begin(), nodes.end(), key2);

    return (std::distance(nodes.begin(), it1) + 1) * (std::distance(nodes.begin(), it2) + 1);
  }
}
