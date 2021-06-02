#include "LexerPrinter.h"

void lexer::LexerPrinter::setSaveToFile(bool writeToFile) {
    this->writeToFile = writeToFile;
}

void lexer::LexerPrinter::printErrorLogs(bool printErrors) {
    this->shouldPrintErrorLogs = printErrors;
}

void lexer::LexerPrinter::print(lexer::Lexer::LexerResponse response) {

}
