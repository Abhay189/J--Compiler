#include"stab.hpp"
#include<iostream>


/**
 * Called to iterate over all the global declerations.  
 * This function takes in the Rootnode as the parameter.
 * @param RootNode 
 */
int main_declaration_counter = 0;

void GlobalScopeIterator(AstNode *RootNode){
    //This is the case when the rootnode has no children 
    //No children -> no main decleration -> semantic error. 
    if(!RootNode->ChildrenArray.empty()){
        for(auto a : RootNode->ChildrenArray){
            First_Iteration_Callback_Function(a);
        }
    }

    if(main_declaration_counter == 0 ){
        std::cerr << "No main declearation found !!\n";
        exit(EXIT_FAILURE);
    }
    else if(main_declaration_counter > 1){
        std::cerr << "More then one main declearation found !!\n";
        exit(EXIT_FAILURE);
    }

    return;
}

/**
 * Goes over all the children nodes of the program node, build their stab. 
 *
 * Checks if the main function has been defined more then one time or less then one time. 
 * 
 * Semantic Checks - 2 : 
 * Main function decleration more then once. 
 * Main function decleration less then once.  
 *  
 */
void First_Iteration_Callback_Function(AstNode * Node){
    switch(Node->AstNodeType){
        case NodeType::MAIN_FNC_DECL: 
            {   
                main_declaration_counter++;
                
                break;
            }
        default: return;
    }
}