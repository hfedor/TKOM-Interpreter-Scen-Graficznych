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
    // Log file
    ofstream log;

    log.open("test_log.txt", ios_base::app);

    log_file = &log;

    // Tokens stream
    TokensFileStream tokens("tokens_stream_tests");

    tokens_stream = &tokens;

    // Programs Tests
    TestLexer(); // Test Lexer
    // Test Parser

    log.close();
}

int Tests::TestLexer()
{
    stringstream input_stream;
    iostream* stream = &input_stream;
    LexerTest lexer_test(stream, tokens_stream, log_file);
    lexer_test.TestAll();
}
