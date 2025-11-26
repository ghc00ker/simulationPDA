#include "../include/PDA.h"

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>
PDA::PDA() = default;
PDA::PDA(std::set<std::string> Q
    , std::set<std::string> S
    , std::set<std::string> G
    , std::string q0
    , std::string z0
    , std::set<std::string> F
    , TransitionMap func)
    : Q(std::move(Q))
    , S(std::move(S))
    , G(std::move(G))
    , q0(std::move(q0))
    , z0(std::move(z0))
    , F(std::move(F))
    , func(std::move(func)) {}
PDA::~PDA() = default;

std::string stack2string(std::stack<std::string> s){
    std::string ret = "";
    while(!s.empty()){
        ret += s.top();
        s.pop();
    }
    return ret;
}

struct TupleIIHash {
    size_t operator()(const std::tuple<std::string, std::string, int>& t) const noexcept {
        // 1. 获取两个整数
        std::string first = std::get<0>(t);
        std::string second = std::get<1>(t);
        int third = std::get<2>(t);   // 旧栈顶符号
        // 2. 为每个整数计算哈希
        auto h1 = std::hash<std::string>{}(first);
        auto h2 = std::hash<std::string>{}(second);
        auto h3 = std::hash<int>{}(third);
        // 3. 使用 Boost 风格的组合（工业标准）
        std::size_t seed = h1;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

std::set<std::string> PDA::getQ(){
    return Q;
}
std::set<std::string> PDA::getS(){
    return S;
}
std::string PDA::getq0(){
    return q0;
}
std::set<std::string> PDA::getF(){
    return F;
}
void PDA::print_PDA() {
    std::cout << "#Q = {";
    bool first = true;
    for (const std::string& item : Q) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << item;
        first = false;
    }
    std::cout << "}" << std::endl;

    std::cout << "#S = {";
    first = true;
    for (const std::string& item : S) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << item;
        first = false;
    }
    std::cout << "}" << std::endl;

    std::cout << "#G = {";
    first = true;
    for (const std::string& item : G) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << item;
        first = false;
    }
    std::cout << "}" << std::endl;

    std::cout << "#q0 = " << q0 << std::endl;

    std::cout << "#z0 = " << z0 << std::endl;

    std::cout << "#F = {";
    first = true;
    for (const std::string& item : F) {
        if (!first) {
            std::cout << ",";
        }
        std::cout << item;
        first = false;
    }
    std::cout << "}" << std::endl;

    for (const auto& pair : func) {
        std::cout << std::get<0>(pair.first) << " " 
        << std::get<1>(pair.first) << " "
        << std::get<2>(pair.first) << " "
        << std::get<0>(pair.second) << " "
        << std::get<1>(pair.second) 
        << std::endl;
    }
}
bool PDA::validity_check(std::string s){
    for (auto &c: s){
        if (S.find(std::string(1, c)) == S.end()){
            return false;
        }
    }
    return true;
}
std::tuple<std::string, std::string> PDA::trans_func (std::string old_state, std::string input, std::string stack_top){
    TransitionKey key = std::make_tuple(old_state, input, stack_top);
    std::tuple<std::string, std::string> ret = func.find(key)->second;
    return ret;
}
bool PDA::run(std::string str){
    // 特殊处理：空串且初始状态是终态
    if (str.empty() && F.find(q0) != F.end()) {
        return true;
    }
    
    std::stack<std::string> curr_stack;
    std::string state = q0;
    curr_stack.push(z0);
    std::unordered_set<std::tuple<std::string, std::string, int>, TupleIIHash> his;
    for (int i = 0;;){
        std::string curr_input = "_";
        if (curr_stack.empty()){
            return false; 
        }
        std::string curr_top = curr_stack.top();
        curr_stack.pop();
        std::string curr_state = state;
        if (func.find(std::make_tuple(curr_state, curr_input, curr_top)) == func.end()){
            if (i < str.size()){
                curr_input = std::string(1, str[i]);
                i++;
            } else {
                return false;
            }
        }
        if (func.find(std::make_tuple(curr_state, curr_input, curr_top)) == func.end()){
            return false;
        }
        std::tuple<std::string, std::string> func_ret = trans_func(curr_state, curr_input, curr_top);
        std::string temp_replace = std::get<1>(func_ret);
        if (temp_replace != "_"){
            for (int j = temp_replace.size() - 1; j >= 0 ; j--){
                curr_stack.push(std::string(1, temp_replace[j]));
            }
        }
        state = std::get<0>(func_ret);
        if (i == str.size() && F.find(state) != F.end()){
            return true;
        }
        std::tuple<std::string, std::string, int> rec = std::make_tuple(state, stack2string(curr_stack), i);
        if (his.find(rec) != his.end()){
            return false;
        } else {
            his.emplace(rec);
        }
    }
    return false;
 }