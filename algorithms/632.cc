#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:

    struct Node {
        int val;
        int row;
        int idx;

        Node(int _val, int _row, int _idx) : val(_val), row(_row), idx(_idx) {}
    };
    struct NodeCmp {
        bool operator() (const Node &a, const Node &b) {
            return a.val > b.val;
        }
    };

    vector<int> smallestRange(vector<vector<int> >& nums) {
        priority_queue<Node, vector<Node>, NodeCmp> queue;
        int start = INT_MAX, end = INT_MIN, max;

        int row = 0;
        for (auto const &num : nums) {
            auto val = num.front();
            queue.emplace(val, row++, 1);
            if (val < start) {
                start = val;
            }
            if (val > end) {
                end = val;
            }
        }
        max = end;

        while (queue.size() == nums.size()) {
            auto node = queue.top();
            queue.pop();
            if (max - node.val < end - start) {
                start = node.val;
                end = max;
            }

            if (node.idx < nums[node.row].size()) {
                node.val = nums[node.row][node.idx++];
                queue.push(node);
                if (node.val > max) {
                    max = node.val;
                }
            }
        }

        vector<int> ret {start, end};
        return ret;
    }
};

int main()
{
    Solution solution;
    //vector<vector<int> > nums = {{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
    vector<vector<int> > nums = {{1,2,3},{1,2,3},{1,2,3}};
    vector<int> ret = solution.smallestRange(nums);

    for (auto num : ret) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}