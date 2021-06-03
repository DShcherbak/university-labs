#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <vector>
#include <memory>

#include "FiniteAuto.h"
#include "CurrentLineWrapper.h"

namespace lexer
{

    class Lexer
    {
        enum LexerState {Default,
                Error,
                Comment,
                LongComment,
                LongCommentEnding,
                Integer,
                Float,
                Char,
                String,
                StringSlash,
                Operator,
                Identifier
        };


        std::vector<std::string> symbolTable;
        std::vector<Token> tokens;
        std::vector<InvalidToken> invalidTokens;
        lexer::CurrentLineWrapper currentLine;
        LexerState currentState = Default;
        std::string cache;
        FiniteAuto operatorsAuto;
        FiniteAuto keyWords;

        void getOperatorToken();
        void addEmptyToken(TokenType token, size_t size);

        void getSingleLineComment(TokenType type);
        void getMultilineComment();
        void getOneQuoteChar();
        void getTwoQuoteString();
        size_t in_key_words(std::string const &word) const;
        void processMultilineMode();
        void processNumber();
        void processComment();
        void processWord();
        void processOneQuoteChar();
        void processTwoQuoteString();
        void processPunctuation();
        void processNextToken();

    public:

        struct LexerResponse{
            LexerResponse();

            LexerResponse(std::vector<Token> tokens, std::vector<std::string> symbolTable,
                          std::vector<InvalidToken> invalidTokens);

            std::vector<Token> tokens;
            std::vector<std::string> symbolTable;
            std::vector<InvalidToken> invalidTokens;
            bool lexerCompleted;
        };


        bool printWhiteSpaces = false;

        Lexer();
        LexerResponse getAllTokens(std::string const &path_to_file);


        void addToken(TokenType token, size_t size);

        void processBadToken(size_t forward);

        void registerError(const std::string& errorName, const std::string& errorLexem, size_t row, size_t col);

        std::pair<TokenType, size_t> getKeyWordToken();

        void getTokenFromAuto(FiniteAuto automata);

        void addLongToken(TokenType token, std::string cache, size_t size);

        void output(const std::string &path_to_file) const;
    };
}




#endif //LEXER_LEXER_H
