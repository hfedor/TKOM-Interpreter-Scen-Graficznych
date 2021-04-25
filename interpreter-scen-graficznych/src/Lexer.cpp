#include "Lexer.h"

#include "ExceptionData.h"

using namespace std;

// CONSTRUCTORS
Lexer::Lexer()
{
}

Lexer::Lexer(istream* input_stream, TokensStream* tokens_stream)
    : input_stream(input_stream), tokens_stream(tokens_stream){}

Lexer::Lexer(istream* input_stream, TokensStream* tokens_stream, ofstream* log_file)
    : input_stream(input_stream), tokens_stream(tokens_stream), log_file(log_file)
{
    *log_file << "\nLexer starting..." << endl;
}

// METHODS
void Lexer::AnalizeInput()
{
    while(*GetNextToken() != Eof())
        ;
}

char Lexer::GetSign()
{
    if(input_stream == NULL) // if input stream is null
    {
        *log_file << "There is no input stream entered!" << endl;
        return 0;
    }

    if(next_sign == 0) // if there is no next sign stored in memory - there was no step back in last move
    {
        last_stream_buffor = stream_buffor;

        if(present_sign != 0) // if there is some present sign before getting next sign from the stream
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
            return 0;
        }
    }
    else // there was a step back in last move
    {
        last_sign = present_sign; // set 'last_sign' as 'present_sign' before getting next sign from the stream
        present_sign = next_sign; // set 'present_sing' as 'next_sign' - 'present_sign' before getting step back
        next_sign = 0; // set 'next_sign' as NULL
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
        last_signs_count = 0; // it want be needed
        if(last_sign != 3)
            signs_count++; // next sign
    }

    if(present_sign != 3)
    {
        stream_buffor += present_sign;
        if(stream_buffor.length() >= 400)
            stream_buffor.erase(0,1);
    }

    return present_sign;
}

Token* Lexer::GetNextToken()
{
    // skip whiteSpaces
    while(IsWhiteSpace(GetSign()))
        ;

    int token_line = lines_count;
    int token_sign = signs_count;

    Token *new_token;

    new_token = BuildParenthesisOpen(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildParenthesisClose(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSquareBracketOpen(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSquareBracketClose(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildBraceOpen(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildBraceClose(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildComma(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDot(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSemicolon(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildGreaterThan(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildLessThan(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildEqual(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDoubleColon(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildNotEqual(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildAndOperator(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildOrOperator(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildPlus(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildMinus(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildMultiplication(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDivision(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildIdentifier(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildStringLiteral(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildNumeric(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildEof(token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    *new_token = Undefined(""+present_sign, token_line, token_sign);
    return new_token;
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
    if(last_sign == 0)
    {
        *log_file << "Error: There is no last_sign stored in memory!" << endl;
        return 0;
    }

    if(present_sign == '\n')
    {
        if(last_signs_count == 0)
        {
            *log_file << "Error: There is no last_signs_count stored in memory!" << endl;
            return 0;
        }

        signs_count = last_signs_count;
        last_signs_count = 0;
        lines_count--;
    }
    else
        signs_count--;

    if(present_sign == 3)
        next_sign = 0;
    else
        next_sign = present_sign;
    present_sign = last_sign;
    last_sign = 0;
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

template <typename T>
T* Lexer::AddNewToken(int token_line, int token_sign)
{
        T *token = new T(token_line, token_sign);
        tokens_stream->AddToken(token);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
}

template <typename T, typename V>
T* Lexer::AddNewToken(V value ,int token_line, int token_sign)
{
        T *token = new T(value, token_line, token_sign);
        tokens_stream->AddToken(token);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
}

// TOKEN BUILDERS
Token* Lexer::BuildParenthesisOpen(int token_line, int token_sign)
{
    if(present_sign == '(')
        return AddNewToken<ParenthesisOpen>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildParenthesisClose(int token_line, int token_sign)
{
    if(present_sign == ')')
        return AddNewToken<ParenthesisClose>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildSquareBracketOpen( int token_line, int token_sign)
{
    if(present_sign == '[')
        return AddNewToken<SquareBracketOpen>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildSquareBracketClose( int token_line, int token_sign)
{
    if(present_sign == ']')
        return AddNewToken<SquareBracketClose>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildBraceOpen( int token_line, int token_sign)
{
    if(present_sign == '{')
        return AddNewToken<BraceOpen>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildBraceClose( int token_line, int token_sign)
{
    if(present_sign == '}')
        return AddNewToken<BraceClose>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildComma( int token_line, int token_sign)
{
    if(present_sign == ',')
        return AddNewToken<Comma>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildDot( int token_line, int token_sign)
{
    if(present_sign == '.')
        return AddNewToken<Dot>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildSemicolon( int token_line, int token_sign)
{
    if(present_sign == ';')
        return AddNewToken<Semicolon>(token_line,token_sign);

    return NULL;
}

Token* Lexer::BuildGreaterThan( int token_line, int token_sign)
{
    if(present_sign == '>')
    {
        if(GetSign() == '=')
            return AddNewToken<GreaterEqualThan>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<GreaterThan>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildLessThan( int token_line, int token_sign)
{
    if(present_sign == '<')
    {
        if(GetSign() == '=')
            return AddNewToken<LessEqualThan>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<LessThan>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildEqual(int token_line, int token_sign)
{
    if(present_sign == '=')
    {
        if(GetSign() == '=')
            return AddNewToken<Equal>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Rewriting>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildDoubleColon( int token_line, int token_sign)
{
    if(present_sign == ':')
    {
        if(GetSign() == ':')
            return AddNewToken<DoubleColon>(token_line,token_sign);
        else
        {
            string token_value = ":";
            if(!IsWhiteSpace(present_sign) && present_sign != 3)
                token_value += present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Undefined>(token_value,token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildNotEqual( int token_line, int token_sign)
{
    if(present_sign == '!')
    {
        if(GetSign() == '=')
            return AddNewToken<NotEqual>(token_line,token_sign);
        else
        {
            string token_value = "!";
            if(!IsWhiteSpace(present_sign) && present_sign != 3)
                token_value += present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Undefined>(token_value,token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildAndOperator( int token_line, int token_sign)
{
    if(present_sign == '&')
    {
        if(GetSign() == '&')
            return AddNewToken<AndOperator>(token_line,token_sign);
        else
        {
            string token_value = "&";
            if(!IsWhiteSpace(present_sign) && present_sign != 3)
                token_value += present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Undefined>(token_value,token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildOrOperator( int token_line, int token_sign)
{
    if(present_sign == '|')
    {
        if(GetSign() == '|')
            return AddNewToken<OrOperator>(token_line,token_sign);
        else
        {
            string token_value = "|";
            if(!IsWhiteSpace(present_sign) && present_sign != 3)
                token_value += present_sign;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Undefined>(token_value,token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildPlus( int token_line, int token_sign)
{
    if(present_sign == '+')
    {
        if(GetSign() == '=')
            return AddNewToken<PlusRewriting>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Plus>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildMinus( int token_line, int token_sign)
{
    if(present_sign == '-')
    {
        if(GetSign() == '=')
            return AddNewToken<MinusRewriting>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Minus>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildMultiplication( int token_line, int token_sign)
{
    if(present_sign == '*')
    {
        if(GetSign() == '=')
            return AddNewToken<MultRewriting>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Multiplication>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildDivision( int token_line, int token_sign)
{
    if(present_sign == '/')
    {
        if(GetSign() == '=')
            return AddNewToken<DivisionRewriting>(token_line,token_sign);
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<Division>(token_line,token_sign);
        }
    }

    return NULL;
}

Token* Lexer::BuildIdentifier( int token_line, int token_sign)
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

                    for(int i = 0; i < MAX_IDENTIFIER - 1; i++)
                    {
                        if(IsStringElem(GetSign()))
                            token_value << present_sign;
                        else
                            break;

                        if(i == MAX_IDENTIFIER - 2)
                        {
                            exceptionData exc;
                            exc.thrownClass = "Lexer";
                            exc.thrownFunction = "BuildIdentifier";
                            exc.thrownStatement = "Too long identifier:";
                            exc.thrownStatement += token_value.str();
                            throw exc;
                        }
                    }
                }

                if(!IsWhiteSpace(present_sign))
                    StepBack();

                return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
            }
        }

        for(int i = 0; i < MAX_IDENTIFIER - 1; i++)
        {
            if(IsStringElem(GetSign()))
                token_value << present_sign;
            else
                break;

            if(i == MAX_IDENTIFIER - 2)
            {
                exceptionData exc;
                exc.thrownClass = "Lexer";
                exc.thrownFunction = "BuildIdentifier";
                exc.thrownStatement = "Too long identifier:";
                exc.thrownStatement += token_value.str();
                throw exc;
            }
        }

        if(!IsWhiteSpace(present_sign))
            StepBack();

        if(token_value.str() == "int")
            return AddNewToken<Int>(token_line,token_sign);

        if(token_value.str() == "float")
            return AddNewToken<Float>(token_line,token_sign);

        if(token_value.str() == "true")
            return AddNewToken<True>(token_line,token_sign);

        if(token_value.str() == "false")
            return AddNewToken<False>(token_line,token_sign);

        if(token_value.str() == "NULL")
            return AddNewToken<Null>(token_line,token_sign);

        if(token_value.str() == "for")
            return AddNewToken<For>(token_line,token_sign);

        if(token_value.str() == "foreach")
            return AddNewToken<Foreach>(token_line,token_sign);

        if(token_value.str() == "if")
            return AddNewToken<If>(token_line,token_sign);

        if(token_value.str() == "else")
            return AddNewToken<Else>(token_line,token_sign);

        if(token_value.str() == "collection")
            return AddNewToken<Collection>(token_line,token_sign);

        if(token_value.str() == "return")
            return AddNewToken<Return>(token_line,token_sign);

        return AddNewToken<Identifier>(token_value.str(),token_line,token_sign);
    }

    return NULL;
}

Token* Lexer::BuildStringLiteral( int token_line, int token_sign)
{
    if(present_sign == '"')
    {
        stringstream token_value;
        token_value << present_sign;

        bool correct_string = true;

        for(int i = 0; i < MAX_STRING_LITERAL - 1; i++)
        {
            if(GetSign() != '"')
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
            else
                break;

            if(i == MAX_STRING_LITERAL - 2)
            {
                exceptionData exc;
                exc.thrownClass = "Lexer";
                exc.thrownFunction = "BuildIdentifier";
                exc.thrownStatement = "Too long identifier:";
                exc.thrownStatement += token_value.str();
                throw exc;
            }
        }

        token_value << present_sign;

        if(correct_string)
            return AddNewToken<StringLiteral>(token_value.str(),token_line,token_sign);
        else
            return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
    }

    return NULL;
}

Token* Lexer::BuildNumeric( int token_line, int token_sign)
{
    if(present_sign == '0')
    {
        stringstream token_value;
        token_value << "0";

        if(GetSign() == '.')
        {
            float float_value = 0;
            token_value << present_sign;

            if(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value += (float)(present_sign - '0')/10;
            }
            else
                return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);

            int i = 100;
            int j = 2;
            while(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value += (float)(present_sign - '0')/i;

                i *= 10;
                j++;
                if(j >= FLOAT_PRECISION)
                    return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
            }

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<FloatValue>(float_value,token_line,token_sign);
        }
        else if(IsStringElem(present_sign))
            return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();

        return AddNewToken<IntValue>(0,token_line,token_sign);
    }

    if(IsNonZeroDigit(present_sign))
    {
        stringstream token_value;
        token_value << present_sign;
        int int_value = present_sign - '0';

        while(IsDigit(GetSign()))
        {
            token_value << present_sign;

            int_value *= 10;
            int_value += present_sign - '0';

            if(int_value > MAX_INT)
                return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
        }

        if(present_sign == '.')
        {
            float float_value = int_value;

            token_value << present_sign;

            if(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value *= 10;
                float_value += present_sign - '0';
            }
            else
                return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);

            int i = 10;
            int j = 2;
            while(IsDigit(GetSign()))
            {
                i *= 10;
                token_value << present_sign;
                float_value *= 10;
                float_value += present_sign - '0';
                j++;
                if(j >= FLOAT_PRECISION)
                    return AddNewToken<Undefined>(token_value.str(),token_line,token_sign);
            }
            float_value /= i;

            if(!IsWhiteSpace(present_sign))
                StepBack();

            return AddNewToken<FloatValue>(float_value,token_line,token_sign);
        }
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();

        return AddNewToken<IntValue>(int_value,token_line,token_sign);
    }

    return NULL;
}

Token* Lexer::BuildEof( int token_line, int token_sign)
{
    if(present_sign == 3)
        return AddNewToken<Eof>(token_line,token_sign);

    return NULL;
}

// SETTERS
void Lexer::SetLogFile(ofstream* new_log_file)
{
    log_file = new_log_file;
    *log_file << "\nLexer starting..." << endl;
}

void Lexer::SetInputStream(istream* new_input_stream)
{
    input_stream = new_input_stream;
}

void Lexer::SetTokensStream(TokensStream* new_tokens_stream)
{
    tokens_stream = new_tokens_stream;
}

Lexer::~Lexer()
{
    for(list<Token*>::iterator i = tokens.begin(); i != tokens.end(); i++)
        delete *i;
    //input_stream = NULL;
    //*log_file << "Lexer closing..." << endl;
}
