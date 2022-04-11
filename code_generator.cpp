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
std::string Current_function_identifier = "";
std::vector<std::string> if_statements_exit_lable_stack;
std::vector<std::string> else_statement_lable_stack ;
std::vector<std::string> while_statement_exit_lable_stack;
std::vector<std::string> while_statement_entry_lable_stack;

//For lookup of any identifier.
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

//For lookup of a function identifier 
SymbolTable* Generator_Function_AstStackLookup(std::string identifier){
    std::unordered_map<std::string, SymbolTable> * temp;

    for (auto it =  generator_scopeStack.rbegin(); it != generator_scopeStack.rend(); ++it){
        temp = *it;
        if(temp->count(identifier) == 1){
            if(temp->at(identifier).ReturnType != ""){
                return &temp->at(identifier);
            }
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
        std::cerr<<"Error : Over complex expression. Out of regesters !\n";
        exit(EXIT_FAILURE);
    }
    return "";
}

void Register_free(std::string reg){
    Regester_Stack.push_back(reg);
}

void Global_Valriablehandler(AstNode * RootNode,std::string Out_file_name){
    // std::ofstream std::cout;
    // std::cout.open(Out_file_name, std::ios_base::app);
    for(auto a : RootNode->ChildrenArray){
        switch(a->AstNodeType){
            case NodeType::VAR_DECL:{
                RootNode->Node_stab.at(a->ChildrenArray[1]->AstStringval).isglobalVariable = true;
                std::cout << "    .data\n";
                std::cout<< RootNode->Node_stab.at(a->ChildrenArray[1]->AstStringval).Enterence_lable_Name << " :\n";
                std::cout<< "    .word 0\n";
                std::cout<< "    .text\n";
                break;
            }
        }
    }
}

void arithmaticExpressionHandler(AstNode * node, std::string Out_file_name,std::string allocated_reg, std::vector<std::string> children_reg){
    // std::ofstream std::cout;
    // std::cout.open(Out_file_name, std::ios_base::app);
    switch(node->AstNodeType){
        case NodeType::NUMBEER:{
            std::cout << "    li "<< allocated_reg << "," <<node->AstIntval<<"\n";
            break;
        }

        case NodeType::OPERATOR:{
            if(node->AstStringval == "+"){
                std::cout << "    addu "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "*"){
                std::cout << "    mul "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "-"){
                std::cout << "    subu "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "/"){
                auto devision_lable = NewlableGenerator();
                auto error_lable = NewlableGenerator();
                std::cout << "    bnez "<<children_reg.at(0)<< "," <<devision_lable <<"\n";
                std::cout << "    .data\n";
                std::cout << error_lable << " :\n";
                std::cout << "    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0\n";
                std::cout << "    .align 2\n";
                std::cout << "    .text\n";
                std::cout << "    la $a0,"<<error_lable<<"\n";
                std::cout << "    j error\n";

                std::cout << devision_lable << " :\n";
                std::cout << "    div "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "%"){
                auto devision_lable = NewlableGenerator();
                auto error_lable = NewlableGenerator();
                std::cout << "    bnez "<<children_reg.at(0)<< "," <<devision_lable <<"\n";
                std::cout << "    .data\n";
                std::cout << error_lable << " :\n";
                std::cout << "    .byte  100 , 105 , 118 , 105 , 115 , 105 , 111 , 110 , 32 , 98 , 121 , 32 , 122 , 101 , 114 , 111 , 0\n";
                std::cout << "    .align 2\n";
                std::cout << "    .text\n";
                std::cout << "    la $a0,"<<error_lable<<"\n";
                std::cout << "    j error\n";

                std::cout << devision_lable << " :\n";
                std::cout << "    rem "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == ">"){
                std::cout << "    sgt "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "<"){
                std::cout << "    slt "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "<="){
                std::cout << "    sle "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == ">="){
                std::cout << "    sge "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "=="){
                std::cout << "    seq "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "!="){
                std::cout << "    sne "<< allocated_reg << "," <<children_reg.at(1)<<"," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
            }
            else if(node->AstStringval == "||"){
                auto Node_exit_lable = NewlableGenerator();
                std::cout<< "    move "<< allocated_reg<<","<<children_reg.at(0)<<"\n" ;
                std::cout<< "    beqz "<< children_reg.at(1) << "," << Node_exit_lable << "\n";
                std::cout<< "    move "<< allocated_reg<<","<<children_reg.at(1)<<"\n" ;
                for(auto a : children_reg){
                    Register_free(a);
                }
                std::cout<< Node_exit_lable <<" :\n";
            }
            else if(node->AstStringval == "&&"){
                auto Node_exit_lable = NewlableGenerator();
                std::cout<< "    move "<< allocated_reg<<","<<children_reg.at(0)<<"\n" ;
                std::cout<< "    beqz "<< allocated_reg << "," << Node_exit_lable << "\n";
                std::cout<< "    move "<< allocated_reg<<","<<children_reg.at(1)<<"\n" ;
                std::cout<< "    beqz "<< allocated_reg << "," << Node_exit_lable << "\n";
                for(auto a : children_reg){
                    Register_free(a);
                }
                std::cout<< Node_exit_lable <<" :\n";
            }
            
            break;
        }

        case NodeType::UNARY_EXPRESSION:{
            if(node->AstStringval == "-"){
                std::cout << "    negu "<< allocated_reg << "," <<children_reg.at(0)<<"\n";
                for(auto a : children_reg){
                        Register_free(a);
                    }
            }
            else if(node->AstStringval == "!"){
                std::cout << "    xori "<< allocated_reg << "," <<children_reg.at(0)<< ",1" <<"\n";
                for(auto a : children_reg){
                        Register_free(a);
                    }
            }
            
            break;
        }
        //this is the case of a variable.
        case NodeType::ID:{
            auto node_stab = Generator_AstStackLookup(node->AstStringval);
            //This if statement makes sure that this identifier is not a part of a function invocation. 
            if(node_stab->ReturnType == ""){
                if(node_stab->isglobalVariable){
                    std::cout << "    lw "<< allocated_reg << "," <<node_stab->Enterence_lable_Name<<"\n";
                }else{
                    std::cout << "    lw "<< allocated_reg << "," <<node_stab->stack_Pointer_Location<<"($sp)"<<"\n";
                }
            }
            
            
            break;
        }
        
        case NodeType::TRUE:{
            std::cout << "    li "<< allocated_reg << "," <<"1"<<"\n";
            break;
        }

        case NodeType::FALSE:{
            std::cout << "    li "<< allocated_reg << "," <<"0"<<"\n";
            break;
        }



        default: std::cout<<"a case not handled in arithmatic expressions  \n";
    }
    // std::cout.close();
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
                returnnum++;
            }
        }
    }
    stack_pointer += (returnnum * 4);
    return returnnum * 4;
}

void Second_Iter_Calc_NodeExit(AstNode * node, std::string Out_file_name){
    // std::ofstream std::cout;
    // std::cout.open(Out_file_name, std::ios_base::app);
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
            std::cout << lable << " : \n" ;
            std::cout << "    lw $ra,0($sp)\n";
            std::cout << "    addu $sp,$sp,"<< memory_ <<"\n" ;
            std::cout<< "    jr $ra\n";
            break;
        }
        case NodeType::FNC_DECL: {
            std::string function_ID;
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    function_ID = a->AstStringval;
                    break;
                }
            }

            SymbolTable *Function_symbol_table = Generator_AstStackLookup(function_ID);
            int memory_ = Function_symbol_table->memory_Size;
            std::string lable = Function_symbol_table->Exit_lable_name;
            std::cout << lable << " : \n" ;
            std::cout << "    lw $ra,0($sp)\n";
            std::cout << "    addu $sp,$sp,"<< memory_ <<"\n" ;
            std::cout<< "    jr $ra\n";
            break;
        }
        case NodeType::IF_STATEMENT: {
            auto if_statement_exit_lable = if_statements_exit_lable_stack.back();
            std::cout<< if_statement_exit_lable<< " :\n";
            if_statements_exit_lable_stack.pop_back(); 
            break;
        }
        case NodeType::WHILE_STATEMENT:{
            auto while_statement_entry_lable = while_statement_entry_lable_stack.back();
            auto while_statement_exit_lable = while_statement_exit_lable_stack.back();
            std::cout<<"    j "<<while_statement_entry_lable<<"\n";
            std::cout<<while_statement_exit_lable<<" :\n";
            while_statement_entry_lable_stack.pop_back();
            while_statement_exit_lable_stack.pop_back();
        }
    }
    // std::cout.close();
}

void Third_iter_callbackfunc(AstNode * node, std::string Out_file_name){
    // std::ofstream std::cout;
    // std::cout.open(Out_file_name, std::ios_base::app);
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
                            std::cout << "    lw " << temp_regg << "," << temp_source <<"\n";
                            std::cout << "    sw " << temp_regg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                        }
                        else{
                            //save this value in the ast of the variable.
                            std::cout << "    lw " << temp_regg << "," << temp_source <<"\n";
                            std::cout << "    sw " << temp_regg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                        }
                        
                        Register_free(reg);
                        Register_free(temp_regg);
                        // std::cout.close();
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
                    if(a->AstNodeType == NodeType::TRUE){
                        value = "1";
                        break;
                    }
                    if(a->AstNodeType == NodeType::FALSE){
                        value = "0";
                        break;
                    }
                    if(a->AstNodeType == NodeType::FNC_INVOCATION){
                        // move $t0,$v0
                        // sw $t0,4($sp)
                        auto local_Var = Register_allocator();
                        std::cout << "    move " << local_Var << ","<<"$v0\n";
                        if(is_global){
                            std::cout << "    sw " << variable_symbol_table->Enterence_lable_Name << ","<<"$v0\n";
                        }
                        else{
                            std::cout << "    sw " << local_Var << "," << std::to_string(variable_symbol_table->stack_Pointer_Location)<<"($sp)\n";

                        }
                        Register_free(local_Var);
                        Register_free(reg);
                        return;
                    }
                    //ToDo: case when we are assigning a boolean type variable. sw $t0,4($sp)
                }
                if(is_expression){
                    if(!is_global){
                        std::cout << "    sw " << source_reg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                    }
                    else{
                        std::cout << "    sw " << source_reg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                    }
                }else{
                    if(!is_global){
                        std::cout << "    li " << reg << "," << value <<"\n";
                        std::cout << "    sw " << reg << "," << VAriableStackLocation<<"($sp)\n"; // To do: create a scope stack for variable identification. 
                    }
                    else{
                        //save this value in the ast of the variable.
                        std::cout << "    li " << reg << "," << value <<"\n";
                        std::cout << "    sw " << reg << "," << variable_symbol_table->Enterence_lable_Name << "\n";
                    }
                }
                Register_free(reg);
            }
            break;
        }
        
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
                    std::cout<< "    .data\n";
                    std::cout<< lable << " :\n";
                    std::cout<< "    .byte ";
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
                                    case 'b': std::cout<< int('\b')<< " ,"; break; 
                                    case 'f': std::cout<< int('\f')<< " ,"; break; 
                                    case 't': std::cout<< int('\t')<< " ,"; break; 
                                    case 'r': std::cout<< int('\r')<< " ,"; break; 
                                    case 'n': std::cout<< int('\n')<< " ,"; break; 
                                    case '\'': std::cout<< int('\'')<< " ,"; break; 
                                    case '\"': std::cout<< int('\"')<< " ,"; break; 
                                    case '\\': std::cout<< int('\\')<< " ,"; break; 
                                    default: std::cout<< int(b)<< " ,"; break;
                                }
                            }else{
                                std::cout<< int(a)<< " ,";
                            }
                            
                        }
                        counter++;
                    }
                    std::cout << "0\n";
                    std::cout<< "    .align 2\n";
                    std::cout<< "    .text\n";

                    auto reg = Register_allocator();
                    std::cout<< "    la " << reg << ","<< lable<<"\n";
                    std::cout<< "    move "<< "$a0," << reg << "\n";
                    std::cout<<"    jal Lprints\n"; 
                    Register_free(reg);
                }
                // li $t0,1
                // move $a0,$t0
                // jal Lprintb
                else if(function_decl_table->Identifier_Name == "printb"){
                    auto reg = Register_allocator();
                    // auto lable = boolean_exp_handler();          //Will be done like this later on. 
                    //----Temporary code
                        std::string lable = "";
                        bool flag = false;
                        int cou = 0; 
                        for(auto a : node->ChildrenArray){
                            if(cou == 0){
                                cou++;
                                continue;
                            }
                            if(a->AstNodeType == NodeType::ID){
                                auto temp_reg = Register_allocator();
                                auto node1_stab = Generator_AstStackLookup(a->AstStringval);
                                if(node1_stab->isglobalVariable){
                                    std::cout<< "    lw " << temp_reg << "," << node1_stab->Enterence_lable_Name<<"\n";
                                }else{
                                    std::cout<< "    lw " << temp_reg << "," << node1_stab->stack_Pointer_Location<<"($sp)"<<"\n";
                                }
                                
                                std::cout<< "    move "<< "$a0," << temp_reg << "\n";
                                Register_free(temp_reg);
                                flag = true;

                            }
                            if(a->AstNodeType == NodeType::TRUE){
                                lable = "1";
                                break;
                            }
                            if(a->AstNodeType == NodeType::FALSE){
                                lable = "0";
                                break;
                            }
                            cou++;
                        }
                    //----
                    if(!flag){
                        std::cout<< "    li " << reg << ","<< lable<<"\n";
                        std::cout<< "    move "<< "$a0," << reg << "\n";
                    }
                    
                    
                    std::cout<< "    jal Lprintb\n"; 
                    Register_free(reg);
                }
                else if(function_decl_table->Identifier_Name == "getchar"){
                    std::cout<<"    jal Lgetchar\n";
                }
                else if(function_decl_table->Identifier_Name == "printc"){
                    if(node->ChildrenArray.at(1)->AstNodeType == NodeType::ID){
                        auto temp_reg = Register_allocator();
                        auto node1_stab = Generator_AstStackLookup(node->ChildrenArray.at(1)->AstStringval);
                        if(node1_stab->isglobalVariable){
                            std::cout<< "    lw " << temp_reg << "," << node1_stab->Enterence_lable_Name<<"\n";
                        }else{
                            std::cout<< "    lw " << temp_reg << "," << node1_stab->stack_Pointer_Location<<"($sp)"<<"\n";
                        }
                        
                        std::cout<< "    move "<< "$a0," << temp_reg << "\n";
                        std::cout<<"    jal Lprintc\n"; 
                        Register_free(temp_reg);
                    }
                }
                else if(function_decl_table->Identifier_Name == "printi"){
                    auto source_reg = Register_allocator();
                    auto temp_reg1 = Register_allocator(); 
                    std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                    assignment_expression_treversal(node->ChildrenArray.at(1), Out_file_name, temp_reg1,children_reg);
                    source_reg = temp_reg1;
                    Register_free(temp_reg1);
                    Register_free(source_reg);
                    std::cout<< "    move "<< "$a0," << source_reg << "\n";
                    std::cout<<"    jal Lprinti\n"; 
                }
            }else{
                // li $t0,89
                // move $a0,$t0
                // jal L1
                // move $t0,$v0
                int counter = -1;

                for(auto a : node->ChildrenArray){
                    if(counter == -1){
                        counter++;
                        continue;
                    }
                    else if(a->AstNodeType == NodeType::NUMBEER){
                        auto temp_reg = Register_allocator();
                        std::cout << "    li " << temp_reg << ","<< a->AstIntval<<"\n";
                        std::cout << "    move " << "$a"<< counter << ","<<temp_reg << "\n";
                        Register_free(temp_reg);
                    }
                    else if (a->AstNodeType == NodeType::ID){
                        auto Identifiername = a->AstStringval;
                        auto identifier_nodestab = Generator_AstStackLookup(Identifiername);
                        auto temp_reg = Register_allocator();
                        if(identifier_nodestab->isglobalVariable){
                            std::cout << "    lw " << temp_reg << ","<< identifier_nodestab->Enterence_lable_Name<<"\n";
                            std::cout << "    move " << "$a"<< counter << ","<<temp_reg << "\n";
                        }else{
                            std::cout << "    lw " << temp_reg << ","<< identifier_nodestab->stack_Pointer_Location<<"($sp)\n";
                            std::cout << "    move " << "$a"<< counter << ","<<temp_reg << "\n";
                        
                        }
                        Register_free(temp_reg);
                    }
                    else if (a->AstNodeType == NodeType::FNC_INVOCATION){   //have to re implement this 
                        auto temp_reg = Register_allocator();
                        std::cout << "    move " << temp_reg << ","<< "$v0"<<"\n";
                        std::cout << "    move " << "$a"<< counter << ","<<temp_reg << "\n";
                        Register_free(temp_reg);
                    }
                    counter++;
                }

                std::cout << "    jal "<<function_decl_table->Enterence_lable_Name<<"\n";

            }
            break;
            
        }

        default: break;
    }
    // std::cout.close();
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
    // std::ofstream std::cout;
    // if(node->AstNodeType == NodeType::PROGRAM_START_NODE){
    //     std::cout.open(Out_file_name, std::ios_base::trunc);
    // }
    // else{
    //     std::cout.open(Out_file_name, std::ios_base::app);
    // }

    switch (node->AstNodeType)
    {
        case NodeType::PROGRAM_START_NODE: {
            std::cout <<   "    .text \n    .globl main \nmain: \n    jal Lable0 \n    li $v0,10 \n    syscall\n\n";
            // std::cout.close();
            Global_Valriablehandler(node,Out_file_name);
        break;
        }

        case NodeType::MAIN_FNC_DECL: {
            localVariables = 0;
            stack_pointer = 0; //first randome change .
            int memory_ = memory_counter(node);
            std::string ExitLable_ = NewlableGenerator();
            std::string main_function_ID = ""; 
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    main_function_ID = a->AstStringval;
                    break;
                }
            }
            Current_function_identifier = main_function_ID;

            SymbolTable *main_symbol_table = Generator_AstStackLookup(main_function_ID);
            main_symbol_table->Exit_lable_name = ExitLable_;
            main_symbol_table->memory_Size = memory_;

            std::cout << "Lable0 : \n    subu $sp,$sp,"<< std::to_string(memory_)<<"\n";
            std::cout << "    sw $ra,0($sp)\n";
            // std::cout.close();
            break;
        }
    
        case NodeType::FNC_DECL:{
            localVariables = 0;
            stack_pointer = 0; 
            int memory_ = memory_counter(node);
            std::string ExitLable_ = NewlableGenerator();
            
            std::string function_ID = ""; 
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ID){
                    function_ID = a->AstStringval;
                    break;
                }
            }
            Current_function_identifier = function_ID;
            SymbolTable *funct_symbol_table = Generator_AstStackLookup(function_ID);
            funct_symbol_table->Exit_lable_name = ExitLable_;
            funct_symbol_table->memory_Size = memory_;

            std::cout << funct_symbol_table->Enterence_lable_Name <<" : \n    subu $sp,$sp,"<< std::to_string(memory_)<<"\n";
            std::cout << "    sw $ra,0($sp)\n";
            // std::cout.close();
            break;
        }
    
        case NodeType::FORMALS_List:{
            int c = 0;
            for(auto a: node->ChildrenArray){
                auto var_Identifier = a->ChildrenArray.at(1)->AstStringval;
                auto variable_symbol_table = Generator_AstStackLookup(var_Identifier);
                auto VAriableStackLocation = variable_symbol_table->stack_Pointer_Location;
                if(variable_symbol_table->stack_Pointer_Location == 0){
                    localVariables ++;
                    VAriableStackLocation = (4*localVariables);
                    variable_symbol_table->stack_Pointer_Location = VAriableStackLocation;
                }else{
                    VAriableStackLocation = variable_symbol_table->stack_Pointer_Location;
                }
                // sw $a0,4($sp)
                // sw $a1,8($sp)
                std::cout << "    sw $a"<< std::to_string(c) <<","<< VAriableStackLocation <<"($sp)\n";
                c++;
            }
            break;
        }

        case NodeType::RETURN:{
            // std::cout<<"return startes herer \n";
            //My current function identifier is inside the global variable Current_function_identifier. 
            //Use this variable to lookup for the stack pointer to the function and use that for return. 
            
            //This is the stab of the function that the return statement is inside.
            auto Function_stab = Generator_Function_AstStackLookup(Current_function_identifier);
            auto Function_Enterence_lable = Function_stab->Enterence_lable_Name;
            auto Function_Exit_lable = Function_stab->Exit_lable_name;

            // li $t0,89
            // move $v0,$t0
            // j L2
            if(!node->ChildrenArray.empty()){
                auto source_reg = Register_allocator();
                auto temp_reg1 = Register_allocator(); 
                std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                assignment_expression_treversal(node->ChildrenArray.at(0), Out_file_name, temp_reg1,children_reg);
                source_reg = temp_reg1;
                Register_free(temp_reg1);
                Register_free(source_reg);
                std::cout<< "    move "<< "$v0," << source_reg << "\n";
            }
            std::cout<<"    j " << Function_Exit_lable<< "\n"; 
            

            // to be implemented 
            
            break;
        }

        case NodeType::IF_STATEMENT:{
            bool contain_else = false ;
            for(auto a : node->ChildrenArray){
                if(a->AstNodeType == NodeType::ELSE_STATEMENT){
                    contain_else = true;
                }
            }
            if(!contain_else){
                auto if_statement_end_Lable = NewlableGenerator();
                if_statements_exit_lable_stack.push_back(if_statement_end_Lable);
                auto temp_reg1 = Register_allocator(); 
                std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                assignment_expression_treversal(node->ChildrenArray.at(0), Out_file_name, temp_reg1,children_reg);
                Register_free(temp_reg1);
                std::cout<< "    beqz "<< temp_reg1<<","<< if_statement_end_Lable<< "\n";
            }else{
                auto if_statement_end_Lable = NewlableGenerator();
                auto else_statement_end_lable = NewlableGenerator();
                else_statement_lable_stack.push_back(else_statement_end_lable);
                if_statements_exit_lable_stack.push_back(if_statement_end_Lable);
                auto temp_reg1 = Register_allocator(); 
                std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
                assignment_expression_treversal(node->ChildrenArray.at(0), Out_file_name, temp_reg1,children_reg);
                Register_free(temp_reg1);
                std::cout<< "    beqz "<< temp_reg1<<","<< else_statement_end_lable<< "\n";
            }
            break;
        }

        case NodeType::ELSE_STATEMENT:{
            auto if_exit_lable = if_statements_exit_lable_stack.back();
            auto else_exit_Lable = else_statement_lable_stack.back();
            std::cout<< "    j "<< if_exit_lable<< "\n";
            std::cout<< else_exit_Lable<<" :\n";
            if(!else_statement_lable_stack.empty()){
                else_statement_lable_stack.pop_back();
            }
            break;
        }
        
        case NodeType::WHILE_STATEMENT:{
            auto while_statement_entry_Lable = NewlableGenerator();
            auto while_statement_exit_lable = NewlableGenerator();
            while_statement_entry_lable_stack.push_back(while_statement_entry_Lable);
            while_statement_exit_lable_stack.push_back(while_statement_exit_lable);
            std::cout<<while_statement_entry_Lable<<" :\n";
            // std::cout.close();
            auto temp_reg1 = Register_allocator(); 
            std::vector<std::string> children_reg;  //this is just to pass inside the function, it does not do anything.
            assignment_expression_treversal(node->ChildrenArray.at(0), Out_file_name, temp_reg1,children_reg);
            Register_free(temp_reg1);
            // outfile.open(Out_file_name, std::ios_base::app);
            std::cout<< "    beqz "<< temp_reg1<<","<< while_statement_exit_lable<< "\n";
            break;
        }

        case NodeType::BREAK: {
            auto while_break_lable = while_statement_exit_lable_stack.back();
            std::cout<< "    j "<< while_break_lable << "\n";
            break;
        }

        default: break;
    }
    // std::cout.close();
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
        }
        else if(Rootnode->AstNodeType == NodeType::FNC_INVOCATION){
            Third_iter(Rootnode,filename);
        }
        else{
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
    // std::ofstream std::cout;
    // std::cout.open(filename, std::ios_base::app);
    std::cout<< "\nLprints: \n    li	$v0, 4\n    syscall\n    jr $ra\n\n" ;
    std::cout << "    .data\nLTrue : \n    .byte 116 ,114 ,117 ,101 ,0\n    .align 2\n    .text\n    .data\nLFalse : \n    .byte 102 ,97 ,108 ,115 ,101 ,0\n    .align 2\n    .text\nLprintb: \n    li $t0,0\n    li $t1,1\n    beq $a0,$t0,LFal\n    beq $a0,$t1,LTru\n    jr $ra\nLFal: \n    la $t0,LFalse\n    move $a0,$t0\n    li	$v0, 4\n    syscall\n    jr $ra\nLTru: \n    la $t0,LTrue\n    move $a0,$t0\n    li	$v0, 4\n    syscall\n    jr $ra \n\n";
    std::cout<< "Lprintc: \n    li	$v0, 11\n    syscall\n    jr $ra\n\n" ;
    std::cout<< "Lprinti: \n    li	$v0, 1\n    syscall\n    jr $ra\n\n" ;
    std::cout << "Lgetchar:\n    li $v0, 12\n    syscall\n    jr $ra\n\n";
    std::cout << "error:\n    li $v0, 4\n    syscall\n    li $v0, 10\n    syscall\n\n";

    // std::cout.close();
}

// This is the deriver function that is called to do the code generation by the deriver. 
void Code_generator::code_generator_driver(AstNode* RootNode){
    // std::cout<<"---------"<<std::endl; 
    // std::cout<<"number of Registers free initially : " <<Regester_Stack.size()<<std::endl;
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

    // std::cout<<"number of Registers free : " <<Regester_Stack.size()<<std::endl;
}