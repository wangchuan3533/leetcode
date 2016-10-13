#include <stdio.h>
#include <set>
#include <deque>
#include <vector>
#define SET_MASK(x, mask) ((x) |= (mask))
#define CLR_MASK(x, mask) ((x) &= ~(mask))

#define TEST_POWER_OF_TWO(x) ((x) && !((x) & (x - 1)))
#define XY2OFFSET(x, y) ((y) * 9 + (x))
using namespace std;
class Solution {
    inline int get_bit_offset(unsigned short v)
    {
        int offset = 0;
        while (v > 0) {
            v = v >> 1;
            offset++;
        }
        return offset;
    }

    inline bool check(unsigned short *table, int x, int y)
    {
        int i = XY2OFFSET(x, y);
        // x
        for (int j = 0; j < 9; j++) {
            int k = XY2OFFSET(j, y);
            if (k != i && table[k] == table[i]) return false;
        }
        // y
        for (int j = 0; j < 9; j++) {
            int k = XY2OFFSET(x, j);
            if (k != i && table[k] == table[i]) return false;
        }
        // z
        for (int j = 0; j < 9; j++) {
            int k = XY2OFFSET(x - (x % 3) + (j % 3), y - (y % 3) + (j / 3));
            if (k != i && table[k] == table[i]) return false;
        }
        return true;
    }

public:

    void solveSudoku(vector<vector<char>>& board) 
	{
		int i, j, k, x, y, xb, yb;
		unsigned short table[81];
		set<int> unsolved;
		deque<int> unprocessed;

		// init table
		for (i = 0; i < 81; i++) {
			x = i % 9;
			y = i / 9;
			if (board[y][x] == '.') {
				table[i] = 0x1ff;
				unsolved.insert(i);
			} else {
				table[i] = 1u << (board[y][x] - '1');
				unprocessed.push_back(i);
			}

		}

	_has_unprocessed:
		while (unprocessed.size() > 0) {
//			printf("unsolved=%lu,unprocessed=%lu\n", unsolved.size(), unprocessed.size()); 

			i = unprocessed.front();
			unprocessed.pop_front();

			x = i % 9;
			y = i / 9;
			xb = x - (x % 3);
			yb = y - (y % 3);

			for (j = 0; j < 9; j++) {
				// x
				k = XY2OFFSET(j, y); 
				if (k != i && (table[i] & table[k])) {
					CLR_MASK(table[k], table[i]);
					if (TEST_POWER_OF_TWO(table[k])) {
						unsolved.erase(unsolved.find(k));
						unprocessed.push_back(k);
                        board[y][j] = '0' + get_bit_offset(table[k]);
						printf("x=%d,y=%d,v=%c\n", j, y, board[y][j]);
					}
				}

				// y
				k = XY2OFFSET(x, j); 
				if (k != i && (table[i] & table[k])) {
					CLR_MASK(table[k], table[i]);
					if (TEST_POWER_OF_TWO(table[k])) {
						unsolved.erase(unsolved.find(k));
						unprocessed.push_back(k);
                        board[j][x] = '0' + get_bit_offset(table[k]);
						printf("x=%d,y=%d,v=%c\n", x, j, board[j][x]);
					}
				}

				// z
				k = XY2OFFSET(xb + j % 3, yb + j / 3);
				if (k != i && (table[i] & table[k])) {
					CLR_MASK(table[k], table[i]);
					if (TEST_POWER_OF_TWO(table[k])) {
						unsolved.erase(unsolved.find(k));
						unprocessed.push_back(k);
                        board[yb + j / 3][xb + j % 3] = '0' + get_bit_offset(table[k]);
						printf("x=%d,y=%d,v=%c\n", xb + j % 3, yb + j / 3, board[yb + j / 3][xb + j % 3]);
					}
				}
			}
		}

        for (auto &it : unsolved) {
            i = it;

            x = i % 9;
            y = i / 9;
            xb = x - (x % 3);
            yb = y - (y % 3);

            unsigned short bit_sum;

            for (j = 0, bit_sum = 0; j < 9; j++) {
                k = XY2OFFSET(j, y); 
                if (k != i) bit_sum |= table[k];
            }
            if (bit_sum != 0x1ff) {
                table[i] = (~bit_sum) & 0x1ff;
                unsolved.erase(unsolved.find(i));
                unprocessed.push_back(i);
                board[y][x] = '0' + get_bit_offset(table[i]);
                printf("x=%d,y=%d,v=%c\n", x, y, board[y][x]);
                goto _has_unprocessed;
            }

            for (j = 0, bit_sum = 0; j < 9; j++) {
                k = XY2OFFSET(x, j); 
                if (k != i) bit_sum |= table[k];
            }
            if (bit_sum != 0x1ff) {
                table[i] = (~bit_sum) & 0x1ff;
                unsolved.erase(unsolved.find(i));
                unprocessed.push_back(i);
                board[y][x] = '0' + get_bit_offset(table[i]);
                printf("x=%d,y=%d,v=%c\n", x, y, board[y][x]);
                goto _has_unprocessed;
            }

            for (j = 0, bit_sum = 0; j < 9; j++) {
                k = XY2OFFSET(xb + j % 3, yb + j / 3); 
                if (k != i) bit_sum |= table[k];
            }
            if (bit_sum != 0x1ff) {
                table[i] = (~bit_sum) & 0x1ff;
                unsolved.erase(unsolved.find(i));
                unprocessed.push_back(i);
                board[y][x] = '0' + get_bit_offset(table[i]);
                printf("x=%d,y=%d,v=%c\n", x, y, board[y][x]);
                goto _has_unprocessed;
            }
        }
        if (unsolved.size() == 0) return;

        struct stack_element {
            int offset;
            unsigned short max;
        };
        vector<struct stack_element> stack(unsolved.size());

        int top = 0;
        for (auto &it : unsolved) {
            stack[top].offset = it;
            stack[top].max = table[it];
            table[it] = 0;
            top++;
        }

        for (top = 0, table[stack[top].offset] = 1; top >= 0;) {
            while (stack[top].max > table[stack[top].offset] && (stack[top].max & table[stack[top].offset]) == 0) {
                table[stack[top].offset] <<= 1;
            }
            if (table[stack[top].offset] > stack[top].max) {
                table[stack[top].offset] = 0;
                top--;
                if (top < 0) break;

                table[stack[top].offset] <<= 1;
                continue;
            }

            //printf("top = %d\n", top);
            if (check(table, stack[top].offset % 9, stack[top].offset / 9)) {
                top++;
                if (top == unsolved.size()) {
                    for (i = 0; i < top; i++) {
                        board[stack[i].offset / 9][stack[i].offset % 9] = '0' + get_bit_offset(table[stack[i].offset]);
                        printf("x=%d,y=%d,v=%d\n", stack[i].offset % 9, stack[i].offset / 9, get_bit_offset(table[stack[i].offset]));
                    }
                    return;
                }
                table[stack[top].offset] = 1;
            } else {
                table[stack[top].offset] <<= 1;
            }
        }
	}
};


int main()
{
    /*
    vector<vector<char>> board {
        {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
        {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
        {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
        {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
        {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
        {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
        {'.', '.', '.', '2', '7', '5', '9', '.', '.'}
    };
    */

    vector<vector<char>> board {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

	Solution s;
    s.solveSudoku(board);
}
