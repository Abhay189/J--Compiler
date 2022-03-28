/* Simple C++ Parser Example */

/* Need to have this line, if generating a c++ parser */
%skeleton "lalr1.cc"
%require "3.5"

// Generate header files
%defines

// Namespace where the parser class is. Default: yy
%define api.namespace {JCC} 

// Name of the parser class. Default: parser
%define api.parser.class {Parser} 

// Enable location tracking
%locations 

/* Any type that is used in union should be included or decalred here 
    (in the requires qualifier) 
*/
%code requires{
    // Used for parse-param
    #include <memory>
    #include <vector>
    #include <iostream>
    #include <string>

    // Forward Declaration.
    // Compiler outputs error otherwise
    class AstNode; 
    class Driver;

}

/* Add a parameter to parse function. */
%parse-param {Driver &driver}

/* Any other includes or C/C++ code can go in %code and 
    bison will place it somewhere optimal */
%code {
    #include <iostream>
    #include <fstream>
    #include "scanner.hpp"
    #include "ast.hpp"
    #include "driver.hpp"

    // Undefine the normal yylex.
    // Bison will search for a yylex function in the global namespace
    // But one doesn't exist! It's in the lexer class. 
    // So define yylex.
    #undef yylex
    #define yylex driver.getToken
}

/* Prefix all tokens with T_ */
/* %define api.token.prefix {T_} */

/* Semantic type (YYSTYPE) */
%union{
    int ival;
    std::string* strVal;
    AstNode* astnode;
};

/* Tokens 
    The character representations can only be used inside bison
*/
%token <strVal> T_ID
%token T_ADD    "+"
%token T_SUB    "-"
%token T_DIV    "/"
%token T_MULT   "*"
%token T_LT     "<"
%token T_GT     ">"
%token T_GE     ">="
%token T_LE     "<="
%token T_PERCENT "%"
%token T_EQ     "="
%token T_EQEQ   "=="
%token T_NOTEQ  "!="
%token T_NOT    "!"
%token T_AND    "&&"
%token T_OR     "||"
%token <strVal> T_STRING
%token T_TRUE   "true"
%token T_FALSE  "false"
%token T_BOOLEAN    "boolean"
%token T_INT    "int"
%token T_VOID   "void"
%token T_IF     "if"
%token T_ELSE   "else"
%token T_WHILE  "while"
%token T_BREAK  "break"
%token T_RETURN "return"
%token T_RIGHTPAREN ")"
%token T_LEFTPAREN "("
%token T_RIGHTCURLY "}"
%token T_LEFTCURLY  "{"
%token T_SEMICOLON  ";"
%token T_COMMA      ","

/* NUM has an attribute and is of type ival (int in union) */
%token <ival> T_NUM "number" 
%type <astnode> literal type globaldeclarations globaldeclaration globaldeclarationsPrime variabledeclaration identifier
%type <astnode> functiondeclaration functionheader functiondeclarator functiondeclaratorleftFactor formalparameterlist formalparameterlistPrime formalparameter
%type <astnode> mainfunctiondeclaration mainfunctiondeclarator block blockleftfactored blockstatements blockstatementsPrime blockstatement
%type <astnode> statement statementreturnleftFactored statementifleftFactored statementexpression primary
%type <astnode> argumentlist argumentlistPrime functioninvocation functioninvocationleftfactored postfixexpression unaryexpression multiplicativeexpression multiplicativeexpressionPrime  additiveexpression additiveexpressionPrime relationalexpression relationalexpressionPrime equalityexpression equalityexpressionPrime conditionalandexpression conditionalandexpressionPrime conditionalorexpression conditionalorexpressionPrime assignmentexpression assignment expression
/* Define the start symbol */
%start start

/* The symbols E and F are of type int and return an int */
/* %type <ival> E F */

%%
start           : /* empty */       
                | globaldeclarations    {
                                        AstNode * Temp = $1;
                                        while(Temp != nullptr){
                                            driver.RootNode->addChild(Temp);
                                            Temp = Temp->NextSibling;
                                        }}
                ;

literal         : T_NUM      {AstNode * newNode = driver.Number($1); $$ = newNode;}       
                | T_STRING  {AstNode * newNode = driver.String(*$1); $$ = newNode;}   
                | T_TRUE    {AstNode * newNode = driver.True(); $$ = newNode;}   
                | T_FALSE   {AstNode * newNode = driver.False(); $$ = newNode;}   
                ;

type            : T_BOOLEAN {AstNode * newNode = driver.Bool_type(); $$ = newNode;} 
                | T_INT {AstNode * newNode = driver.Int_type(); $$ = newNode;}
                ;

globaldeclarations      : globaldeclaration globaldeclarationsPrime     {$$ = $1;
                                                                        $$->setSibling($2);
                                                                        }
                        ;

globaldeclarationsPrime : globaldeclaration globaldeclarationsPrime {$$ = $1; 
                                                                    $$->setSibling($2);
                                                                    }
                        | /* empty */   {$$ = nullptr;}
                        ;
                
globaldeclaration       : variabledeclaration               {$$ = $1;}
                        | functiondeclaration               {$$ = $1;}        
                        | mainfunctiondeclaration           {$$ = $1;}
                        ;

variabledeclaration     : type identifier ";"       {AstNode* newNode = driver.Var_decl();
                                                    newNode->addChild($1);
                                                    newNode->addChild($2);
                                                    $$ = newNode;
                                                    }
                        ;

identifier              : T_ID          {AstNode* newNode = driver.Ident(*$1);
                                        $$ = newNode;}
                        ;

functiondeclaration     : functionheader block      {AstNode* newNode = driver.Fnc_decl();
                                                    AstNode * Temp = $1;
                                                    while(Temp != nullptr){
                                                        newNode->addChild(Temp);
                                                        Temp = Temp->NextSibling;
                                                    }
                                                    newNode->addChild($2);
                                                    $$ = newNode;}                          
                        ;

functionheader          : type functiondeclarator   {   
                                                        $$ = $1;
                                                        AstNode * Temp = $2;
                                                        if(Temp != nullptr){
                                                            $$->setSibling(Temp);
                                                        }
                                                    }                     
                        | T_VOID functiondeclarator{    AstNode* newNode = driver.void_();
                                                        $$ = newNode;
                                                        AstNode * Temp = $2;
                                                        if(Temp != nullptr){
                                                            $$->setSibling(Temp);
                                                        }
                                                    } 
                        ;

functiondeclarator      : identifier "(" functiondeclaratorleftFactor   {$$ = $1;
                                                                        if($3 != nullptr){
                                                                            $$->setSibling($3);
                                                                        }
                                                                        }
                        ;

functiondeclaratorleftFactor : formalparameterlist ")" {AstNode* newNode = driver.Formals_List();
                                                        AstNode * Temp = $1;
                                                        while(Temp != nullptr){
                                                            newNode->addChild(Temp);
                                                            Temp = Temp->NextSibling;
                                                        }
                                                        $$ = newNode;
                                                        }
                        | ")"       {$$ = nullptr;}
                        ;

formalparameterlist     : formalparameter formalparameterlistPrime      {$$ = $1; 
                                                                        AstNode * Temp = $2;
                                                                        if(Temp != nullptr){
                                                                            $$->setSibling(Temp);
                                                                        }
                                                                        }
                        ;

formalparameterlistPrime : "," formalparameter formalparameterlistPrime {   $$ = $2;
                                                                            AstNode * Temp = $3;
                                                                            if(Temp != nullptr){
                                                                                $$->setSibling(Temp);
                                                                            }

                                                                        }
                        | /* empty */       {$$ = nullptr;}
                        ;

formalparameter         : type identifier   {AstNode* newNode = driver.Formals(); 
                                            newNode->addChild($1);
                                            newNode->addChild($2);
                                            $$ = newNode;}
                        ;

mainfunctiondeclaration : mainfunctiondeclarator block          {AstNode * newNode = driver.Main_decl(); $$ = newNode;
                                                                newNode->addChild($1);
                                                                newNode->addChild($2);
                                                                }
                        ;

mainfunctiondeclarator  : identifier "(" ")"    {$$ = $1;}
                        ;

block                   : "{" blockleftfactored     {$$ = $2;}
                        ;

blockleftfactored       : blockstatements "}"   {$$ = $1;}
                        | "}"           {AstNode * newNode = driver.Block(); $$ = newNode;}
                        ;

blockstatements         : blockstatement blockstatementsPrime   {AstNode * newNode = driver.Block(); $$ = newNode;
                                                                newNode->addChild($1);
                                                                AstNode * Temp = $2;

                                                                while(Temp != nullptr){
                                                                    newNode->addChild(Temp);
                                                                    Temp = Temp->NextSibling;
                                                                }
                                                                }
                        ;

blockstatementsPrime    : blockstatement blockstatementsPrime   {$$ = $1;
                                                                if($2 != nullptr){
                                                                    $$->setSibling($2);
                                                                }                                        
                                                                }
                        | /* empty */ {$$ = nullptr;}
                        ;

blockstatement          : variabledeclaration       {$$ = $1;}
                        | statement     {$$ = $1;}
                        ;
 
statement               : block     {$$ = $1;}
                        | ";"       {$$ = nullptr;}
                        | statementexpression ";"   {$$ = $1;}
                        | T_BREAK ";"   {AstNode * newNode = driver.Break(); $$ = newNode;}
                        | T_RETURN statementreturnleftFactored  {AstNode * newNode = driver.Return(); 
                                                                if($2 != nullptr){
                                                                    newNode->addChild($2);
                                                                }
                                                                $$ = newNode;}
                        | T_IF "(" expression ")" statement statementifleftFactored {AstNode * newNode = driver.IfStatement(); 
                                                                                    if($3 != nullptr){
                                                                                        newNode->addChild($3);
                                                                                    }
                                                                                    if($5 != nullptr){
                                                                                        newNode->addChild($5);
                                                                                    }
                                                                                    if($6 != nullptr){
                                                                                        newNode->addChild($6);
                                                                                    }
                                                                                    $$ = newNode;
                                                                                    }
                        | T_WHILE "(" expression ")" statement {AstNode * newNode = driver.WhileStatement(); 
                                                                                    if($3 != nullptr){
                                                                                        newNode->addChild($3);
                                                                                    }
                                                                                    if($5 != nullptr){
                                                                                        newNode->addChild($5);
                                                                                    }
                                                                                    $$ = newNode;
                                                                                    }
                        ;

statementreturnleftFactored : expression ";"    {$$ = $1;}
                        | ";"    {$$ = nullptr;}
                        ;

statementifleftFactored : T_ELSE statement  {AstNode * newNode = driver.ElseStatement(); 
                                            if($2 != nullptr){
                                                newNode->addChild($2);
                                            }
                                            $$ = newNode;
                                            }
                        | /*empty*/     {$$ = nullptr;}
                        ;

statementexpression     : assignment    {AstNode * newNode = driver.StmntExpression(); 
                                        newNode->addChild($1);
                                        $$ = newNode;
                                        }
                        | functioninvocation {AstNode * newNode = driver.StmntExpression(); 
                                            newNode->addChild($1);
                                            $$ = newNode;
                                            }
                        ;

primary                 : literal {$$ = $1;}
                        | "(" expression ")"    {$$ = $2;}
                        | functioninvocation    {$$ = $1;}
                        ;

argumentlist            : expression argumentlistPrime  {$$ = $1; 
                                                        AstNode * Temp = $2;
                                                        if(Temp != nullptr){
                                                            $$->setSibling(Temp);
                                                        }
                                                        }
                        ;

argumentlistPrime       : "," expression argumentlistPrime  {$$ = $2;
                                                            AstNode * Temp = $3;
                                                            if(Temp != nullptr){
                                                                $$->setSibling(Temp);
                                                            }
                                                            }
                        | /* empty */   {$$ = nullptr;}
                        ;

functioninvocation      : identifier "(" functioninvocationleftfactored     {AstNode * newNode = driver.Function_Invocation();
                                                                            $$ = newNode;
                                                                            $$->addChild($1);
                                                                            if($3 != nullptr){
                                                                                AstNode * Temp = $3;
                                                                                while(Temp != nullptr){
                                                                                    $$->addChild(Temp);
                                                                                    Temp = Temp->NextSibling;
                                                                                }
                                                                            }
                                                                            }
                        ;

functioninvocationleftfactored : argumentlist ")" {$$ = $1;}
                        | ")"   {$$= nullptr;}
                        ;

postfixexpression       : primary {$$ = $1;}
                        | identifier {$$ = $1;}
                        ;

unaryexpression         : "-" unaryexpression   {
                                                AstNode * newNode = driver.Unary_Exp("-");
                                                AstNode * Temp = $2;
                                                while(Temp != nullptr){
                                                    newNode->addChild(Temp);
                                                    Temp = Temp->NextSibling;
                                                }
                                                $$ = newNode;
                                                }
                        | "!" unaryexpression   {AstNode * newNode = driver.Unary_Exp("!");
                                                AstNode * Temp = $2;
                                                while(Temp != nullptr){
                                                    newNode->addChild(Temp);
                                                    Temp = Temp->NextSibling;
                                                }
                                                $$ = newNode;
                                                }
                        | postfixexpression {$$ = $1;}
                        ;

multiplicativeexpression: unaryexpression multiplicativeexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

multiplicativeexpressionPrime : "*" unaryexpression multiplicativeexpressionPrime   {
                                                                                    AstNode * newNode1 = driver.Operator("*");
                                                                                    newNode1->addChild($2);
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | "/" unaryexpression multiplicativeexpressionPrime      {
                                                                                    AstNode * newNode1 = driver.Operator("/");
                                                                                    newNode1->addChild($2);
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | "%" unaryexpression multiplicativeexpressionPrime      {
                                                                                    AstNode * newNode1 = driver.Operator("%");
                                                                                    newNode1->addChild($2);
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | /* empty */   {$$ = nullptr;}
                        ;

additiveexpression      : multiplicativeexpression additiveexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

additiveexpressionPrime : "+" multiplicativeexpression additiveexpressionPrime {
                                                                                    AstNode * newNode1 = driver.Operator("+");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | "-" multiplicativeexpression additiveexpressionPrime  {
                                                                                    AstNode * newNode1 = driver.Operator("+");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | /* empty */ {$$ = nullptr;}
                        ;

relationalexpression    : additiveexpression relationalexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

relationalexpressionPrime : "<" additiveexpression relationalexpressionPrime {
                                                                                    AstNode * newNode1 = driver.Operator("<");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | ">" additiveexpression relationalexpressionPrime {
                                                                                    AstNode * newNode1 = driver.Operator(">");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | T_LE additiveexpression relationalexpressionPrime  {
                                                                                    AstNode * newNode1 = driver.Operator("<=");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | T_GE additiveexpression relationalexpressionPrime {
                                                                                    AstNode * newNode1 = driver.Operator(">=");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        |/* empty */ {$$ = nullptr;}
                        ;

equalityexpression      : relationalexpression equalityexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

equalityexpressionPrime : T_EQEQ relationalexpression equalityexpressionPrime{
                                                                                    AstNode * newNode1 = driver.Operator("==");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | T_NOTEQ relationalexpression equalityexpressionPrime{
                                                                                    AstNode * newNode1 = driver.Operator("!=");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | /* empty */ {$$ = nullptr;}
                        ;

conditionalandexpression: equalityexpression conditionalandexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

conditionalandexpressionPrime : T_AND equalityexpression conditionalandexpressionPrime{
                                                                                    AstNode * newNode1 = driver.Operator("&&");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | /* empty */ {$$ = nullptr;}
                        ;

conditionalorexpression : conditionalandexpression conditionalorexpressionPrime {if($2 != nullptr)
                                                                        {   $$ = $2; 
                                                                            $$->addChild($1);
                                                                        }else{
                                                                            $$ = $1;
                                                                        }}
                        ;

conditionalorexpressionPrime : T_OR conditionalandexpression conditionalorexpressionPrime{
                                                                                    AstNode * newNode1 = driver.Operator("||");
                                                                                    if($2 != nullptr){
                                                                                        newNode1->addChild($2);
                                                                                    }
                                                                                    
                                                                                    if($3 != nullptr){
                                                                                        newNode1->addChild($3);
                                                                                    }
                                                                                    $$ = newNode1;
                                                                                    }
                        | /* empty */ {$$ = nullptr;}
                        ;

assignmentexpression    : conditionalorexpression   {$$ = $1;}
                        | assignment        {$$ = $1;}
                        ;

assignment              : identifier "=" assignmentexpression   {AstNode * newNode = driver.AssignmentStmntExpression(); 
                                                                newNode->addChild($1);
                                                                AstNode * newNode1 = driver.Operator("=");
                                                                newNode->addChild(newNode1);
                                                                newNode->addChild($3);
                                                                $$ = newNode;

                                                                }
                        ;

expression              : assignmentexpression  {$$ = $1;}
                        ;

%%

/* Parser will call this function when it fails to parse */
/* Tip: You can store the current token in the lexer to output meaningful error messages */
void JCC::Parser::error(const location_type &loc, const std::string &errmsg)
{
    std::cerr << "Error: " << errmsg << " at " << loc << "\n";
}

