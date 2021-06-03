#ifndef LEXER_DETFINITEAUTOMATON_H
#define LEXER_DETFINITEAUTOMATON_H

#include <vector>
#include <map>
#include "Token.h"
#include <memory>


namespace lexer
{
    struct AutoState
    {
        TokenType type = TokenType::INVALID;
        char c = '\0';
        std::map <char, std::shared_ptr<AutoState>> nextState;
    };

    class FiniteAuto
    {
        bool const commentingOnConstruction = false;
        std::shared_ptr<AutoState> root;
        unsigned long startToken = 0;


        void
        DfsInitialisation(std::shared_ptr<AutoState> state,
                          TokenList const &tokenList,
                          const size_t &depth);

        std::pair<TokenType, size_t> checkValueInternal(std::shared_ptr<AutoState> state, std::string const &code, size_t const pos);
    public:
        std::pair<TokenType, size_t> checkValue(std::string const &code, size_t const &start_pos);

        FiniteAuto() = default;
        void setupAuto(std::vector<std::string> tokensList, int shiftToken);

        void printAuto(const AutoState &root, const size_t &depth);


    };
}


#endif //LEXER_DETFINITEAUTOMATON_H
