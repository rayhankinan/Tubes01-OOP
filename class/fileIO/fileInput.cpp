#include "fileInputInterface.hpp"
using namespace std;

string FileInput::configPath = "./config";

string FileInput::getConfigPath(){
  return FileInput::configPath;
}

vector<string> FileInput::wordsFromSentence(string str){
  vector<string> words;
  string word = "";

  for (auto x : str){
    if (x == ' '){
      words.push_back(word);
      word = "";
    } else {
      word += x;
    }
  }
  words.push_back(word);
  return words;
}

vector<vector<string>> FileInput::vectorOfWords(){
  // initialize placeholder for the items and words
  vector<vector<string>> vectorOfWords;
  vector<string> words;
  // initilaize file input
  string line;
  string itemConfigPath = FileInput::configPath + "/item.txt";
  ifstream itemConfigFile(itemConfigPath);

  // read each line
  while (getline(itemConfigFile, line)){
    words = wordsFromSentence(line);
    // input each line to vector of words
    vectorOfWords.push_back(words);
  }

  itemConfigFile.close();

  return vectorOfWords;
}

vector<Tool> FileInput::listOfTool(){
  vector<vector<string>> vectorOfWords = FileInput::vectorOfWords();
  vector<Tool> tools;

  for (int i = 0; i < vectorOfWords.size(); i++){
    // define item depends of the type
    if (vectorOfWords[i][3] == "TOOL"){
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

vector<NonTool> FileInput::listOfNonTool(){
  vector<vector<string>> vectorOfWords = FileInput::vectorOfWords();
  vector<NonTool> nonTools;

  for (int i = 0; i < vectorOfWords.size(); i++){
    // define item depends of the type
    if (vectorOfWords[i][3] == "NONTOOL"){
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
