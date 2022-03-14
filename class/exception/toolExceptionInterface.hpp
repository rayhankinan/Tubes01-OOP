#ifndef TOOL_EXCEPTION_INTERFACE_HPP
#define TOOL_EXCEPTION_INTERFACE_HPP

#include "itemExceptionInterface.hpp"

class ToolException : public ItemException {
    private:
        static int numOfToolException;
        static string message[];

    public:
        ToolException(int); // user-defined ctor
        ToolException(const ToolException&); // cctor

        static int getNumOfToolException(); // numOfToolException getter

        void displayMessage() const; // message display
};

#endif