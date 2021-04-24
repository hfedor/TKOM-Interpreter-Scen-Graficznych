#ifndef LEXERTEST_H
#define LEXERTEST_H

#include "Lexer.h"
#include "Token.h"

#include <iostream>
#include <fstream>

class LexerTest
{
    private:
        std::iostream* stream = NULL;
        std::ofstream* log_file = NULL;
        Lexer lexer;
    public:
        // CONSTRUCTORS
        LexerTest();
        LexerTest(std::ofstream*);
        LexerTest(std::iostream*);
        LexerTest(std::iostream*, std::ofstream*);
        // GETTERS
        std::iostream* GetStream(){return stream;}
        std::ofstream* GetLogFile(){return log_file;}
        Lexer GetLexer(){return lexer;}
        // LEXER GETTERS
        std::istream* GetLexersInputStream(){return lexer.GetInputStream();}
        std::ofstream* GetLexersLogFile(){return lexer.GetLogFile();}
        int GetLexersLinesCount(){return lexer.GetLinesCount();}
        int GetLexersSignsCount(){return lexer.GetSignsCount();}
        std::string GetLexersStreamBuffor(){return lexer.GetStreamBuffor();}
        char GetLexersLastSign(){return lexer.GetLastSign();}
        char GetLexersPresentSign(){return lexer.GetPresentSign();}
        char GetLexersNextSign(){return lexer.GetNextSign();}
        // LEXERS ATTRIBUTES CHECKERS
        bool CheckLexersInputStream(std::istream* expected){return GetLexersInputStream() == expected ? true : false;}
        bool CheckLexersLogFile(std::ofstream* expected){return GetLexersLogFile() == expected ? true : false;}
        bool CheckLexersLinesCount(int expected){return GetLexersLinesCount() == expected ? true : false;}
        bool CheckLexersSignsCount(int expected){return GetLexersSignsCount() == expected ? true : false;}
        bool CheckLexersStreamBuffor(std::string expected){return GetLexersStreamBuffor() == expected ? true : false;}
        bool CheckLexersLastSign(char expected){return GetLexersLastSign() == expected ? true : false;}
        bool CheckLexersPresentSign(char expected){return GetLexersPresentSign() == expected ? true : false;}
        bool CheckLexersNextSign(char expected){return GetLexersNextSign() == expected ? true : false;}
        // LEXERS ATTRIBUTES TESTS
        void TestLexersInputStream(std::istream* expected);
        void TestLexersInputStream(std::istream* expected, std::string thrownStatement);
        void TestLexersLogFile(std::ofstream* expected);
        void TestLexersLogFile(std::ofstream* expected, std::string thrownStatement);
        void TestLexersLinesCount(int expected);
        void TestLexersLinesCount(int expected, std::string thrownStatement);
        void TestLexersSignsCount(int expected);
        void TestLexersSignsCount(int expected, std::string thrownStatement);
        void TestLexersStreamBuffor(std::string expected);
        void TestLexersStreamBuffor(std::string expected, std::string thrownStatement);
        void TestLexersLastSign(char expected);
        void TestLexersLastSign(char expected, std::string thrownStatement);
        void TestLexersPresentSign(char expected);
        void TestLexersPresentSign(char expected, std::string thrownStatement);
        void TestLexersNextSign(char expected);
        void TestLexersNextSign(char expected, std::string thrownStatement);
        void TestLexerState(int exp_line, int exp_sign, char exp_last_sign, char exp_present_sign, char exp_next_sign);
        // SETTERS
        int SetLogFile(std::ofstream*);
        int SetStream(std::iostream*);
        // TESTS
        int TestAll();
        int TestGetNextToken(Token);
        int TestGetSign(char);
        int TestSetLogFile();
        int TestStepBack(char);

};

#endif // LEXERTEST_H
