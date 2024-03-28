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
        p1.push_back(NodeType::INT_TYPE);
        p1.push_back(NodeType::INT_TYPE);
        
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
    
    //--------adding pre built functions here to the scope stack. 
    std::unordered_map<std::string, SymbolTable> Node_stab = {};

    SymbolTable getChar_table;
    getChar_table.Identifier_Name = "getchar";
    getChar_table.ReturnType = "INT";

    SymbolTable halt_table;
    halt_table.Identifier_Name = "halt";
    halt_table.ReturnType = "VOID";

    SymbolTable printb_table;
    printb_table.Identifier_Name = "printb";
    printb_table.ReturnType = "VOID";
    printb_table.Formals.push_back("BOOLEAN");

    SymbolTable printc_table;
    printc_table.Identifier_Name = "printc";
    printc_table.ReturnType = "VOID";
    printc_table.Formals.push_back("INT");

    SymbolTable printi_table;
    printi_table.Identifier_Name = "printi";
    printi_table.ReturnType = "VOID";
    printi_table.Formals.push_back("INT");

    SymbolTable prints_table;
    prints_table.Identifier_Name = "prints";
    prints_table.ReturnType = "VOID";
    prints_table.Formals.push_back("STRING");

    Node_stab.insert({getChar_table.Identifier_Name,getChar_table});
    Node_stab.insert({"halt",halt_table});
    Node_stab.insert({printb_table.Identifier_Name,printb_table});
    Node_stab.insert({printc_table.Identifier_Name,printc_table});
    Node_stab.insert({printi_table.Identifier_Name,printi_table});
    Node_stab.insert({prints_table.Identifier_Name,prints_table});

    scopeStack.push_back(&Node_stab);
    //----------------------------------------------. 

    GlobalScopeIterator(RootNode);
    secondIteration(RootNode);
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
                    main_stab.isMainFunction = true;
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
                //this is a semantic check to see if the function has a return type or not. 
                if(function_stab.ReturnType != "VOID"){
                    int return_counter = 0; 
                    AstNode * Function_block;
                    for(auto a : Node->ChildrenArray){
                        if(a->AstNodeType == NodeType::BLOCK){
                            Function_block = a;
                            break;
                        }
                    }
                    for(auto b : Function_block->ChildrenArray){
                        if(b->AstNodeType == NodeType::RETURN){
                            return_counter++;
                        }
                    }
                    if(return_counter == 0){
                        std::cerr << "error: No return statement for the non-void function \"" + function_stab.Identifier_Name + "\"\n";
                        exit(EXIT_FAILURE);
                    }
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

void Second_Iteration_Callback_Function(AstNode * Node, std::unordered_map<std::string, SymbolTable> * Node_stab){
    switch(Node->AstNodeType){
        //if we find a variable decleration inside of a function, then we need to add that to the stab of function in which it is defined. 
        //Do not do anyting if this variable decleration is in the global scope, as that has already been dealt with. 
        case NodeType::VAR_DECL:{
            SymbolTable VariableTable;

            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::INT_TYPE: {VariableTable.Var_type = "INT"; break;}
                    case NodeType::BOOL_TYPE: {VariableTable.Var_type = "BOOLEAN"; break;}
                    case NodeType::ID: {VariableTable.Identifier_Name = a->AstStringval; break;}
                    }
            }

            auto topStab = scopeStack.back();
            //Does not check for the global variables as the scope size is more then 1 for his check. 
            if(scopeStack.size() != 2){
                if(scopeStack.size() == 4){
                    if(topStab->count(VariableTable.Identifier_Name) == 0){
                        topStab->insert({VariableTable.Identifier_Name,VariableTable});
                    }
                    else{
                        std::cerr << "error: Multiple Declerations of variable \"" + VariableTable.Identifier_Name + "\" within the same scope\n";
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    std::cerr << "error: Variable decleration not in outermost block \"" + VariableTable.Identifier_Name + "\"\n";
                        exit(EXIT_FAILURE);
                }
            }
            break;
        }
        
        case NodeType::ID:{
            auto node_stab_info = AstStackLookup(Node->AstStringval);
            if(node_stab_info == nullptr){
                std::cerr << "error: Identifier not defined! \"" + Node->AstStringval + "\"\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
        
        case NodeType::FNC_INVOCATION:{
            SymbolTable Function_Invocation_table;
            int count = 0;
            for(auto a : Node->ChildrenArray){
                switch(a->AstNodeType){
                    case NodeType::ID: {
                        if(count == 0){
                            Function_Invocation_table.Identifier_Name = a->AstStringval; 
                            break;
                        }
                        else{
                            auto identifier_stab = AstStackLookup(a->AstStringval);
                            Function_Invocation_table.Formals.push_back(identifier_stab->Var_type); break;
                        }
                        }
                    case NodeType::NUMBEER: {Function_Invocation_table.Formals.push_back("INT"); break;}
                    case NodeType::STRING: {Function_Invocation_table.Formals.push_back("STRING"); break;}
                    case NodeType::TRUE: {Function_Invocation_table.Formals.push_back("BOOLEAN"); break;}
                    case NodeType::FALSE: {Function_Invocation_table.Formals.push_back("BOOLEAN"); break;}
                    case NodeType::OPERATOR: {
                        auto ppp = OperatorTypeChecker(a->AstStringval);
                        for(auto a : ppp){
                            if(a[2] == NodeType::BOOL_TYPE){
                                Function_Invocation_table.Formals.push_back("BOOLEAN");
                            }
                            else if(a[2] == NodeType::INT_TYPE){
                                Function_Invocation_table.Formals.push_back("INT");
                            }
                        }
                        break;
                    }
                    case NodeType::UNARY_EXPRESSION: {
                        auto ppp = OperatorTypeChecker(a->AstStringval);
                        if(a->AstStringval == "-"){
                            auto aa = ppp[1];
                            if(aa[1] == NodeType::INT_TYPE){
                                Function_Invocation_table.Formals.push_back("INT");
                            }
                        }
                        else if(a->AstStringval == "!"){
                            auto aa = ppp[0];
                            if(aa[1] == NodeType::INT_TYPE){
                                Function_Invocation_table.Formals.push_back("BOOLEAN");
                            }
                        }
                        break;
                    }
                    case NodeType::FNC_INVOCATION:{
                        auto sub_func_name = a->ChildrenArray.at(0)->AstStringval;
                        // std::cout<<sub_func_name<<std::endl;
                        auto sub_fnc_invocation = AstStackLookup(sub_func_name);
                        auto sub_function_return_type = sub_fnc_invocation->ReturnType;
                        Function_Invocation_table.Formals.push_back(sub_function_return_type); break;
                    }
                
                }
                count++;
            }
            auto node_stab_info = AstStackLookup(Function_Invocation_table.Identifier_Name);
            if(node_stab_info == nullptr){
                std::cerr << "error: Function not defined before use! \"" + Function_Invocation_table.Identifier_Name + "\"\n";
                exit(EXIT_FAILURE);
            }
            if(node_stab_info->isMainFunction){
                std::cerr << "error: Main function called inside a function. \n";
                exit(EXIT_FAILURE);
            }
            
            //Checking is the function invocation is called with the right amount of parameters. 
            if(Function_Invocation_table.Formals.size() != node_stab_info->Formals.size()){
                std::cerr << "error: Number of parameter in the function invocation \"" + Function_Invocation_table.Identifier_Name + "\" are not equal to number of parameter in its decleration.\n";
                exit(EXIT_FAILURE);
            }
            //To check if the function has been called with the right types of parameters. 
            if(Function_Invocation_table.Formals != node_stab_info->Formals){
                std::cerr << "error: Function \"" + Function_Invocation_table.Identifier_Name + "\" is called with wrong type(s) of parameter.\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
        
        default: break;
    }
}

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