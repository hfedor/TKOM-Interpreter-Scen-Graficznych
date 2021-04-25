#include "TokensStream.h"

using namespace std;

TokensStream::TokensStream()
{
    //ctor
}

TokensFileStream::TokensFileStream(string file_name):file_name(file_name)
{
    file.open(file_name, std::ofstream::out | std::ofstream::trunc);
    file.close();
}

int TokensFileStream::AddToken(Token* new_token)
{
    file.open(file_name, ios_base::app);
    file << *new_token;
    file.close();
}
