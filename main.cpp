#include <cstdlib>
#include <cerrno>
#include <cstring>

#include "driver.hpp"


/**
 * @brief this is the main function that calls the driver to make the parser and the scannar. and also do the code geneartion. 
 * 
 * @param argc 
 * @param argv The executable needs to be called with the input file. 
 * @return int 
 */
int main(int argc, char **argv) {

    Driver *driver;
    std::istream *input = &std::cin;

    std::ifstream file;
    
    if (argc == 2)
    {
        file.open(argv[1]);

        if (!file.good())
        {
            std::cerr << "Error: " << strerror(errno) << "\n";
            return EXIT_FAILURE;
        }

        input = &file;
    }

    if (argc == 2) {
        driver = new Driver(argv[1]);
        } 
    else{
        std::cerr<<"Error: No input File provided \n";
        exit(EXIT_FAILURE);
        } 
    bool res = driver->start(*input);
    
    if (file.is_open()) file.close();

    return res;
}