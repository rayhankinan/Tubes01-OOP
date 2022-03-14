#ifndef NON_TOOL_EXCEPTION_INTERFACE_HPP
#define NON_TOOL_EXCEPTION_INTERFACE_HPP

#include "itemExceptionInterface.hpp"

class NonToolException : public ItemException {
    private:
        static int numOfNonToolException;
        static string message[];

    public:
        NonToolException(int); // user-defined ctor
        NonToolException(const NonToolException&); // cctor

        static int getNumOfNonToolException(); // numOfNonToolException getter

        void displayMessage() const; // message display
};

#endif