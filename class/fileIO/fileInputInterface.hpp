#ifndef FILE_INPUT_INTERFACE_HPP
#define FILE_INPUT_INTERFACE_HPP

#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../crafting/recipeInterface.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileInput
{
protected:
  static string configPath;

public:
  // getter for configPath
  static string getConfigPath();
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
  // display tool
  void displayTool();
  // display non tool
  void displayNonTool();
  // display recipe
  void displayRecipe();
};

#endif