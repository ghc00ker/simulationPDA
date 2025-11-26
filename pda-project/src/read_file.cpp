#include "../include/read_file.h"
#include "../include/PDA.h"
#include <cstddef>
#include <fstream>
#include <iostream> 
#include <tuple>
#include <utility>
#include <vector>

std::string delete_comment(std::string line){
    size_t pos = line.find_first_of(';');
    std::string new_line = line.substr(0, pos);
    return new_line;
}
std::set<std::string> split_str(std::string str, char c){
    std::set<std::string> ret;
    while(str.find(c) != std::string::npos){
        size_t pos = str.find(c);
        ret.insert(str.substr(0, pos));
        str = str.substr(pos + 1);
    }
    if (!str.empty()){
        ret.insert(str);
    }
    return ret;
}
std::vector<std::string> split_str_vec(std::string str, char c){
    std::vector<std::string> ret;
    while(str.find(c) != std::string::npos){
        size_t pos = str.find(c);
        ret.push_back(str.substr(0, pos));
        str = str.substr(pos + 1);
    }
    if (!str.empty()){
        ret.push_back(str);
    }
    return ret;
}
std::set<std::string> handleQ(std::string line){
    size_t pos1 = line.find('{');
    size_t pos2 = line.find('}');
    std::set<std::string> ret = split_str(line.substr(pos1 + 1, pos2 - pos1 - 1), ',');
    return ret;
}
std::set<std::string> handleS(std::string line){
    size_t pos1 = line.find('{');
    size_t pos2 = line.find('}');
    std::set<std::string> ret = split_str(line.substr(pos1 + 1, pos2 - pos1 - 1), ',');
    return ret;
}
std::set<std::string> handleG(std::string line){
    size_t pos1 = line.find('{');
    size_t pos2 = line.find('}');
    std::set<std::string> ret = split_str(line.substr(pos1 + 1, pos2 - pos1 - 1), ',');
    return ret;
}
std::string handleq0(std::string line){
    return line.substr(6);
}
std::string handlez0(std::string line){
    return line.substr(6);
}
std::set<std::string> handleF(std::string line){
    size_t pos1 = line.find('{');
    size_t pos2 = line.find('}');
    std::set<std::string> ret = split_str(line.substr(pos1 + 1, pos2 - pos1 - 1), ',');
    return ret;
}
void handlefunc(std::string line, TransitionMap &func){
    std::vector<std::string> f = split_str_vec(line, ' ');
    TransitionKey key = std::make_tuple(f[0], f[1], f[2]);
    func.emplace(std::move(key), std::move(std::make_tuple(f[3], f[4])));
}

PDA read_file(const std::string& path) {
    std::ifstream fin;
    fin.open(path, std::ios::in);
    if (!fin) {
        std::cerr << "无法打开文件\n";
        return PDA();
    }

    std::string line;

    std::set<std::string>Q;
    std::set<std::string>S;
    std::set<std::string>G;
    std::string q0;
    std::string z0;
    std::set<std::string>F;
    TransitionMap func;

    while (std::getline(fin, line)) {
        std::string nline = delete_comment(line);
        if (nline.empty()){
            continue;
        }
        char sign = nline.at(1);
        if (nline.at(0) == '#'){
            switch (sign){
                case 'Q':
                    Q = handleQ(nline);
                    break;
                case 'S':
                    S = handleS(nline);
                    break;
                case 'q':
                    q0 = handleq0(nline);
                    break;
                case 'F':
                    F = handleF(nline);
                    break;
                case 'G':
                    G = handleG(nline);
                    break;
                case 'z':
                    z0 = handlez0(nline);
                    break;
            }
        } else {
            handlefunc(nline, func);
        }
        

    }
    fin.close(); // 可选，离开作用域会自动关闭

    PDA ret = PDA(Q,S,G,q0,z0,F,func);
    return ret;
}
