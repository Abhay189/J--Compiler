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
    std::vector<std::string> Children_regester;
    bool is_already_seen = false;
    //------

    //------Things needed for semantic analysis. 
    std::string Identifier_Name = "";

    //----Just for functions : 
    std::string ReturnType = "";
    std::vector<std::string> Formals; 
    bool is_builtinFunction = false;

    //-----For variables :
    std::string Var_type = "";
    bool isglobalVariable = false;
    int Var_Int_value = 0;
    bool Var_Bool_Value;

    //------For identifying main function
    bool isMainFunction = false;

    //------For if statements : 
    std::string If_statement_exit_lable = "";



}
;
#endif