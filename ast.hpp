#ifndef AST_H
#define AST_H

#include<stdio.h>
#include<string>
#include<vector>
#include <unordered_map>

typedef enum{
    PROGRAM_START_NODE, 
    
    MAIN_FNC_DECL, 
    FNC_DECL, 
    FNC_INVOCATION,
    VOID, 
    ID, 
    FORMALS_List,
    FORMALS,
    VAR_DECL,
    INT_TYPE, 
    BOOL_TYPE,
    BLOCK,
    OPERATOR,
    NUMBEER,
    STRING,
    TRUE,
    FALSE,
    STATEMENTEXPRESSION,
    ASSIGNMENTSTATEMENT,
    BREAK,
    RETURN,
    IF_STATEMENT,
    ELSE_STATEMENT,
    WHILE_STATEMENT,
    UNARY_EXPRESSION,
    MULTIPLICATIVE_EXPRESSION,
    ADDITIVE_EXPRESSION,
    RELATIONAL_EXPRESSION,
    EQUALITY_EXPRESSION,
    CONDITIONAL_EXPRESSION,
    } NodeType;

class AstNode{
    public :
    NodeType AstNodeType;
    int AstIntval;
    std::string AstStringval; 
    //A vector containing all the children of this node. This will be empty if this node is a leaf node. 
    std::vector<AstNode*> ChildrenArray;
    //This is a linked list. If the NextSibling is empty then this will be empty. 
    AstNode* NextSibling;

    AstNode();

    AstNode(NodeType nodetype);

    void setSibling(AstNode* nextnode);

    void addChild(AstNode* childNode);
};
#endif