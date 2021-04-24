#include "Token.h"

using namespace std;

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
