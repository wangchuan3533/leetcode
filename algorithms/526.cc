#include <iostream>
#include <algorithm>
#include <vector>
class Solution {
public:
    bool checkDivisible(int a, int b)
    {
        return (a % b) == 0 || (b % a) == 0;
    }

    void printVec(const std::vector<int> &vec)
    {
        for (int v : vec) {
            std::cout << v + 1 << ", ";
        }
        std::cout << std::endl;
    }

    bool getNextAtPos(std::vector<int> &vec, int pos)
    {
        if (pos < 0) {
            return false;
        }

        std::sort(vec.begin() + pos + 1, vec.end());
        for (int i = pos + 1; i < vec.size(); i++) {
            if (vec[i] > vec[pos]) {
                std::swap(vec[i], vec[pos]);
                return true;
            }
        }
        return getNextAtPos(vec, pos - 1);
    }

    bool getNext(std::vector<int> &vec, int &count)
    {
        for (int i = 0; i < vec.size(); i++) {
            if (!checkDivisible(i + 1, vec[i] + 1)) {
                if (getNextAtPos(vec, i)) {
                    return getNext(vec, count);
                } else {
                    return false;
                }
            }
        }

        //printVec(vec);
        count++;

        for (int end = vec.size() - 1, i = end; i >= 0; i--) {
            if (i == end || vec[i] > vec[i + 1]) {
                continue;
            }
            if (getNextAtPos(vec, i)) {
                return getNext(vec, count);
            } else {
                return false;
            }
       }
        return false;
    }

    int countArrangement(int N)
    {
        std::vector<int> vec(N);
        for (int i = 0; i < N; i++) {
            vec[i] = i;
        }

        int count = 0;
        int base = 0;

        while (getNext(vec, count));
        return count;
    }
};

// compile with -O3 tail recursion
int main()
{
    Solution solution;
    for (int i = 0; i <= 15; i++) {
        int ret = solution.countArrangement(i);
        std::cout << "case " << i << ":\n    return " << ret << ";" << std::endl;
    }
    return 0;
}
