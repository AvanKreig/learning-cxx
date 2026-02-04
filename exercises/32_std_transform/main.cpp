#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>
#include <functional> // 可能需要 std::multiplies

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    
    // 先创建一个临时向量存储乘以2的结果
    std::vector<int> doubled;
    doubled.resize(val.size());
    std::transform(val.begin(), val.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    
    // 再将整数转换为字符串
    std::vector<std::string> ans;
    ans.resize(doubled.size());
    std::transform(doubled.begin(), doubled.end(), ans.begin(),
                   [](int x) { return std::to_string(x); });
    
    // 或者使用单次transform，直接计算并转换
    // std::vector<std::string> ans;
    // ans.resize(val.size());
    // std::transform(val.begin(), val.end(), ans.begin(),
    //               [](int x) { return std::to_string(x * 2); });
    
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}