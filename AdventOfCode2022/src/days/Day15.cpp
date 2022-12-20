#include "aoc.h"

namespace day15
{
  struct Scanner
  {
    Index2D position;
    Index2D beacon;
  };
  REGISTER_DAY(day15, std::vector<Scanner>, int64_t);

  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 1, 26);
  REGISTER_TEST        (day15, Input,        1, 5564017);
  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 2, 56000011);
  REGISTER_TEST        (day15, Input,        2, 11558423398893);

	struct Line
	{
		int start;
		int end;
    bool operator<(const Line& rhs) const
    {
      if (start == rhs.start) return end < rhs.end;
      return start < rhs.start;
    }
	};

  bool IsOverlap(const Line& l1, const Line& l2)
  {
    return (l1.start >= l2.start && l1.end <= l2.end) || (l2.start >= l1.start && l2.end <= l1.end);
  }

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Scanner> scanners;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Scanner scanner;
      ss >> "Sensor at x=" >> scanner.position.x >> ", y=" >> scanner.position.y >> ": closest beacon is at x=" >> scanner.beacon.x >> ", y=" >> scanner.beacon.y;
      scanners.emplace_back(scanner);
    }
    return scanners;
  }

  OUTPUT1(input)
  {
    int row = 2000000;
    if (isExample)
    {
      row = 10;
    }
    std::set<Line> lines;
    for (auto& scanner : input) {
      Index2D diff = scanner.position - scanner.beacon;
			int manhattan = std::abs(diff.x) + std::abs(diff.y);
      if ((scanner.position.y <= row && scanner.position.y + manhattan >= row) || (scanner.position.y >= row && scanner.position.y - manhattan <= row))
      {
        int distance = std::abs(row - scanner.position.y);
        int count = manhattan * 2 + 1 - (distance) * 2;
        Line line;
        line.start = scanner.position.x - count / 2;
        line.end = scanner.position.x + count / 2;
        lines.emplace(line);
      }
    }
    int min = lines.begin()->start;
    int max = lines.begin()->end;
    for (auto& line : lines)
    {
      min = std::min(min, line.start);
      max = std::max(max, line.end);
    }
    std::set<Index2D> beacons;
    for (auto& scanner : input)
    {
      if (scanner.beacon.y == row && scanner.beacon.x >= min && scanner.beacon.x <= max)
        beacons.emplace(scanner.beacon);
    }


    return max - min + 1 - beacons.size();
  }

#if 0
  OUTPUT2(input)
  {
    Array2D<char> grid{20, 20};
    grid.Fill('.');
    for (int y = 0; y < 20; y++)
    {
      for (int x = 0; x < 20; x++)
      {
        int i = 0;
        for (auto& scanner : input)
        {
          if (Index2D{x, y} == scanner.position)
            grid.Set(x, y, 'A' + i);
          else
          {
            Index2D diff = scanner.position - scanner.beacon;
            int manhattan = std::abs(diff.x) + std::abs(diff.y);
            int manhattan2 = std::abs(scanner.position.x - x) + std::abs(scanner.position.y - y);
            if (manhattan2 <= manhattan) {
              grid.Set(x, y, 'a' + i);
            }
          }
          i++;
        }

      }
    }
    std::cout << grid << std::endl;
    return 0;
    // return (int64_t)2889604 * (int64_t)4000000 + (int64_t)3398893;
    int row = 4000000;
    if (isExample)
      row = 20;
    for (int i = 0; i < row; i++)
    {
      std::set<Line> lines;
      for (auto& scanner : input) {
        Index2D diff = scanner.position - scanner.beacon;
        int manhattan = std::abs(diff.x) + std::abs(diff.y);
        if ((scanner.position.y <= i && scanner.position.y + manhattan >= i) || (scanner.position.y >= i && scanner.position.y - manhattan <= i ))
        {
          int distance = std::abs(i - scanner.position.y);
          int count = manhattan * 2 + 1 - (distance) * 2;
          Line line;
          line.start = scanner.position.x - count / 2;
          line.end = scanner.position.x + count / 2;
          lines.emplace(line);
        }
      }
      std::vector<Line> nonOverlappingLines;
      if (lines.size() > 0)
      {
        Line currentLine = *lines.begin();
        for (auto& line : lines)
        {
          if (currentLine.end + 1 < line.start)
          {
            std::cout << "Row: " << i << "Pos: " << currentLine.end << std::endl;
            return (int64_t)(currentLine.end + 1) * (int64_t)4000000 + (int64_t)i;
            nonOverlappingLines.emplace_back(currentLine);
            currentLine = line;
          }
          else
            currentLine.end = std::max(currentLine.end, line.end);
        }
        nonOverlappingLines.emplace_back(currentLine);
        // std::cout << "Size: " << nonOverlappingLines.size() << std::endl;
      }
    }
    return 10;
  }
#else
  int Manhattan(const Index2D& i1, const Index2D& i2)
  {
    return std::abs(i1.x - i2.x) + std::abs(i1.y - i2.y);
  }
  bool CheckDistances(const Scanner& scanner1, const Scanner& scanner2)
  {
		int manhattan1 = Manhattan(scanner1.position, scanner1.beacon);
		int manhattan2 = Manhattan(scanner2.position, scanner2.beacon);
		int manhattan3 = Manhattan(scanner1.position, scanner2.position);
    return manhattan1 + manhattan2 + 2 >= manhattan3;
  }

  std::vector<Index2D> GetOneAway(const Scanner& scanner1, const Scanner& scanner2, const Scanner& scanner3, int range)
  {
    std::vector<Index2D> valid;
    int distance = Manhattan(scanner1.position, scanner1.beacon) + 1;
    for (int i = 0; i < distance * 2; i++)
    {
      int y = scanner1.position.y + distance - i;
      if (y >= 0 && y <= range)
      {
        if (i >= distance)
        {
          if(scanner1.position.x + distance * 2 - i >= 0 && scanner1.position.x + distance * 2 - i <= range)
						valid.emplace_back(scanner1.position + Index2D{distance * 2 - i, distance - i});
          if(scanner1.position.x - distance * 2 + i >= 0 && scanner1.position.x - distance * 2 + i <= range)
						valid.emplace_back(scanner1.position + Index2D{i - distance * 2, distance - i});
        }
        else
        {
          if(scanner1.position.x + i >= 0 && scanner1.position.x + i <= range)
						valid.emplace_back(scanner1.position + Index2D{i, distance - i});
          if(scanner1.position.x - i >= 0 && scanner1.position.x - i <= range)
						valid.emplace_back(scanner1.position + Index2D{-i, distance - i});
        }
      }
    }
    std::vector<Index2D> valid2;
    for (auto& pos : valid)
    {
      if (Manhattan(pos, scanner2.position) == Manhattan(scanner2.position, scanner2.beacon) + 1)
      {
        valid2.emplace_back(pos);
      }
    }
    std::vector<Index2D> valid3;
    for (auto& pos : valid2)
    {
      if (Manhattan(pos, scanner3.position) == Manhattan(scanner3.position, scanner3.beacon) + 1)
      {
        valid3.emplace_back(pos);
      }
    }
    return valid3;
  }

  OUTPUT2(input)
  {
    int range = 4000000;
    if (isExample)
      range = 20;
    for(int i = 0; i < input.size(); i++)
    {
			for(int j = i + 1; j < input.size(); j++)
			{
        if(CheckDistances(input[i], input[j]))
        {
					for (int k = j + 1; k < input.size(); k++)
					{
						if (CheckDistances(input[i], input[k]) && CheckDistances(input[j], input[k]))
						{
							std::vector<Index2D> valid = GetOneAway(input[i], input[j], input[k], range);
							for (auto& pos : valid)
							{
								bool found = true;
								for (auto& scanner : input)
								{
									if (Manhattan(scanner.position, pos) <= Manhattan(scanner.position, scanner.beacon))
									{
										found = false;
										break;
									}
								}
								if(found)
									return (int64_t)pos.x * 4000000 + (int64_t)pos.y;
							}
						}
					}
        }
			}
    }
    return 0;
  }
#endif
}

