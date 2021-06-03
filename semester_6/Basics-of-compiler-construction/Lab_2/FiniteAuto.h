#ifndef LEXER_DETFINITEAUTOMATON_H
#define LEXER_DETFINITEAUTOMATON_H

#include <vector>
#include "Token.h"


namespace lexer
{
    struct AutoState
    {
        TokenType type = TokenType::INVALID;
        char c = '\0';
        std::vector <AutoState> nextState;
    };

    class FiniteAuto
    {
        bool const commentingOnConstrucion = false;

        AutoState root;

        void DfsInitialisation(AutoState &state, TokenList const &tokenList, size_t const &depth);
        std::pair<TokenType, size_t> checkValueInternal(AutoState const &state, std::string const &code, size_t const pos);
    public:
        void initStates();
        std::pair<TokenType, size_t> checkValue(std::string const &code, size_t const &start_pos);

        FiniteAuto() = default;
    };
}


#endif //LEXER_DETFINITEAUTOMATON_H
