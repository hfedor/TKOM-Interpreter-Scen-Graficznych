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

Token* Lexer::GetNextToken()
{
    // skip whiteSpaces
    while(IsWhiteSpace(GetSign()))
        ;

    int token_line = lines_count;
    int token_sign = signs_count;

    Token *new_token;

    new_token = BuildParenthesisOpen(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildParenthesisClose(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSquareBracketOpen(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSquareBracketClose(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildComma(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDot(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildSemicolon(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildGreaterThan(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildLessThan(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildEqual(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDoubleColon(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildNotEqual(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildAndOperator(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildOrOperator(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildPlus(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildMinus(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildMultiplication(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildDivision(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildIdentifier(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildStringLiteral(present_sign, token_line, token_sign);
    if(new_token != NULL)
        return new_token;

    new_token = BuildNumeric(present_sign, token_line, token_sign);
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
Token* Lexer::BuildParenthesisOpen(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '(')
    {
        ParenthesisOpen *token = new ParenthesisOpen(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildParenthesisClose(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ')')
    {
        ParenthesisClose *token = new ParenthesisClose(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildSquareBracketOpen(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '[')
    {
        SquareBracketOpen *token = new SquareBracketOpen(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildSquareBracketClose(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ']')
    {
        SquareBracketClose *token = new SquareBracketClose(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildComma(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ',')
    {
        Comma *token = new Comma(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildDot(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '.')
    {
        Dot *token = new Dot(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildSemicolon(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ';')
    {
        Semicolon *token = new Semicolon(token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildGreaterThan(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '>')
    {
        if(GetSign() == '=')
        {
            GreaterEqualThan *token = new GreaterEqualThan(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            GreaterThan *token = new GreaterThan(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildLessThan(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '<')
    {
        if(GetSign() == '=')
        {
            LessEqualThan *token = new LessEqualThan(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            LessThan *token = new LessThan(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildEqual(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '=')
    {
        if(GetSign() == '=')
        {
            Equal *token = new Equal(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Rewriting *token = new Rewriting(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildDoubleColon(char present_sign, int token_line, int token_sign)
{
    if(present_sign == ':')
    {
        if(GetSign() == ':')
        {
            DoubleColon *token = new DoubleColon(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined *token = new Undefined(":"+present_sign, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildNotEqual(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '!')
    {
        if(GetSign() == '=')
        {
            NotEqual *token = new NotEqual(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined *token = new Undefined("!"+present_sign, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildAndOperator(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '&')
    {
        if(GetSign() == '&')
        {
            AndOperator *token = new AndOperator(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined *token = new Undefined("&"+present_sign, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildOrOperator(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '|')
    {
        if(GetSign() == '|')
        {
            OrOperator *token = new OrOperator(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Undefined *token = new Undefined("|"+present_sign, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildPlus(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '+')
    {
        if(GetSign() == '=')
        {
            PlusRewriting *token = new PlusRewriting(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Plus *token = new Plus(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildMinus(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '-')
    {
        if(GetSign() == '=')
        {
            MinusRewriting *token = new MinusRewriting(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Minus *token = new Minus(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildMultiplication(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '*')
    {
        if(GetSign() == '=')
        {
            MultRewriting *token = new MultRewriting(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Multiplication *token = new Multiplication(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildDivision(char present_sign, int token_line, int token_sign)
{
    if(present_sign == '/')
    {
        if(GetSign() == '=')
        {
            DivisionRewriting *token = new DivisionRewriting(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            if(!IsWhiteSpace(present_sign))
                StepBack();

            Division *token = new Division(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildIdentifier(char present_sign, int token_line, int token_sign)
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

                Undefined *token = new Undefined(token_value.str(), token_line, token_sign);
                tokens.push_back(token);
                *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

                return token;
            }
        }

        while(IsStringElem(GetSign()))
            token_value << present_sign;

        if(!IsWhiteSpace(present_sign))
            StepBack();

        if(token_value.str() == "int")
        {
            Int *token = new Int(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "float")
        {
            Float *token = new Float(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "true")
        {
            True *token = new True(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "false")
        {
            False *token = new False(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "NULL")
        {
            Null *token = new Null(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "for")
        {
            For *token = new For(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "foreach")
        {
            Foreach *token = new Foreach(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "if")
        {
            If *token = new If(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "else")
        {
            Else *token = new Else(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "collection")
        {
            Collection *token = new Collection(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        if(token_value.str() == "return")
        {
            Return *token = new Return(token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }

        Identifier *token = new Identifier(token_value.str(), token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
}

Token* Lexer::BuildStringLiteral(char present_sign, int token_line, int token_sign)
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
            StringLiteral *token = new StringLiteral(token_value.str(), token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
        {
            Undefined *token = new Undefined(token_value.str(), token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
    }

    return NULL;
}

Token* Lexer::BuildNumeric(char present_sign, int token_line, int token_sign)
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
                float_value += (present_sign - '0')/10;
            }
            else
            {
                Undefined *token = new Undefined(token_value.str(), token_line, token_sign);
                tokens.push_back(token);
                *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

                return token;
            }

            int i = 100;
            while(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value += (present_sign - '0')/i;

                i *= 10;
            }

            if(!IsWhiteSpace(present_sign))
                StepBack();

            FloatValue *token = new FloatValue(float_value, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else if(IsStringElem(present_sign))
        {
            Undefined *token = new Undefined(token_value.str(), token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();

        IntValue *token = new IntValue(0, token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
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
        }

        if(present_sign == '.')
        {
            float float_value = int_value;

            token_value << present_sign;

            if(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value += (present_sign - '0')/10;
            }
            else
            {
                Undefined token(token_value.str(), token_line, token_sign);
                *log_file << "Get new token:\ntype:'" << token.TypeToString() << "; value: " << token.GetValue() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;
                return &token;
            }

            int i = 100;
            while(IsDigit(GetSign()))
            {
                token_value << present_sign;
                float_value += (present_sign - '0')/i;

                i *= 10;
            }

            if(!IsWhiteSpace(present_sign))
                StepBack();

            FloatValue *token = new FloatValue(float_value, token_line, token_sign);
            tokens.push_back(token);
            *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

            return token;
        }
        else
            if(!IsWhiteSpace(present_sign))
                StepBack();

        IntValue *token = new IntValue(0, token_line, token_sign);
        tokens.push_back(token);
        *log_file << "Get new token:\ntype:'" << token->TypeToString() << "; line: " << token_line << "; sign:" << token_sign << ";" << endl;

        return token;
    }

    return NULL;
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
    for(list<Token*>::iterator i = tokens.begin(); i != tokens.end(); i++)
        delete *i;
    //input_stream = NULL;
    //*log_file << "Lexer closing..." << endl;
}
