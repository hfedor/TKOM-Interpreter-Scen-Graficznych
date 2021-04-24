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
    Token(){}
    Token(int line, int sign):line(line),sign(sign){}
    TokenType GetType() { return type; }
    int GetLine() { return line; }
    int GetSign() { return sign; }
    void SetType(TokenType newType) { type = newType; }
    void SetLine(int new_line) { line = new_line; }
    void SetSign(int new_sign) { sign = new_sign; }
    std::string ToString();
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
protected:
    TokenType type = TokenType::Numeric;
    Numeric(int line, int sign):Token(line, sign){}
    std::string TypeToString(){return "Numeric";}
};

class IntValue : public Numeric
{
private:
    NumericType type = NumericType::IntValue;
    int value;
public:
    IntValue(int value, int line, int sign):value(value),Numeric(line,sign){}
    int GetValue(){return value;}
    std::string TypeToString(){return "Numeric::IntValue";}
};

class FloatValue : public Numeric
{
private:
    NumericType numeric_type = NumericType::FloatValue;
    float value;
public:
    FloatValue(float value, int line, int sign):value(value),Numeric(line,sign){}
    float GetValue(){return value;}
    std::string TypeToString(){return "Numeric::FloatValue";}
};

class StringLiteral : public Token  // tekst w ""
{
    TokenType type = TokenType::StringLiteral;
    std::string value;
public:
    StringLiteral(std::string value, int line, int sign):value(value),Token(line,sign){}
    std::string GetValue(){return value;}
    std::string TypeToString(){return "StringLiteral";}
};

class Identifier : public Token  // nazwy funkcji, argumenty funkcji, właœciwoœci obiektów
{
    TokenType type = TokenType::Identifier;
    std::string value;
public:
    Identifier(std::string value, int line, int sign):value(value),Token(line,sign){}
    std::string GetValue(){return value;}
    std::string TypeToString(){return "Identifier";}
};

class Boolean : public Token
{
protected:
    TokenType type = TokenType::Boolean;
    BooleanType boolean_type;
    bool value;
public:
    Boolean(int line, int sign):Token(line,sign){}
    bool GetValue(){return value;}
    std::string TypeToString(){return "Boolean";}
};

class False : public Boolean  // false
{
    BooleanType boolean_type = BooleanType::False;
    bool value = false;
public:
    False(int line, int sign):Boolean(line,sign){}
    bool GetValue(){return value;}
    std::string TypeToString(){return "Boolean::False";}
};

class True : public Boolean  // true
{
    BooleanType boolean_type = BooleanType::True;
    bool value = true;
public:
    True(int line, int sign):Boolean(line,sign){}
    bool GetValue(){return value;}
    std::string TypeToString(){return "Boolean::True";}
};

class Null : public Token  // null
{
    TokenType type = TokenType::Null;
public:
    Null(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Null";}
};

class Parenthesis : public Token
{
    TokenType type = TokenType::Parenthesis;
public:
    Parenthesis(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Parenthesis";}
};

class ParenthesisOpen : public Parenthesis   // (
{
    ParenthesisType parenthesis_type = ParenthesisType::ParenthesisOpen;
public:
    ParenthesisOpen(int line, int sign):Parenthesis(line,sign){}
    std::string TypeToString(){return "Parenthesis::ParenthesisOpen";}
};

class ParenthesisClose : public Parenthesis  // )
{
    ParenthesisType parenthesis_type = ParenthesisType::ParenthesisClose;
public:
    ParenthesisClose(int line, int sign):Parenthesis(line,sign){}
    std::string TypeToString(){return "Parenthesis::ParenthesisClose";}
};

class SquareBracket : public Token
{
    TokenType type = TokenType::SquareBracket;
public:
    SquareBracket(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "SquareBracket";}
};

class SquareBracketOpen : public SquareBracket  // [
{
    SquareBracketType square_bracket_type = SquareBracketType::SquareBracketOpen;
public:
    SquareBracketOpen(int line, int sign):SquareBracket(line,sign){}
    std::string TypeToString(){return "SquareBracket::SquareBracketOpen";}
};

class SquareBracketClose : public SquareBracket  // ]
{
    SquareBracketType square_bracket_type = SquareBracketType::SquareBracketClose;
public:
    SquareBracketClose(int line, int sign):SquareBracket(line,sign){}
    std::string TypeToString(){return "SquareBracket::SquareBracketClose";}
};

class Relation : public Token
{
    TokenType type = TokenType::Relation;
public:
    Relation(int line, int sign):Token(line,sign){}
};

class GreaterThan : public Relation  // >
{
    RelationType relation_type = RelationType::GreaterThan;
public:
    GreaterThan(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::GreaterThan";}
};

class LessThan : public Relation  // <
{
    RelationType relation_type = RelationType::LessThan;
public:
    LessThan(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::LessThan";}
};

class GreaterEqualThan : public Relation  // >=
{
    RelationType relation_type = RelationType::GreaterEqualThan;
public:
    GreaterEqualThan(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::GreaterEqualThan";}
};

class LessEqualThan : public Relation  // <=
{
    RelationType relation_type = RelationType::LessEqualThan;
public:
    LessEqualThan(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::LessEqualThan";}
};

class Equal : public Relation  // ==
{
    RelationType relation_type = RelationType::Equal;
public:
    Equal(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::Equal";}
};

class NotEqual : public Relation  // !=
{
    RelationType relation_type = RelationType::NotEqual;
public:
    NotEqual(int line, int sign):Relation(line,sign){}
    std::string TypeToString(){return "Relation::NotEqual";}
};

class Comma : public Token  // ,
{
    TokenType type = TokenType::Comma;
public:
    Comma(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Comma";}
};

class Dot : public Token  // .
{
    TokenType type = TokenType::Dot;
public:
    Dot(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Dot";}
};

class DoubleColon : public Token  // ::
{
    TokenType type = TokenType::DoubleColon;
public:
    DoubleColon(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "DoubleColon";}
};

class Semicolon : public Token  // ;
{
    TokenType type = TokenType::Semicolon;
public:
    Semicolon(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Semicolon";}
};

class Rewriting : public Token  // =
{
    TokenType type = TokenType::Rewriting;
public:
    Rewriting(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Rewriting";}
};

class Operator : public Token  // &&
{
    TokenType type = TokenType::Operator;
public:
    Operator(int line, int sign):Token(line,sign){}
};

class AndOperator : public Operator // &&
{
    OperatorType operator_type = OperatorType::AndOperator;
public:
    AndOperator(int line, int sign):Operator(line,sign){}
    std::string TypeToString(){return "Operator::AndOperator";}
};

class OrOperator : public Operator // ||
{
    OperatorType operator_type = OperatorType::OrOperator;
public:
    OrOperator(int line, int sign):Operator(line,sign){}
    std::string TypeToString(){return "Operator::OrOperator";}
};

class Aritmetic : public Token
{
    TokenType type = TokenType::Aritmetic;
public:
    Aritmetic(int line, int sign):Token(line,sign){}
};

class PlusMinus : public Aritmetic
{
    AritmeticType aritmetic_type = AritmeticType::PlusMinus;
public:
    PlusMinus(int line, int sign):Aritmetic(line,sign){}
};

class Plus : public PlusMinus  // +
{
    PlusMinusType plus_minus_type = PlusMinusType::Plus;
public:
    Plus(int line, int sign):PlusMinus(line,sign){}
    std::string TypeToString(){return "Aritmetic::PlusMinus::Plus";}
};

class Minus : public PlusMinus  // -
{
    PlusMinusType plus_minus_type = PlusMinusType::Minus;
public:
    Minus(int line, int sign):PlusMinus(line,sign){}
    std::string TypeToString(){return "Aritmetic::PlusMinus::Minus";}
};

class MultDiv : public Aritmetic
{
    AritmeticType aritmetic_type = AritmeticType::MultDiv;
public:
    MultDiv(int line, int sign):Aritmetic(line,sign){}
};

class Multiplication : public MultDiv  // *
{
    MultDivType mult_div_type = MultDivType::Multiplication;
public:
    Multiplication(int line, int sign):MultDiv(line,sign){}
    std::string TypeToString(){return "Aritmetic::MultDiv::Multiplication";}
};

class Division : public MultDiv // /
{
    MultDivType mult_div_type = MultDivType::Division;
public:
    Division(int line, int sign):MultDiv(line,sign){}
    std::string TypeToString(){return "Aritmetic::MultDiv::Division";}
};

class AritmeticRewriting : public Token  // +=
{
    TokenType type = TokenType::AritmeticRewriting;
public:
    AritmeticRewriting(int line, int sign):Token(line,sign){}
};

class PlusRewriting : public AritmeticRewriting  // +=
{
    AritmeticRewritingType type = AritmeticRewritingType::PlusRewriting;
public:
     PlusRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    std::string TypeToString(){return "AritmeticRewriting::PlusRewriting";}
};

class MinusRewriting : public AritmeticRewriting  // -=
{
    AritmeticRewritingType type = AritmeticRewritingType::MinusRewriting;
public:
     MinusRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    std::string TypeToString(){return "AritmeticRewriting::MinusRewriting";}
};

class MultRewriting : public AritmeticRewriting  // *=
{
    AritmeticRewritingType type = AritmeticRewritingType::MultRewriting;
public:
     MultRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    std::string TypeToString(){return "AritmeticRewriting::MultRewriting";}
};

class DivisionRewriting : public AritmeticRewriting // /=
{
    AritmeticRewritingType type = AritmeticRewritingType::DivisionRewriting;
public:
     DivisionRewriting(int line, int sign):AritmeticRewriting(line,sign){}
    std::string TypeToString(){return "AritmeticRewriting::DivisionRewriting";}
};

class Data : public Token
{
    TokenType type = TokenType::Data;
public:
    Data(int line, int sign):Token(line,sign){}
};

class Int : public Data
{
    DataType data_type = DataType::Int;
public:
    Int(int line, int sign):Data(line,sign){}
    std::string TypeToString(){return "Data::Int";}
};

class Float : public Data
{
    DataType data_type = DataType::Float;
public:
    Float(int line, int sign):Data(line,sign){}
    std::string TypeToString(){return "Data::Int";}
};

class For : public Token  // for
{
    TokenType type = TokenType::For;
public:
    For(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "For";}
};

class Foreach : public Token  // foteach
{
    TokenType type = TokenType::Foreach;
public:
    Foreach(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Foreach";}
};

class If : public Token  // if
{
    TokenType type = TokenType::If;
public:
    If(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "If";}
};

class Else : public Token  // else
{
    TokenType type = TokenType::Else;
public:
    Else(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Else";}
};

class Collection : public Token  // collection
{
    TokenType type = TokenType::Collection;
public:
    Collection(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Collection";}
};

class Return : public Token  // Return
{
    TokenType type = TokenType::Return;
public:
    Return(int line, int sign):Token(line,sign){}
    std::string TypeToString(){return "Return";}
};

class Undefined : public Token  // Return
{
    TokenType type = TokenType::Undefined;
    std::string value;
public:
    Undefined(std::string value, int line, int sign):value(value),Token(line,sign){}
    std::string GetValue(){return value;}
    std::string TypeToString(){return "Undefined";}
};

class Empty : public Token  // Return
{
    TokenType type = TokenType::Empty;
public:
    Empty(){}
};

std::string ToString(TokenType);

#endif // TOKEN_H
