#ifndef TOKEN_H
#define TOKEN_H

#pragma once

#include <iostream>
#include <string>

enum class TokenType
{
    Undefined,                  // nierozpoznany

    StringLiteral,              // tekst w ""

    Numeric,                    // int, float

    Identifier,                 // nazwy funkcji, argumenty funkcji, właœciwoœci obiektów

    Boolean,                    // false, true

    Null,                       // null

    Parenthesis,                // (, )

    SquareBracket,              // [, ]

    Brace,                      // {, }

    Rewriting,                  // =

    Relation,                   // >, <, >=, <=, ==, !=

    Comma,                      // ,
    Dot,                        // .
    DoubleColon,                // ::
    Semicolon,                  // ;

    Operator,                   // &&, ||

    Aritmetic,                  // +, -, *, /

    AritmeticRewriting,         // +=, -=, *=, /=

    Data,                       // typy danych

    For,                        // for
    Foreach,                    // foteach
    If,                         // if
    Else,                       // else
    Collection,                 // collection
    Return,                     // Return

    Eof,                        // znak koñca pliku
};

enum class NumericType
{
    IntValue,                   // int
    FloatValue,                 // float
};

enum class BooleanType
{
    False,                      // false
    True,                       // true
};

enum class ParenthesisType
{
    ParenthesisOpen,            // (
    ParenthesisClose,           // )
};

enum class SquareBracketType
{
    SquareBracketOpen,          // [
    SquareBracketClose,         // ]
};

enum class BraceType
{
    BraceOpen,                 // [
    BraceClose,                // ]
};

enum class RelationType
{
    GreaterThan,                // >
    LessThan,                   // <
    Rewriting,                  // =
    GreaterEqualThan,           // >=
    LessEqualThan,              // <=
    Equal,                      // ==
    NotEqual,                   // !=
};

enum class OperatorType
{
    AndOperator,                // &&
    OrOperator,                 // ||
};

enum class AritmeticType
{
    PlusMinus,
    MultDiv,
};

enum class PlusMinusType
{
    Plus,                       // +
    Minus,                      // -
};

enum class MultDivType
{
    Multiplication,             // *
    Division,                   // /
};

enum class AritmeticRewritingType
{
    PlusRewriting,              // +=
    MinusRewriting,             // -=
    MultRewriting,              // *=
    DivisionRewriting,          // /=
};

enum class DataType
{
    Int,                        // int
    Float,                      // float
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
    virtual const std::string ToString(){return TypeToString();}
    virtual const std::string TypeToString() = 0;
    std::string ToStreamBegin(){return "Token:"+TypeToString();}
    std::string ToStreamEnd(){return ",line:"+std::to_string(line)+",sign:"+std::to_string(sign)+";";}
    friend std::ostream & operator <<( std::ostream & s, Token & t)
        {s<<t.ToString()<<t.ToStreamEnd()<<std::endl;return s;}
    friend bool operator ==( const Token &, const Token & );
    friend bool operator !=( const Token &, const Token & );
    friend std::string operator +=( std::string &, const Token & );
    friend std::string operator +=( std::string &, const TokenType & );
    friend std::string operator +( std::string &, const Token & );
    friend const char* operator +( const char[], const Token & );
};

class Numeric : public Token
{
protected:
    NumericType numeric_type;
public:
    Numeric(NumericType numeric_type):Token(TokenType::Numeric),numeric_type(numeric_type){}
    Numeric(NumericType numeric_type, int line, int sign):Token(TokenType::Numeric,line, sign),numeric_type(numeric_type){}
    template <typename T>
    friend bool operator ==( T p1, T p2 ){return p1.type == p2.type && p1.GetValue() == p2.GetValue();}
    template <typename T>
    friend bool operator !=( T p1, T p2 ){return p1.type != p2.type || p1.GetValue() != p2.GetValue();}
};

class IntValue : public Numeric
{
private:
    int value;
public:
    IntValue(int value):Numeric(NumericType::IntValue),value(value){}
    IntValue(int value, int line, int sign):Numeric(NumericType::IntValue,line,sign),value(value){}
    int GetValue(){return value;}
    const std::string TypeToString(){return "Numeric::IntValue";}
    const std::string ToString()override{return "Numeric::IntValue::"+std::to_string(value);}
};

class FloatValue : public Numeric
{
private:
    float value;
public:
    FloatValue(float value):Numeric(NumericType::FloatValue),value(value){}
    FloatValue(float value, int line, int sign):Numeric(NumericType::FloatValue,line,sign),value(value){}
    float GetValue(){return value;}
    const std::string TypeToString(){return "Numeric::FloatValue";}
    const std::string ToString(){return "Numeric::FloatValue::"+std::to_string(value);}
};

class StringLiteral : public Token  // tekst w ""
{
    std::string value;
public:
    StringLiteral(std::string value):Token(TokenType::StringLiteral),value(value){}
    StringLiteral(std::string value, int line, int sign):Token(TokenType::StringLiteral,line,sign),value(value){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "StringLiteral";}
    const std::string ToString(){return "StringLiteral::"+value;}
    friend bool operator ==( const StringLiteral& s1, const StringLiteral& s2){return s1.type == s2.type && s1.value == s2.value;}
    friend bool operator !=( const StringLiteral& s1, const StringLiteral& s2){return s1.type != s2.type || s1.value != s2.value;}
};

class Identifier : public Token  // nazwy funkcji, argumenty funkcji, właœciwoœci obiektów
{
    std::string value;
public:
    Identifier(std::string value):Token(TokenType::Identifier),value(value){}
    Identifier(std::string value, int line, int sign):Token(TokenType::Identifier,line,sign),value(value){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "Identifier";}
    const std::string ToString(){return "Identifier::\""+value+'"';}
    friend bool operator ==( const Identifier& s1, const Identifier& s2){return s1.type == s2.type && s1.value == s2.value;}
    friend bool operator !=( const Identifier& s1, const Identifier& s2){return s1.type != s2.type || s2.value != s2.value;}
};

class Boolean : public Token
{
protected:
    BooleanType boolean_type;
    bool value;
public:
    Boolean(BooleanType boolean_type, bool value):Token(TokenType::Boolean),boolean_type(boolean_type),value(value){}
    Boolean(BooleanType boolean_type, bool value, int line, int sign):Token(TokenType::Boolean,line,sign),boolean_type(boolean_type),value(value){}
    bool GetValue(){return value;}
};

class False : public Boolean  // false
{
public:
    False():Boolean(BooleanType::False,false){}
    False(int line, int sign):Boolean(BooleanType::False,false,line,sign){}
    bool GetValue(){return value;}
    const std::string TypeToString(){return "Boolean::False";}
    const std::string ToString(){return "Boolean::False::"+value;}
};

class True : public Boolean  // true
{
public:
    True():Boolean(BooleanType::True,true){}
    True(int line, int sign):Boolean(BooleanType::True,true,line,sign){}
    bool GetValue(){return value;}
    const std::string TypeToString(){return "Boolean::True";}
    const std::string ToString(){return "Boolean::True::"+value;}
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
    Parenthesis(ParenthesisType parenthesis_type):Token(TokenType::Parenthesis),parenthesis_type(parenthesis_type){}
    Parenthesis(ParenthesisType parenthesis_type, int line, int sign):Token(TokenType::Parenthesis,line,sign),parenthesis_type(parenthesis_type){}
    friend bool operator ==( const Parenthesis& p1, const Parenthesis& p2 ){return p1.type == p2.type && p1.parenthesis_type == p2.parenthesis_type;}
    friend bool operator !=( const Parenthesis& p1, const Parenthesis& p2 ){return p1.type != p2.type || p1.parenthesis_type != p2.parenthesis_type;}
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
    SquareBracket(SquareBracketType square_bracket_type):Token(TokenType::SquareBracket),square_bracket_type(square_bracket_type){}
    SquareBracket(SquareBracketType square_bracket_type, int line, int sign):Token(TokenType::SquareBracket,line,sign),square_bracket_type(square_bracket_type){}
    friend bool operator ==( const SquareBracket& p1, const SquareBracket& p2 ){return p1.type == p2.type && p1.square_bracket_type == p2.square_bracket_type;}
    friend bool operator !=( const SquareBracket& p1, const SquareBracket& p2 ){return p1.type != p2.type || p1.square_bracket_type != p2.square_bracket_type;}
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
public:
    SquareBracketClose():SquareBracket(SquareBracketType::SquareBracketClose){}
    SquareBracketClose(int line, int sign):SquareBracket(SquareBracketType::SquareBracketClose,line,sign){}
    const std::string TypeToString(){return "SquareBracket::SquareBracketClose";}
};

class Brace : public Token
{
    BraceType brace_type;
public:
    Brace(BraceType brace_type):Token(TokenType::Brace),brace_type(brace_type){}
    Brace(BraceType brace_type, int line, int sign):Token(TokenType::Brace,line,sign),brace_type(brace_type){}
    friend bool operator ==( const Brace& p1, const Brace& p2 ){return p1.type == p2.type && p1.brace_type == p2.brace_type;}
    friend bool operator !=( const Brace& p1, const Brace& p2 ){return p1.type != p2.type || p1.brace_type != p2.brace_type;}
};

class BraceOpen : public Brace  // {
{
public:
    BraceOpen():Brace(BraceType::BraceOpen){}
    BraceOpen(int line, int sign):Brace(BraceType::BraceOpen,line,sign){}
    const std::string TypeToString(){return "Brace::BraceOpen";}
};

class BraceClose : public Brace  // }
{
public:
    BraceClose():Brace(BraceType::BraceClose){}
    BraceClose(int line, int sign):Brace(BraceType::BraceClose,line,sign){}
    const std::string TypeToString(){return "Brace::BraceClose";}
};

class Relation : public Token
{
protected:
    RelationType relation_type;
public:
    Relation(RelationType relation_type):Token(TokenType::Relation),relation_type(relation_type){}
    Relation(RelationType relation_type,int line, int sign):Token(TokenType::Relation,line,sign),relation_type(relation_type){}
    friend bool operator ==( const Relation& p1, const Relation& p2 ){return p1.type == p2.type && p1.relation_type == p2.relation_type;}
    friend bool operator !=( const Relation& p1, const Relation& p2 ){return p1.type != p2.type || p1.relation_type != p2.relation_type;}
};

class GreaterThan : public Relation  // >
{
public:
    GreaterThan():Relation(RelationType::GreaterThan){}
    GreaterThan(int line, int sign):Relation(RelationType::GreaterThan,line,sign){}
    const std::string TypeToString(){return "Relation::GreaterThan";}
};

class LessThan : public Relation  // <
{
public:
    LessThan():Relation(RelationType::LessThan){}
    LessThan(int line, int sign):Relation(RelationType::LessThan,line,sign){}
    const std::string TypeToString(){return "Relation::LessThan";}
};

class GreaterEqualThan : public Relation  // >=
{
public:
    GreaterEqualThan():Relation(RelationType::GreaterEqualThan){}
    GreaterEqualThan(int line, int sign):Relation(RelationType::GreaterEqualThan,line,sign){}
    const std::string TypeToString(){return "Relation::GreaterEqualThan";}
};

class LessEqualThan : public Relation  // <=
{
public:
    LessEqualThan():Relation(RelationType::LessEqualThan){}
    LessEqualThan(int line, int sign):Relation(RelationType::LessEqualThan,line,sign){}
    const std::string TypeToString(){return "Relation::LessEqualThan";}
};

class Equal : public Relation  // ==
{
public:
    Equal():Relation(RelationType::Equal){}
    Equal(int line, int sign):Relation(RelationType::Equal,line,sign){}
    const std::string TypeToString(){return "Relation::Equal";}
};

class NotEqual : public Relation  // !=
{
public:
    NotEqual():Relation(RelationType::NotEqual){}
    NotEqual(int line, int sign):Relation(RelationType::NotEqual,line,sign){}
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
protected:
    OperatorType operator_type;
public:
    Operator(OperatorType operator_type):Token(TokenType::Operator),operator_type(operator_type){}
    Operator(OperatorType operator_type, int line, int sign):Token(TokenType::Operator,line,sign),operator_type(operator_type){}
};

class AndOperator : public Operator // &&
{
public:
    AndOperator():Operator(OperatorType::AndOperator){}
    AndOperator(int line, int sign):Operator(OperatorType::AndOperator,line,sign){}
    const std::string TypeToString(){return "Operator::AndOperator";}
};

class OrOperator : public Operator // ||
{
public:
    OrOperator():Operator(OperatorType::OrOperator){}
    OrOperator(int line, int sign):Operator(OperatorType::OrOperator,line,sign){}
    const std::string TypeToString(){return "Operator::OrOperator";}
};

class Aritmetic : public Token
{
protected:
    AritmeticType aritmetic_type;
public:
    Aritmetic(AritmeticType aritmetic_type):Token(TokenType::Aritmetic),aritmetic_type(aritmetic_type){}
    Aritmetic(AritmeticType aritmetic_type, int line, int sign):Token(TokenType::Aritmetic,line,sign),aritmetic_type(aritmetic_type){}
};

class PlusMinus : public Aritmetic
{
protected:
    PlusMinusType plus_minus_type;
public:
    PlusMinus(PlusMinusType plus_minus_type):Aritmetic(AritmeticType::PlusMinus),plus_minus_type(plus_minus_type){}
    PlusMinus(PlusMinusType plus_minus_type, int line, int sign):Aritmetic(AritmeticType::PlusMinus,line,sign),plus_minus_type(plus_minus_type){}
};

class Plus : public PlusMinus  // +
{
public:
    Plus():PlusMinus(PlusMinusType::Plus){}
    Plus(int line, int sign):PlusMinus(PlusMinusType::Plus,line,sign){}
    const std::string TypeToString(){return "Aritmetic::PlusMinus::Plus";}
};

class Minus : public PlusMinus  // -
{
public:
    Minus():PlusMinus(PlusMinusType::Minus){}
    Minus(int line, int sign):PlusMinus(PlusMinusType::Minus,line,sign){}
    const std::string TypeToString(){return "Aritmetic::PlusMinus::Minus";}
};

class MultDiv : public Aritmetic
{
    MultDivType mult_div_type;
public:
    MultDiv(MultDivType mult_div_type):Aritmetic(AritmeticType::MultDiv),mult_div_type(mult_div_type){}
    MultDiv(MultDivType mult_div_type, int line, int sign):Aritmetic(AritmeticType::MultDiv,line,sign),mult_div_type(mult_div_type){}
};

class Multiplication : public MultDiv  // *
{
public:
    Multiplication():MultDiv(MultDivType::Multiplication){}
    Multiplication(int line, int sign):MultDiv(MultDivType::Multiplication,line,sign){}
    const std::string TypeToString(){return "Aritmetic::MultDiv::Multiplication";}
};

class Division : public MultDiv // /
{
public:
    Division():MultDiv(MultDivType::Division){}
    Division(int line, int sign):MultDiv(MultDivType::Division,line,sign){}
    const std::string TypeToString(){return "Aritmetic::MultDiv::Division";}
};

class AritmeticRewriting : public Token  // +=
{
protected:
    AritmeticRewritingType aritmetic_rewriting_type;
public:
    AritmeticRewriting(AritmeticRewritingType aritmetic_rewriting_type):Token(TokenType::AritmeticRewriting),aritmetic_rewriting_type(aritmetic_rewriting_type){}
    AritmeticRewriting(AritmeticRewritingType aritmetic_rewriting_type,int line, int sign):Token(TokenType::AritmeticRewriting,line,sign),aritmetic_rewriting_type(aritmetic_rewriting_type){}
};

class PlusRewriting : public AritmeticRewriting  // +=
{
public:
    PlusRewriting():AritmeticRewriting(AritmeticRewritingType::PlusRewriting){}
    PlusRewriting(int line, int sign):AritmeticRewriting(AritmeticRewritingType::PlusRewriting,line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::PlusRewriting";}
};

class MinusRewriting : public AritmeticRewriting  // -=
{
public:
    MinusRewriting():AritmeticRewriting(AritmeticRewritingType::MinusRewriting){}
    MinusRewriting(int line, int sign):AritmeticRewriting(AritmeticRewritingType::MinusRewriting,line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::MinusRewriting";}
};

class MultRewriting : public AritmeticRewriting  // *=
{
public:
    MultRewriting():AritmeticRewriting(AritmeticRewritingType::MultRewriting){}
    MultRewriting(int line, int sign):AritmeticRewriting(AritmeticRewritingType::MultRewriting,line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::MultRewriting";}
};

class DivisionRewriting : public AritmeticRewriting // /=
{
public:
    DivisionRewriting():AritmeticRewriting(AritmeticRewritingType::DivisionRewriting){}
    DivisionRewriting(int line, int sign):AritmeticRewriting(AritmeticRewritingType::DivisionRewriting,line,sign){}
    const std::string TypeToString(){return "AritmeticRewriting::DivisionRewriting";}
};

class Data : public Token
{
protected:
    DataType data_type;
public:
    Data(DataType data_type):Token(TokenType::Data),data_type(data_type){}
    Data(DataType data_type, int line, int sign):Token(TokenType::Data,line,sign),data_type(data_type){}
};

class Int : public Data
{
public:
    Int():Data(DataType::Int){}
    Int(int line, int sign):Data(DataType::Int,line,sign){}
    const std::string TypeToString(){return "Data::Int";}
};

class Float : public Data
{
public:
    Float():Data(DataType::Float){}
    Float(int line, int sign):Data(DataType::Float,line,sign){}
    const std::string TypeToString(){return "Data::Int";}
};

class For : public Token  // for
{
public:
    For():Token(TokenType::For){}
    For(int line, int sign):Token(TokenType::For,line,sign){}
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
    Undefined(std::string value):Token(TokenType::Undefined),value(value){}
    Undefined(std::string value, int line, int sign):Token(TokenType::Undefined,line,sign),value(value){}
    std::string GetValue(){return value;}
    const std::string TypeToString(){return "Undefined::\""+value+'"';}
    friend bool operator ==( const Undefined& p1, const Undefined& p2 ){return p1.type == p2.type && p1.value == p2.value;}
    friend bool operator !=( const Undefined& p1, const Undefined& p2 ){return p1.type != p2.type || p1.value != p2.value;}
};

class Eof : public Token  // Return
{
public:
    Eof():Token(TokenType::Eof){}
    Eof(int line, int sign):Token(TokenType::Eof,line,sign){}
    const std::string TypeToString(){return "Eof";}
};

#endif // TOKEN_H
