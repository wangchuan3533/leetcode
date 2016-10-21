#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class BITree {
public:
    BITree(int n): _arr(n + 1, 0)
    {
    }

    int lsb(int index)
    {
        return index & (-index);
    }

    void add(int index, int val)
    {
        index = index + 1;
        while (index < _arr.size()) {
            _arr[index] += val;
            index += lsb(index);
        }
    }

    int query(int index) 
    {
        int sum = 0;
        index = index + 1;
        while (index > 0) {
            sum += _arr[index];
            index -= lsb(index);
        }
        return sum;
    }

private:
    vector<int> _arr;
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> clone = nums;
        sort(clone.begin(), clone.end());
        unordered_map<int, int> rank;
        for (int i = 0; i < clone.size(); i++) {
            rank[clone[i]] = i;
        }


        BITree tree(clone.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            int r = rank[nums[i]];
            clone[i] = tree.query(r - 1);
            tree.add(r, 1);
        }
        return clone;
    }
};

int main()
{
    /*
    BITree tree(10);
    tree.add(0, 10);
    tree.add(1, 10);
    cout << tree.query(9) << endl;
    */

    vector<int> nums {5, 2, 6, 1};
    Solution s;
    vector<int> ret = s.countSmaller(nums);

    for (auto it = ret.begin(); it != ret.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}
