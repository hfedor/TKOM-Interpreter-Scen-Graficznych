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

// TODO
string operator +=( std::string & str, const Token & token)
{
    return "";
}
