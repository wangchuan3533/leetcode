#include <vector>
#include <iostream>
using namespace std;

class NumArray {
public:
    NumArray(vector<int> &nums) :_arr(nums), _sum(nums.size() + 1, 0)
    {
        for (int i = 0; i < nums.size(); i++) {
            add(i, nums[i]);
        }
    }

    void update(int i, int val)
    {
        add(i, val - _arr[i]);
        _arr[i] = val;
    }

    int sumRange(int i, int j)
    {
        return sum(j) - sum(i - 1);
        
    }

private:
    int lsb(int i)
    {
        return i & (-i);
    }

    int sum(int i)
    {
        int sum = 0;
        for (i = i + 1;i > 0; i -= lsb(i)) {
            sum += _sum[i];
        }

        return sum;

    }

    void add(int i, int diff)
    {
        for (i = i + 1; i < _sum.size(); i += lsb(i)) {
            _sum[i] += diff;
        }
    }

private:
    vector<int> _arr;
    vector<int> _sum;
};
//[7,2,7,2,0],update(4,6),update(0,2),update(0,9),sumRange(4,4),update(3,8),sumRange(0,4),update(4,1),sumRange(0,3),sumRange(0,4),update(0,4)
int main()
{
    vector<int> nums {7, 2, 7, 2, 0};
    NumArray numArray(nums);
    numArray.update(4, 6);
    numArray.update(0, 2);
    numArray.update(0, 9);
    cout << numArray.sumRange(4, 4) << endl;
    numArray.update(3, 8);
    cout << numArray.sumRange(0, 4) << endl;
    numArray.update(4, 1);
    cout << numArray.sumRange(0, 3) << endl;
    cout << numArray.sumRange(0, 4) << endl;
    numArray.update(0, 4);
    return 0;
}

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

