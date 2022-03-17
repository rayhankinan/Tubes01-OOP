#include "./class/fileIO/fileInputInterface.hpp"
#include "./class/item/itemInterface.hpp"
#include "./class/item/nonToolInterface.hpp"
#include "./class/item/toolInterface.hpp"
#include "./class/fileIO/fileInput.cpp"
#include "./class/item/item.cpp"
#include "./class/item/nonTool.cpp"
#include "./class/item/tool.cpp"
#include "./class/exception/exception.cpp"
#include "./class/exception/itemException.cpp"
#include "./class/exception/nonToolException.cpp"
#include "./class/exception/toolException.cpp"

using namespace std;

int main(){
  FileInput FI;
  vector<Tool> tools = FI.listOfTool();
  vector<NonTool> nonTools = FI.listOfNonTool();
  vector<vector<string>> words = FI.vectorOfWords();

  for (int i = 0; i < tools.size(); i++){
    cout << tools[i] << endl;
  }

  for (int i = 0; i < nonTools.size(); i++){
    cout << nonTools[i] << endl;
  }
  
}