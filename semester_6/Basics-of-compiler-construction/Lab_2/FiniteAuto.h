#ifndef LEXER_DETFINITEAUTOMATON_H
#define LEXER_DETFINITEAUTOMATON_H

#include <vector>
#include "Token.h"


namespace lexer
{
    class FiniteAuto
    {
        bool const commentingOnConstrucion = false;
        struct AutoState
        {
            TokenType type = TokenType::INVALID;
            char c = '\0';
            std::vector <AutoState> nextState;
        };

        static AutoState root;
        FiniteAuto() = default;
        static void DfsInitialisation(AutoState &state, TokenList const &tokenList, size_t const &depth);
        static std::pair<TokenType, size_t> checkValueInternal(AutoState const &state, std::string const &code, size_t const pos);
    public:
        static void initStates();
        static std::pair<TokenType, size_t> checkValue(std::string const &code, size_t const &start_pos);
    };
}


#endif //LEXER_DETFINITEAUTOMATON_H
