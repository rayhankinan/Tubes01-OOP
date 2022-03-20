#include "fileExceptionInterface.hpp"
#include <string>
using namespace std;

int FileException::numOfFileException = 0;

FileException::FileException(string _Path) : Exception(ID)
{
  this->Path = _Path;
  FileException::numOfFileException++;
}

FileException::FileException(const FileException &FE) : Exception(FE.ID)
{
  this->Path = FE.Path;
  FileException::numOfFileException++;
}

string FileException::getFileException()
{
  return this->Path;
}

int FileException::getNumOfFileException()
{
  return FileException::numOfFileException;
}

void FileException::displayMessage() const
{
  cout << "Path '" << this->Path << "' invalid." << endl;
}
