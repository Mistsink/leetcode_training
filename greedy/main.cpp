#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    /**
     * 455. 分发饼干
     */
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end(), greater<>());
        sort(s.begin(), s.end(), greater<>());

        int si = 0, gi = 0, res = 0;

        while (si < s.size() && gi < g.size()) {
            if (s[si] >= g[gi]) {
                si ++;
                gi ++;
                res += 1;
            } else {
                gi ++;
            }
        }

        return res;
    }


    /**
     * 392. 判断子序列
     */
    bool isSubsequence(string s, string t) {
        if (!s.size()) return true;
        int si = 0, ti = 0;
        while (si < s.size() && ti < t.size() ) {
            if (s[si] == t[ti]) {
                si ++;
                ti ++;
            } else {
                ti ++;
            }

            if (si == s.size()) return true;
        }
        return false;
    }



    /**
     * 435. 无重叠区间
     */
     //     动态规划解法
    int eraseOverlapIntervals_dynamic_programming(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(), compare_dp);

        //  memo[i] 为 [0, ... , i]的最长不重叠区间数 （转换成了最长子序列的问题）
        vector<int>memo(intervals.size(), 1);

        for (int i = 1; i < intervals.size(); i ++) {
            for (int j = 0; j < i; j ++) {
                if (intervals[i][0] >= intervals[j][1]) {
                    memo[i] = max(memo[i], memo[j] + 1);
                }
            }
        }

        int res = 1;
        for (int m: memo) {
            res = max(res, m);
        }

        return intervals.size() - res;
    }

    //  贪心解法:
    //      按照区间结尾排序  --->  选择结尾最早的，且和前一个区间不重叠的区间
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(), compare_greedy);

        int res = 1, pre = 0;   //  res初始化为第一个区间的最长不重叠区间长度
        //  pre 表示已选择的 区间的 前一个区间索引

        for (int i = 1; i < intervals.size(); i ++ ) {
            if (intervals[i][0] >= intervals[pre][1]) {
                res ++;
                pre = i;
            }
        }

        return intervals.size() - res;
    }


private:
    bool static compare_dp(const vector<int> &a, const  vector<int> &b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
    }

    //  按照结尾来排序
    bool static compare_greedy(const vector<int> &a, const  vector<int> &b) {
        if (a[1] != b[1]) return a[1] < b[1];
        return a[0] < b[0];
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
