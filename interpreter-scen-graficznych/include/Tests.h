#ifndef TESTS_H
#define TESTS_H

#include "LexerTest.h"

#include <fstream>

class Tests
{
    std::ofstream* log_file = NULL;

    public:
        Tests();
        int TestLexer();
        int TestAll();

    protected:

    private:
};

#endif // TESTS_H
