#include "LexerTest.h"

#include "ExceptionData.h"

using namespace std;

// CONSTRUCTORS
LexerTest::LexerTest(){}

LexerTest::LexerTest(ofstream* new_log_file)
{
    SetLogFile(new_log_file); // set new log file
}

LexerTest::LexerTest(iostream* new_stream)
{
    SetStream(new_stream); // set new stream
}

LexerTest::LexerTest(iostream* new_stream, ofstream* new_log_file)
{
    SetLogFile(new_log_file); // set new log file

    SetStream(new_stream); // set new stream
}

// LEXERS ATTRIBUTES TESTS
void LexerTest::TestLexersLinesCount(int expected)
{
    if(!CheckLexersLinesCount(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersLinesCount";
        exc.thrownStatement = "The lines_count error: eq ";
        exc.thrownStatement += to_string(GetLexersLinesCount());
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += to_string(expected);
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersLinesCount(int expected, string thrownStatement)
{
    if(!CheckLexersLinesCount(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersLinesCount";
        exc.thrownStatement = thrownStatement;
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersSignsCount(int expected)
{
    if(!CheckLexersSignsCount(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersSignsCount";
        exc.thrownStatement = "The signs_count error: eq ";
        exc.thrownStatement += to_string(GetLexersSignsCount());
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += to_string(expected);
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersSignsCount(int expected, string thrownStatement)
{
    if(!CheckLexersSignsCount(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersSignsCount";
        exc.thrownStatement = thrownStatement;
        throw exc;
    }
}

void LexerTest::TestLexersStreamBuffor(string expected)
{
    if(!CheckLexersStreamBuffor(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersStreamBuffor";
        exc.thrownStatement = "The stream_buffor error: eq ";
        exc.thrownStatement += GetLexersStreamBuffor();
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += expected;
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersStreamBuffor(string expected, string thrownStatement)
{
    if(!CheckLexersStreamBuffor(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersStreamBuffor";
        exc.thrownStatement = thrownStatement;
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersLastSign(char expected)
{
    if(!CheckLexersLastSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersLastSign";
        exc.thrownStatement = "The last_signs error: eq ";
        exc.thrownStatement += GetLexersLastSign();
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += expected;
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersLastSign(char expected, std::string thrownStatement)
{
    if(!CheckLexersLastSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersLastSign";
        exc.thrownStatement = thrownStatement;
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersPresentSign(char expected)
{
    if(!CheckLexersPresentSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersPresentSign";
        exc.thrownStatement = "The presunt_signs error: eq ";
        exc.thrownStatement += GetLexersLastSign();
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += expected;
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersPresentSign(char expected, std::string thrownStatement)
{
    if(!CheckLexersPresentSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersPresentSign";
        exc.thrownStatement = thrownStatement;
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersNextSign(char expected)
{
    if(!CheckLexersNextSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersNextSign";
        exc.thrownStatement = "The next_signs error: eq ";
        exc.thrownStatement += GetLexersNextSign();
        exc.thrownStatement += " when exp. ";
        exc.thrownStatement += expected;
        exc.thrownStatement += ".";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

void LexerTest::TestLexersNextSign(char expected, std::string thrownStatement)
{
    if(!CheckLexersNextSign(expected))
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "CheckLexersNextSign";
        exc.thrownStatement = thrownStatement;
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

// SETTERS
int LexerTest::SetLogFile(ofstream* new_log_file)
{
    log_file = new_log_file; // set new log file
    lexer.SetLogFile(log_file); // set new log file for the lexer
    *log_file << "Starting testing lexer..." << endl;
}

int LexerTest::SetStream(iostream* new_stream)
{
    stream = new_stream; // set new stream
    lexer.SetInputStream(stream); // set new stream for lexer
}

// TESTS
int LexerTest::TestAll()
{
    *log_file << "Start Lexer::Test all:" << endl;

    try
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";

        // Tests on program start:
        TestLexersLinesCount(0, "The lines_count isn't equal 0 on programs start.");
        TestLexersSignsCount(0, "The sings_count isn't equal 0 on programs start.");
        TestLexersLastSign(NULL, "The last_signs isn't empty on programs start.");
        TestLexersPresentSign(NULL, "The present_signs isn't empty on programs start.");
        TestLexersNextSign(NULL, "The next_signs isn't empty on programs start.");

        // GetSign tests:

        *stream << "test" << endl;

        TestGetSign('t');
        TestLexerState(0,1,NULL,'t',NULL);

        TestGetSign('e');
        TestLexerState(0,2,'t','e',NULL);

        TestStepBack('t');
        TestLexerState(0,1,NULL,'t','e');

        TestGetSign('e');
        TestLexerState(0,2,'t','e',NULL);

        TestGetSign('s');
        TestLexerState(0,3,'e','s',NULL);
        TestGetSign('t');
        TestLexerState(0,4,'s','t',NULL);

        TestGetSign('\n'); // check endl;
        TestLexerState(1,0,'t','\n',NULL);

        TestStepBack('t');
        TestLexerState(0,4,NULL,'t','\n');

        TestGetSign('\n'); // check endl;
        TestLexerState(1,0,'t','\n',NULL);

        // GetNextToken tests:
        *stream << '(';
        TestGetNextToken(ParenthesisOpen());
        TestLexerState(1,1,'\n','(',NULL);

        *stream << ')';
        TestGetNextToken(ParenthesisClose());
        TestLexerState(1,2,'(',')',NULL);

        *stream << '[';
        TestGetNextToken(SquareBracketOpen());
        TestLexerState(1,3,')','[',NULL);

        *stream << ']';
        TestGetNextToken(SquareBracketClose());
        TestLexerState(1,4,'[',']',NULL);

        *stream << ',';
        TestGetNextToken(Comma());
        TestLexerState(1,5,']',',',NULL);

        *stream << '.';
        TestGetNextToken(Dot());
        TestLexerState(1,6,',','.',NULL);

/*
        *stream << ';';
        TestGetNextToken(TokenType::Semicolon);
        TestLexerState(1,7,'.',';',NULL);

        *stream << '>';
        TestGetNextToken(RelationType::GreaterThan);
        TestLexerState(1,8,NULL,'>',NULL);

        *stream << ">=";
        TestGetNextToken(RelationType::GreaterEqualThan);
        TestLexerState(1,10,'>','=',NULL);

        *stream << '<';
        TestGetNextToken(RelationType::LessThan);
        TestLexerState(1,11,NULL,'<',NULL);

        *stream << "<=";
        TestGetNextToken(RelationType::LessEqualThan);
        TestLexerState(1,13,'<','=',NULL);

        *stream << "= ";
        TestGetNextToken(RelationType::Rewriting);
        TestLexerState(1,15,'=',' ',NULL);

        *stream << "==";
        TestGetNextToken(RelationType::Equal);
        TestLexerState(1,17,'=','=',NULL);

        *stream << ':';
        TestGetNextToken(TokenType::Undefined, ":");
        TestLexerState(1,18,NULL,':',NULL);

        *stream << "::";
        TestGetNextToken(TokenType::DoubleColon);
        TestLexerState(1,20,':',':',NULL);

        *stream << '!';
        TestGetNextToken(TokenType::Undefined, "!");
        TestLexerState(1,21,NULL,'!',NULL);

        *stream << "!=";
        TestGetNextToken(RelationType::NotEqual);
        TestLexerState(1,23,'!','=',NULL);

        *stream << '&';
        TestGetNextToken(TokenType::Undefined, "&");
        TestLexerState(1,24,NULL,'&',NULL);

        *stream << "&&";
        TestGetNextToken(OperatorType::AndOperator);
        TestLexerState(1,26,'&','&',NULL);

        *stream << '|';
        TestGetNextToken(TokenType::Undefined, "|");
        TestLexerState(1,27,NULL,'|',NULL);

        *stream << "||";
        TestGetNextToken(OperatorType::OrOperator);
        TestLexerState(1,29,'|','|',NULL);

        *stream << '+';
        TestGetNextToken(PlusMinusType::Plus);
        TestLexerState(1,30,NULL,'+',NULL);

        *stream << "+=";
        TestGetNextToken(AritmeticRewritingType::PlusRewriting);
        TestLexerState(1,32,'+','=',NULL);

        *stream << '-';
        TestGetNextToken(PlusMinusType::Minus);
        TestLexerState(1,33,NULL,'-',NULL);

        *stream << "-=";
        TestGetNextToken(AritmeticRewritingType::MinusRewriting);
        TestLexerState(1,35,'-','=',NULL);

        *stream << '*';
        TestGetNextToken(MultDivType::Multiplication);
        TestLexerState(1,36,NULL,'*',NULL);

        *stream << "*=";
        TestGetNextToken(AritmeticRewritingType::MultRewriting);
        TestLexerState(1,38,'*','=',NULL);

        *stream << '/';
        TestGetNextToken(MultDivType::Division);
        TestLexerState(1,39,NULL,'/',NULL);

        *stream << "/=";
        TestGetNextToken(AritmeticRewritingType::DivisionRewriting);
        TestLexerState(1,41,'/','=',NULL);

        *stream << "int";
        TestGetNextToken(DataType::Int);
        TestLexerState(1,44,NULL,'t',NULL);

        *stream << "float";
        TestGetNextToken(DataType::Float);
        TestLexerState(1,49,NULL,'t',NULL);

        *stream << "true";
        TestGetNextToken(BooleanType::True);
        TestLexerState(1,53,NULL,'e',NULL);

        *stream << "false";
        TestGetNextToken(BooleanType::False);
        TestLexerState(1,58,NULL,'e',NULL);

        *stream << "NULL";
        TestGetNextToken(TokenType::Null);
        TestLexerState(1,62,NULL,'L',NULL);

        *stream << "for";
        TestGetNextToken(TokenType::For);
        TestLexerState(1,65,NULL,'r',NULL);

        *stream << "foreach";
        TestGetNextToken(TokenType::Foreach);
        TestLexerState(1,72,NULL,'h',NULL);

        *stream << "if";
        TestGetNextToken(TokenType::If);
        TestLexerState(1,74,NULL,'f',NULL);

        *stream << "else";
        TestGetNextToken(TokenType::Else);
        TestLexerState(1,78,NULL,'e',NULL);

        *stream << "collection";
        TestGetNextToken(TokenType::Collection);
        TestLexerState(1,88,NULL,'n',NULL);

        *stream << "return";
        TestGetNextToken(TokenType::Return);
        TestLexerState(1,94,NULL,'n',NULL);

        *stream << "identifier";
        TestGetNextToken(TokenType::Identifier, "identifier");
        TestLexerState(1,104,NULL,'r',NULL);

        *stream << "identifier1";
        TestGetNextToken(TokenType::Identifier, "identifier1");
        TestLexerState(1,115,NULL,'1',NULL);

        *stream << "identifier_test";
        TestGetNextToken(TokenType::Identifier, "identifier_test");
        TestLexerState(1,130,NULL,'t',NULL);

        *stream << "IdentifierTest";
        TestGetNextToken(TokenType::Identifier, "IdentifierTest");
        TestLexerState(1,144,NULL,'t',NULL);

        *stream << "_IdentifierTest";
        TestGetNextToken(TokenType::Identifier, "_IdentifierTest");
        TestLexerState(1,159,NULL,'t',NULL);

        *stream << "_";
        TestGetNextToken(TokenType::Undefined, "_");
        TestLexerState(1,160,NULL,'_',NULL);

        *stream << "_1234";
        TestGetNextToken(TokenType::Undefined, "_1234");
        TestLexerState(1,165,NULL,'4',NULL);

        *stream << "__identifier";
        TestGetNextToken(TokenType::Undefined, "__identifier");
        TestLexerState(1,177,NULL,'r',NULL);

        *stream << "\"StringLiteral test\"";
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral test\"");
        TestLexerState(1,197,'t','\"',NULL);

        *stream << "\"StringLiteral\ntest\"" << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral\ntest\"");
        TestLexerState(2,5,'t','\"',NULL);

        *stream << "\"StringLiteral\ttest\"" << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral\ttest\"");
        TestLexerState(3,20,'t','\"',NULL);

        *stream << string("\"StringLiteral\\ntest\"") << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral\ntest\"");
        TestLexerState(4,21,'t','\"',NULL);

        *stream << string("\"StringLiteral\\ttest\"") << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral\ttest\"");
        TestLexerState(5,21,'t','\"',NULL);

        *stream << string("\"StringLiteral\\\\test\"") << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"StringLiteral\\test\"");
        TestLexerState(6,21,'t','\"',NULL);

        *stream << string("\"\\\"StringLiteral test\\\"\"") << endl;
        TestGetNextToken(TokenType::StringLiteral, "\"\"StringLiteral test\"\"");
        TestLexerState(7,24,'\"','\"',NULL);

        *stream << '0' << endl;
        TestGetNextToken(NumericType::IntValue, 0);
        TestLexerState(9,0,'0','\n',NULL);

        *stream << '1' << endl;
        TestGetNextToken(NumericType::IntValue, 1);
        TestLexerState(10,0,'1','\n',NULL);

        *stream << '9' << endl;
        TestGetNextToken(NumericType::IntValue, 9);
        TestLexerState(11,0,'9','\n',NULL);

        *stream << "123" << endl;
        TestGetNextToken(NumericType::IntValue, 123);
        TestLexerState(12,0,'3','\n',NULL);

        *stream << "0.1" << endl;
        TestGetNextToken(NumericType::FloatValue, (float)0.1);
        TestLexerState(13,0,'1','\n',NULL);

        *stream << "0.123456789" << endl;
        TestGetNextToken(NumericType::FloatValue, (float)0.123456789);
        TestLexerState(14,0,'9','\n',NULL);

        *stream << "123.123" << endl;
        TestGetNextToken(NumericType::FloatValue, (float)123.123);
        TestLexerState(15,0,'3','\n',NULL);
*/
        *log_file << "All tests passed." << endl;
        cout << "All Lexer's tests passed." << endl;

    }
    catch(exceptionData exc)
    {
        *log_file << exc << endl;
        cerr << exc << endl;
        *log_file << "End Lexer::Test all. -- FAILED" << endl;
        return 0;
    }

    *log_file << "End Lexer::Test all." << endl;
}

template <typename T>
void LexerTest::TestGetNextToken(T expected)
{
    T *result;
    result = dynamic_cast<T*>(lexer.GetNextToken());

    if(*result != expected)
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "TestGetNextToken";
        exc.thrownStatement = "The TestGetNextToken error: eq. \n";
        exc.thrownStatement += result->TypeToString();
        exc.thrownStatement += "\n when exp. \n";
        exc.thrownStatement += expected.TypeToString();
        exc.thrownStatement += "\nin line:";
        exc.thrownStatement += GetLexersLinesCount();
        exc.thrownStatement += " sign:";
        exc.thrownStatement += GetLexersSignsCount();
        exc.thrownStatement += ".\n";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

template <typename T, typename v>
T LexerTest::TestGetNextToken(const T& expected, const v& exp_value)
{
    T result = lexer.GetNextToken();

    if(result != expected || result.GetValue != exp_value)
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "TestGetNextToken";
        exc.thrownStatement = "The TestGetNextToken error: eq. \n";
        exc.thrownStatement += result.ToString();
        exc.thrownStatement += "\n when exp. \n";
        exc.thrownStatement += expected.ToString();
        exc.thrownStatement += "\nin line:";
        exc.thrownStatement += GetLexersLinesCount();
        exc.thrownStatement += " sign:";
        exc.thrownStatement += GetLexersSignsCount();
        exc.thrownStatement += ".\n";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

int LexerTest::TestGetSign(char expected)
{
    char result = lexer.GetSign();

    if(result != expected)
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "TestGetSign";
        exc.thrownStatement = "The TestGetSign error: eq. '";
        exc.thrownStatement += result;
        exc.thrownStatement += "' when exp. '";
        exc.thrownStatement += expected;
        exc.thrownStatement += "' in line:";
        exc.thrownStatement += GetLexersLinesCount();
        exc.thrownStatement += " sign:";
        exc.thrownStatement += GetLexersSignsCount();
        exc.thrownStatement += ".\n";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}

int LexerTest::TestStepBack(char expected)
{
    char result = lexer.StepBack();

    if(result != expected)
    {
        exceptionData exc;
        exc.thrownClass = "Lexer";
        exc.thrownFunction = "TestStepBack";
        exc.thrownStatement = "The TestStepBack error: eq. '";
        exc.thrownStatement += result;
        exc.thrownStatement += "' when exp. '";
        exc.thrownStatement += expected;
        exc.thrownStatement += "' In line:";
        exc.thrownStatement += GetLexersLinesCount();
        exc.thrownStatement += " sign:";
        exc.thrownStatement += GetLexersSignsCount();
        exc.thrownStatement += ".\n";
        exc.thrownStatement += lexer.ShowPresentPosition();
        throw exc;
    }
}


void LexerTest::TestLexerState(int exp_line, int exp_sign, char exp_last_sign, char exp_present_sign, char exp_next_sign)
{
        TestLexersLinesCount(exp_line);
        TestLexersSignsCount(exp_sign);
        TestLexersLastSign(exp_last_sign);
        TestLexersPresentSign(exp_present_sign);
        TestLexersNextSign(exp_next_sign);
}
