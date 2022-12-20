#include "aoc.h"

namespace day07
{
  struct Directory
  {
    Directory* parent;
    std::string name;
    int size = 0;
    std::map<std::string, Directory> directories;
    std::map<std::string, int> files;

    bool operator<(const Directory& rhs)
    {
      return name < rhs.name;
    }
  };

  REGISTER_DAY(day07, Directory, int);

  REGISTER_TEST_EXAMPLE(day07, ExampleInput, 1, 95437);
  REGISTER_TEST        (day07, Input,        1, 1084134);
  REGISTER_TEST_EXAMPLE(day07, ExampleInput, 2, 24933642);
  REGISTER_TEST        (day07, Input,        2, 6183184);

  void CalculateSize(Directory& directory)
  {
    if (directory.size != 0)
      return;
    int size = 0;
    for (auto& file : directory.files)
    {
      size += file.second;
    }
    for (auto& directory2 : directory.directories)
    {
      CalculateSize(directory2.second);
      size += directory2.second.size;
    }
    directory.size = size;
  }

  int SumOfDirectories(Directory& directory, int maxSize)
  {
    int sum = 0;
    if (directory.size <= maxSize)
      sum += directory.size;

    for (auto& directory2 : directory.directories) 
    {
      sum += SumOfDirectories(directory2.second, maxSize);
    }

    return sum;
  }

  int FindSmallest(Directory& directory, int minimum)
  {
    int smallest = 70000000;
    if (directory.size >= minimum)
      smallest = directory.size;

    for (auto& dir : directory.directories) {
      int min = FindSmallest(dir.second, minimum);
      if (smallest != 70000000)
        smallest = std::min(min, smallest);
    }
    return smallest;
  }

  READ_INPUT(input)
  {
    std::string str;
    std::set<int> elfs;
    int sum = 0;
    Directory* currentDirectory;

    Directory rootDirectory;
    rootDirectory.name = "/";
    currentDirectory = &rootDirectory;
    std::getline(input, str); // $ cd /
    while (std::getline(input, str))
    {
      if (str[0] == '$')
      {
        std::stringstream ss{str};
        std::string command;
				ss >> "$" >> command;
				if(command == "cd")
				{ 
          std::string directory;
          ss >> directory;
          if(directory == "..")
            currentDirectory = currentDirectory->parent;
          else
						currentDirectory = &currentDirectory->directories[directory];
        }
      }
      else
      {
				std::stringstream ss{str};
        if (str[0] == 'd')
        {
          Directory directory;
          ss >> "dir" >> directory.name;
					directory.parent = currentDirectory;
					currentDirectory->directories.emplace(directory.name, directory);
        }
        else
        {
          int size;
          std::string name;
          ss >> size >> name;
          currentDirectory->files.emplace(name, size);
        }
      }

    }
    return rootDirectory;
  }

  OUTPUT1(input)
  {
    Directory directory = input;
    CalculateSize(directory);

    return SumOfDirectories(directory, 100000);
  }

  OUTPUT2(input)
  {
    Directory directory = input;
    CalculateSize(directory);
    int space = 70000000;
    int neededSpace = 30000000 - (space - directory.size);
    return FindSmallest(directory, neededSpace);
  }
}
