#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <iterator>

class Solution {
public:
    std::string predictPartyVictory(std::string senate)
    {
        std::list<char> senateList(senate.begin(), senate.end());

        char winner;
        auto it = senateList.begin();
        while (senateList.size() > 0) {
            auto it2 = std::next(it, 1);
            while (it2 != senateList.end()) {
                if (*it != *it2) {
                    senateList.erase(it2);
                    break;
                } else {
                    it2++;
                }
            }
            if (it2 == senateList.end()) {
                winner = *it;
                goto _winner;
            } else {
                senateList.push_back(*it);
                it = senateList.erase(it);
            }
        }

_winner:
        if (winner == 'R' || winner == 'r') {
            return "Radiant";
        } else {
            return "Dire";
        }
    }
};

int main()
{
    Solution solution;
    //std::string input = "RD";
    //std::string input = "RDD";
    std::string input = "DDRRR";
    std::string output = solution.predictPartyVictory(input);
    std::cout << output << std::endl;
    return 0;
}
