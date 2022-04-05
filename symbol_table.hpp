#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include<string>

class SymbolTable{
    public: 
    std::string Enterence_lable_Name = ""; 
    std::string Exit_lable_name = "";
    int memory_Size = 0;
    int stack_Pointer_Location = 0;
}
;
#endif