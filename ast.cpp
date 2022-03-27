
#include "ast.hpp"


AstNode::AstNode(){
    this->AstNodeType = NodeType::PROGRAM_START_NODE;
}

AstNode::AstNode(NodeType nodetype){
    this->AstNodeType = nodetype;
}

void AstNode::setSibling(AstNode* nextnode){
    this->NextSibling = nextnode;
}

void AstNode::addChild(AstNode* childNode){
    this->ChildrenArray.push_back(childNode);
}

