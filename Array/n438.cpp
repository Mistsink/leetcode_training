//
// Created by firework on 2021/3/2.
//

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> record;
        for (char c : p) {
            record.insert(c, 0);
        }

        vector<int> res;
        int i = 0, l = -1;

        while (i < s.size()) {
            char c = s[i];
            if (record.find(c)) {
                if ()
            }

            i ++;
        }
        record.find()
    }
};
