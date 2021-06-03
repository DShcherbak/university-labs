#ifndef LEXER_CHARCHECKS_H
#define LEXER_CHARCHECKS_H

#include "Lexer.h"

namespace lexer
{
    bool isDigit(char const c)
    {
        return ('0' <= c && c <= '9');
    }

    bool isFirstIdentifierSymbol(char const c)
    {
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
    }

    bool isDot(char const c)
    {
        return c == '.';
    }

    bool isWhitespace(char const c)
    {
        return c == ' ';
    }

    bool isTab(char const c){
        return c == '\t';
    }

    bool isPunctuation(char const c)
    {
        std::string punctuation = ",;[]{}()";
        return punctuation.find(c) != std::string::npos;
    }

    bool isOperator(char const c)
    {
        std::string operators = "+-*/%^|&=<>!?:$";
        return operators.find(c) != std::string::npos;
    }


    bool isCorrectAfterNumber(char const c)
    {
        return isPunctuation(c) || isWhitespace(c) || isOperator(c);
    }

    bool isComment(char const c1, char const c2)
    {
        return c2 == '-' && (c1 == '-' || c1 == '{');
    }

    bool isIdentifier(char const c)
    {
        return isFirstIdentifierSymbol(c) || isDigit(c) || c == '\'';
    }

    bool isSingleQuote(char const c)
    {
        return c == '\'';
    }

    bool isDoubleQuote(char const c)
    {
        return c == '"';
    }

    bool isBracket(char const c)
    {
        return c == '[' || c == ']';
    }

    bool isArrow(char const c1, char const c2)
    {
        return (c1 == '-' || c1 == '=') && c2 == '>';
    }

    bool isCloseBrace(char const c)
    {
        return c == '}';
    }

    bool isEndOfToken(char const c){
        return isWhitespace(c) || isTab(c);
    }

}
#endif //LEXER_CHARCHECKS_H
