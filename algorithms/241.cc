#include <stdlib.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> operands, operators, prod, *table, ret;
        int i, j, k, n, r;

        // parse
        parse(input.c_str(), operands, operators);
        n = operands.size();

        // verify the parsing
        //cout << "n = " << n << endl;
        //print_vector(operands);
        //print_vector(operators);

        table = new vector<int>[n * n];
        for (i = 0; i < n; i++) {
            for (j = 0; j + i < n; j++) {
                k = i * n + j;
                //cout << "i = " << i << " j = " << j << " k = " << k << endl;
                if (i == 0) {
                    table[k].push_back(operands[j]);
                } else {
                    for (r = 0; r < i; r++) {
                        vector<int> &left = table[r * n + j];
                        vector<int> &right = table[(i - 1 - r) * n + j + r + 1];
                        prod = vector_prod(left, right, operators[j + r]);
                        table[k].insert(table[k].end(), prod.begin(), prod.end());
                    }
                }
            }
        }

        ret = table[(n - 1) * n];
        delete [] table;
        return ret;
    }

    void print_vector(vector<int> &v)
    {
        cout << "[";
        for (int i = 0;  i < v.size(); i++) {
            cout << v[i] << (i < v.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }


private:

	int calc(int a, int b, int op)
	{
		switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		}

        cerr << "invalid op: " << (char)op << endl;
		exit(1);
		return 0;
	}

    vector<int> vector_prod(vector<int> v1, vector<int> v2, int op)
    {
        vector<int> ret;

        ret.reserve(v1.size() * v2.size());
        for (vector<int>::iterator i = v1.begin(); i != v1.end(); i++) {
            for (vector<int>::iterator j = v2.begin(); j != v2.end(); j++) {
                ret.push_back(calc(*i, *j, op));
            }
        }

        return ret;
    }

    void parse(const char *input, vector<int> &operands, vector<int> &operators)
    {
        char *tmp, *next;

        for (tmp = (char *)input; *tmp != '\0';) {
            operands.push_back(strtol(tmp, &next, 10));
            if (*next == '\0') break;
            operators.push_back(*next);
            tmp = next + 1;
        }
    }

};

int main()
{
    Solution solution;
    string input = "2*3-4*5";
    vector<int> ret = solution.diffWaysToCompute(input);
    solution.print_vector(ret);
    return 0;
}
