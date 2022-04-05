#include "code_generator.hpp"
#include <vector>
#include "ast.hpp"
#include <iostream>
#include <string>
#include <fstream>

int counter = 1;
std::vector<std::string> Regester_Stack { "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6" ,"$t7" ,"$t8", "$t9", "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",};
int stack_pointer = 0;

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

void First_iter(AstNode * Rootnode){
    for(auto a : Rootnode->ChildrenArray){
        if(a->AstNodeType != NodeType::MAIN_FNC_DECL){
            auto Lable = NewlableGenerator();
            SymbolTable LableST;
            LableST.Enterence_lable_Name = Lable;
            a->Node_stab.insert({"Entry_Lable", LableST});
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
            int memory_ = node->Node_stab.at("Memory").memory_Size; 
            std::string lable = node->Node_stab.at("Exit_Lable").Exit_lable_name;
            outfile << lable << " : \n" ;
            outfile << "    lw $ra,0($sp)\n";
            outfile << "    addu $sp,$sp,"<< memory_ <<"\n" ;
            outfile<< "    jr $ra\n";
            std::cout<<memory_<<std::endl;
            break;
        }
    }
    outfile.close();
}

// void Tree_sub_treversal_func(AstNode * node, std::string fileName){
//     std::ofstream outfile;
//     outfile.open(fileName, std::ios_base::app); // append instead of overwrite

//     switch (node->AstNodeType){
        
//     }
//     outfile.close();
// }

// void Tree_sub_treversal(AstNode * node, std::string fileName){
//     if(node->ChildrenArray.empty()){
//         Tree_sub_treversal_func(node,fileName);
//     }
//     else{
//         Tree_sub_treversal_func(node,fileName);
//         for(auto a : node->ChildrenArray){
//             Tree_sub_treversal(a,fileName);
//         }
//     }
// }

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
        break;
        }
        case NodeType::MAIN_FNC_DECL: {
            int memory_ = memory_counter(node);
            std::string ExitLable_ = NewlableGenerator();
            
            SymbolTable ExitLable;
            ExitLable.Exit_lable_name = ExitLable_;

            SymbolTable memory;
            memory.memory_Size = memory_;
            
            node->Node_stab.insert({"Exit_Lable",ExitLable});
            node->Node_stab.insert({"Memory",memory});
            outfile << "Lable0 : \n    subu $sp,$sp,"<< std::to_string(memory_)<<"\n";
            outfile << "    sw $ra,0($sp)\n";
            outfile.close();
            break;
        }
        case NodeType::OPERATOR: {
            if(node->AstStringval == "="){
                auto reg = Register_allocator();
                std::string value; 

                for(auto a : node->ChildrenArray){
                    if(a->AstNodeType == NodeType::NUMBEER){
                        value = std::to_string(a->AstIntval);
                        std::cout<<value<<std::endl;
                        break;
                    }
                    //ToDo: case when we are assigning a voolean type variable. sw $t0,4($sp)
                }
                outfile << "    li " << reg << "," << value <<"\n";
                outfile << "    sw " << reg << "," ; // To do: create a scope stack for variable identification. 
            }
        }
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
        Second_Iter_Calc_NodeEnterence(Rootnode,filename);
        for(auto a : Rootnode->ChildrenArray){
            Second_iter(a,filename);
        }   
        Second_Iter_Calc_NodeExit(Rootnode,filename);
    }
}

// This is the deriver function that is called to do the code generation by the deriver. 
void Code_generator::code_generator_driver(AstNode* RootNode){
    std::cout<<"---------"<<std::endl;
    First_iter(RootNode);
    std::string Out_file_name = "My_file.s";
    Second_iter(RootNode,Out_file_name);
}