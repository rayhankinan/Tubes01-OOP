#ifndef FILE_IO_INTERFACE_HPP
#define FILE_IO_INTERFACE_HPP

#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../crafting/recipeInterface.hpp"
#include "../exception/fileExceptionInterface.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileIO
{
protected:
  static string configPath;
  static string testsPath;

public:
  // getter for configPath
  static string getConfigPath();
  // getter for testsPath
  static string getTestsPath();
  // get count of test file
  int countOfTestFile(string path);
  // split words from sentences to a vector of string
  vector<string> wordsFromSentence(string);
  // read each words from file
  vector<vector<string>> vectorOfWords(string);
  // vector of tools
  vector<Tool> listOfTool();
  // vector of non tools
  vector<NonTool> listOfNonTool();
  // vector of recipe
  vector<Recipe> listOfRecipe();
  // exporting item from inventory
  void EXPORT(string);
  // main program
  // void start(string);
  // display tool
  void displayTool();
  // display non tool
  void displayNonTool();
  // display recipe
  void displayRecipe();
};

#endif