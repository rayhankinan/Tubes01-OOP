// HEADER
#include "./class/fileIO/fileInputInterface.hpp"
#include "./class/item/itemInterface.hpp"
#include "./class/item/nonToolInterface.hpp"
#include "./class/item/toolInterface.hpp"
#include "./class/fileIO/fileInput.cpp"
#include "./class/crafting/recipeInterface.hpp"
#include "./class/collection/matrixInterface.hpp"
// BIAR GAUSAH PAKE MAKE FILE TESTNYA
#include "./class/item/item.cpp"
#include "./class/item/nonTool.cpp"
#include "./class/item/tool.cpp"
#include "./class/exception/exception.cpp"
#include "./class/exception/itemException.cpp"
#include "./class/exception/nonToolException.cpp"
#include "./class/exception/toolException.cpp"
#include "./class/crafting/recipe.cpp"

using namespace std;

int main(){
  FileInput FI;
  vector<Tool> tools = FI.listOfTool();
  vector<NonTool> nonTools = FI.listOfNonTool();

  // for (int i = 0; i < tools.size(); i++){
  //   cout << tools[i] << endl;
  // }

  // for (int i = 0; i < nonTools.size(); i++){
  //   cout << nonTools[i] << endl;
  // }
  

  vector<Recipe> recipes = FI.listOfRecipe();
  // cout << recipes.size();

  for (int i = 0; i < recipes.size(); i++){
    recipes[i].printRecipe();
  }

}