#ifndef EXCEPTION_DATA_H
#define EXCEPTION_DATA_H

#include <iostream>

struct exceptionData
{
    std::string thrownClass;
    std::string thrownFunction;
    std::string thrownStatement;
};

std::ostream & operator<< (std::ostream &out, const exceptionData &exc);

exceptionData PreperExceptionData(std::string className, std::string functionName, std::string statement);

#endif // EXCEPTION_DATA_H
