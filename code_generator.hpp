#ifndef CODE_GEN
#define CODE_GEN

#include<string>
#include<vector>
#include"ast.hpp"
#include <fstream>

class Code_generator{
    public:
    std::string out_fileName = "Myfile.s";

    void code_generator_driver(AstNode * Rootnode);

    std::vector<std::string> Regester_Stack { "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6" ,"$t7" ,"$t8", "$t9", "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",};

    std::string Register_allocator();

    void Register_free(std::string reg);

    /**
     * @brief This program takes in the root node of the AST tree as the Parameter and goes over the global function declaraions,
     * main declerations, variable declerations and generate lables for them. 
     * These lables are then added to the symbol table of those nodes so that we have their lables in
     * the second traversals. 
     * 
     * @param RootNode -> put in the Ast structures Rootnode into this function. 
     */
    void First_iter(AstNode * RootNode);

    void Second_iter(AstNode * RootNode,  std::string out_finename);

}
;

#endif