#include <istream>
#include "ast.hpp"

/**
 * @brief Function for iteration over the AST for semantic analysis purposes. 
 */
void postderrIteratorFunc(AstNode *RootNode, void (*NodeProcessingFunction)){
    if(RootNode->ChildrenArray.empty()){
        return;
    }
    if(!RootNode->ChildrenArray.empty()){
        for(auto a : RootNode->ChildrenArray){
            postderrIteratorFunc(a, NodeProcessingFunction);
        }
    }
}

