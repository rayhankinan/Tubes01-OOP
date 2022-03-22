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

  /* loop until command EXIT*/
  while (this->command != "")
  {
    try {
      if (this->command == "SHOW")
      {
        /* Display crafting table */
        this->Command::SHOW(inventory);
      }
      else if (this->command == "GIVE")
      {
        string itemName;
        int itemQty;

        cin >> itemName >> itemQty;
        /* Give item */
        this->Command::GIVE(inventory, itemName, itemQty);
      }
      else if (this->command == "DISCARD")
      {
        string inventorySlotID;
        int itemQty;

        cin >> inventorySlotID >> itemQty;
        /* Discard item */
        this->Command::DISCARD(inventory, inventorySlotID, itemQty);
      }
      else if (this->command == "MOVE")
      {
        string slotSrc, slotDest;
        int slotQty;

        cin >> slotSrc >> slotQty >> slotDest;
        /* Move item */
        this->Command::MOVE(inventory, slotSrc, slotQty, slotDest);
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
        this->Command::CRAFT();
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
    catch(CommandException CE) 
    {
      CE.displayMessage();
    }
    /* ask again for IO */
    setCommand();
  }
}