#include <iostream>
#include <string>


#include "../include/read_file.h"
#include "../include/PDA.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./min_PDA <input_file>\n";
        return 1;
    }
    const std::string input_p = argv[1];
    std::string input_str = argv[2];
    PDA PDA = read_file(input_p);
    // std::cout << "test for print: " << std::endl;
    // PDA.print_PDA();
    // std::cout << "test for delete_unreachable: " << std::endl;
    // PDA.delete_unreachable();
    // PDA.print_PDA();
    // std::cout << "test for trans_func: " << std::endl;
    // std::cout << PDA.trans_func("q1", "a") << std::endl;
    // std::cout << "test for minimize: " << std::endl;
    // PDA.minimize();
    // PDA.print_PDA();
    // std::cout << "test for out_file: " << std::endl;
    // PDA.output_file(output_p);
    // std::cout << "This is for testing" << std::endl;
    // PDA.print_PDA();
    // 去除引号的操作：
    // input_str = input_str.substr(1, input_str.size() - 2);

    if (!PDA.validity_check(input_str)){
        std::cout << "illegal input";
        return 0;
    }
    if (PDA.run(input_str)){
        std::cout << "true";
    } else {
        std::cout << "false";
    }
    std::cout << std::endl;
    return 0;
}
// c
/*
cmake -B build && cd ./build; make && cd .. && ./bin/pda case.pda ()()
curl -X POST -F "file=@231870134_邓思源_FLA25proj2.zip" http://114.212.82.118:5000/upload
*/