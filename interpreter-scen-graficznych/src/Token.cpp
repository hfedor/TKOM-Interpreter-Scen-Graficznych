#include "Token.h"

using namespace std;

string Token::ToString()
{
    /*
    string result = "Token type:";

    if(type == TokenType::Undefined)
        result += "Undefined";
    else if(type == TokenType::StringLiteral)
        result += "String Literal";
    else if(type == TokenType::Numeric)
    {
        if(numeric_type == NumericType::Int)
            result += "int";
        else if(numeric_type == NumericType::Float)
            result += "float";
    }
    else if(type == TokenType::Identifier)
        result += "Identifier";
    else if(type == TokenType::False)
        result += "false";
    else if(type == TokenType::True)
        result += "true";
    else if(type == TokenType::Null)
        result += "NULL";
    else if(type == TokenType::ParenthesisOpen)
        result += "(";
    else if(type == TokenType::ParenthesisClose)
        result += ")";
    else if(type == TokenType::SquareBracketOpen)
        result += "[";
    else if(type == TokenType::SquareBracketClose)
        result += "]";
    else if(type == TokenType::GreaterThan)
        result += ">";
    else if(type == TokenType::LessThan)
        result += "<";
    else if(type == TokenType::Comma)
        result += ",";
    else if(type == TokenType::Dot)
        result += ".";
    else if(type == TokenType::DoubleColon)
        result += "::";
    else if(type == TokenType::Semicolon)
        result += ":";
    else if(type == TokenType::Rewriting)
        result += "=";
    else if(type == TokenType::GreaterEqualThan)
        result += ">=";
    else if(type == TokenType::LessEqualThan)
        result += "<=";
    else if(type == TokenType::Equal)
        result += "==";
    else if(type == TokenType::NotEqual)
        result += "!=";
    else if(type == TokenType::AndOperator)
        result += "&&";
    else if(type == TokenType::OrOperator)
        result += "||";
    else if(type == TokenType::Plus)
        result += "+";
    else if(type == TokenType::Minus)
        result += "-";
    else if(type == TokenType::Multiplication)
        result += "*";
    else if(type == TokenType::Division)
        result += "/";
    else if(type == TokenType::PlusRewriting)
        result += "+=";
    else if(type == TokenType::MinusRewriting)
        result += "-=";
    else if(type == TokenType::MultRewriting)
        result += "*=";
    else if(type == TokenType::DivisionRewriting)
        result += "/=";
    else if(type == TokenType::For)
        result += "for";
    else if(type == TokenType::Foreach)
        result += "foreach";
    else if(type == TokenType::If)
        result += "if";
    else if(type == TokenType::Else)
        result += "else";
    else if(type == TokenType::Collection)
        result += "collection";
    else if(type == TokenType::Return)
        result += "result +=";
    else if(type == TokenType::Eof)
        result += "EOF";
    else
        return "EMPTY_TOKEN";

    return result + ";\nToken value:\n" + value;*/
}

bool operator ==( const Token & token1, const Token & token2 )
{
    return token1.type == token2.type;
}

bool operator !=( const Token & token1, const Token & token2 )
{
    return token1.type != token2.type;
}

bool operator ==( const Token & token, const TokenType & token_type )
{
    return token.type == token_type;
}

bool operator !=( const Token & token, const TokenType & token_type )
{
    return token.type != token_type;
}

// TODO
string operator +=( std::string & str, const Token & token)
{
    return "";
}
