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
 
}
;

#endif