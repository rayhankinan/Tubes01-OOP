#include "consoleInputInterface.hpp"

ConsoleInput::ConsoleInput() : Command()
{
  this->command = "";
}

ConsoleInput::ConsoleInput(string command)
{
  this->command = command;
}

ConsoleInput::ConsoleInput(const ConsoleInput &CI)
{
  this->command = CI.command;
}

string ConsoleInput::getCommand()
{
  return this->command;
}

void ConsoleInput::setCommand(string command)
{
  this->command = command;
}

void ConsoleInput::setCommand()
{
  string command;
  cin >> command;
  this->command = command;
}

void ConsoleInput::start()
{
  /* Read command from user */
  setCommand();

  while (this->command != "EXIT")
  {
    if (this->command == "SHOW")
    {
      /* Display crafting table */
      this->Command::SHOW();
    }
    else if (this->command == "GIVE")
    {
      string itemName;
      int itemQty;

      cin >> itemName >> itemQty;
      /* Give item */
      this->Command::GIVE();
    }
    else if (this->command == "DISCARD")
    {
      string inventorySlotID;
      int itemQty;

      cin >> inventorySlotID >> itemQty;
      /* Discard item */
      this->Command::DISCARD();
    }
    else if (this->command == "MOVE")
    {
      string slotSrc, slotDest;
      int slotQty;

      cin >> slotSrc >> slotQty >> slotDest;
      /* Move item */
      this->Command::MOVE();
    }
    else if (this->command == "USE")
    {
      string inventorySlotID;

      cin >> inventorySlotID;
      /* Use item */
      this->Command::USE();
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
      this->Command::EXPORT();
    }
    else
    {
      this->Command::INVALID_COMMAND();
    }

    setCommand();
  }
}