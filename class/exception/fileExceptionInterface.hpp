#ifndef FILE_EXCEPTION_INTERFACE_HPP
#define FILE_EXCEPTION_INTERFACE_HPP

#include "exceptionInterface.hpp"
#include <string>
using namespace std;

class FileException : public Exception
{
protected:
  static int numOfFileException;
  string Path;

public:
  FileException(string);              // user-defined ctor
  FileException(const FileException &); // cctor

  string getFileException();
  static int getNumOfFileException();
  void displayMessage() const;
};

#endif