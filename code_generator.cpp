#include "code_generator.hpp"
#include <vector>
#include "ast.hpp"
#include <iostream>
#include <string>
#include <fstream>

int counter = 1;
std::vector<std::unordered_map<std::string, SymbolTable> *> generator_scopeStack;
std::vector<std::string> Regester_Stack { "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6" ,"$t7" ,"$t8", "$t9", "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
int stack_pointer = 0;
int localVariables = 0;

SymbolTable* Generator_AstStackLookup(std::string identifier){
    std::unordered_map<std::string, SymbolTable> * temp;

    for (auto it =  generator_scopeStack.rbegin(); it != generator_scopeStack.rend(); ++it){
        temp = *it;
        if(temp->count(identifier) == 1){
            return &temp->at(identifier);
        }
    }
    return nullptr;
}

//Lable0 will not be distributed through this function as that is fixed for the main function.
std::string NewlableGenerator(){
    std::string str = std::to_string(counter);
    counter++;
    return "Lable" + str;
}

std::string Register_allocator(){
    if(!Regester_Stack.empty()){
        auto temp = Regester_Stack.back();
        Regester_Stack.pop_back();
        return temp;
    }
    else{
        "Error : Over complex expression. Out of regesters !";
    }
    return "";
}

void Register_free(std::string reg){
    Regester_Stack.push_back(reg);
}

void Global_Valriablehandler(AstNode * RootNode,std::string Out_file_name){
    std::ofstream outfile;
    outfile.open(Out_file_name, std::ios_base::app);
    for(auto a : RootNode->ChildrenArray){
        switch(a->AstNodeType){
            case NodeType::VAR_DECL:{
                RootNode->Node_stab.at(a->ChildrenArray[1]->AstStringval).isglobalVariable = true;
                outfile << "    .data\n";
                outfile<< RootNode->Node_stab.at(a->ChildrenArray[1]->AstStringval).Enterence_lable_Name << " :\n";
                outfile<< "    .word 0\n";
                outfile<< "    .text\n";
                break;
            }
        }
    }
}

void arithmaticExpressionHandler(AstNode * node, std::string Out_file_name,std::string allocated_reg, std::vector<std::string> children_reg){
    std::ofstream outfile;
    outfile.open(Out_file_name, std::ios_base::app);
    switch(node->AstNodeType){
        case NodeType::NUMBEER:{
            outfile << "    li "<< allocated_reg << "," <<node->AstIntval<<"\n";
            break;
        }

        case NodeType::OPERATOR:{
            if(node->AstStringval == "+"){
                outfile << "    addu "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "*"){
                outfile << "    mul "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "-"){
                outfile << "    subu "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "/"){
                auto devision_lable = NewlableGenerator();
                auto error_lable = NewlableGenerator();
                outfile << "    bnez "<<children_reg.at(0)<< "," <<devision_lable <<"\n";
                outfile << "    .data\n";
                outfile << error_lable << " :\n";
                outfile << "    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0\n";
                outfile << "    .align 2\n";
                outfile << "    .text\n";
                outfile << "    la $a0,"<<error_lable<<"\n";
                outfile << "    j error\n";

                outfile << devision_lable << " :\n";
                outfile << "    div "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "%"){
                auto devision_lable = NewlableGenerator();
                auto error_lable = NewlableGenerator();
                outfile << "    bnez "<<children_reg.at(0)<< "," <<devision_lable <<"\n";
                outfile << "    .data\n";
                outfile << error_lable << " :\n";
                outfile << "    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0\n";
                outfile << "    .align 2\n";
                outfile << "    .text\n";
                outfile << "    la $a0,"<<error_lable<<"\n";
                outfile << "    j error\n";

                outfile << devision_lable << " :\n";
                outfile << "    rem "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            break;
        }

        case NodeType::UNARY_EXPRESSION:{
            outfile << "    negu "<< allocated_reg << "," <<children_reg.at(0)<<"\n";
            for(auto a : children_reg){
                    Register_free(a);
                }
            break;
        }
        //this is the case of a variable.
        case NodeType::ID:{
            auto node_stab = Generator_AstStackLookup(node->AstStringval);
            if(node_stab->isglobalVariable){
                outfile << "    lw "<< allocated_reg << "," <<node_stab->Enterence_lable_Name<<"\n";
            }else{
                outfile << "    lw "<< allocated_reg << "," <<node_stab->stack_Pointer_Location<<"($sp)"<<"\n";
            }
            
            break;
        }
        default: outfile<<"a case not handled in arithmatic expressions  \n";
    }
    outfile.close();
}

void assignment_expression_treversal(AstNode * node, std::string outfile, std::string allocated_reg, std::vector<std::string> children_reg){
    if(node->ChildrenArray.empty()){
        arithmaticExpressionHandler(node,outfile,allocated_reg,children_reg);
        return;
    }
    else{
        std::vector<std::string> children_reg;
        for(auto a : node->ChildrenArray){
            auto reg = Register_allocator();
            children_reg.push_back(reg);
            assignment_expression_treversal(a, outfile, reg, children_reg);
        }//free the regesters.
        arithmaticExpressionHandler(node,outfile,allocated_reg,children_reg);
    }
}

void First_iter(AstNode * Rootnode,std::string Out_file_name){
    for(auto a : Rootnode->ChildrenArray){
        if(a->AstNodeType != NodeType::MAIN_FNC_DECL){
            auto Lable = NewlableGenerator();
            std::string Identifier = "";
            for(auto aa : a->ChildrenArray){
                if(aa->AstNodeType == NodeType::ID){
                    Identifier = aa->AstStringval;
                    break;
                }
            }
            Rootnode->Node_stab.at(Identifier).Enterence_lable_Name = Lable;
        }
    }
}

/**
 * @brief This functin calculates the amount of memory required by a function or main decleration.
 * 
 * @param BaseNode The main decleration node or function declerator node. 
 * @return The amount of space required by the function on the stack.  
 */
int memory_counter(AstNode* BaseNode){
    int returnnum = 1;
    AstNode * BlockNode = nullptr;
    AstNode * FormalDeclerationNode = nullptr; 
    for (auto a : BaseNode->ChildrenArray){
        if(a->AstNodeType == NodeType::BLOCK){
            BlockNode = a ;
        }
        if(a->AstNodeType == NodeType::FORMALS_List){
            FormalDeclerationNode = a;
        }
    }
    if(BlockNode != nullptr){
        for(auto a : BlockNode->ChildrenArray){
            if(a->AstNodeType == NodeType::VAR_DECL){
                returnnum++;
            }
        }
    }
    if(FormalDeclerationNode != nullptr){
        for(auto a : FormalDeclerationNode->ChildrenArray){
            if(a->AstNodeType == NodeType::FORMALS){
                counter++;
            }
        }
    }
    stack_pointer += (returnnum * 4);
    return returnnum * 4;
}

void Second_Iter_Calc_NodeExit(AstNode * node, std::string Out_file_name){
    std::ofstream outfile;
    outfile.open(Out_file_name, std::ios_base::app);
    switch (node->AstNodeType)
    {
        case NodeType::MAIN_FNC_DECL: {
            std::string main_function_ID;
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    main_function_ID = a->AstStringval;
                    break;
                }
            }

            SymbolTable *main_symbol_table = Generator_AstStackLookup(main_function_ID);
            int memory_ = main_symbol_table->memory_Size;
            std::string lable = main_symbol_table->Exit_lable_name;
            outfile << lable << " : \n" ;
            outfile << "    lw $ra,0($sp)\n";
            outfile << "    addu $sp,$sp,"<< memory_ <<"\n" ;
            outfile<< "    jr $ra\n";
            break;
        }
    }
    outfile.close();
}

void Third_iter_callbackfunc(AstNode * node, std::string Out_file_name){
    std::ofstream outfile;
    outfile.open(Out_file_name, std::ios_base::app);
    switch (node->AstNodeType)
    {
        case NodeType::OPERATOR: {
            if(node->AstStringval == "="){
                auto reg = Register_allocator();
                std::string source_reg = "";
                std::string source_lable = "";
                std::string value = ""; 
                int VAriableStackLocation = 0;
                bool is_global = false;
                SymbolTable *variable_symbol_table;
                bool is_expression = false;

                for(auto a : node->ChildrenArray){
                    if(a->AstNodeType == NodeType::ID){
                        variable_symbol_table = Generator_AstStackLookup(a->AstStringval);
                        is_global = variable_symbol_table->isglobalVariable;
                        if(!is_global){
                            if(variable_symbol_table->stack_Pointer_Location == 0){
                                localVariables ++;
                                VAriableStackLocation = (4*localVariables);
                                variable_symbol_table->stack_Pointer_Location = VAriableStackLocation;
                            }else{
                                VAriableStackLocation = variable_symbol_table->stack_Pointer_Location;
                            }
                        }
                    }
                    //what to do hen you see a situation like a = b = c ?
                    //tackle b =c first. 
                    //when you come to a = .. then the right hand side of this equation will actully be the equal to node 
                    //from the equal to node, load the value of the left hand side of the sub qualt to node and move that to out primary identifier.  
                    if(node->ChildrenArray.at(1)->AstNodeType == NodeType::OPERATOR && node->ChildrenArray.at(1)->AstStringval == "="){
                        //this is the sub uqual to node inside the tree. we need the value of its left child. 
                        is_expression = true;
                        printf("ola im here amigo\n");
                        auto subequalnode = node->ChildrenArray.at(1);
                        //this is the variable or function value that we need to pass up the tree. 
                        auto subEq_leftchild = subequalnode->ChildrenArray.at(0);
                        //we need to lookup this nodes stab first. 
                        auto subEq_leftChild_nodestab = Generator_AstStackLookup(subEq_leftchild->AstStringval);
                        auto temp_regg = Register_allocator();
                        std::string temp_source = "";
                        if(subEq_leftChild_nodestab->isglobalVariable){
                            temp_source = subEq_leftChild_nodestab->Enterence_lable_Name;
                        }else{
                            temp_source =  std::to_string(subEq_leftChild_nodestab->stack_Pointer_Location)+"($sp)";
                        }
                        if(!is_global){
                            outfile << "    lw " << temp_regg << "," << temp_source <<"\n";
                            outfile << "    sw " << temp_regg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                        }
                        else{
                            //save this value in the ast of the variable.
                            outfile << "    lw " << temp_regg << "," << temp_source <<"\n";
                            outfile << "    sw " << temp_regg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                        }
                        
                        Register_free(reg);
                        Register_free(temp_regg);
                        outfile.close();
                        return;
                        break;
                    }
                    if(node->ChildrenArray.at(1)->AstNodeType == NodeType::ID){
                        is_expression = true;
                        auto temp_reg1 = Register_allocator(); 
                        std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                        assignment_expression_treversal(node->ChildrenArray.at(1), Out_file_name, temp_reg1,children_reg);
                        source_reg = temp_reg1;
                        Register_free(source_reg);
                        break;
                    }
                    if(a->AstNodeType == NodeType::OPERATOR || a->AstNodeType ==NodeType::UNARY_EXPRESSION){
                        is_expression = true;
                        auto temp_reg1 = Register_allocator(); 
                        std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                        assignment_expression_treversal(a, Out_file_name, temp_reg1,children_reg);
                        source_reg = temp_reg1;
                        Register_free(source_reg);
                        break;
                    }
                    if(a->AstNodeType == NodeType::NUMBEER){
                        value = std::to_string(a->AstIntval);
                        break;
                    }
                    //ToDo: case when we are assigning a voolean type variable. sw $t0,4($sp)
                }
                if(is_expression){
                    if(!is_global){
                        outfile << "    sw " << source_reg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                    }
                    else{
                        outfile << "    sw " << source_reg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                    }
                }else{
                    if(!is_global){
                        outfile << "    li " << reg << "," << value <<"\n";
                        outfile << "    sw " << reg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                    }
                    else{
                        //save this value in the ast of the variable.
                        outfile << "    li " << reg << "," << value <<"\n";
                        outfile << "    sw " << reg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                    }
                }
                Register_free(reg);
            }
            break;
        }
        default: break;
    }
    outfile.close();
}

void Third_iter(AstNode * Rootnode, std::string filename){
    if(Rootnode->ChildrenArray.empty()){
        Third_iter_callbackfunc(Rootnode,filename);
    }
    else{
        generator_scopeStack.push_back(&Rootnode->Node_stab);
        for(auto a : Rootnode->ChildrenArray){
            Third_iter(a,filename);
        }   
        if(!generator_scopeStack.empty()){
            generator_scopeStack.pop_back();
        }
        Third_iter_callbackfunc(Rootnode,filename);
    }
}

//This is the actual function that generates the code on a node enterence. 
void Second_Iter_Calc_NodeEnterence(AstNode * node, std::string Out_file_name){
    std::ofstream outfile;
    if(node->AstNodeType == NodeType::PROGRAM_START_NODE){
        outfile.open(Out_file_name, std::ios_base::trunc);
    }
    else{
        outfile.open(Out_file_name, std::ios_base::app);
    }

    switch (node->AstNodeType)
    {
        case NodeType::PROGRAM_START_NODE: {
            outfile <<   "    .text \n    .globl main \nmain: \n    jal Lable0 \n    li $v0,10 \n    syscall\n\n";
            outfile.close();
            Global_Valriablehandler(node,Out_file_name);
        break;
        }

        case NodeType::MAIN_FNC_DECL: {
            localVariables = 0;
            int memory_ = memory_counter(node);
            std::string ExitLable_ = NewlableGenerator();
            std::string main_function_ID = ""; 
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    main_function_ID = a->AstStringval;
                    break;
                }
            }

            SymbolTable *main_symbol_table = Generator_AstStackLookup(main_function_ID);
            main_symbol_table->Exit_lable_name = ExitLable_;
            main_symbol_table->memory_Size = memory_;

            outfile << "Lable0 : \n    subu $sp,$sp,"<< std::to_string(memory_)<<"\n";
            outfile << "    sw $ra,0($sp)\n";
            outfile.close();
            break;
        }

        // case NodeType::OPERATOR: {
        //     if(node->AstStringval == "="){
        //         auto reg = Register_allocator();
        //         std::string value = ""; 
        //         int VAriableStackLocation = 0;
        //         bool is_global = false;
        //         SymbolTable *variable_symbol_table;
        //         bool is_expression = false;

        //         for(auto a : node->ChildrenArray){
        //             if(a->AstNodeType == NodeType::ID){
        //                 variable_symbol_table = Generator_AstStackLookup(a->AstStringval);
        //                 is_global = variable_symbol_table->isglobalVariable;
        //                 if(!is_global){
        //                     if(variable_symbol_table->stack_Pointer_Location == 0){
        //                         localVariables ++;
        //                         VAriableStackLocation = (4*localVariables);
        //                         variable_symbol_table->stack_Pointer_Location = VAriableStackLocation;
        //                     }else{
        //                         VAriableStackLocation = variable_symbol_table->stack_Pointer_Location;
        //                     }
        //                 }
        //             }
        //             if(node->ChildrenArray.at(1)->AstNodeType == NodeType::ID){
        //                 is_expression = true;
        //                 auto reg = Register_allocator(); 
        //                 std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
        //                 assignment_expression_treversal(node->ChildrenArray.at(1), Out_file_name, reg,children_reg);
        //                 value = reg;
        //                 Register_free(reg);
        //                 break;
        //             }
        //             // Handle variable to variable assignment 
        //             if(a->AstNodeType == NodeType::OPERATOR || a->AstNodeType ==NodeType::UNARY_EXPRESSION){
        //                 is_expression = true;
        //                 auto reg = Register_allocator(); 
        //                 std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
        //                 assignment_expression_treversal(a, Out_file_name, reg,children_reg);
        //                 value = reg;
        //                 Register_free(reg);
        //                 break;
        //             }
        //             if(a->AstNodeType == NodeType::NUMBEER){
        //                 value = std::to_string(a->AstIntval);
        //                 break;
        //             }
        //             //ToDo: case when we are assigning a voolean type variable. sw $t0,4($sp)
        //         }
        //         if(is_expression){
        //             if(!is_global){
        //                 outfile << "    sw " << value << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
        //             }
        //             else{
        //                 outfile << "    sw " << value << "," << variable_symbol_table->Enterence_lable_Name << "\n";
        //             }
        //         }else{
        //             if(!is_global){
        //                 outfile << "    li " << reg << "," << value <<"\n";
        //                 outfile << "    sw " << reg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
        //             }
        //             else{
        //                 //save this value in the ast of the variable.
        //                 outfile << "    li " << reg << "," << value <<"\n";
        //                 outfile << "    sw " << reg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
        //             }
        //         }
                
        //         Register_free(reg);
        //     }
        //     break;
        // }

        case NodeType::FNC_INVOCATION:{
            std::string Function_Identifier = "";
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    Function_Identifier = a->AstStringval;
                    break;
                }
            }
            auto function_decl_table = Generator_AstStackLookup(Function_Identifier);

            if(function_decl_table->is_builtinFunction){
                //this is the case when the function invocation is for the built in prints function. 
                if(function_decl_table->Identifier_Name == "prints"){
                    //generate a lable for the function.
                    std::string lable = NewlableGenerator();
                    std::string printParam = "";
                    for(auto a : node->ChildrenArray){
                        if(a->AstNodeType == NodeType::STRING){
                            printParam = a->AstStringval;
                            break;
                        }
                    }
                    outfile<< "    .data\n";
                    outfile<< lable << " :\n";
                    outfile<< "    .byte ";
                    int stringlen = printParam.size();
                    int counter = 1;
                    for (int i = 0; i < printParam.size(); i++){
                        auto a = printParam[i];
                        if(counter != stringlen && counter != 1){
                            if(a == '\\'){
                                i++;
                                counter++;
                                auto b = printParam[i];
                                switch(b){
                                    case 'b': outfile<< int('\b')<< " ,"; break; 
                                    case 'f': outfile<< int('\f')<< " ,"; break; 
                                    case 't': outfile<< int('\t')<< " ,"; break; 
                                    case 'r': outfile<< int('\r')<< " ,"; break; 
                                    case 'n': outfile<< int('\n')<< " ,"; break; 
                                    case '\'': outfile<< int('\'')<< " ,"; break; 
                                    case '\"': outfile<< int('\"')<< " ,"; break; 
                                    case '\\': outfile<< int('\\')<< " ,"; break; 
                                    default: outfile<< int(b)<< " ,"; break;
                                }
                            }else{
                                outfile<< int(a)<< " ,";
                            }
                            
                        }
                        counter++;
                    }
                    outfile << "0\n";
                    outfile<< "    .align 2\n";
                    outfile<< "    .text\n";

                    auto reg = Register_allocator();
                    outfile<< "    la " << reg << ","<< lable<<"\n";
                    outfile<< "    move "<< "$a0," << reg << "\n";
                    outfile<<"    jal Lprints\n"; 
                    Register_free(reg);
                }
                // li $t0,1
                // move $a0,$t0
                // jal Lprintb
                if(function_decl_table->Identifier_Name == "printb"){
                    auto reg = Register_allocator();
                    // auto lable = boolean_exp_handler();          //Will be done like this later on. 
                    //----Temporary code
                        std::string lable = ""; 
                        for(auto a : node->ChildrenArray){
                            if(a->AstNodeType == NodeType::TRUE){
                                lable = "true";
                                break;
                            }
                            if(a->AstNodeType == NodeType::FALSE){
                                lable = "false";
                                break;
                            }
                        }
                    //----
                    outfile<< "    li " << reg << ","<< lable<<"\n";
                    outfile<< "    move "<< "$a0," << reg << "\n";
                    outfile<<"    jal Lprintb\n"; 
                    Register_free(reg);
                }
                else if(function_decl_table->Identifier_Name == "printi"){
                    if(node->ChildrenArray.at(1)->AstNodeType == NodeType::ID){
                        auto temp_reg = Register_allocator();
                        auto node1_stab = Generator_AstStackLookup(node->ChildrenArray.at(1)->AstStringval);
                        if(node1_stab->isglobalVariable){
                            outfile<< "    lw " << temp_reg << "," << node1_stab->Enterence_lable_Name<<"\n";
                        }else{
                            outfile<< "    lw " << temp_reg << "," << node1_stab->stack_Pointer_Location<<"($sp)"<<"\n";
                        }
                        
                        outfile<< "    move "<< "$a0," << temp_reg << "\n";
                        outfile<<"    jal Lprinti\n"; 
                        Register_free(temp_reg);
                    }
                }
            }
            break;
            
        }
    
        default: break;
    }
    outfile.close();
}

/**
 * @brief This is a preorder treversal of the AST. 
 * 
 * @param Rootnode The root node of the program. 
 * @param filename The name of the output file to be create. 
 */
void Second_iter(AstNode * Rootnode, std::string filename){
    if(Rootnode->ChildrenArray.empty()){
        Second_Iter_Calc_NodeEnterence(Rootnode,filename);
        Second_Iter_Calc_NodeExit(Rootnode,filename);
    }
    else{
        if(Rootnode->AstNodeType == NodeType::OPERATOR && Rootnode->AstStringval=="="){
            Third_iter(Rootnode,filename);
            //Do nothing for children. they will be handled...
        }else{
            Second_Iter_Calc_NodeEnterence(Rootnode,filename);
            generator_scopeStack.push_back(&Rootnode->Node_stab);
            for(auto a : Rootnode->ChildrenArray){
                Second_iter(a,filename);
            } 
            if(!generator_scopeStack.empty()){
                generator_scopeStack.pop_back();
            }
            Second_Iter_Calc_NodeExit(Rootnode,filename);
        }
    }
}


void function_lable_adder(std::string filename){
    std::ofstream outfile;
    outfile.open(filename, std::ios_base::app);
    outfile<< "\nLprints: \n    li	$v0, 4\n    syscall\n    jr $ra\n\n" ;
    outfile<< "Lprintb: \n    li	$v0, 1\n    syscall\n    jr $ra\n\n" ;  //needs to be reimplemented.
    outfile<< "Lprintc: \n    li	$v0, 11\n    syscall\n    jr $ra\n\n" ;
    outfile<< "Lprinti: \n    li	$v0, 1\n    syscall\n    jr $ra\n\n" ;

    outfile.close();
}

// This is the deriver function that is called to do the code generation by the deriver. 
void Code_generator::code_generator_driver(AstNode* RootNode){
    std::cout<<"---------"<<std::endl; 
    std::cout<<"number of Registers free initially : " <<Regester_Stack.size()<<std::endl;
    std::unordered_map<std::string, SymbolTable> Node_stab = {};

    SymbolTable getChar_table;
    getChar_table.Identifier_Name = "getchar";
    getChar_table.ReturnType = "INT";
    getChar_table.Enterence_lable_Name = "Lgetchar";
    getChar_table.is_builtinFunction = true;

    SymbolTable halt_table;
    halt_table.Identifier_Name = "halt";
    halt_table.ReturnType = "VOID";
    halt_table.Enterence_lable_Name = "Lhalt";
    halt_table.is_builtinFunction = true;

    SymbolTable printb_table;
    printb_table.Identifier_Name = "printb";
    printb_table.ReturnType = "VOID";
    printb_table.Formals.push_back("BOOLEAN");
    printb_table.Enterence_lable_Name = "Lprintb";
    printb_table.is_builtinFunction = true;

    SymbolTable printc_table;
    printc_table.Identifier_Name = "printc";
    printc_table.ReturnType = "VOID";
    printc_table.Formals.push_back("INT");
    printc_table.Enterence_lable_Name = "Lprintc";
    printc_table.is_builtinFunction = true;

    SymbolTable printi_table;
    printi_table.Identifier_Name = "printi";
    printi_table.ReturnType = "VOID";
    printi_table.Formals.push_back("INT");
    printi_table.Enterence_lable_Name = "Lprinti";
    printi_table.is_builtinFunction = true;

    SymbolTable prints_table;
    prints_table.Identifier_Name = "prints";
    prints_table.ReturnType = "VOID";
    prints_table.Formals.push_back("STRING");
    prints_table.Enterence_lable_Name = "Lprints";
    prints_table.is_builtinFunction = true;

    Node_stab.insert({getChar_table.Identifier_Name,getChar_table});
    Node_stab.insert({"halt",halt_table});
    Node_stab.insert({printb_table.Identifier_Name,printb_table});
    Node_stab.insert({printc_table.Identifier_Name,printc_table});
    Node_stab.insert({printi_table.Identifier_Name,printi_table});
    Node_stab.insert({prints_table.Identifier_Name,prints_table});

    generator_scopeStack.push_back(&Node_stab);

    std::string Out_file_name = "My_file.s";
    First_iter(RootNode,Out_file_name);
    Second_iter(RootNode,Out_file_name);
    function_lable_adder(Out_file_name);

    std::cout<<"number of Registers free : " <<Regester_Stack.size()<<std::endl;
}