#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        std::vector<std::vector<int>> ret;
        for (int i = 0; i < 512; i++) {
            int bitCount = 0;
            int sum = 0;
            for (int j = 0; j < 9; j++) {
                if (i & (1 << j)) {
                    bitCount += 1;
                    sum += (j + 1);
                }
            }

            if (bitCount == k && sum == n) {
                std::vector<int> combination;
                combination.reserve(k);
                for (int j = 0; j < 9; j++) {
                    if (i & (1 << j)) {
                        combination.push_back(j + 1);
                    }
                }
                std::cout << "i = " << i << std::endl;
                ret.push_back(combination);
            }
        }
        return ret;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> ret = solution.combinationSum3(3, 7);
    for (auto &vec : ret) {
        for (auto &val : vec) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }
    return 0;
}
