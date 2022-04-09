#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>
#include <istream>

#include "scanner.hpp"
#include "parser.hh"
#include "ast.hpp"


class Driver {

    public:
    AstNode * Ident(std::string Name);
    AstNode * Main_decl();
    AstNode * Fnc_decl();
    AstNode * Formals(); 
    AstNode * Formals_List();
    AstNode * Function_Invocation();
    AstNode * void_();
    AstNode * Int_type();
    AstNode * Bool_type();
    AstNode * Var_decl();
    AstNode * Progran_start_node();
    AstNode * Block();
    AstNode * Operator(std::string name);
    AstNode * Number(long long int num_val);
    AstNode * String(std::string name);
    AstNode * True();
    AstNode * False();
    AstNode * StmntExpression();
    AstNode * AssignmentStmntExpression();   
    AstNode * IfStatement();
    AstNode * ElseStatement();
    AstNode * Break(); 
    AstNode * Return(); 
    AstNode * WhileStatement(); 
    AstNode * Unary_Exp(std::string name);
    AstNode * Multiplicative_Exp();
    AstNode * Additive_Exp();
    AstNode * Relational_Exp();
    AstNode * Equlaity_Exp();
    AstNode * Conditional_Exp();

    AstNode * RootNode = new AstNode();

    void AstIteratorFunction(AstNode *RootNode,int tabs);

    Driver(const char* file) : file_name(file) {}

    ~Driver();

    // Will start the compilation of the file
    bool start(std::istream &in);

    // Stores AST. Parser will fill this.
    std::string getFileName() { return file_name; }

    // Makes it easy to debug. Parser will set this as yylex.
    // getToken will then actually call yylex, print out the token if needed and returns the token
    // No modification of the token or it's attribute should be done here.
    int getToken(JCC::Parser::semantic_type *yylval, JCC::Parser::location_type *location);

    private:
    std::string file_name;
    
    bool parse(std::istream &in);
    std::unique_ptr<JCC::Parser> parser{nullptr};
    std::unique_ptr<JCC::Lexer> lexer{nullptr};

};

#endif