#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include<string>
#include<vector>

class SymbolTable{
    public: 
    //--These are things needed for code generation. 
    std::string Enterence_lable_Name = ""; 
    std::string Exit_lable_name = "";
    int memory_Size = 0;
    int stack_Pointer_Location = 0;
    int local_variables = 0;
    //------

    //------Things needed for semantic analysis. 
    std::string Identifier_Name = "";

    //----Just for functions : 
    std::string ReturnType = "";
    std::vector<std::string> Formals; 

    //-----For variables :
    std::string Var_type = "";

    //------For identifying main function
    bool isMainFunction = false;

}
;
#endif