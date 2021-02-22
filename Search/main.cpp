#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>


using namespace std;


class Solution {
public:
    /**
     * Search. 两个数组的交集
     */
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> record(nums1.begin(), nums1.end());

        unordered_set<int> result;

        for (int num : nums2)
            if (record.find(num) != record.end()) result.insert(num);

        return vector<int>(result.begin(), result.end());
    }


    /**
    * 350. 两个数组的交集 II
    */
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> record;

        for (int num: nums1) {
            record[num] ++;
        }

        vector<int> res;
        for (int num: nums2) {
            if (record[num] > 0) {
                res.push_back(num);
                record[num] --;
            }
        }

        return res;
    }


    /**
     * 454. 四数相加 II
     */
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> record;         // [num] : freq

        for (int numC : C)
            for (int numD: D)
                record[numC + numD] ++;

        int res = 0;
        for (int numA : A)
            for (int numB: B)
                if (record.find(0 - numA - numB) != record.end())
                    res += record[0 - numA - numB];

        return res;
    }

    /**
     * 447. 回旋镖的数量
     */
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); i ++) {
            unordered_map<int, int> record;         // [distance]: count

            for (int j = 0; j < points.size(); j ++) {
                if (j != i) {
                    record[distance(points[i], points[j])] ++;
                }
            }

            for (unordered_map<int, int>::iterator iter = record.begin();
                iter != record.end(); iter ++) {
                int freq = iter->second;
                if (freq >= 2) {
                    res += freq * (freq  - 1);
                }
            }
        }

        return res;
    }


    /**
     * 219. 存在重复元素 II
     */
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> record;

        for (int i = 0; i < nums.size(); i ++) {
            if (record.find(nums[i]) != record.end()) {
                return true;
            }

            record.insert(nums[i]);

            if (record.size() == k + 1) {
                record.erase(nums[i - k]);
            }
        }

        return false;
    }


    /**
     * 220. 存在重复元素 III
     */
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<long long> record;          // 采用longlong 64整型防止加法溢出

        for (int i = 0; i < nums.size(); i ++) {
            if (record.lower_bound((long long)nums[i] - (long long)t) != record.end()
                && *record.lower_bound((long long)nums[i] - (long long)t) <= (long long)nums[i] + (long long)t) {
                return true;
            }

            record.insert(nums[i]);

            if (record.size() == k + 1) {
                record.erase(nums[i - k]);
            }
        }

        return false;
    }


private:
    int distance(vector<int> point1, vector<int> point2) {
        return (point1[0] - point2[0]) * (point1[0] - point2[0]) +
                (point1[1] - point2[1]) * (point1[1] - point2[1]);
    }
};

int main() {
    vector<vector<int>> test = {{0,0},{1,0},{2,0}};
    std::cout << Solution().numberOfBoomerangs(test) << std::endl;
    return 0;
}
