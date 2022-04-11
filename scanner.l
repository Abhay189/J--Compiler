%option c++
%option yyclass="JCC::Lexer"
%option yylineno
%option noyywrap

/* Declarations */
%{
    // Declarations go here
    #include <iostream>
    #include <fstream>
    #include "scanner.hpp"
    #include "parser.hh"

    using Token = JCC::Parser::token;

    #undef  YY_DECL
    #define YY_DECL int JCC::Lexer::yylex(JCC::Parser::semantic_type *yylval, JCC::Parser::location_type *loc)
    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

/* Definitions here */
alpha       [a-zA-Z]
digit       [0-9]
underscore  [_]

num             {digit}{digit}*
ID              {alpha}({alpha}|{digit}|{underscore})*

/* Comment States */
%x COMMENT
%x STRING

%% 
 /* Rules here */
[ \t\r]+    ;          
\n          loc->lines();


">"         return Token::T_GT;
"<"         return Token::T_LT;
">="        return Token::T_GE;
"<="        return Token::T_LE;
"+"         return Token::T_ADD;
"-"         return Token::T_SUB;
"/"         return Token::T_DIV;
"*"         return Token::T_MULT;
"%"         return Token::T_PERCENT;
"="         return Token::T_EQ;
"=="        return Token::T_EQEQ;
"!="        return Token::T_NOTEQ;
"!"         return Token::T_NOT;
"&&"        return Token::T_AND;
"||"        return Token::T_OR;
"true"      return Token::T_TRUE;
"false"     return Token::T_FALSE;
"boolean"   return Token::T_BOOLEAN;
"int"       return Token::T_INT;
"void"      return Token::T_VOID;
"if"        return Token::T_IF;
"else"      return Token::T_ELSE;
"while"     return Token::T_WHILE;
"break"     return Token::T_BREAK;
"return"    return Token::T_RETURN;
"("         return Token::T_LEFTPAREN;
")"         return Token::T_RIGHTPAREN;
"{"         return Token::T_LEFTCURLY;
"}"         return Token::T_RIGHTCURLY;
";"         return Token::T_SEMICOLON;
","         return Token::T_COMMA;

{ID}        {yylval->strVal = new std::string(yytext); return Token::T_ID;}
{num}       {yylval->ival = std::stoll(yytext); return Token::T_NUM;}

"\""                            {yymore();BEGIN(STRING);}
<STRING>\n                      {std::cerr << "error: newline in string literal at or near line " << *loc -1<< std::endl;exit(EXIT_FAILURE);}
<STRING>{alpha}|{digit}|[ ]     {yymore();}
<STRING>\\b|\\f|\\t|\\r|\\n     {yymore();}
<STRING>\0                      {yymore(); std::cout<<"\\ 0 detected in the string\n";}
<STRING>\\\\|\\'|\\\"           {yymore();}
<STRING>\"                      {BEGIN(INITIAL); yylval->strVal = new std::string(yytext);return Token::T_STRING;}
<STRING>\\                      {std::cerr << "error: Illegal character inside string in line " << *loc<< std::endl; exit(EXIT_FAILURE);}
<STRING>.                       {yymore();}

""

"//"             BEGIN(COMMENT);
<COMMENT>.
<COMMENT>\n     {BEGIN(INITIAL); }

.               {std::cerr << "Illegal char at line " << *loc << std::endl;exit(EXIT_FAILURE);}


%% 

/* User routines here*/

/* int yyFlexLexer::yywrap() { return 1; } */

/* Creates and returns unique pointer to lexer */
std::unique_ptr<JCC::Lexer> createLexer(std::istream* input) {
    return std::make_unique<JCC::Lexer>(input);
}

