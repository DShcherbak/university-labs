#include <algorithm>
#include <iostream>
#include "FiniteAuto.h"

namespace lexer
{
    FiniteAuto::AutoState FiniteAuto::root;

    void FiniteAuto::DfsInitialisation(AutoState &state, TokenList const &tokenList, size_t const &depth)
    {
        size_t i = 0;
        do
        {
            if (tokenList[i].first.length() > depth)
            {
                TokenList next_list;
                AutoState next_state;
                if (depth+1 == tokenList[i].first.length())
                    next_state.type = tokenList[i].second;
                else
                {
                    next_state.type = TokenType::INVALID;
                    next_list.push_back(tokenList[i]);
                }
                next_state.c = tokenList[i].first[depth];

                size_t j = i+1;
                while (j < tokenList.size() && tokenList[j].first.length() > depth + 1)
                {
                    if (next_state.c == tokenList[j].first[depth])
                        next_list.push_back(tokenList[j]);
                    else
                        break;
                    ++j;
                }
                if (!next_list.empty())
                    DfsInitialisation(next_state, next_list, depth + 1);

                state.nextState.push_back(std::move(next_state));
                i = j;
            }
        }
        while (i < tokenList.size());
    }



    std::pair<TokenType, size_t> FiniteAuto::checkValueInternal(AutoState const &state, std::string const &code, size_t const pos)
    {
        if (code.length() <= pos)
            return { state.type, pos };
// ! -> = -> =
        for (int i = 0;i < state.nextState.size(); ++i)
            if (state.nextState[i].c == code[pos])
                return checkValueInternal(state.nextState[i], code, pos + 1);
        return { state.type, pos };
    }

    void FiniteAuto::initStates()
    {
        TokenList dfa_tokens_list;
        size_t start = static_cast<size_t>(TokenType::Add);
        size_t end = static_cast<size_t>(TokenType::SingleLineComment);
        for (size_t i = start;i < end; ++i)
            dfa_tokens_list.push_back( { TokenValue[i], static_cast<TokenType>(i) } );
        std::sort(dfa_tokens_list.begin(), dfa_tokens_list.end());

        DfsInitialisation(root, dfa_tokens_list, 0);
    }

    std::pair<TokenType, size_t> FiniteAuto::checkValue(std::string const &code, size_t const &start_pos)
    {
        return checkValueInternal(root, code, start_pos);
    }

}