#include <iostream>
#include <iomanip>
#include <fstream>
#include "FiniteAuto.h"
#include "Lexer.h"
#include "LexerPrinter.h"

void printHeading(std::ofstream ofstream);

int main()
{
    bool saveToFile = false;
    lexer::Lexer lexer1;
    auto result = lexer1.getAllTokens("../input.hs");
    if (result.lexerCompleted)
    {
        lexer::LexerPrinter printer;
        printer.setSaveToFile(false);
        printer.printErrorLogs(false);
        printer.print(result);
        std::cout << "Finished!";
    } else {
        std::cerr << "An error occured during lexer execution";
    }
    return 0;
}

void printHeading(std::ofstream ofstream) {

}
