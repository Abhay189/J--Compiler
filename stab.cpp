#include"stab.hpp"
#include<string>
#include<iostream>
#include <vector>

/**
 * Called to iterate over all the global declerations.  
 * This function takes in the Rootnode as the parameter.
 * @param RootNode 
 */
int main_declaration_counter = 0;

/**
 * @brief This is the scope stack, it contains the pointer to the stab of current Node as the last value inside the vector. 
 * 
 */
std::vector<std::unordered_map<std::string, std::string> *> scopeStack;

/**
 * @brief Looks up if an identifier has been defined in any stab in the stack scope. 
 * this fucntion will first check the stab of the top of the stack, then the one below it and so on. 
 * 
 * @return std::string : The identifier of the function or the variable. 
 */
std::string AstStackLookup(std::string identifier){
    std::unordered_map<std::string, std::string> * temp;

    for (auto it =  scopeStack.rbegin(); it != scopeStack.rend(); ++it){
        temp = *it;
        if(temp->count(identifier) == 1){
            return temp->at(identifier);
        }
    }
    return "";

}

void SemanticCheck_Driver(AstNode *RootNode){
    GlobalScopeIterator(RootNode);
    secondIteration(RootNode);
    printf("No semantic error detected! \n");
}

void GlobalScopeIterator(AstNode *RootNode){
    //This is the case when the rootnode has no children 
    //No children -> no main decleration -> semantic error. 
    if(!RootNode->ChildrenArray.empty()){
        for(auto a : RootNode->ChildrenArray){
            First_Iteration_Callback_Function(a,&RootNode->Node_stab);
        }
    }

    if(main_declaration_counter == 0 ){
        std::cerr << "No main declearation found !!\n";
        exit(EXIT_FAILURE);
    }
    else if(main_declaration_counter > 1){
        std::cerr << "More then one Main declearation found !!\n";
        exit(EXIT_FAILURE);
    }

    return;
}

/**
 * @brief This function is used to recursively create a string that contains the informatin about all of the parameters of a function.  
 * 
 * @param Node Give in the Formal List node to this function  
 * @param thestring This function takes in an empty string that is processed and finally returned with all the info.  
 * 
 */
void Formals_String_Generator(std::string * thestring ,AstNode * Node, std::unordered_map<std::string, std::string> * Node_stab){
    //Each of a is goint to be of the type Formal. 
    for(auto a : Node->ChildrenArray){
        std::string variable_Type;
        if(a->ChildrenArray[0]->AstNodeType == NodeType::INT_TYPE){
            variable_Type = "INT";
            thestring->append(" INT");
        }
        else if(a->ChildrenArray[0]->AstNodeType == NodeType::BOOL_TYPE){
            variable_Type = "BOOLEAN";
            thestring->append(" BOOLEAN");
        }

        if(Node_stab->count(a->ChildrenArray[1]->AstStringval) == 0){
            std::string var_Identifier = a->ChildrenArray[1]->AstStringval;
            
            std::string var_Info = variable_Type + " " + var_Identifier;
            Node_stab->insert({var_Identifier,var_Info});
        }
        else{
            std::cerr << "Multiple Declerations of a Variable \"" + a->ChildrenArray[1]->AstStringval + "\"\n";
            exit(EXIT_FAILURE);
        }
    }
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
void First_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string, std::string> * Node_stab){
    switch(Node->AstNodeType){
        //Case of the main function. 
        case NodeType::MAIN_FNC_DECL: 
            {   
                main_declaration_counter++;
                std::string node_name;
                for(auto a : Node->ChildrenArray){
                    if(a->AstNodeType == NodeType::ID){
                        node_name = a->AstStringval;
                        break;
                    }
                }
                if(Node_stab->count(node_name) == 0){
                    Node_stab->insert({node_name,node_name});
                }else{
                    std::cerr << "More then one Main 5 declearation found !!\n";
                    exit(EXIT_FAILURE);
                }

                break;
            }
        //Case to deal when a functin has been defined in the global scope.     
        case NodeType::FNC_DECL:
            {
                std::string Function_Identifier;
                std::string Function_return_type;
                std::string Function_parameters;

                std::string Function_info;
                for(auto a : Node->ChildrenArray){
                    switch(a->AstNodeType){
                        case NodeType::INT_TYPE: {Function_return_type = "INT"; break;}
                        case NodeType::BOOL_TYPE: {Function_return_type = "BOOLEAN"; break;}
                        case NodeType::VOID: {Function_return_type = "VOID"; break;}
                        case NodeType::ID: {Function_Identifier = a->AstStringval; break;}
                        case NodeType::FORMALS_List: {
                            auto Function_decleration_stab = &Node->Node_stab;
                            Formals_String_Generator( &Function_parameters, a, Function_decleration_stab); break;
                        }
                        }
                }
                Function_info = Function_return_type + " " + Function_Identifier + Function_parameters;

                if(Node_stab->count(Function_Identifier) == 0){
                    Node_stab->insert({Function_Identifier,Function_info});
                }
                else{
                    std::cerr << "Multiple Declerations of a function \"" + Function_Identifier + "\"\n";
                    exit(EXIT_FAILURE);
                }
                break;
            }
        //Case to deal with global variable declerations 
        case NodeType::VAR_DECL: {
            std::string var_Type;
            std::string var_Identifier;
            std::string var_Info;

            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::INT_TYPE: {var_Type = "INT"; break;}
                    case NodeType::BOOL_TYPE: {var_Type = "BOOLEAN"; break;}
                    case NodeType::ID: {var_Identifier = a->AstStringval; break;}
                    }
            }

            var_Info = var_Type + " " + var_Identifier;

            // std::cout<<var_Info + "\n";

            if(Node_stab->count(var_Identifier) == 0){
                Node_stab->insert({var_Identifier,var_Info});
            }
            else{
                std::cerr << "Multiple Declerations of variable \"" + var_Identifier + "\" in global scope\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
        
        default: return;
    }
    
}


/**
 * @brief Goes over the AST the 2nd time to do semantic checking. Also takes care of putting things on and off the scope stack. 
 * 
 * @param Rootnode Put in the root node of the AST while calling this function. 
 */
void secondIteration(AstNode * Rootnode){
    if(Rootnode->ChildrenArray.empty()){
        Second_Iteration_Callback_Function(Rootnode,&Rootnode->Node_stab);
        return;
    }
    else{
        Second_Iteration_Callback_Function(Rootnode,&Rootnode->Node_stab);
        scopeStack.push_back(&Rootnode->Node_stab);
        for(auto a : Rootnode->ChildrenArray){
            secondIteration(a);
        }
        if(!scopeStack.empty()){
            scopeStack.pop_back();
        }
        
    }
}


void Second_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string, std::string> * Node_stab){
    switch(Node->AstNodeType){
        //if we find a variable decleration inside of a function, then we need to add that to the stab of function in which it is defined. 
        //Do not do anyting if this variable decleration is in the global scope, as that has already been dealt with. 
        case NodeType::VAR_DECL:{
            std::string var_Type;
            std::string var_Identifier;
            std::string var_Info;

            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::INT_TYPE: {var_Type = "INT"; break;}
                    case NodeType::BOOL_TYPE: {var_Type = "BOOLEAN"; break;}
                    case NodeType::ID: {var_Identifier = a->AstStringval; break;}
                    }
            }
            var_Info = var_Type + " " + var_Identifier;

            auto topStab = scopeStack.back();
            //Does not check for the global variables as the scope size is more then 1 for his check. 
            if(scopeStack.size() != 1){
                if(scopeStack.size() == 3){
                    if(topStab->count(var_Identifier) == 0){
                    topStab->insert({var_Identifier,var_Info});
                    }
                    else{
                        std::cerr << "Multiple Declerations of variable \"" + var_Identifier + "\" within the same scope\n";
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    std::cerr << "Variable decleration not in outermost block \"" + var_Identifier + "\"\n";
                        exit(EXIT_FAILURE);
                }
            }
            break;
        }
 
        case NodeType::ID:{
            auto node_stab_info = AstStackLookup(Node->AstStringval);
            if(node_stab_info == ""){
                std::cerr << "Identifier not defined! \"" + Node->AstStringval + "\"\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
        
        case NodeType::FNC_INVOCATION:{
            std::string Function_Identifier;
            std::string Function_parameters;

            std::string Function_info;
            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::ID: {Function_Identifier = a->AstStringval; break;}
                    case NodeType::NUMBEER: {Function_parameters.append(" INT"); break;}
                    case NodeType::STRING: {Function_parameters.append(" STRING"); break;}
                    case NodeType::TRUE: {Function_parameters.append(" BOOLEAN"); break;}
                    case NodeType::FALSE: {Function_parameters.append(" BOOLEAN"); break;}
                    default: break;
                }
            }
            Function_info = Function_Identifier + Function_parameters;

            auto node_stab_info = AstStackLookup(Function_Identifier);
            if(node_stab_info == ""){
                std::cerr << "Function not defined before use! \"" + Function_Identifier + "\"\n";
                exit(EXIT_FAILURE);
            }

















            
            // std::string delimiter = " ";
            // std::string token = node_stab_info.substr(3, node_stab_info.find(delimiter));

            std::cout<<node_stab_info<<std::endl;
            std::cout<<Function_info<<std::endl;
            break;
        }
        
        default: break;
    }
}