#include"stab.hpp"
#include<string>
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
void Formals_String_Generator(std::string * thestring ,AstNode * Node){
    if(Node->ChildrenArray.empty()){
        if(Node->AstNodeType == NodeType::INT_TYPE){
            thestring->append(" INT");
        }
        else if(Node->AstNodeType == NodeType::BOOL_TYPE){
            thestring->append(" BOOLEAN");
        }
        else if(Node->AstNodeType == NodeType::ID){
            thestring->append(" " + Node->AstStringval);
        }
    }
    else{
        for(auto a : Node->ChildrenArray){
            Formals_String_Generator(thestring, a);
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
                            Formals_String_Generator( &Function_parameters, a); break;
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
 * @brief Goes over the AST the 2nd time to do semantic checking. 
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
        for(auto a : Rootnode->ChildrenArray){
            secondIteration(a);
        }
    }
}


void Second_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string, std::string> * Node_stab){

}