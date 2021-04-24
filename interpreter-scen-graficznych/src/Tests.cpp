#include "Tests.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Tests::Tests()
{
}

int Tests::TestAll()
{
    ofstream log;

    log.open("test_log.txt", ios_base::app);

    log_file = &log;

    fstream input_file;

    TestLexer();

    log.close();
}

int Tests::TestLexer()
{
    stringstream sstream;
    iostream *stream = &sstream;

    LexerTest lexer_test(stream, log_file);
    lexer_test.TestAll();
}
