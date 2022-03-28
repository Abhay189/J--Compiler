#include "driver.hpp"
#include "stab.hpp"


AstNode * Driver::Ident(std::string Name){
    AstNode * newNode = new AstNode(NodeType::ID);
    newNode->AstStringval = Name;
    return newNode;
}

AstNode * Driver::Main_decl(){
    AstNode * newNode = new AstNode(NodeType::MAIN_FNC_DECL);
    return newNode;
}

AstNode * Driver::Fnc_decl(){
    AstNode * newNode = new AstNode(NodeType::FNC_DECL);
    return newNode;
}

AstNode * Driver::Function_Invocation(){
    AstNode * newNode = new AstNode(NodeType::FNC_INVOCATION);
    return newNode;
}

AstNode * Driver::Formals_List(){
    AstNode * newNode = new AstNode(NodeType::FORMALS_List);
    return newNode;
}

AstNode * Driver::Formals(){
    AstNode * newNode = new AstNode(NodeType::FORMALS);
    return newNode;
}


AstNode * Driver::void_(){
    AstNode * newNode = new AstNode(NodeType::VOID);
    return newNode;
}

AstNode * Driver::Int_type(){
    AstNode * newNode = new AstNode(NodeType::INT_TYPE);
    return newNode;
}

AstNode * Driver::Bool_type(){
    AstNode * newNode = new AstNode(NodeType::BOOL_TYPE);
    return newNode;
}

AstNode * Driver::Var_decl(){
    AstNode * newNode = new AstNode(NodeType::VAR_DECL);
    return newNode;
}

AstNode * Driver::Block(){
    AstNode * newNode = new AstNode(NodeType::BLOCK);
    return newNode;
}

AstNode * Driver::Operator(std::string name){
    AstNode * newNode = new AstNode(NodeType::OPERATOR);
    newNode->AstStringval = name;
    return newNode;
}

AstNode * Driver::Number(int num_val){
    AstNode * newNode = new AstNode(NodeType::NUMBEER);
    newNode->AstIntval = num_val;
    return newNode;
}

AstNode * Driver::String(std::string name){
    AstNode * newNode = new AstNode(NodeType::STRING);
    newNode->AstStringval = name;
    return newNode;
}

AstNode * Driver::True(){
    AstNode * newNode = new AstNode(NodeType::TRUE);
    return newNode;
}

AstNode * Driver::False(){
    AstNode * newNode = new AstNode(NodeType::FALSE);
    return newNode;
}


AstNode * Driver::StmntExpression(){
    AstNode * newNode = new AstNode(NodeType::STATEMENTEXPRESSION);
    return newNode;
}

AstNode * Driver::AssignmentStmntExpression(){
    AstNode * newNode = new AstNode(NodeType::ASSIGNMENTSTATEMENT);
    return newNode;
}

AstNode * Driver::IfStatement(){
    AstNode * newNode = new AstNode(NodeType::IF_STATEMENT);
    return newNode;
}

AstNode * Driver::ElseStatement(){
    AstNode * newNode = new AstNode(NodeType::ELSE_STATEMENT);
    return newNode;
}

AstNode * Driver::WhileStatement(){
    AstNode * newNode = new AstNode(NodeType::WHILE_STATEMENT);
    return newNode;
}

AstNode * Driver::Break(){
    AstNode * newNode = new AstNode(NodeType::BREAK);
    return newNode;
}

AstNode * Driver::Return(){
    AstNode * newNode = new AstNode(NodeType::RETURN);
    return newNode;
}

AstNode * Driver::Unary_Exp(std::string name){
    AstNode * newNode = new AstNode(NodeType::UNARY_EXPRESSION);
    newNode->AstStringval = name;
    return newNode;
}

AstNode * Driver::Multiplicative_Exp(){
    AstNode * newNode = new AstNode(NodeType::MULTIPLICATIVE_EXPRESSION);
    return newNode;
}

AstNode * Driver::Additive_Exp(){
    AstNode * newNode = new AstNode(NodeType::ADDITIVE_EXPRESSION);
    return newNode;
}

AstNode * Driver::Relational_Exp(){
    AstNode * newNode = new AstNode(NodeType::RELATIONAL_EXPRESSION);
    return newNode;
}

AstNode * Driver::Equlaity_Exp(){
    AstNode * newNode = new AstNode(NodeType::EQUALITY_EXPRESSION);
    return newNode;
}

AstNode * Driver::Conditional_Exp(){
    AstNode * newNode = new AstNode(NodeType::CONDITIONAL_EXPRESSION);
    return newNode;
}


std::string NodeNameFunction(AstNode *Node){
    switch(Node->AstNodeType){
        case NodeType::PROGRAM_START_NODE: return "Prog_node";
        case NodeType::MAIN_FNC_DECL: return "Main function decleration";
        case NodeType::FNC_DECL: return "Function decleration";
        case NodeType::FNC_INVOCATION: return "Function Invocation";
        case NodeType::VOID: return "Void";
        case NodeType::ID: return "Identifier , Name: \'" + Node->AstStringval + "\'";
        case NodeType::FORMALS: return "Formal";
        case NodeType::FORMALS_List: return "Formal List";
        case NodeType::VAR_DECL: return "Variable decleration";
        case NodeType::INT_TYPE: return "Int type";
        case NodeType::BOOL_TYPE: return "Boolean type";
        case NodeType::BLOCK: return "Block";
        case NodeType::OPERATOR: return ("Operator, Type: " + Node->AstStringval);
        case NodeType::NUMBEER: return ("Number, Value: " + std::to_string(Node->AstIntval));
        case NodeType::STRING: return ("String, Value: " + Node->AstStringval);
        case NodeType::TRUE: return ("True");
        case NodeType::FALSE: return ("False");
        case NodeType::STATEMENTEXPRESSION: return ("Stmt Expression");
        case NodeType::ASSIGNMENTSTATEMENT: return ("Assignment Statement");
        case NodeType::BREAK: return ("Break statement");
        case NodeType::RETURN: return ("Return statement");
        case NodeType::IF_STATEMENT: return ("If statement");
        case NodeType::ELSE_STATEMENT: return ("Else statement");  
        case NodeType::WHILE_STATEMENT: return ("While Statement");    
        case NodeType::UNARY_EXPRESSION: return ("Unary Expression , Type: " + Node->AstStringval);    
        case NodeType::MULTIPLICATIVE_EXPRESSION: return ("Multiplicative Expression , Type: ");    
        case NodeType::ADDITIVE_EXPRESSION: return ("Additive Expression , Type: ");    
        case NodeType::RELATIONAL_EXPRESSION: return ("Relational Expression , Type: ");    
        case NodeType::EQUALITY_EXPRESSION: return ("Equality Expression , Type: ");    
        case NodeType::CONDITIONAL_EXPRESSION: return ("Conditional Expression , Type: ");    
        
        default: return "";
    }
}

void Driver::AstIteratorFunction(AstNode *RootNode, int tabs){
    if(RootNode->ChildrenArray.empty()){
        std::string tabbed_space( tabs ,' ');
        std::cout<<tabbed_space + NodeNameFunction(RootNode)<< std::endl;
        return;
    }
    if(!RootNode->ChildrenArray.empty()){
        std::string tabbed_space( tabs ,' ');
        std::cout<<tabbed_space + NodeNameFunction(RootNode)<< std::endl;
        for(auto a : RootNode->ChildrenArray){
            AstIteratorFunction(a,tabs + 4);
        }
    }
}

Driver::~Driver() 
{
    // Resets the unique pointers.
    // Equivalent to destruction
    lexer.reset();
    parser.reset();
}

bool Driver::start(std::istream &in) 
{
    // If the stream is bad or if the stream is at EOF
    // Return 1
    if (!in.good() && in.eof()) {
        return 1;
    }
    bool res = parse(in);

    if (!res) {
        this->AstIteratorFunction(Driver::RootNode,0);
    }

    return res;
}

// Calls yylex and returns the token.
// Called by the parser for every token
// Prints out the token if needed. Can be a flag or a global debug var.
int Driver::getToken(JCC::Parser::semantic_type *yylval, JCC::Parser::location_type *location)
{
    auto tok = lexer->yylex(yylval, location);
    // std::cout << "Token: " << (JCC::Parser::token::yytokentype)tok << "\n";
    return tok;
}


bool Driver::parse(std::istream &in) 
{
    lexer = createLexer(&in);

    // Pass this driver as an argument.
    parser = std::make_unique<JCC::Parser>(*this);
   
    if( parser->parse() != 0 )
    {
        std::cerr << "Parse failed!!\n";
        return 1;
    }

    GlobalScopeIterator(RootNode);

    return 0;
}