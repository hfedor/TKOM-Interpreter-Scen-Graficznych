#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#include "Token.h"

class Lexer
{
private:
    std::istream* input_stream = NULL;
    std::ofstream* log_file = NULL;
    int lines_count = 0;
    int signs_count = 0;
    int last_signs_count = NULL;
    std::string last_stream_buffor = "";
    std::string stream_buffor = "";
    char last_sign = NULL;
    char present_sign = NULL;
    char next_sign = NULL;
    std::list<Token*> tokens;
public:
    // CONSTRUCORS
    Lexer();
    Lexer(std::istream*);
    Lexer(std::istream*, std::ofstream*);
    // GETTERS
    std::istream* GetInputStream(){return input_stream;}
    std::ofstream* GetLogFile(){return log_file;}
    int GetLinesCount(){return lines_count;}
    int GetSignsCount(){return signs_count;}
    std::string GetStreamBuffor(){return stream_buffor;}
    char GetLastSign(){return last_sign;}
    char GetPresentSign(){return present_sign;}
    char GetNextSign(){return next_sign;}
    // METHODS
    char GetSign();
    Token* GetNextToken();
    std::string MakeUpStreamBuffor();
    char StepBack();
    std::string ShowPresentPosition();
    // TOKEN BUILDERS
    Token* BuildParenthesisOpen(char, int, int);
    Token* BuildParenthesisClose(char, int, int);
    Token* BuildSquareBracketOpen(char, int, int);
    Token* BuildSquareBracketClose(char, int, int);
    Token* BuildComma(char, int, int);
    Token* BuildDot(char, int, int);
    Token* BuildSemicolon(char, int, int);
    Token* BuildGreaterThan(char, int, int);
    Token* BuildLessThan(char, int, int);
    Token* BuildEqual(char, int, int);
    Token* BuildNotEqual(char, int, int);
    Token* BuildDoubleColon(char, int, int);
    Token* BuildAndOperator(char, int, int);
    Token* BuildOrOperator(char, int, int);
    Token* BuildPlus(char, int, int);
    Token* BuildMinus(char, int, int);
    Token* BuildMultiplication(char, int, int);
    Token* BuildDivision(char, int, int);
    Token* BuildIdentifier(char, int, int);
    Token* BuildStringLiteral(char, int, int);
    Token* BuildNumeric(char, int, int);
    // SIGN CHECKERS
    bool DoStepBack(char c){return !IsWhiteSpace(c) && c != 3;}
    bool IsWhiteSpace(char c){return (c == ' ' || c == '\t' || c == '\n');}
    bool IsDigit(char c){return IsNonZeroDigit(c) || c == '0';}
    bool IsNonZeroDigit(char c){return (c >= 49 && c <= 57 );}
    bool IsAritmeticOperator(char c){return (c == '+'|| c == '-' || c == '/' || c == '*' );}
    bool IsRelationalOperator(char c){return (c == '<' || c == '>');}
    bool IsBigLetter(char c){return (c >= 65 && c<= 90);}
    bool IsLetter(char c){return IsBigLetter(c) || IsSmallLetter(c);}
    bool IsSmallLetter(char c){return (c >= 97 && c <= 122);}
    bool IsEndOfToken(char c){return IsWhiteSpace(c) || c == NULL;}
    bool IsStringBegin(char c){return (IsLetter(c) || c == '_');}
    bool IsStringElem(char c){return IsStringBegin(c) || IsDigit(c);}
    // SETTERS
    int SetLogFile(std::ofstream*);
    int SetInputStream(std::iostream*);
    ~Lexer();
};

#endif // LEXER_H
