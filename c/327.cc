#include <vector>
#include <map>
#include <iostream>
using namespace std;
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        map<long, long> sums;
        int result = 0;

        sums[0] = 1;
        long sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            auto it = sums.lower_bound(sum - upper);
            auto end1 = sums.upper_bound(sum - lower);
            auto end2 = sums.end();
            for (;it != end1 && it != end2; it++) {
                result += it->second;
            }
            sums[sum]++;
        }
        return result;
    }
};

int main()
{
    Solution s;
    //vector<int> nums {-2, 5, -1};
    //int ret = s.countRangeSum(nums, -2, 2);
    vector<int> nums {-2147483647,0,-2147483647,2147483647};
    int ret = s.countRangeSum(nums, -564, 3864);


    cout << "ret = " << ret << endl;
    return 0;
}
