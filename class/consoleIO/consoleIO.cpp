#include "consoleIOInterface.hpp"

ConsoleIO::ConsoleIO() : Command()
{
  this->command = "";
}

ConsoleIO::ConsoleIO(string command)
{
  this->command = command;
}

ConsoleIO::ConsoleIO(const ConsoleIO &CI)
{
  this->command = CI.command;
}

string ConsoleIO::getCommand()
{
  return this->command;
}

void ConsoleIO::setCommand(string command)
{
  this->command = command;
}

void ConsoleIO::setCommand()
{
  string command;
  cin >> command;
  this->command = command;
}

void ConsoleIO::start()
{
  /* Read command from user */
  setCommand();
  Inventory inventory = Inventory();
  CraftingTable table = CraftingTable();

  /* loop until command EXIT*/
  while (this->command != "")
  {
    try {
      if (this->command == "SHOW")
      {
        /* Display crafting table */
        this->Command::SHOW(inventory, table);
      }
      else if (this->command == "GIVE")
      {
        string itemName;
        string itemQtyStr;

        cin >> itemName >> itemQtyStr;
        int itemQty = stoi(itemQtyStr);

        /* Give item */
        this->Command::GIVE(inventory, itemName, itemQty);
      }
      else if (this->command == "DISCARD")
      {
        string inventorySlotID;
        string itemQtyStr;

        cin >> inventorySlotID >> itemQtyStr;
        int itemQty = stoi(itemQtyStr);
        /* Discard item */
        this->Command::DISCARD(inventory, inventorySlotID, itemQty);
      }
      else if (this->command == "MOVE")
      {
        string slotQtyStr;
        string slotSrc, slotDest;

        cin >> slotSrc >> slotQtyStr;
        int slotQty = stoi(slotQtyStr);
        if (slotQty == 1) {
          cin >> slotDest;
          if (slotDest[0] == 'I') {
            if (slotSrc[0] == 'I') {
              /* Move item inventory to inventory */
              this->Command::MOVE(inventory, slotSrc, slotQty, slotDest);
            }
            else {
              /* Move item crafting to inventory */
              this->Command::MOVE(table, inventory, slotSrc, slotQty, slotDest);
            }
          }
          else {
            /* Move item inventory to crafting (1 item) */
            vector<string> slots = { slotDest };
            this->Command::MOVE(table, inventory, slotSrc, slotQty, slots);
          }
        } 
        else {
          /* Move item inventory to crafting (multiple item) */
          vector<string> slots;
          for (int i = 0; i < slotQty; i++) {
            cin >> slotDest;
            slots.push_back(slotDest);
          }
          this->Command::MOVE(table, inventory, slotSrc, slotQty, slots);
        }
      }
      else if (this->command == "USE")
      {
        string inventorySlotID;

        cin >> inventorySlotID;
        /* Use item */
        this->Command::USE(inventory, inventorySlotID);
      }
      else if (this->command == "CRAFT")
      {
        /* Craft item */
        this->Command::CRAFT(table, inventory);
      }
      else if (this->command == "EXPORT")
      {
        string fileName;

        cin >> fileName;
        /* Export to file */
        this->Command::EXPORT(inventory, fileName);
      }
      else
      {
        this->Command::INVALID_COMMAND(this->command);
      }
    }
    /* catch for any invalid command */
    catch(Exception &E) 
    {
      E.displayMessage();
    }
    catch(invalid_argument &e){
      cout << "Can't be parsed to a number." << endl;
    }
    /* ask again for IO */
    setCommand();
  }
}