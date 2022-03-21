#include "fileIOInterface.hpp"
#include <filesystem>
using namespace std;

string FileIO::configPath = "./config";
string FileIO::testsPath = "./tests";

/* get folder config path */
string FileIO::getConfigPath()
{
  return FileIO::configPath;
}

/* get tests config path */
string FileIO::getTestsPath()
{
  return FileIO::testsPath;
}

/* get count of .in file from tests folder */
int FileIO::countOfTestFile(string path)
{
  auto dirIter = filesystem::directory_iterator(path);
  int fileCount = 0;

  for (auto &entry : dirIter)
  {
    if (entry.path().extension() == ".in")
    {
      ++fileCount;
    }
  }
  return fileCount;
}

/* split sentences into vector of words */
vector<string> FileIO::wordsFromSentence(string str)
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

/* mapping every words in a file */
vector<vector<string>> FileIO::vectorOfWords(string path)
{
  // initialize placeholder for the items and words
  vector<vector<string>> vectorOfWords;
  vector<string> words;
  // initilaize file IO
  try
  {
    string line;
    ifstream wordsConfigFile(path);

    // read each line
    while (getline(wordsConfigFile, line))
    {
      words = wordsFromSentence(line);
      // IO each line to vector of words
      vectorOfWords.push_back(words);
    }

    wordsConfigFile.close();
  }
  catch (FileException FE)
  {
    FE.displayMessage();
  }

  return vectorOfWords;
}

/* get list of tool */
vector<Tool> FileIO::listOfTool()
{
  vector<vector<string>> vectorOfWords = FileIO::vectorOfWords(FileIO::configPath + "/item.txt");
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

/* get list of non tool */
vector<NonTool> FileIO::listOfNonTool()
{
  vector<vector<string>> vectorOfWords = FileIO::vectorOfWords(FileIO::configPath + "/item.txt");
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

/* get list of recipe*/
vector<Recipe> FileIO::listOfRecipe()
{
  vector<vector<string>> vectorOfWords;
  vector<Recipe> recipes;

  // read recipe from recipe folder
  for (const auto &entry : filesystem::directory_iterator(FileIO::configPath + "/recipe"))
  {
    string recipeConfigPath = entry.path().string();
    vectorOfWords = FileIO::vectorOfWords(recipeConfigPath);

    // line 0 of .txt is the m, n of matrix
    int length = vectorOfWords.size();
    int m = stoi(vectorOfWords[0][0]);
    int n = stoi(vectorOfWords[0][1]);
    // recipe.setRow(m);
    // recipe.setCol(n);
    Recipe recipe(m, n);

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

/* exporting inventory */
/* BELUM BISA INVENTORYNYA BELUM FIXED */
void FileIO::EXPORT(string FileName)
{
  // try
  // {

  // }

  // catch (FileException FE)
  // {
  //   FE.displayMessage();
  // }
}

/* MAIN PROGRAM */
void FileIO::start(string FileName)
{
  string FilePath = FileIO::testsPath + FileName;
  vector<vector<string>> commands = vectorOfWords(FilePath);

  // iterate each line of the command
  for (int i = 0; i += 0; i++)
  {
    string command = commands[i][0];

    try
    {
      if (command == "SHOW")
      {
        /* Display crafting table */
        this->Command::SHOW();
      }
      else if (command == "GIVE")
      {
        string itemName = commands[i][1];
        string itemQty = commands[i][2];

        /* Give item */
        this->Command::GIVE();
      }
      else if (command == "DISCARD")
      {
        string inventorySlotID = commands[i][1];
        string itemQty = commands[i][2];

        /* Discard item */
        this->Command::DISCARD();
      }
      else if (command == "MOVE")
      {
        string slotSrc = commands[i][1];
        string slotDest = commands[i][2];
        string slotQty = commands[i][3];

        /* Move item */
        this->Command::MOVE();
      }
      else if (command == "USE")
      {
        string inventorySlotID = commands[i][1];

        cin >> inventorySlotID;
        /* Use item */
        this->Command::USE();
      }
      else if (command == "CRAFT")
      {
        /* Craft item */
        this->Command::CRAFT();
      }
      else if (command == "EXPORT")
      {
        string fileName = commands[i][1];

        /* Export to file */
        this->Command::EXPORT();
      }
      else
      {
        this->Command::INVALID_COMMAND(command);
      }
    }
    /* catch for any invalid command */
    catch (CommandException CE)
    {
      CE.displayMessage();
    }
  }
}

/* tester function */
void FileIO::displayTool()
{
  vector<Tool> tools = listOfTool();

  cout << "List of Tool: " << endl;
  for (int i = 0; i < tools.size(); i++)
  {
    cout << i + 1 << "." << endl;
    tools[i].display();
    cout << endl;
  }
  cout << endl;
}

/* tester function */
void FileIO::displayNonTool()
{
  vector<NonTool> nonTools = listOfNonTool();

  cout << "List of NonTool: " << endl;
  for (int i = 0; i < nonTools.size(); i++)
  {
    cout << i + 1 << "." << endl;
    nonTools[i].display();
    cout << endl;
  }
  cout << endl;
}

/* tester function */
void FileIO::displayRecipe()
{
  vector<Recipe> recipes = listOfRecipe();

  cout << "List of Recipe: " << endl;
  for (int i = 0; i < recipes.size(); i++)
  {
    cout << i + 1 << "." << endl;
    recipes[i].display();
    cout << endl;
  }
  cout << endl;
}