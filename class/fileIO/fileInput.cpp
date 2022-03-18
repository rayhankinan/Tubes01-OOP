#include "fileInputInterface.hpp"
#include <filesystem>
using namespace std;

string FileInput::configPath = "./config";

string FileInput::getConfigPath()
{
  return FileInput::configPath;
}

vector<string> FileInput::wordsFromSentence(string str)
{
  vector<string> words;
  string word = "";

  for (auto x : str)
  {
    if (x == ' ')
    {
      words.push_back(word);
      word = "";
    }
    else
    {
      word += x;
    }
  }
  words.push_back(word);
  return words;
}

vector<vector<string>> FileInput::vectorOfWords(string path)
{
  // initialize placeholder for the items and words
  vector<vector<string>> vectorOfWords;
  vector<string> words;
  // initilaize file input
  string line;
  ifstream wordsConfigFile(path);

  // read each line
  while (getline(wordsConfigFile, line))
  {
    words = wordsFromSentence(line);
    // input each line to vector of words
    vectorOfWords.push_back(words);
  }

  wordsConfigFile.close();

  return vectorOfWords;
}

vector<Tool> FileInput::listOfTool()
{
  vector<vector<string>> vectorOfWords = FileInput::vectorOfWords(FileInput::configPath + "/item.txt");
  vector<Tool> tools;

  for (int i = 0; i < vectorOfWords.size(); i++)
  {
    // define item depends of the type
    if (vectorOfWords[i][3] == "TOOL")
    {
      int ID = stoi(vectorOfWords[i][0]);
      string name = vectorOfWords[i][1];
      string type = vectorOfWords[i][2];
      // auto set to 10
      int durability = 10;
      Tool tool(ID, name, type, durability);
      tools.push_back(tool);
    }
  }

  return tools;
}

vector<NonTool> FileInput::listOfNonTool()
{
  vector<vector<string>> vectorOfWords = FileInput::vectorOfWords(FileInput::configPath + "/item.txt");
  vector<NonTool> nonTools;

  for (int i = 0; i < vectorOfWords.size(); i++)
  {
    // define item depends of the type
    if (vectorOfWords[i][3] == "NONTOOL")
    {
      int ID = stoi(vectorOfWords[i][0]);
      string name = vectorOfWords[i][1];
      string type = vectorOfWords[i][2];
      // set quantity to 0
      int quantity = 0;
      NonTool nonTool(ID, name, type, quantity);
      nonTools.push_back(nonTool);
    }
  }

  return nonTools;
}

vector<Recipe> FileInput::listOfRecipe()
{
  vector<vector<string>> vectorOfWords;
  vector<Recipe> recipes;

  // read recipe from recipe folder
  for (const auto &entry : filesystem::directory_iterator(FileInput::configPath + "/recipe"))
  {
    string recipeConfigPath = entry.path().string();
    cout << recipeConfigPath << endl;
    vectorOfWords = FileInput::vectorOfWords(recipeConfigPath);
    cout << vectorOfWords.size() << endl;

    // line 0 of .txt is the m, n of matrix
    int length = vectorOfWords.size();
    int m = stoi(vectorOfWords[0][0]);
    int n = stoi(vectorOfWords[0][1]);
    cout << m << n << endl;
    // recipe.setRow(m);
    // recipe.setCol(n);
    cout << "POPO" << endl;
    Recipe recipe(m, n);
    cout << "POPO" << endl;

    // iterate from line 0 to m
    for (int i = 1; i <= m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        // set elmt
        recipe.setConfigElmt(i - 1, j, vectorOfWords[i][j]);
      }
    }

    string name = vectorOfWords[length - 1][0];
    int qty = stoi(vectorOfWords[length - 1][1]);

    // set name and qty in recipe
    recipe.setProductName(name);
    recipe.setProductQty(qty);
    // add to recipes
    recipes.push_back(recipe);
  }

  return recipes;
}