#include <vector>
#include <list>
#include <utility>
#include <iostream>
//#include <cassert>
#include "util/json.hpp"

typedef std::vector<int> Building;

void dumpResult(const std::vector<std::pair<int, int> > &result)
{
    std::cout << "[";
    for (int i = 0; i < result.size(); i++) {
        std::cout << "[" << result[i].first << "," << result[i].second << "]" << ((i == result.size() - 1) ? "" : ",");
    }
    std::cout << "]\n";
}

void dumpOutline(const std::list<Building> &outline)
{
    std::cout << "[";
    std::list<Building>::const_iterator it = outline.cbegin();
    for (int i = 0; i < outline.size(); i++) {
        std::cout << "[" << (*it)[0] << "," << (*it)[1] << "," << (*it)[2] << "]" << ((i == outline.size() - 1) ? "]\n" : ",");
        it++;
    }
}

void parseTestCase(const char *testCase, std::vector<Building> &buildings)
{
    auto j = nlohmann::json::parse(testCase);
    for (auto it = j.begin(); it != j.end(); it++) {
        buildings.push_back(std::vector<int>{it->at(0), it->at(1), it->at(2)});
    }
}

class Solution {
public:
    std::vector<std::pair<int, int> > getSkyline(std::vector<Building>& buildings)
    {
        std::vector<std::pair<int, int> > result; 
        if (buildings.size() == 0) return result;

        std::list<Building> outline;
        std::list<Building>::iterator head = outline.begin();
        for (Building &building : buildings) {
            std::list<Building>::iterator it = head, next = outline.end();
            for (; it != outline.end() && building[0] < building[1]; it++) {
                Building &current = *it;
                if (current[1] <= building[0]) continue;
                if (building[2] <= current[2]) {
                    building[0] = current[1];
                    if (next == outline.end()) {
                        next = it;
                    }
                    continue;
                }
                if (building[0] > current[0]) {
                    it = outline.emplace(it, Building {current[0], building[0], current[2]});
                    current[0] = building[0];
                    continue;
                }
                //assert(building[0] == current[0]);
                if (current[1] > building[1]) {
                    it = outline.emplace(it, building);
                    current[0] = building[1];
                    building[0] = building[1];
                    if (next == outline.end()) {
                        next = it;
                    }
                    break;
                } else {
                    current[2] = building[2];
                    building[0] = current[1];
                    if (next == outline.end()) {
                        next = it;
                    }
                }
            }

            if (it == outline.end()) {
                // fill empty
                if (!outline.empty()) {
                    Building &back = outline.back();
                    if (back[1] < building[0]) {
                        outline.emplace(it, Building {back[1], building[0], 0});
                    }
                }

                if (building[1] > building[0]) {
                    it = outline.emplace(it, building);
                }
                if (next == outline.end() && it != outline.end()) {
                    next = it;
                }
            }
            if (next != outline.end()) {
                head = next;
            }
        }

        // dump outline
        // dumpOutline(outline);

        int lastHeight = 0, lastRight = 0;
        for (const Building &building : outline) {
            if (building[2] != lastHeight) {
                result.emplace_back(building[0], building[2]);
            }
            lastHeight = building[2];
            lastRight = building[1];
        }

        result.emplace_back(lastRight, 0);

        return result;
    }
};

int main()
{
    Solution solution;

    //const char *testCase = "[]";
    //const char *testCase = "[[1,2,1],[1,2,2],[1,2,3]]";
    //const char *testCase = "[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]";
    const char *testCase = "[[2,4,70],[3,8,30],[6,100,41],[7,15,70],[10,30,102],[15,25,76],[60,80,91],[70,90,72],[85,120,59]]";

    std::vector<std::vector<int> > buildings;
    parseTestCase(testCase, buildings);

    std::vector<std::pair<int, int> > result = solution.getSkyline(buildings);
    dumpResult(result);

    return 0;
}
