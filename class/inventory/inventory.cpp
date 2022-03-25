#include "inventoryInterface.hpp"
#include <iostream>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */


using namespace std;

// default ctor and fill with default item constructor
Inventory::Inventory(){
    this->table = Matrix<Item*>(length, width);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            this->table.setElmt(i, j, NULL);
        }
    }
} 

// copy constructor
Inventory::Inventory(const Inventory &inv) {
    // create Matrix of pointers to items
    this->table = Matrix<Item*>(length, width);
    // copy table
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            *(this->table(i, j)) = *(inv.table(i, j));
        }
    }
}

// dtor
Inventory::~Inventory(){
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            delete table(i, j);
        }
    }
    this->table.~Matrix();
}

void Inventory::show() const{
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (this->table(i, j) == NULL) {
                cout << "[I" << i*9+j << "|0]\t\t";
                if (j == 8) {
                    cout << endl;
                }
            }
            else {
                if (this->table(i,j)->isTool()){
                    cout << BOLDMAGENTA << "[I" << i*9+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getDurability() << "]\t" << RESET;
                    if (j == 8) {
                        cout << endl;
                    }
                }
                else{
                    cout << BOLDCYAN << "[I" << i*9+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getQuantity() << "]\t" << RESET;
                    if (j == 8) {
                        cout << endl;
                    }
                }
            }
        }
    }
}

void Inventory::give(string name, int qty){
    FileIO FI;
    string category;
    category = getCategory(name);
    bool found = false;
    if(qty <= 0){
        throw InventoryException(7); //throw
    }
    if (category == "TOOL") {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (qty > 0){
                    if (this->table(i, j) == NULL) {
                        this->table(i, j) = new Tool(getInventoryID(name),name, getInventoryType(name), 10);
                        qty--;
                    }
                }
            }
        }
        if (qty > 0) {
            throw InventoryException(0); //throw
        }
    
    }
    else if(category == "NONTOOL"){
        for (int i = 0; i < length && qty > 0; i++) {
            for (int j = 0; j < width && qty > 0; j++) {
                if (this->table(i,j) != NULL && this->table(i, j)->getName() == name) {
                    try {
                        *(this->table(i, j)) += qty;
                        qty = 0;
                        
                    } catch(NonToolException &e){
                        int sisa = 64 - this->table(i, j)->getQuantity();
                        *(this->table(i, j)) += sisa;
                        qty -= sisa;
                    }
                }
            }
        }

        for (int i = 0; i < length && qty > 0; i++) {
            for (int j = 0; j < width && qty > 0; j++) {
                if (this->table(i, j) == NULL) {
                    this->table(i, j) = new NonTool(getInventoryID(name),name, getInventoryType(name), qty > 64 ? 64 : qty);
                    qty -= 64;
                }
            }
        }
        if (qty > 0) {
            throw InventoryException(0); //throw
        }
        
    }
}

void Inventory::give(string name, int dur, int qty){
    FileIO FI;
    string category;
    category = getCategory(name);
    cout << category << endl;
    bool found = false;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (qty > 0){
                if (this->table(i, j) == NULL) {
                    this->table(i, j) = new Tool(getInventoryID(name),name, getInventoryType(name), dur);
                    qty--;
                }
            }
        }
    }
    if (qty > 0) {
        throw InventoryException(0); //throw
    }
}

void Inventory::discard(string slotID, int qty){
    if(table[slotID] == NULL){
        throw InventoryException(5);
    }
    if(qty < 1){
        throw InventoryException(8);
    }
    if((this->table[slotID])->isTool()){
        if (qty == 1) {
            delete table[slotID];
            this->table[slotID] = NULL;
        } else {
            throw InventoryException(10);
        }
    }
    else {
        try{
            *(this->table[slotID])-= qty;
            if (this->table[slotID]->getQuantity() == 0) {
                delete table[slotID];
                this->table[slotID] = NULL;
            }
        }
        catch(NonToolException &e){
            e.displayMessage();
        }
    }
    
}

void Inventory::use(const string slotID){
    if(this->table[slotID] == NULL){
        throw InventoryException(5);
    }
    try{
        this->table[slotID]->use();
        if(this->table[slotID]->getDurability()==0){
            this->table[slotID] = NULL;
        }
    }
    catch(ToolException &e){
        e.displayMessage();
    }
}

void Inventory::moveInInventory(string slotSrc, int qty, string slotTarget){
    // slot asal tidak boleh kosong
    if(this->table[slotSrc] == NULL){
        throw InventoryException(5);
    }
    //jika slot tujuan tidak kosong maka id harus sama
    if(this->table[slotTarget] != NULL){
        if (this->table[slotSrc]->getID() != this->table[slotTarget]->getID()){
            throw InventoryException(2);
        }
    }
    //jika slot src adalah tool maka tidak boleh dipindah ke selain null
    if(this->table[slotSrc]->isTool()){
        if(this->table[slotTarget] != NULL){
            throw InventoryException(1);
        }
    }
    if(qty != 1){
        throw InventoryException(6);
    }
    
    //jika target kosong
    if(this->table[slotTarget] == NULL){
        if (this->table[slotSrc]->isTool())
        {
            this->table[slotTarget] = new Tool(this->table[slotSrc]->getID(), this->table[slotSrc]->getName(), this->table[slotSrc]->getType(), this->table[slotSrc]->getDurability());
        }
        else
        {
            this->table[slotTarget] = new NonTool(this->table[slotSrc]->getID(), this->table[slotSrc]->getName(), this->table[slotSrc]->getType(), this->table[slotSrc]->getQuantity());
        }
        
        delete this->table[slotSrc];
        this->table[slotSrc] = NULL;
    }
    //jika target tidak kosong, dan sudah pasti yang dipindah nontool
    else{
        try{
            *(this->table[slotTarget]) += *(this->table[slotSrc]);
            *(this->table[slotSrc]) -= *(this->table[slotSrc]);
            if (this->table[slotSrc]->getQuantity() == 0) {
                delete table[slotSrc];
                this->table[slotSrc] = NULL;
            }
        }
        catch(NonToolException &e){
            int sisa = 64 - this->table[slotTarget]->getQuantity();
            *(this->table[slotSrc]) -= sisa;
            *(this->table[slotTarget]) += sisa;
        }

    }
}


 // get table element based on slotID
Item*& Inventory::getElmt(string slotID) {
    return this->table[slotID];
}

void Inventory::setElmt(string slotID, Item* item){
    delete this->getElmt(slotID);
    this->table[slotID] = item;
}

int Inventory::getInventoryID(string name){
    FileIO FI;
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item ID
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getID();
        }
    }
    for (int i = 0; i < listNonTool.size(); i++) {
        if (listNonTool[i].getName() == name) {
            return listNonTool[i].getID();
        }
    }

    throw InventoryException(4);
}

string Inventory::getInventoryType(string name){
    FileIO FI;
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item type
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getType();
        }
    }
    for (int i = 0; i < listNonTool.size(); i++) {
        if (listNonTool[i].getName() == name) {
            return listNonTool[i].getType();
        }
    }
    throw InventoryException(4);
}

string Inventory::getCategory(string name){
    FileIO FI;
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item category
    for (int i = 0; i < listTool.size(); i++) {
        int checkTool = listTool[i].getName().compare(name);
        checkTool = checkTool == 0;
        if (checkTool) {
            return "TOOL";
        }
    }
    // search name item in list of non tool and return item category
    for (int i = 0; i < listNonTool.size(); i++) {
        int checkTool = listNonTool[i].getName().compare(name);
        checkTool = checkTool == 0;
        if (checkTool) {
            return "NONTOOL";
        }
    }
    throw InventoryException(4);
}

void Inventory::EXPORT(string FileName){
  FileIO FI;
  ofstream outputFile("./" + FileName);

  for (int i = 0; i < length; i++){
    for (int j = 0; j < width; j++){
      if (this->table(i, j) == NULL){
        outputFile << "0:0" << endl;
      } else {
        outputFile << *(this->table(i, j)) << endl;
      }
    }
  }

  outputFile.close();
}

void Inventory::peek(string itemName)
{
  FileIO FIO;
  vector<Tool> tools = FIO.listOfTool();
  vector<NonTool> nonTools = FIO.listOfNonTool();
  vector<Recipe> recipes = FIO.listOfRecipe();
  bool itemFound = false;

  // check for tool
  cout << "Item: " << endl;
  for (int i = 0; i < tools.size() && !itemFound; i++)
  {
    if (itemName == tools[i].getName())
    {
      tools[i].display();
      cout << "TOOL" << endl;
      cout << endl;
      itemFound = true;
    }
  }

  // check for nontool
    for (int i = 0; i < nonTools.size() && !itemFound; i++)
  {
    if (itemName == nonTools[i].getName())
    {
      nonTools[i].display();
      cout << "NON-TOOL" << endl;
      cout << endl;
      itemFound = true;
    }
  }

  // check if item is found
  if (itemFound)
  {
    for (int i = 0; i < recipes.size(); i++)
    {
      if (itemName == recipes[i].getProductName())
      {
        recipes[i].display();
        cout << endl;
        return;
      }
    }
    throw InventoryException(9);
  }
  else 
  {
    throw InventoryException(4);
  }
}

void Inventory::peek(int id)
{
  FileIO FIO;
  vector<Tool> tools = FIO.listOfTool();
  vector<NonTool> nonTools = FIO.listOfNonTool();
  vector<Recipe> recipes = FIO.listOfRecipe();
  bool itemFound = false;
  string itemName;

  // check for tool
  cout << "Item: " << endl;
  for (int i = 0; i < tools.size() && !itemFound; i++)
  {
    if (id == tools[i].getID())
    {
      tools[i].display();
      cout << "TOOL" << endl;
      cout << endl;
      itemName = tools[i].getName();
      itemFound = true;
    }
  }

  // check for nontool
    for (int i = 0; i < nonTools.size() && !itemFound; i++)
  {
    if (id == nonTools[i].getID())
    {
      nonTools[i].display();
      cout << "NON-TOOL" << endl;
      cout << endl;
      itemName = nonTools[i].getName();
      itemFound = true;
    }
  }

  // check if item is found
  if (itemFound)
  {
    for (int i = 0; i < recipes.size(); i++)
    {
      if (itemName == recipes[i].getProductName())
      {
        recipes[i].display();
        cout << endl;
        return;
      }
    }
    throw InventoryException(9);
  }
  else 
  {
    throw InventoryException(4);
  }
}