#include "../exercise.h"
#include <numeric>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    
    // 直接计算字节数
    int size = std::accumulate(
        shape, 
        shape + 4, 
        static_cast<int>(sizeof(DataType)), 
        std::multiplies<int>()
    );
    
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}