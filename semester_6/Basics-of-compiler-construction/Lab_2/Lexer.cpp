#include "Lexer.h"
#include "CharFunctions.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>

namespace lexer
{


    void Lexer::getTokenFromAuto(FiniteAuto automata){
        std::pair<TokenType, size_t> autoToken = automata.checkValue(currentLine.line, currentLine.column);
        if (autoToken.first == TokenType::INVALID)
            processBadToken(autoToken.second - currentLine.column);
        else
        {
            addEmptyToken(autoToken.first, autoToken.second - currentLine.column);
        }
    }

    void Lexer::getOperatorToken() {
        std::pair<TokenType, size_t> autoToken = operatorsAuto.checkValue(currentLine.line, currentLine.column);
        if (autoToken.first == TokenType::INVALID)
            processBadToken(autoToken.second - currentLine.column);
        else
        {
            addToken(autoToken.first, autoToken.second - currentLine.column);
        }
    }

     std::pair<TokenType, size_t> Lexer::getKeyWordToken(){
         return keyWords.checkValue(currentLine.line, currentLine.column);
    }

    void Lexer::getSingleLineComment(TokenType const type){
        addToken(TokenType::SingleLineComment, currentLine.line.length() - currentLine.column);
    }

    void Lexer::getMultilineComment(){
        currentState = LongComment;
        char currentSymbol;
        size_t forward = 0;
        while(!currentLine.ended(forward + 1)){
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
            if(currentState == LongComment){
                if(currentSymbol == '-'){
                    currentState = LongCommentEnding;
                }
                continue;
            } else if (currentState == LongCommentEnding){
                if(currentSymbol == '}'){
                    addLongToken(TokenType::MultiLineComment, cache, forward+1);
                    return;
                } else if (currentSymbol != '-'){
                    currentState = LongComment;
                }
            }
        }
        if(cache.length() > 0) cache += "\\n";
        cache += currentLine.line.substr(currentLine.column, forward);
        currentLine.column += forward + 1;
        currentState = LongComment;
    }

    void Lexer::getOneQuoteChar(){
        currentState = Char;
        char c = currentLine.getNextSymbol();
        if(c == '\\' && !currentLine.ended(2)){
            char next = currentLine.getNextSymbol(2);
            if(next == '\''){
                addToken(TokenType::CharValueOneQuote, 4);
            }
        } else if (!currentLine.ended(1) && currentLine.getNextSymbol(1) == '\'') {
            addToken(TokenType::CharValueOneQuote, 3);
        } else {
            processBadToken(1);
            return;
        }
    }

    void Lexer::getTwoQuoteString(){
        currentState = String;
        char currentSymbol;
        size_t forward = 0;
        while(!currentLine.ended(forward + 1)){
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
            if(currentState == LongComment){
                if(currentSymbol == '\\'){
                    currentState = StringSlash;
                }
                else if (currentSymbol == '\"'){
                    addToken(TokenType::String, forward);
                    return;
                }
            } else if (currentState == StringSlash){
                currentState = String;
            }
        }
        std::string errorText = "No matching \" found to this quotation mark: (";
        errorText += std::to_string(currentLine.row);
        errorText += ", ";
        errorText += std::to_string(currentLine.column);
        errorText += ")";
        registerError(errorText,
                     currentLine.line.substr(currentLine.column, forward),
                     currentLine.row,
                     currentLine.column);

    }

    void Lexer::processMultilineMode(){
        if (currentState == LongComment)
            getMultilineComment();
        else
            processBadToken(0);
    }

    void Lexer::processNumber(){
        currentState = Integer;
        char currentSymbol = currentLine.getNextSymbol();
        int forward = 0;

        while(!currentLine.ended(forward + 1) && isDigit(currentSymbol) || isDot(currentSymbol)){
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
        }

        if(isDot(currentSymbol)){
            currentState = Float;
        }

        while(!currentLine.ended(forward + 1) && isDigit(currentSymbol)){
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
        }

        if(currentLine.ended(forward) || isEndOfToken(currentSymbol)) {
            addToken(currentState == Integer ? TokenType::IntValue : TokenType::FloatValue, forward);
            return;
        }
        else {
            processBadToken(forward);
        }
    }

    void Lexer::registerError(const std::string& errorName, const std::string& errorLexem, size_t row, size_t col){
        invalidTokens.emplace_back(errorName, errorLexem, row, col);
        currentLine.column += col + 1;
        currentState = Default;
    }

    void Lexer::processBadToken(size_t forward){
        currentState = Error;
        char currentSymbol = currentLine.getNextSymbol(forward);
        while(!currentLine.ended(forward + 1) || isEndOfToken(currentSymbol)){
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
        }
        registerError("Invalid token ",
                      currentLine.line.substr(currentLine.column,forward),
                      currentLine.row,
                      currentLine.column);

    }

    void Lexer::processComment() {
        char c = currentLine.getNextSymbol();;
        if (c == '-')
            getSingleLineComment(TokenType::SingleLineComment);
        else {
            getMultilineComment();
        }

    }

    void Lexer::processWord()
    {
        size_t forward = 0;
        char currentSymbol;
        do{
            forward++;
            currentSymbol = currentLine.getNextSymbol(forward);
            if(isEndOfToken(currentSymbol)){
                auto pair = getKeyWordToken();
                if(pair.first == TokenType::INVALID){
                    addToken(TokenType::Identifier, forward);
                } else {
                    addToken(pair.first, forward);
                }
                return;
            }
            if(currentState == Identifier){
                if(currentSymbol == '\\'){
                    currentState = StringSlash;
                }
                else if (currentSymbol == '\"'){

                }
            }
        }
        while(!currentLine.ended(forward + 1));
        auto pair = getKeyWordToken();
        if(pair.first == TokenType::INVALID){
            addToken(TokenType::Identifier, forward);
        } else {
            addToken(pair.first, forward);
        }
    }

    void Lexer::processOneQuoteChar()
    {
        currentLine.token = Token(TokenType::CharValueOneQuote, currentLine.row, currentLine.column, symbolTable.size());
        symbolTable.emplace_back("'");
        currentLine.column += 1;
        getOneQuoteChar();
    }


    void Lexer::processTwoQuoteString()
    {
        currentLine.column += 1;
        if (currentLine.column < currentLine.line.length())
        {
            getTwoQuoteString();
        }
        else
        {
            symbolTable[currentLine.token.symbolTableIndex] += "\\n";
        }
    }


    void Lexer::processPunctuation()
    {
        std::string word;
        word += currentLine.getNextSymbol();;
        auto start = static_cast<size_t>(TokenType::Comma);
        auto end = static_cast<size_t>(TokenType::RBrace);
        size_t pos = SYMBOL_TABLE_MAX;
        for (size_t i = start;i <= end; ++i)
        {
            if (word == TokenValue[i])
            {
                pos = i;
                break;
            }
        }
        tokens.emplace_back(static_cast<TokenType>(pos), currentLine.row, currentLine.column);
        currentLine.column += 1;
    }

    void Lexer::addEmptyToken(TokenType token, size_t size){
        tokens.emplace_back(token, currentLine.row, currentLine.column);
        currentLine.column += size;
        currentState = Default;
    }

    void Lexer::addToken(TokenType token, size_t size){
        int index = symbolTable.size();
        tokens.emplace_back(token, currentLine.row, currentLine.column, index);
        symbolTable.emplace_back(currentLine.line.substr(currentLine.column, size));
        currentLine.column += size;
        currentState = Default;
    }

    void Lexer::addLongToken(TokenType token, std::string cache, size_t size){
        int index = symbolTable.size();
        tokens.emplace_back(token, currentLine.row, currentLine.column, index);
        symbolTable.emplace_back(cache + currentLine.line.substr(currentLine.column, size));
        currentLine.column += size;
        currentState = Default;
    }


    void Lexer::processNextToken()
    {
        if(currentLine.column > currentLine.line.length())
            return;

        if(currentState != Default){
            processMultilineMode();
            return;
        }

        char currentSymbol = currentLine.getNextSymbol();;

        if(isWhitespace(currentSymbol)){
            addToken(TokenType::WhiteSpace, 1);
            return;
        }

        if(isTab(currentSymbol)){
            addToken(TokenType::Tab, 1);
            return;
        }

        if (isDigit(currentSymbol))
        {
            processNumber();
            return;
        }

        if (currentLine.column + 1 < currentLine.line.length() &&
            isComment(currentSymbol, currentLine.line[currentLine.column + 1]))
        {
            processComment();
            return;
        }

        if (isFirstIdentifierSymbol(currentSymbol))
        {
            processWord();
            return;
        }

        if (isSingleQuote(currentSymbol))
        {
            processOneQuoteChar();
            return;
        }
        if (isDoubleQuote(currentSymbol))
        {
            processTwoQuoteString();
            return;
        }
        if (isOperator(currentSymbol))
        {
            getOperatorToken();
            return;
        }
     //   if (isPunctuation(currentSymbol))
     //   {
     //       processPunctuation();
     //       return;
     //   }
        std::string symbol;
        symbol += currentLine.getNextSymbol();
        invalidTokens.emplace_back("Invalid symbol", symbol, currentLine.row, currentLine.column);
        currentLine.column += 1;
    }

    Lexer::LexerResponse Lexer::getAllTokens(std::string const &path_to_file)
    {
        std::ifstream ifs(path_to_file);
        if (!ifs)
        {
            std::cerr << "\tFile doesn't exists!\n";
            return {};
        }
        while (!ifs.eof())
        {
            std::getline(ifs, currentLine.line);
            currentLine.column = 0;
            while (!currentLine.ended())
            {
                processNextToken();
            }
            currentLine.row += 1;
        }

        return LexerResponse(tokens, symbolTable, invalidTokens);
    }

    Lexer::LexerResponse::LexerResponse(std::vector<Token> tokens, std::vector<std::string> symbolTable,
                                        std::vector<InvalidToken> invalidTokens) {
        this->tokens = std::move(tokens);
        this->symbolTable = std::move(symbolTable);
        this->invalidTokens = std::move(invalidTokens);
        this->lexerCompleted = true;
    }

    Lexer::LexerResponse::LexerResponse() {
        this->tokens = {};
        this->symbolTable = {};
        this->invalidTokens = {};
        this->lexerCompleted = false;
    }

    void Lexer::output(std::string const &path_to_file) const
    {
        std::ofstream ofs(path_to_file);

        ofs << "---------------------------Tokens list---------------------------\n";
        ofs << std::left << std::setw(22) << "Token type";
        ofs << std::left << std::setw(4) << "|row" << "|";
        ofs << std::left << std::setw(6) << "col|";
        ofs << std::left << "symbol table index and value\n";
        ofs << "-----------------------------------------------------------------\n";
        for (int i = 0;i < tokens.size(); ++i)
        {
            if(printWhiteSpaces || tokens[i].type != TokenType::WhiteSpace){
                ofs << std::left << std::setw(22) << TokenValue[static_cast<size_t>(tokens[i].type)];
                ofs << std::right <<std::setw(4) << tokens[i].row_pos << "|";
                ofs << std::left << std::setw(6) << tokens[i].column_pos;


                if (tokens[i].symbolTableIndex != SYMBOL_TABLE_MAX)
                    ofs << std::left << tokens[i].symbolTableIndex << ") |"
                        << symbolTable[tokens[i].symbolTableIndex] << "|";
                ofs << '\n';
            }
        }
        ofs << "\n---------------------------Invalid tokens---------------------------\n";
        ofs << std::left << std::setw(2) << "|row" << "|";
        ofs << std::left << std::setw(8) << "col|";
        ofs << "Error explanation";
        ofs << "\n--------------------------------------------------------------------\n";
        for (int i = 0;i < invalidTokens.size(); ++i)
        {
            ofs << std::right <<std::setw(2) << invalidTokens[i].row_pos << "|";
            ofs << std::left << std::setw(8) << invalidTokens[i].column_pos;
            ofs << invalidTokens[i].error_message + " |" + invalidTokens[i].error_symbol + "|\n";
        }
        ofs << "\n---------------------------Symbol table---------------------------\n";
        for (int i = 0;i < symbolTable.size(); ++i)
        {
            ofs << i << ") |" << symbolTable[i] << "|\n";
        }
    }

    Lexer::Lexer()
    {
        std::vector<std::string> operators = {"$", "+", "-",                        // Sub
                     "*",
                     "/",
                     "%",
                     "**",
                     "=",
                     "==",
                     "/=",                       // NotEqualQuest
                     "<>",                       // NotEqualBracket
                     ">",                        // GreaterThan
                     "<",                        // LessThan
                     ">=",                       // GreaterThanEqual
                     "<=",                       // LessThanEqual
                     "++",                       // Concat
                // logic //14
                     "&",                        // Ampersand
                     "&&",                       // AndSymb
                     "||",                       // OrSymb
                     "!",                        // Not
                     "|",                        // BitwiseOr
                     "^",                        // BitwiseXor
                     "<<",                       // LeftShift
                     ">>",                       // RightShift
                     "|=",                       // BitwiseOrAssignment
                     "^=",                       // BitwiseXorAssignment
                     "<<=",                      // LeftShiftAssignment
                     ">>=",                      // RightShiftOrAssignment
                     "-<",                      // MinusLess
                     "--<",
                     ".",                        // Dot
                     "?",                        // QuestMark
                     ":",                        // Colon
                     "??",                       // NullCoalescing
                     "=>",                       // ArrayKey
                     "->",                       // VarReference,
                     "::",
                  ",",                        // Comma
                  ";",                        // Semicolon
                  "(",                        // LParen
                  ")",                        // RParen
                  "[",                        // LBracket
                  "]",                        // RBracket
                  "{",                        // LBrace
                  "}",                        // RBrace
                  "@",                        // Cat
                  "_",                        // Dash
                  "...",                        // DotDotDot
        };

        std::vector<std::string> keywords = { //47
                "include",                 // Include //14
                "import",                 // Import
                "if",                      // If
                "then",                    // Else
                "else",                  // ElseIf
                "class",                // Function
                "where",                  // Return
                "do",                    // Define
                "case",                    // Static
                "of",                    // Global
                "error",                    // Global
                "deriving",                    // Global
                "echo",                      // Echo
                "print",                     // Print
                //data types cast
                "Int", //12
                "Integer",
                "Bool",
                "Scientific",
                "Char",
                "String",
                "Integral",
                "Ratio",
                "Float",
                "Fractional",
                "Double",
                "Complex",
                //type classes //19
                "Eq",
                "Num",
                "Ord",
                "Show",
                "Bounded",
                "Enum",
                "Read",
                "Monad",
                "Maybe",
                "Functor",
                "Either",
                "Ordering",
                "Nothing",
                "Just",
                "Left",
                "Right",
                "LT",
                "EQ",
                "GT",
                "True",
                "False"
        };
        operatorsAuto.setupAuto(operators, 52);
        keyWords.setupAuto(keywords, 1);

    }
}