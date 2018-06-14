#include <iostream>
#include <vector>
class Solution {
public:
    int findLengthOfLCIS(const std::vector<int>& nums)
    {
        int max = 0;
        for (int i = 0, current = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] > nums[i - 1]) {
                current++;
            } else {
                current = 1;
            }
            if (current > max) {
                max = current;
            }
        }
        return max;
    }
};

int main()
{
    Solution solution;
    return 0;
}