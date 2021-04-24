#include "Lexer.h"

using namespace std;

// CONSTRUCTORS
Lexer::Lexer()
{
}

Lexer::Lexer(istream* new_inout_stream)
{
    input_stream = new_inout_stream;
}

Lexer::Lexer(istream* new_inout_stream, ofstream* new_log_file)
{
    input_stream = new_inout_stream;
    log_file = new_log_file;

    *log_file << "\nLexer starting..." << endl;
}

// METHODS
char Lexer::GetSign()
{
    if(input_stream == NULL) // if input stream is null
    {
        *log_file << "There is no input stream entered!" << endl;
        return NULL;
    }

    if(next_sign == NULL) // if there is no next sign stored in memory - there was no step back in last move
    {
        last_stream_buffor = stream_buffor;

        if(present_sign != NULL) // if there is some present sign before getting next sign from the stream
            last_sign = present_sign; // setting last sign as present sign before getting the next sign

        istream& result = input_stream->get(present_sign); // get next sign from the stream and put it to the 'result'

        if(input_stream->eof()) //  if it is the end of the stream
        {
            *log_file << "End of input stream." << endl;
            present_sign = 3;

            input_stream->clear();
        }
        else if(!input_stream->good()) // if stream isn't good - there is an error
        {
            *log_file << "Error reading input stream!" << endl;
            return NULL;
        }
    }
    else // there was a step back in last move
    {
        last_sign = present_sign; // set 'last_sign' as 'present_sign' before getting next sign from the stream
        present_sign = next_sign; // set 'present_sing' as 'next_sign' - 'present_sign' before getting step back
        next_sign = NULL; // set 'next_sign' as NULL
    }

    if(present_sign == '\n') // if received sign is end-of-line sign
    {
        last_signs_count = signs_count; // save 'signs_count' before getting new line - in if(token_value == of getting step back in next step
        signs_count = 0; // set 'signs_count' to 0 - the beginning of new line.
        lines_count++; // next line
        stream_buffor.clear();
        stream_buffor = "";
    }
    else
    {
        last_signs_count = NULL; // it want be needed
        signs_count++; // next line
    }

    if(present_sign != 3)
    {
        stream_buffor += present_sign;
        if(stream_buffor.length() >= 400)
            stream_buffor.erase(0,1);
    }

    return present_sign;
}

Token Lexer::GetNextToken()
{
    // skip whiteSpaces
    while(IsWhiteSpace(GetSign()))
        ;

    int token_line = lines_count;
    int token_sign = signs_count;

    Token *new_token;

    *new_token = BuildParenthesisOpen(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildParenthesisClose(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildSquareBracketOpen(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildSquareBracketClose(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildComma(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildDot(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildSemicolon(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildGreaterThan(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildLessThan(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildEqual(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildDoubleColon(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildNotEqual(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildAndOperator(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildOrOperator(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildPlus(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildMinus(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildMultiplication(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildDivision(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildIdentifier(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildStringLiteral(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    *new_token = BuildNumeric(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return *new_token;

    return NewToken(TokenType::Undefined, ""+present_sign, token_line, token_sign);
}

string Lexer::MakeUpStreamBuffor()
{
    char tmp;

    for(int i = 0; i <= 200; i++)
    {
        input_stream->get(tmp); // get next sign from the stream and put it to the 'result'

        if(input_stream->good()) // if stream is good - there is no error
        {
            if(tmp == '\n' || input_stream->eof())
                return stream_buffor;

            stream_buffor += tmp;

            if(stream_buffor.length() > 400)
                stream_buffor.erase(0,1);
        }
        else
            return stream_buffor;
    }

    return stream_buffor;
}

char Lexer::StepBack()
{
    if(last_sign == NULL)
    {
        *log_file << "Error: There is no last_sign stored in memory!" << endl;
        return NULL;
    }

    if(present_sign == '\n')
    {
        if(last_signs_count == NULL)
        {
            *log_file << "Error: There is no last_signs_count stored in memory!" << endl;
            return NULL;
        }

        signs_count = last_signs_count;
        last_signs_count = NULL;
        lines_count--;
    }
    else
        signs_count--;

    if(present_sign == 3)
        next_sign = NULL;
    else
        next_sign = present_sign;
    present_sign = last_sign;
    last_sign = NULL;
    return present_sign;
}

string Lexer::ShowPresentPosition()
{
    MakeUpStreamBuffor();

    string present_position = "\n";

    for(int i = 1; i < signs_count; i++)
        present_position += " ";

    present_position += "^\n";

    return "...\n" + stream_buffor + "..." + present_position;
}

// TOKEN BUILDERS
Token Lexer::BuildParenthesisOpen(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '(')
    {
        ParenthesisOpen token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }
}

Token Lexer::BuildParenthesisClose(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ')')
    {
        ParenthesisOpen token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }
}

Token Lexer::BuildSquareBracketOpen(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ']')
    {
        Dot token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return Empty();
}

Token Lexer::BuildSquareBracketClose(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ']')
    {
        Dot token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return Empty();
}

Token Lexer::BuildComma(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ',')
    {
        Dot token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return Empty();
}

Token Lexer::BuildDot(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '.')
    {
        Dot token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return Empty();
}

Token Lexer::BuildSemicolon(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ';')
    {
        Semicolon token(token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return Empty();
}

Token Lexer::BuildGreaterThan(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '>')
    {
        if(GetSign() == '=')
        {
            GreaterEqualThan token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            GreaterThan token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildLessThan(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '<')
    {
        if(GetSign() == '=')
        {
            LessEqualThan token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            LessThan token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildEqual(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '=')
    {
        if(GetSign() == '=')
        {
            Equal token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Rewriting token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildDoubleColon(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ':')
    {
        if(GetSign() == ':')
        {
            DoubleColon token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined token(":"+present_sign, token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildNotEqual(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '!')
    {
        if(GetSign() == '=')
        {
            NotEqual token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined token("!"+present_sign, token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildAndOperator(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '&')
    {
        if(GetSign() == '&')
        {
            AndOperator token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined token("&"+present_sign, token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildOrOperator(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '|')
    {
        if(GetSign() == '|')
        {
            OrOperator token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined token("|"+present_sign, token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildPlus(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '+')
    {
        if(GetSign() == '=')
        {
            PlusRewriting token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Plus token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildMinus(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '-')
    {
        if(GetSign() == '=')
        {
            MinusRewriting token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Minus token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildMultiplication(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '*')
    {
        if(GetSign() == '=')
        {
            MultRewriting token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Multiplication token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildDivision(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '/')
    {
        if(GetSign() == '=')
        {
            DivisionRewriting token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Division token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildIdentifier(char present_sign, int token_line, int token_sign)
{
    if(IsStringBegin(present_sign))
    {
        stringstream token_value;
        token_value << present_sign;

        if(present_sign == '_')
        {
            if(IsLetter(GetSign()))
                token_value << present_sign;
            else
            {
                if(IsStringElem(present_sign))
                {
                    token_value << present_sign;

                    while(IsStringElem(GetSign()))
                        token_value << present_sign;
                }

                if(!IsWhiteSpace(present_sign))
                    StepBack();

                Undefined token(token_value.str(), token_line, token_sign);
                *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
                return token;
            }
        }

        while(IsStringElem(GetSign()))
            token_value << present_sign;

        if(!IsWhiteSpace(present_sign))
            StepBack();

        if(token_value.str() == "int")
        {
            Int token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "float")
        {
            Float token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "true")
        {
            True token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "false")
        {
            False token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "NULL")
        {
            Null token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "for")
        {
            For token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "foreach")
        {
            Foreach token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "if")
        {
            If token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "else")
        {
            Else token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "collection")
        {
            Collection token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        if(token_value.str() == "return")
        {
            Return token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }

        Identifier token(token_value.str(), token_line, token_sign);
        *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
        return token;
    }

    return Empty();
}

Token Lexer::BuildStringLiteral(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '"')
    {
        stringstream token_value;
        token_value << present_sign;

        bool correct_string = true;

        while(GetSign() != '"')
        {
            if(present_sign == '\\')
            {
                GetSign();
                if(present_sign == '"')
                    token_value << '"';
                else if(present_sign == '\\')
                    token_value << '\\';
                else if(present_sign == 'n')
                    token_value << '\n';
                else if(present_sign == 't')
                    token_value << '\t';
                else
                {
                    correct_string = false;
                    StepBack();
                }
            }
            else
                token_value << present_sign;
        }

        token_value << present_sign;

        if(correct_string)
        {
            StringLiteral token(token_value.str(), token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }
        else
        {
            Undefined token(token_line, token_sign);
            *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
            return token;
        }
    }

    return Empty();
}

Token Lexer::BuildNumeric(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '0')
    {
        stringstream token_value;
        token_value << "0";

        if(GetSign() == '.')
        {
            token_value << present_sign;

            if(IsDigit(GetSign()))
                token_value << present_sign;
            else
                return NewToken(TokenType::Undefined, token_value.str(), token_line, token_sign);

            while(IsDigit(GetSign()))
                token_value << present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return NewToken(NumericType::Float, token_value.str(), token_line, token_sign);
        }
        else if(IsStringElem(present_sign))
            return NewToken(TokenType::Undefined, token_value.str(), token_line, token_sign);
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();
        return NewToken(TokenType::Int, token_value.str(), token_line, token_sign);
    }

    if(IsNonZeroDigit(present_sign))
    {
        stringstream token_value;
        token_value << present_sign;

        while(IsDigit(GetSign()))
            token_value << present_sign;

        if(present_sign == '.')
        {
            token_value << present_sign;

            if(IsDigit(GetSign()))
                token_value << present_sign;
            else
                return NewToken(TokenType::Undefined, token_value.str(), token_line, token_sign);

            while(IsDigit(GetSign()))
                token_value << present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();
            return NewToken(TokenType::Float, token_value.str(), token_line, token_sign);
        }
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();

        return NewToken(TokenType::Int, token_value.str(), token_line, token_sign);
    }

    return Empty();
}

// SETTERS
int Lexer::SetLogFile(ofstream* new_log_file)
{
    log_file = new_log_file;
    *log_file << "\nLexer starting..." << endl;
}

int Lexer::SetInputStream(iostream* new_input_stream)
{
    input_stream = new_input_stream;
}

Lexer::~Lexer()
{
    //input_stream = NULL;
    //*log_file << "Lexer closing..." << endl;
}
