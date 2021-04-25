#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#include "Token.h"
#include "TokensStream.h"

#define MAX_IDENTIFIER 200
#define MAX_STRING_LITERAL 10000
#define MAX_INT 2147483647
#define FLOAT_PRECISION 7

class Lexer
{
private:
    std::istream* input_stream = NULL;
    std::ofstream* log_file = NULL;
    int lines_count = 0;
    int signs_count = 0;
    int last_signs_count = 0;
    std::string last_stream_buffor = "";
    std::string stream_buffor = "";
    char last_sign = 0;
    char present_sign = 0;
    char next_sign = 0;
    std::list<Token*> tokens;
    TokensStream* tokens_stream = NULL;
public:
    // CONSTRUCORS
    Lexer();
    Lexer(std::istream* input_stream, TokensStream* tokens_stream);
    Lexer(std::istream* input_stream, TokensStream* tokens_stream, std::ofstream* log_file);
    // GETTERS
    std::istream* GetInputStream(){return input_stream;}
    std::ofstream* GetLogFile(){return log_file;}
    int GetLinesCount(){return lines_count;}
    int GetSignsCount(){return signs_count;}
    std::string GetStreamBuffor(){return stream_buffor;}
    char GetLastSign(){return last_sign;}
    char GetPresentSign(){return present_sign;}
    char GetNextSign(){return next_sign;}
    TokensStream* GetTokenSStream(){return tokens_stream;}
    // METHODS
    void AnalizeInput();
    char GetSign();
    Token* GetNextToken();
    std::string MakeUpStreamBuffor();
    char StepBack();
    std::string ShowPresentPosition();
    template <typename T>
    T* AddNewToken(int, int);
    template <typename T, typename V>
    T* AddNewToken(V,int, int);
    // TOKEN BUILDERS
    Token* BuildParenthesisOpen(int, int);
    Token* BuildParenthesisClose(int, int);
    Token* BuildSquareBracketOpen(int, int);
    Token* BuildSquareBracketClose(int, int);
    Token* BuildBraceOpen(int, int);
    Token* BuildBraceClose(int, int);
    Token* BuildComma(int, int);
    Token* BuildDot(int, int);
    Token* BuildSemicolon(int, int);
    Token* BuildGreaterThan(int, int);
    Token* BuildLessThan(int, int);
    Token* BuildEqual(int, int);
    Token* BuildNotEqual(int, int);
    Token* BuildDoubleColon(int, int);
    Token* BuildAndOperator(int, int);
    Token* BuildOrOperator(int, int);
    Token* BuildPlus(int, int);
    Token* BuildMinus(int, int);
    Token* BuildMultiplication(int, int);
    Token* BuildDivision(int, int);
    Token* BuildIdentifier(int, int);
    Token* BuildStringLiteral(int, int);
    Token* BuildNumeric(int, int);
    Token* BuildEof(int, int);
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
    bool IsEndOfToken(char c){return IsWhiteSpace(c) || c == 0;}
    bool IsStringBegin(char c){return (IsLetter(c) || c == '_');}
    bool IsStringElem(char c){return IsStringBegin(c) || IsDigit(c);}
    // SETTERS
    void SetLogFile(std::ofstream*);
    void SetInputStream(std::istream*);
    void SetTokensStream(TokensStream*);
    // DESTRUCTOR
    ~Lexer();
};

#endif // LEXER_H
