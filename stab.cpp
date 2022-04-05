#include "stab.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <tuple> 
#include "symbol_table.hpp"

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
std::vector<std::unordered_map<std::string, SymbolTable> *> scopeStack;

std::vector<std::vector<NodeType>> OperatorTypeChecker(std::string operatorType){
    std::vector<std::vector<NodeType>> pp;
    if(operatorType == "||"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "&&"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "=="){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);

        std::vector<NodeType> p1; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
        pp.push_back(p1);
    }
    else if(operatorType == "!="){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);

        std::vector<NodeType> p1; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
        pp.push_back(p1);
    }
    else if(operatorType == "="){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);

        std::vector<NodeType> p1; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
        pp.push_back(p1);
    }
    else if(operatorType == "<"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == ">"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "<="){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == ">="){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "+"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "*"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "/"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "%"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "!"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::BOOL_TYPE);
        p.push_back(NodeType::BOOL_TYPE);
        
        pp.push_back(p);
    }
    else if(operatorType == "-"){
        std::vector<NodeType> p; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);

        std::vector<NodeType> p1; 
        p.push_back(NodeType::INT_TYPE);
        p.push_back(NodeType::INT_TYPE);
        
        pp.push_back(p);
        pp.push_back(p1);
    }
    return pp;

}

/**
 * @brief Looks up if an identifier has been defined in any stab in the stack scope. 
 * this fucntion will first check the stab of the top of the stack, then the one below it and so on. 
 * 
 * @return A reference to the symbol table of the identifier if it exists. 
 */
SymbolTable* AstStackLookup(std::string identifier){
    std::unordered_map<std::string, SymbolTable> * temp;

    for (auto it =  scopeStack.rbegin(); it != scopeStack.rend(); ++it){
        temp = *it;
        if(temp->count(identifier) == 1){
            return &temp->at(identifier);
        }
    }
    return nullptr;
}

void SemanticCheck_Driver(AstNode *RootNode){
    GlobalScopeIterator(RootNode);
    // secondIteration(RootNode);
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
void Formals_String_Generator(AstNode * FormalsNode, SymbolTable * SymbolTable_pointer, AstNode * Function_decl_node){
    //Each of a is goint to be of the type Formal. 
    for(auto a : FormalsNode->ChildrenArray){
        std::string variable_Type;
        if(a->ChildrenArray[0]->AstNodeType == NodeType::INT_TYPE){
            variable_Type = "INT";
            SymbolTable_pointer->Formals.push_back("INT");
        }
        else if(a->ChildrenArray[0]->AstNodeType == NodeType::BOOL_TYPE){
            variable_Type = "BOOLEAN";
            SymbolTable_pointer->Formals.push_back("BOOLEAN");
        }

        if(Function_decl_node->Node_stab.count(a->ChildrenArray[1]->AstStringval) == 0){
            std::string var_Identifier = a->ChildrenArray[1]->AstStringval;
            
            std::string var_Info = variable_Type + " " + var_Identifier;
            SymbolTable VarStab ;
            VarStab.Identifier_Name = var_Identifier;
            VarStab.Var_type = variable_Type;
            Function_decl_node->Node_stab.insert({var_Identifier,VarStab});
        }
        else{
            std::cerr << "error: Multiple Declerations of a Variable \"" + a->ChildrenArray[1]->AstStringval + "\"\n";
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
void First_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string,SymbolTable>* RootNode_symboltable){
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
                if(RootNode_symboltable->count(node_name) == 0){
                    SymbolTable main_stab;
                    main_stab.Identifier_Name = node_name;
                    RootNode_symboltable->insert({node_name,main_stab});
                }else{
                    std::cerr << "error: More then one Main declearation found !!\n";
                    exit(EXIT_FAILURE);
                }
                break;
            }
        //Case to deal when a functin has been defined in the global scope.     
        case NodeType::FNC_DECL:
            {
                SymbolTable function_stab;
                for(auto a : Node->ChildrenArray){
                    switch(a->AstNodeType){
                        case NodeType::INT_TYPE: {function_stab.ReturnType = "INT"; break;}
                        case NodeType::BOOL_TYPE: {function_stab.ReturnType ="BOOLEAN"; break;}
                        case NodeType::VOID: {function_stab.ReturnType ="VOID"; break;}
                        case NodeType::ID: {function_stab.Identifier_Name = a->AstStringval; break;}
                        case NodeType::FORMALS_List: {
                            Formals_String_Generator(a,&function_stab, Node); break;
                        }
                        }
                }

                if(RootNode_symboltable->count(function_stab.Identifier_Name) == 0){
                    RootNode_symboltable->insert({function_stab.Identifier_Name,function_stab});
                }
                else{
                    std::cerr << "error: Multiple Declerations of a function \"" + function_stab.Identifier_Name + "\"\n";
                    exit(EXIT_FAILURE);
                }
                break;
            }
        //Case to deal with global variable declerations 
        case NodeType::VAR_DECL: {
            SymbolTable VarsymbolTable;
            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::INT_TYPE: {VarsymbolTable.Var_type = "INT"; break;}
                    case NodeType::BOOL_TYPE: {VarsymbolTable.Var_type = "BOOLEAN"; break;}
                    case NodeType::ID: {VarsymbolTable.Identifier_Name = a->AstStringval; break;}
                    }
            }

            // std::cout<<var_Info + "\n";

            if(RootNode_symboltable->count(VarsymbolTable.Identifier_Name) == 0){
                RootNode_symboltable->insert({VarsymbolTable.Identifier_Name,VarsymbolTable});
            }
            else{
                std::cerr << "error: Multiple Declerations of variable \"" + VarsymbolTable.Identifier_Name + "\" in global scope\n";
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
// void secondIteration(AstNode * Rootnode){
//     if(Rootnode->ChildrenArray.empty()){
//         Second_Iteration_Callback_Function(Rootnode,&Rootnode->Node_stab);
//         return;
//     }
//     else{
//         Second_Iteration_Callback_Function(Rootnode,&Rootnode->Node_stab);
//         scopeStack.push_back(&Rootnode->Node_stab);
//         for(auto a : Rootnode->ChildrenArray){
//             secondIteration(a);
//         }
//         if(!scopeStack.empty()){
//             scopeStack.pop_back();
//         }
        
//     }
// }

// /**
//  * @brief This function is for splitting the inputted string into tokens and returning those tokens into a vector of strings. 
//  * 
//  * @param s : The input string to be tokenized
//  * @param option : there are two options - input 1 for decleration strings - 2 for function invocations.  
//  * @return std::vector<std::string> : Vector containing string tokens, splitted at whitespaces.
//  */
// std::vector<std::string> simple_tokenizer(std::string s, int option)
// { 
//     std::vector<std::string> temp;
//     std::stringstream ss(s);
//     std::string word;
//     int count = 0;
//     while (ss >> word) {
//         if(count != 0 || option == 2){
//             temp.push_back(word);
//         }
//         count++;
//     }
//     return temp;
// }

// void Second_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string, std::string> * Node_stab){
//     switch(Node->AstNodeType){
//         //if we find a variable decleration inside of a function, then we need to add that to the stab of function in which it is defined. 
//         //Do not do anyting if this variable decleration is in the global scope, as that has already been dealt with. 
//         case NodeType::VAR_DECL:{
//             std::string var_Type;
//             std::string var_Identifier;
//             std::string var_Info;

//             for(auto a : Node->ChildrenArray){
//                 switch(a->AstNodeType){
//                     case NodeType::INT_TYPE: {var_Type = "INT"; break;}
//                     case NodeType::BOOL_TYPE: {var_Type = "BOOLEAN"; break;}
//                     case NodeType::ID: {var_Identifier = a->AstStringval; break;}
//                     }
//             }
//             var_Info = var_Type + " " + var_Identifier;

//             auto topStab = scopeStack.back();
//             //Does not check for the global variables as the scope size is more then 1 for his check. 
//             if(scopeStack.size() != 1){
//                 if(scopeStack.size() == 3){
//                     if(topStab->count(var_Identifier) == 0){
//                     topStab->insert({var_Identifier,var_Info});
//                     }
//                     else{
//                         std::cerr << "error: Multiple Declerations of variable \"" + var_Identifier + "\" within the same scope\n";
//                         exit(EXIT_FAILURE);
//                     }
//                 }
//                 else{
//                     std::cerr << "error: Variable decleration not in outermost block \"" + var_Identifier + "\"\n";
//                         exit(EXIT_FAILURE);
//                 }
//             }
//             break;
//         }
        
//         case NodeType::ID:{
//             auto node_stab_info = AstStackLookup(Node->AstStringval);
//             if(node_stab_info == ""){
//                 std::cerr << "error: Identifier not defined! \"" + Node->AstStringval + "\"\n";
//                 exit(EXIT_FAILURE);
//             }
//             break;
//         }
        
//         case NodeType::FNC_INVOCATION:{
//             std::string Function_Identifier;
//             std::string Function_parameters;

//             std::string Function_info;
//             for(auto a : Node->ChildrenArray){
//                 switch(a->AstNodeType){
//                     case NodeType::ID: {Function_Identifier = a->AstStringval; break;}
//                     case NodeType::NUMBEER: {Function_parameters.append(" INT"); break;}
//                     case NodeType::STRING: {Function_parameters.append(" STRING"); break;}
//                     case NodeType::TRUE: {Function_parameters.append(" BOOLEAN"); break;}
//                     case NodeType::FALSE: {Function_parameters.append(" BOOLEAN"); break;}
//                     case NodeType::OPERATOR: {
//                         auto ppp = OperatorTypeChecker(a->AstStringval);
//                         for(auto a : ppp){
//                             if(a[2] == NodeType::BOOL_TYPE){
//                                 Function_parameters.append(" BOOLEAN");
//                             }
//                             else if(a[2] == NodeType::INT_TYPE){
//                                 Function_parameters.append(" INT");
//                             }
//                         }
//                         break;
//                     }
//                     case NodeType::UNARY_EXPRESSION: {
//                         auto ppp = OperatorTypeChecker(a->AstStringval);
//                         for(auto a : ppp){
//                             if(a[1] == NodeType::BOOL_TYPE){
//                                 Function_parameters.append(" BOOLEAN");
//                             }
//                             else if(a[1] == NodeType::INT_TYPE){
//                                 Function_parameters.append(" INT");
//                             }
//                         }
//                         break;
//                     }
//                     default: Function_parameters.append(" something"); break;
//                 }
//             }
//             Function_info = Function_Identifier + Function_parameters;

//             auto node_stab_info = AstStackLookup(Function_Identifier);
//             if(node_stab_info == Function_Identifier){
//                 std::cerr << "error: Main function called inside a function. \n";
//                 exit(EXIT_FAILURE);
//             }
//             if(node_stab_info == ""){
//                 std::cerr << "error: Function not defined before use! \"" + Function_Identifier + "\"\n";
//                 exit(EXIT_FAILURE);
//             }
//             auto node_stab_info_vector = simple_tokenizer(node_stab_info,1);
//             auto function_info_vector = simple_tokenizer(Function_info,2);
            
//             //Checking is the function invocation is called with the right amount of parameters. 
//             if(function_info_vector.size() != node_stab_info_vector.size()){
//                 std::cerr << "error: Number of parameter in the function invocation \"" + Function_Identifier + "\" are not equal to number of parameter in its decleration.\n";
//                 exit(EXIT_FAILURE);
//             }
//             //To check if the function has been called with the right types of parameters. 
//             if(node_stab_info_vector != function_info_vector){
//                 std::cerr << "error: Function \"" + Function_Identifier + "\" is called with wrong type(s) of parameter.\n";
//                 exit(EXIT_FAILURE);
//             }
//             break;
//         }
        
//         default: break;
//     }
// }

// void third_Iteration(AstNode * RootNode){
//     if(RootNode->ChildrenArray.empty()){
//         Third_Iteration_Callback_Function(RootNode);
//         return;
//     }
//     else{
//         Third_Iteration_Callback_Function(RootNode);
//         for(auto a : RootNode->ChildrenArray){
//             third_Iteration(a);
//         }
//     }
// }

// void Third_Iteration_Callback_Function(AstNode * Node){
//     switch(Node->AstNodeType){
//         {
//         case NodeType::OPERATOR:{
//             if(Node->AstStringval == "||"){

//             }
//             break;
//         }
//         default:
//             break;
//         }
//     }

// }