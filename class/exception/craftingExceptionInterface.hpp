#ifndef CRAFTING_EXCEPTION_INTERFACE_HPP
#define CRAFTING_EXCEPTION_INTERFACE_HPP

#include "exceptionInterface.hpp"
using namespace std;

class CraftingException : public Exception
{
protected:
  static int numOfCraftingException;
  static string errorMessages[];

public:
  CraftingException(int); // user-defined ctor
  CraftingException(const CraftingException &); // cctor

  static int getNumOfCraftingException();

  void displayMessage() const;
};

#endif
