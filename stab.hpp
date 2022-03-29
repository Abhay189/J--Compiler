#ifndef STAB_H
#define STAB_H

#include "ast.hpp"
#include<unordered_map>
#include<string>


void GlobalScopeIterator(AstNode *RootNode);

void First_Iteration_Callback_Function(AstNode * astNode, std::unordered_map<std::string, std::string> * Node_stab);




#endif