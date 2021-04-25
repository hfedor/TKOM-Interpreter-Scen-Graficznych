#ifndef TOKENSSTREAM_H
#define TOKENSSTREAM_H

#include <iostream>
#include <fstream>

#include "Token.h"

class TokensStream
{
protected:
public:
    TokensStream();
    virtual int AddToken(Token*) = 0;
};

class TokensFileStream : public TokensStream
{
private:
    std::ofstream file;
    std::string file_name;
public:
    TokensFileStream(std::string file_name);
    int AddToken(Token*);
};

#endif // TOKENSSTREAM_H
