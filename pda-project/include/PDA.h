#ifndef PDA_H   // 如果 PERSON_H 这个宏还没有被定义
#define PDA_H   // 那么定义它，并继续包含下面的内容
#include <unordered_set>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <tuple>
#include <functional>

// 自定义哈希函数结构体，用于为三元组 (状态, 输入符号, 栈顶符号) 生成哈希值
// 这样可以将三元组作为 unordered_map 的键，实现 PDA 的转移函数快速查找
struct TransitionKeyHash {
    // 重载 () 运算符，使该结构体可以像函数一样被调用
    // 参数: key - 包含三个字符串的元组 (旧状态, 输入符号, 旧栈顶符号)
    // 返回: 该元组的哈希值
    // noexcept: 保证该函数不抛出异常
    std::size_t operator()(const std::tuple<std::string, std::string, std::string>& key) const noexcept {
        // 从元组中提取三个字符串
        const auto& first = std::get<0>(key);   // 旧状态
        const auto& second = std::get<1>(key);  // 输入符号
        const auto& third = std::get<2>(key);   // 旧栈顶符号
        
        // 计算每个字符串的哈希值
        std::size_t h1 = std::hash<std::string>{}(first);
        std::size_t h2 = std::hash<std::string>{}(second);
        std::size_t h3 = std::hash<std::string>{}(third);
        
        // 组合三个哈希值 (使用 boost 风格的哈希组合方法)
        // 0x9e3779b9 是黄金比例常数，有助于减少哈希冲突
        std::size_t seed = h1;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

using TransitionKey = std::tuple<std::string, std::string, std::string>;
using TransitionMap = std::unordered_map<TransitionKey, std::tuple<std::string, std::string>, TransitionKeyHash>;
class PDA {
    public:
    PDA();
    PDA(std::set<std::string> Q
        , std::set<std::string> S
        , std::set<std::string> G
        , std::string q0
        , std::string z0
        , std::set<std::string> F
        , TransitionMap func);
    ~PDA();

    void print_PDA();
    std::tuple<std::string, std::string> trans_func (std::string old_state, std::string input, std::string stack_top);
    bool run(std::string);
    bool validity_check(std::string s);
    std::set<std::string> getQ();
    std::set<std::string> getS();
    std::set<std::string> getG();
    std::string getq0();
    std::string getz0();
    std::set<std::string> getF();

    private:
    std::set<std::string> Q;
    std::set<std::string> S;
    std::set<std::string> G;
    std::string q0;
    std::string z0;
    std::set<std::string> F;
    TransitionMap func;
    void d_ur_helper(std::string curr_state, std::unordered_set<std::string> &his);
    int minimize_helper(std::unordered_map<std::string, int> &partition, std::string c);

};

#endif