#ifndef TESTS_H
#define TESTS_H

#include "LexerTest.h"
#include "TokensStream.h"

#include <fstream>

class Tests
{
    private:
    std::ofstream* log_file = NULL;
    TokensStream* tokens_stream = NULL;

    public:
        Tests();
        int TestLexer();
        int TestAll();
};

#endif // TESTS_H
