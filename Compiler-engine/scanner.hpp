/********************************
 * Example C++ Lexical Analyzer
 * Written for CPSC 411 Tutorial
 * File: scanner.hpp
 * Shankar Ganesh
 * *****************************/

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>
#include <fstream>
#include <memory>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.hh"
#include "location.hh"

namespace JCC{
    class Lexer : public yyFlexLexer {
        public:

        Lexer(std::istream *in) : yyFlexLexer(in) {};
        
        virtual ~Lexer() = default;

        // Redefining yylex. Flex will generate this for us. Just create the prototype.
        virtual int yylex(JCC::Parser::semantic_type *yylval, JCC::Parser::location_type *location);
    };
}

std::unique_ptr<JCC::Lexer> createLexer(std::istream* input);


#endif