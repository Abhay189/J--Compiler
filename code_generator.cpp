#include "code_generator.hpp"
#include <vector>
#include "ast.hpp"
#include <iostream>
#include <string>

int counter = 0;

std::string NewlableGenerator(){
    std::string str = std::to_string(counter);
    counter++;
    return "Lable" + str;
}

std::string Code_generator::Register_allocator(){
    if(!Code_generator::Regester_Stack.empty()){
        return Code_generator::Regester_Stack.back();
    }
    else{
        "Error : Over complex expression. Out of regesters !";
    }
    return "";
}

void Code_generator::Register_free(std::string reg){
    Code_generator::Regester_Stack.push_back(reg);
}

void Code_generator::First_iter(AstNode * Rootnode){
    for(auto a : Rootnode->ChildrenArray){
        auto Lable = NewlableGenerator();
        SymbolTable LableST;
        LableST.Name = Lable;
        a->Node_stab.insert({"Lable", LableST});
    }
}


void Code_generator::code_generator_driver(AstNode* RootNode){
    std::cout<<"---------"<<std::endl;
    First_iter(RootNode);
 
    for(auto a : RootNode->ChildrenArray){
        auto pp = a->Node_stab.at("Lable");
        std::cout<<pp.Name<<std::endl;
    }
}

