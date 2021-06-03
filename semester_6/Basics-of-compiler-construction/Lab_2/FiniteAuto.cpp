#include <algorithm>
#include <iostream>
#include "FiniteAuto.h"

namespace lexer
{


    void FiniteAuto::DfsInitialisation(std::shared_ptr<AutoState> state, TokenList const &tokenList, size_t const &depth)
    {
        std::map<char, TokenList> sons;
        for(int i = 0; i < tokenList.size(); i++){
            if(tokenList[i].first.length() > depth){
                char letter = tokenList[i].first[depth];
                if(sons.find(letter) == sons.end()){
                    TokenList tl;
                    sons.insert({letter, tl});
                }
                sons[letter].push_back(tokenList[i]);
            }
        }
        for(auto keyVal : sons){
            auto newNode = std::make_shared<AutoState>();
            state->nextState.insert({keyVal.first, newNode});
            for(auto letterSon : keyVal.second){
                if(letterSon.first.length() == depth+1){
                    newNode->type = letterSon.second;
                }
            }
            DfsInitialisation(newNode, sons[keyVal.first], depth + 1);
        }
  /*      size_t i = 0;
        do
        {
            if (tokenList[i].first.length() > depth)
            {
                TokenList next_list;
                AutoState next_state;
                if (depth+1 == tokenList[i].first.length())
                    next_state->type = tokenList[i].second;
                else
                {
                    next_state->type = TokenType::INVALID;
                    next_list.push_back(tokenList[i]);
                }
                next_state->c = tokenList[i].first[depth];

                size_t j = i+1;
                while (j < tokenList.size())
                {
                    if(tokenList[j].first.length() > depth + 1 && next_state->c == tokenList[j].first[depth])
                        next_list.push_back(tokenList[j]);
                    ++j;
                }
                if (!next_list.empty()){
                    auto x = next_list[0].first;
                    DfsInitialisation(next_state, next_list, depth + 1);
                }

                state->nextState[next_state->c] = (std::move(next_state));
                i++;
            }
        }
        while (i < tokenList.size());*/
    }



    std::pair<TokenType, size_t> FiniteAuto::checkValueInternal(std::shared_ptr<AutoState> state, std::string const &code, size_t const pos)
    {
        if (code.length() <= pos)
            return { state->type, pos };
        if(state->nextState.find(code[pos]) != state->nextState.end()){
            std::shared_ptr<AutoState> nextNode = state->nextState.at(code[pos]);
            return checkValueInternal(nextNode, code, pos + 1);
        }
        return {state->type, pos};

    }

    std::pair<TokenType, size_t> FiniteAuto::checkValue(std::string const &code, size_t const &start_pos)
    {
        return checkValueInternal(root, code, start_pos);
    }

    void FiniteAuto::setupAuto(std::vector<std::string> tokensList, int shift) {
        std::vector<std::pair<std::string, TokenType>> finiteAutoBase;
        for (size_t i = 0; i < tokensList.size(); ++i){
            std::pair<std::string, TokenType> p = { tokensList[i], static_cast<TokenType>(shift + i) };
            finiteAutoBase.push_back(p);
        }
        root = std::make_shared<AutoState>();
        DfsInitialisation(root, finiteAutoBase, 0);
        //printAuto(root, 0);
    }

 /*   void FiniteAuto::printAuto(AutoState const &root, size_t const &depth)
    {
        for (size_t i = 0;i < depth; ++i)
            std::cout << "  ";
        auto typer = root.type;
        std::cout << root.c << " " << TokenValue[static_cast<size_t>(typer)] << "\n";
        for (auto c : root.nextState){
            printAuto(c.second, depth + 1);

        }
    }*/


}