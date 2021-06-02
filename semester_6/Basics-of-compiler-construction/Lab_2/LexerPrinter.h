//
// Created by sadoffnick on 02.06.21.
//

#ifndef LAB_2_LEXERPRINTER_H
#define LAB_2_LEXERPRINTER_H

#include "Lexer.h"

namespace lexer{

    class LexerPrinter {
    private:
        bool writeToFile;
        bool shouldPrintErrorLogs;


    public:
        void setSaveToFile(bool b);
        void printErrorLogs(bool b);
        void print(lexer::Lexer::LexerResponse response);
    };
}




#endif //LAB_2_LEXERPRINTER_H
