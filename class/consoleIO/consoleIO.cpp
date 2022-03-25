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

  /* loop until command EXIT or reach an EOF*/
  while (!(this->command == "" || this->command == "EXIT"))
  {
    try
    {
      /* Display inventory and crafting table */
      if (this->command == "SHOW")
      {
        this->SHOW(inventory, table);
      }
      /* Give item */
      else if (this->command == "GIVE")
      {
        string itemName;
        string itemQtyStr;

        cin >> itemName >> itemQtyStr;
        int itemQty = stoi(itemQtyStr);

        this->GIVE(inventory, itemName, itemQty);
      }
      /* Discard item */
      else if (this->command == "DISCARD")
      {
        string inventorySlotID;
        string itemQtyStr;

        cin >> inventorySlotID >> itemQtyStr;
        int itemQty = stoi(itemQtyStr);
        this->DISCARD(inventory, inventorySlotID, itemQty);
      }
      /* Move item */
      else if (this->command == "MOVE")
      {
        string slotQtyStr;
        string slotSrc, slotDest;

        cin >> slotSrc >> slotQtyStr;
        int slotQty = stoi(slotQtyStr);
        if (slotQty == 1)
        {
          cin >> slotDest;
          if (slotDest[0] == 'I')
          {
            if (slotSrc[0] == 'I')
            {
              /* Move item inventory to inventory */
              this->MOVE(inventory, slotSrc, slotQty, slotDest);
            }
            else
            {
              /* Move item crafting to inventory */
              this->MOVE(table, inventory, slotSrc, slotQty, slotDest);
            }
          }
          else
          {
            /* Move item inventory to crafting (1 item) */
            vector<string> slots = {slotDest};
            this->MOVE(table, inventory, slotSrc, slotQty, slots);
          }
        }
        else
        {
          /* Move item inventory to crafting (multiple item) */
          vector<string> slots;
          for (int i = 0; i < slotQty; i++)
          {
            cin >> slotDest;
            slots.push_back(slotDest);
          }
          this->MOVE(table, inventory, slotSrc, slotQty, slots);
        }
      }
      /* Use item */
      else if (this->command == "USE")
      {
        string inventorySlotID;

        cin >> inventorySlotID;
        this->USE(inventory, inventorySlotID);
      }
      /* Craft item */
      else if (this->command == "CRAFT")
      {
        this->CRAFT(table, inventory);
      }
      /* Export to file */
      else if (this->command == "EXPORT")
      {
        string fileName;

        cin >> fileName;
        this->Command::EXPORT(inventory, fileName);
      }
      /* Peek recipe */
      else if (this->command == "PEEK")
      {
        string item;
        
        cin >> item;
        this->Command::PEEK(table, item);
      }
      /* Invalid command */
      else
      {
        this->Command::INVALID_COMMAND(this->command);
      }
    }
    /* catch for any invalid command */
    catch (Exception &E)
    {
      E.displayMessage();
    }
    /* catch for invalid argument from conversion */
    catch (invalid_argument &e)
    {
      cout << "Can't be parsed to a number." << endl;
    }
    /* ask again for IO */
    setCommand();
  }
}