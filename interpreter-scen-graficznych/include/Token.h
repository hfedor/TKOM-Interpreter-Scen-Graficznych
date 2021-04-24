#ifndef TOKEN_H
#define TOKEN_H

#pragma once

#include <iostream>

enum class TokenType
{
    Undefined,

    StringLiteral,          // tekst w ""

    Numeric,

    //Int,                    // int
    //Float,                  // float

    Identifier,             // nazwy funkcji, argumenty funkcji, właœciwoœci obiektów

    Boolean,
    //False,                  // false
    //True,                   // true

    Null,                   // null

    Parenthesis,
    //ParenthesisOpen,        // (
    //ParenthesisClose,       // )

    SquareBracket,
    //SquareBracketOpen,      // [
    //SquareBracketClose,     // ]

    Rewriting,              // =

    Relation,
    //GreaterThan,            // >
    //LessThan,               // <
    //GreaterEqualThan,       // >=
    //LessEqualThan,          // <=
    //Equal,                  // ==
    //NotEqual,               // !=

    Comma,                  // ,
    Dot,                    // .
    DoubleColon,            // ::
    Semicolon,              // ;

    Operator,
    //AndOperator,            // &&
    //OrOperator,             // ||

    Aritmetic,
    //Plus,                   // +
    //Minus,                  // -
    //Multiplication,         // *
    //Division,                // /

    AritmeticRewriting,
    //PlusRewriting,          // +=
    //MinusRewriting,         // -=
    //MultRewriting,          // *=
    //DivisionRewriting,       // /=

    Data,                    // typy danych

    For,                    // for
    Foreach,                // foteach
    If,                     // if
    Else,                   // else
    Collection,             // collection
    Return,                 // Return

    Eof,                    // znak koñca pliku

    Empty,                  // jeszcze nie zdefiniowany
};

enum class NumericType
{
    IntValue,                    // int
    FloatValue,                  // float
};

enum class BooleanType
{
    False,                  // false
    True,                   // true
};

enum class ParenthesisType
{
    ParenthesisOpen,        // (
    ParenthesisClose,       // )
};

enum class SquareBracketType
{
    SquareBracketOpen,      // [
    SquareBracketClose,     // ]
};

enum class RelationType
{
    GreaterThan,            // >
    LessThan,               // <
    Rewriting,              // =
    GreaterEqualThan,       // >=
    LessEqualThan,          // <=
    Equal,                  // ==
    NotEqual,               // !=
};

enum class OperatorType
{
    AndOperator,            // &&
    OrOperator,             // ||
};

enum class AritmeticType
{
    PlusMinus,
    MultDiv,
};

enum class PlusMinusType
{
    Plus,                   // +
    Minus,                  // -
};

enum class MultDivType
{
    Multiplication,         // *
    Division,                // /
};

enum class AritmeticRewritingType
{
    PlusRewriting,          // +=
    MinusRewriting,         // -=
    MultRewriting,          // *=
    DivisionRewriting,       // /=
};

enum class DataType
{
    Int,            // int
    Float,          // float
};

class Token
{
protected:
    TokenType type;         // typ tokena
    int line = 0;
    int sign = 0;
public:
    Token(TokenType type):type(type){}
    Token(TokenType type, int line, int sign):type(type),line(line),sign(sign){}
    TokenType GetType() { return type; }
    int GetLine() { return line; }
    int GetSign() { return sign; }
    void SetType(TokenType newType) { type = newType; }
    void SetLine(int new_line) { line = new_line; }
    void SetSign(int new_sign) { sign = new_sign; }
    virtual const std::string TypeToString() = 0;
    friend bool operator ==( const Token &, const Token & );
    friend bool operator !=( const Token &, const Token & );
    friend bool operator ==( const Token &, const TokenType & );
    friend bool operator !=( const Token &, const TokenType & );
    friend std::string operator +=( std::string &, const Token & );
    friend std::string operator +=( std::string &, const TokenType & );
    friend std::string operator +( std::string &, const Token & );
    friend const char* operator +( const char[], const Token & );
};

class Numeric : public Token
{
public:
    Numeric():Token(TokenType::Numeric){}
    Numeric(int line, int sign):Token(TokenType::Numeric,line, sign){}
};

class IntValue : public Numeric
{
private:
    NumericType type = NumericType::IntValue;
    int value;
public:
    IntValue(int value):value(value){}
    IntValue(int value, int line, int sign):value(value),Numeric(line,sign){}
    int GetValue(){return value;}
    const std::string TypeToString(){return "Numeric::IntValue";}
};

class FloatValue : public Numeric
{
private:
    NumericType numeric_type = NumericType::FloatValue;
    float value;
public:
    FloatValue(float value):value(value){}
    FloatValue(float value, int line, int sign):value(value),Numeric(line,sign){}
    float GetValue(){return value;}
    const std::string TypeToString(){return "Numeric::FloatValue";}
};

class StringLiteral : public Token  // tekst w ""
{
    std::string value;
public:
    StringLiteral(std::string value):value(value),Token(TokenType::StringLiteral){}
    StringLiteral(std::string value, int line, int sign):value(value),Token(TokenType::StringLiteral,line,sign){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "StringLiteral";}
};

class Identifier : public Token  // nazwy funkcji, argumenty funkcji, właœciwoœci obiektów
{
    std::string value;
public:
    Identifier(std::string value):value(value),Token(TokenType::Identifier){}
    Identifier(std::string value, int line, int sign):value(value),Token(TokenType::Identifier,line,sign){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "Identifier";}
};

class Boolean : public Token
{
protected:
    BooleanType boolean_type;
    bool value;
public:
    Boolean():Token(TokenType::Boolean){}
    Boolean(int line, int sign):Token(TokenType::Boolean,line,sign){}
    bool GetValue(){return value;}
    const std::string TypeToString(){return "Boolean";}
};

class False : public Boolean  // false
{
    BooleanType boolean_type = BooleanType::False;
    bool value = false;
public:
    False(){}
    False(int line, int sign):Boolean(line,sign){}
    bool GetValue(){return value;}
    const std::string TypeToString(){return "Boolean::False";}
};

class True : public Boolean  // true
{
    BooleanType boolean_type = BooleanType::True;
    bool value = true;
public:
    True(){}
    True(int line, int sign):Boolean(line,sign){}
    bool GetValue(){return value;}
    const std::string TypeToString(){return "Boolean::True";}
};

class Null : public Token  // null
{
public:
    Null():Token(TokenType::Null){}
    Null(int line, int sign):Token(TokenType::Null,line,sign){}
    const std::string TypeToString(){return "Null";}
};

class Parenthesis : public Token
{
protected:
    ParenthesisType parenthesis_type;
public:
    Parenthesis(ParenthesisType parenthesis_type):parenthesis_type(parenthesis_type),Token(TokenType::Parenthesis){}
    Parenthesis(ParenthesisType parenthesis_type, int line, int sign):parenthesis_type(parenthesis_type),Token(TokenType::Parenthesis,line,sign){}
    friend bool operator ==( const Parenthesis& p1, const Parenthesis& p2 ){return p1.parenthesis_type == p2.parenthesis_type ? true : false;}
    friend bool operator !=( const Parenthesis& p1, const Parenthesis& p2 ){return p1.parenthesis_type != p2.parenthesis_type ? true : false;}
};

class ParenthesisOpen : public Parenthesis   // (
{
public:
    ParenthesisOpen():Parenthesis(ParenthesisType::ParenthesisOpen){}
    ParenthesisOpen(int line, int sign):Parenthesis(ParenthesisType::ParenthesisOpen,line,sign){}
    const std::string TypeToString(){return "Parenthesis::ParenthesisOpen";}
};

class ParenthesisClose : public Parenthesis  // )
{
public:
    ParenthesisClose():Parenthesis(ParenthesisType::ParenthesisClose){}
    ParenthesisClose(int line, int sign):Parenthesis(ParenthesisType::ParenthesisClose,line,sign){}
    const std::string TypeToString(){return "Parenthesis::ParenthesisClose";}
};

class SquareBracket : public Token
{
    SquareBracketType square_bracket_type;
public:
    SquareBracket(SquareBracketType square_bracket_type):square_bracket_type(square_bracket_type),Token(TokenType::SquareBracket){}
    SquareBracket(SquareBracketType square_bracket_type, int line, int sign):square_bracket_type(square_bracket_type),Token(TokenType::SquareBracket,line,sign){}
    friend bool operator ==( const SquareBracket& p1, const SquareBracket& p2 ){return p1.square_bracket_type == p2.square_bracket_type ? true : false;}
    friend bool operator !=( const SquareBracket& p1, const SquareBracket& p2 ){return p1.square_bracket_type != p2.square_bracket_type ? true : false;}
};

class SquareBracketOpen : public SquareBracket  // [
{
public:
    SquareBracketOpen():SquareBracket(SquareBracketType::SquareBracketOpen){}
    SquareBracketOpen(int line, int sign):SquareBracket(SquareBracketType::SquareBracketOpen,line,sign){}
    const std::string TypeToString(){return "SquareBracket::SquareBracketOpen";}
};

class SquareBracketClose : public SquareBracket  // ]
{
    SquareBracketType square_bracket_type = SquareBracketType::SquareBracketClose;
public:
    SquareBracketClose():SquareBracket(SquareBracketType::SquareBracketClose){}
    SquareBracketClose(int line, int sign):SquareBracket(SquareBracketType::SquareBracketClose,line,sign){}
    const std::string TypeToString(){return "SquareBracket::SquareBracketClose";}
};

class Relation : public Token
{
public:
    Relation():Token(TokenType::Relation){}
    Relation(int line, int sign):Token(TokenType::Relation,line,sign){}
};

class GreaterThan : public Relation  // >
{
    RelationType relation_type = RelationType::GreaterThan;
public:
    GreaterThan(){}
    GreaterThan(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::GreaterThan";}
};

class LessThan : public Relation  // <
{
    RelationType relation_type = RelationType::LessThan;
public:
    LessThan(){}
    LessThan(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::LessThan";}
};

class GreaterEqualThan : public Relation  // >=
{
    RelationType relation_type = RelationType::GreaterEqualThan;
public:
    GreaterEqualThan(){}
    GreaterEqualThan(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::GreaterEqualThan";}
};

class LessEqualThan : public Relation  // <=
{
    RelationType relation_type = RelationType::LessEqualThan;
public:
    LessEqualThan(){}
    LessEqualThan(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::LessEqualThan";}
};

class Equal : public Relation  // ==
{
    RelationType relation_type = RelationType::Equal;
public:
    Equal(){}
    Equal(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::Equal";}
};

class NotEqual : public Relation  // !=
{
    RelationType relation_type = RelationType::NotEqual;
public:
    NotEqual(){}
    NotEqual(int line, int sign):Relation(line,sign){}
    const std::string TypeToString(){return "Relation::NotEqual";}
};

class Comma : public Token  // ,
{
public:
    Comma():Token(TokenType::Comma){}
    Comma(int line, int sign):Token(TokenType::Comma,line,sign){}
    const std::string TypeToString(){return "Comma";}
};

class Dot : public Token  // .
{
public:
    Dot():Token(TokenType::Dot){}
    Dot(int line, int sign):Token(TokenType::Dot,line,sign){}
    const std::string TypeToString(){return "Dot";}
};

class DoubleColon : public Token  // ::
{
public:
    DoubleColon():Token(TokenType::DoubleColon){}
    DoubleColon(int line, int sign):Token(TokenType::DoubleColon,line,sign){}
    const std::string TypeToString(){return "DoubleColon";}
};

class Semicolon : public Token  // ;
{
public:
    Semicolon():Token(TokenType::Semicolon){}
    Semicolon(int line, int sign):Token(TokenType::Semicolon,line,sign){}
    const std::string TypeToString(){return "Semicolon";}
};

class Rewriting : public Token  // =
{
public:
    Rewriting():Token(TokenType::Rewriting){}
    Rewriting(int line, int sign):Token(TokenType::Rewriting,line,sign){}
    const std::string TypeToString(){return "Rewriting";}
};

class Operator : public Token  // &&
{
public:
    Operator():Token(TokenType::Operator){}
    Operator(int line, int sign):Token(TokenType::Operator,line,sign){}
};

class AndOperator : public Operator // &&
{
    OperatorType operator_type = OperatorType::AndOperator;
public:
    AndOperator(){}
    AndOperator(int line, int sign):Operator(line,sign){}
    const std::string TypeToString(){return "Operator::AndOperator";}
};

class OrOperator : public Operator // ||
{
    OperatorType operator_type = OperatorType::OrOperator;
public:
    OrOperator(){}
    OrOperator(int line, int sign):Operator(line,sign){}
    const std::string TypeToString(){return "Operator::OrOperator";}
};

class Aritmetic : public Token
{
public:
    Aritmetic():Token(TokenType::Aritmetic){}
    Aritmetic(int line, int sign):Token(TokenType::Aritmetic,line,sign){}
};

class PlusMinus : public Aritmetic
{
    AritmeticType aritmetic_type = AritmeticType::PlusMinus;
public:
    PlusMinus(){}
    PlusMinus(int line, int sign):Aritmetic(line,sign){}
};

class Plus : public PlusMinus  // +
{
    PlusMinusType plus_minus_type = PlusMinusType::Plus;
public:
    Plus(){}
    Plus(int line, int sign):PlusMinus(line,sign){}
    const std::string TypeToString(){return "Aritmetic::PlusMinus::Plus";}
};

class Minus : public PlusMinus  // -
{
    PlusMinusType plus_minus_type = PlusMinusType::Minus;
public:
    Minus(){}
    Minus(int line, int sign):PlusMinus(line,sign){}
    const std::string TypeToString(){return "Aritmetic::PlusMinus::Minus";}
};

class MultDiv : public Aritmetic
{
    AritmeticType aritmetic_type = AritmeticType::MultDiv;
public:
    MultDiv(){}
    MultDiv(int line, int sign):Aritmetic(line,sign){}
};

class Multiplication : public MultDiv  // *
{
    MultDivType mult_div_type = MultDivType::Multiplication;
public:
    Multiplication(){}
    Multiplication(int line, int sign):MultDiv(line,sign){}
    const std::string TypeToString(){return "Aritmetic::MultDiv::Multiplication";}
};

class Division : public MultDiv // /
{
    MultDivType mult_div_type = MultDivType::Division;
public:
    Division(){}
    Division(int line, int sign):MultDiv(line,sign){}
    const std::string TypeToString(){return "Aritmetic::MultDiv::Division";}
};

class AritmeticRewriting : public Token  // +=
{
public:
    AritmeticRewriting():Token(TokenType::AritmeticRewriting){}
    AritmeticRewriting(int line, int sign):Token(TokenType::AritmeticRewriting,line,sign){}
};

class PlusRewriting : public AritmeticRewriting  // +=
{
    AritmeticRewritingType type = AritmeticRewritingType::PlusRewriting;
public:
    PlusRewriting(){}
    PlusRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::PlusRewriting";}
};

class MinusRewriting : public AritmeticRewriting  // -=
{
    AritmeticRewritingType type = AritmeticRewritingType::MinusRewriting;
public:
    MinusRewriting(){}
    MinusRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::MinusRewriting";}
};

class MultRewriting : public AritmeticRewriting  // *=
{
    AritmeticRewritingType type = AritmeticRewritingType::MultRewriting;
public:
    MultRewriting(){}
    MultRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::MultRewriting";}
};

class DivisionRewriting : public AritmeticRewriting // /=
{
    AritmeticRewritingType type = AritmeticRewritingType::DivisionRewriting;
public:
    DivisionRewriting(){}
    DivisionRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::DivisionRewriting";}
};

class Data : public Token
{
public:
    Data():Token(TokenType::Data){}
    Data(int line, int sign):Token(TokenType::Data,line,sign){}
};

class Int : public Data
{
    DataType data_type = DataType::Int;
public:
    Int(){}
    Int(int line, int sign):Data(line,sign){}
    const std::string TypeToString(){return "Data::Int";}
};

class Float : public Data
{
    DataType data_type = DataType::Float;
public:
    Float(){}
    Float(int line, int sign):Data(line,sign){}
    const std::string TypeToString(){return "Data::Int";}
};

class For : public Token  // for
{
public:
    For():Token(TokenType::Data){}
    For(int line, int sign):Token(TokenType::Data,line,sign){}
    const std::string TypeToString(){return "For";}
};

class Foreach : public Token  // foteach
{
public:
    Foreach():Token(TokenType::Foreach){}
    Foreach(int line, int sign):Token(TokenType::Foreach,line,sign){}
    const std::string TypeToString() {return "Foreach";}
};

class If : public Token  // if
{
public:
    If():Token(TokenType::If){}
    If(int line, int sign):Token(TokenType::If,line,sign){}
    const std::string TypeToString(){return "If";}
};

class Else : public Token  // else
{
public:
    Else():Token(TokenType::Else){}
    Else(int line, int sign):Token(TokenType::Else,line,sign){}
    const std::string TypeToString(){return "Else";}
};

class Collection : public Token  // collection
{
public:
    Collection():Token(TokenType::Collection){}
    Collection(int line, int sign):Token(TokenType::Collection,line,sign){}
    const std::string TypeToString(){return "Collection";}
};

class Return : public Token  // Return
{
public:
    Return():Token(TokenType::Return){}
    Return(int line, int sign):Token(TokenType::Return,line,sign){}
    const std::string TypeToString(){return "Return";}
};

class Undefined : public Token  // Return
{
    std::string value;
public:
    Undefined():Token(TokenType::Undefined){}
    Undefined(std::string value, int line, int sign):value(value),Token(TokenType::Undefined,line,sign){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "Undefined";}
};

std::string ToString(TokenType);
std::string ToString(NumericType);
std::string ToString(BooleanType);
std::string ToString(ParenthesisType);
std::string ToString(SquareBracketType);
std::string ToString(RelationType);
std::string ToString(OperatorType);
std::string ToString(AritmeticType);
std::string ToString(PlusMinusType);
std::string ToString(MultDivType);
std::string ToString(AritmeticRewritingType);
std::string ToString(DataType);

#endif // TOKEN_H
