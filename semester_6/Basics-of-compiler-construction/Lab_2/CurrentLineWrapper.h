#ifndef LAB_2_CURRENTLINEWRAPPER_H
#define LAB_2_CURRENTLINEWRAPPER_H

#include <cstdio>
#include "Token.h"

namespace lexer {
    class CurrentLineWrapper {
    public:
        size_t column {0};
        size_t row {0};
        std::string line;
        Token token;
        bool ended(size_t forward = 0) const;
        char getNextSymbol(size_t forward = 0) const;
    };
}



#endif //LAB_2_CURRENTLINEWRAPPER_H
