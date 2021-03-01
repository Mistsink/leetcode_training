#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /**
     * Array. 移动零
     */
//    void moveZeroes(vector<int> nums) {
//        int k = 0;      // nums[0, k) 为非零元素
//
//        for (int i = 0; i < nums.size(); i ++)
//            if (nums[i])
//                nums[k++] = nums[i];
//
//        while (k < nums.size()) {
//            nums[k++] = 0;
//        }
//    }
    void moveZeroes(vector<int>& nums) {
        int k = 0;      // nums[0, k) 为非零元素

        for (int i = 0; i < nums.size(); i ++)
            if (nums[i])
                if (i != k)
                    swap(nums[k++], nums[i]);
                else
                    k ++;

    }


    /**
     * 209. 长度最小的子数组
     */
    //  滑动窗口        O(n)
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = -1;   // [l, r]
        int sum = 0, res = nums.size() + 1;

        while (l < nums.size()) {
            if (sum < target && r + 1 < nums.size() )
                sum += nums[++r];
            else
                sum -= nums[l++];

            if (sum >= target)
                res = min(res, r - l +1);

        }

        return res == nums.size() + 1 ? 0 : res;

    }


    /**
     * 167. 两数之和 II - 输入有序数组
     */
    // 思路一：以二分搜索去寻找另一个加数的索引。                    O(log n)
    // 思路二：对撞指针，分别从两边往中间去查询(前提是有序数组)。      O(n)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;

        while (l < r) {
            if (numbers[l] + numbers[r] < target) {
                l ++;
            } else if (numbers[l] + numbers[r] > target) {
                r --;
            } else {
                int res[2] = {l + 1, r + 1};
                return vector<int>(res, res + 2);
            }
        }

        throw invalid_argument("The input has no solution.");
    }



    /**
     * 75. 颜色分类
     */
    // 三路快排思想: 仅有0， 1， 2 三种值
    void sortColors(vector<int>& nums) {
        int l = 0, r = nums.size() - 1, p;

//        p = l + (r - l) / 2;    // 以中间值为基值
//        swap(nums[p], nums[l]);

        int i = l -1, j = l - 1, k = r + 1, m = l;            // [l, i] = 0, [i+1, j] = 1, [k, r] = 2;
        while (m < k) {
            assert( nums[m] >=0 && nums[m] <= 2);
            if (nums[m] < 1) {
                swap(nums[++i], nums[m]);
                j ++;
                m ++;
            } else if (nums[m] == 1) {
                j ++;
                m ++;
            } else {
                swap(nums[--k], nums[m]);
            }
        }
    }


    /**
     * 3. 无重复字符的最长子串
     */
    //  滑动窗口        O(n)
    int lengthOfLongestSubstring(string s) {

        int freq[256] = {0};
        int l = 0, r = -1; // [l, r]
        int res = 0;

        while (l < s.size()) {
            if (r + 1 < s.size() && freq[s[r + 1]] == 0)
                freq[s[++r]] = 1;
            else
                freq[s[l++]] = 0;

            res = max(res, r - l +1);
        }
        return res;
    }


    /**
     *  88. 合并两个有序数组
     *  与归并排序中的合并的思路一致
     */
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        if (n == 0) return;

        vector<int> temp(m);
        for (int i = 0; i < m; i ++) temp[i] = (nums1[i]);

        if (nums2[0] > nums1[m-1]) {
            for (int i = m; i < m+n; i ++)
                nums1[i] = nums2[i-m];
            return;
        }

        int l = 0, r = 0, i = 0;
        while (l < m && r < n) {
            if (temp[l] < nums2[r]) {
                nums1[i++] = temp[l++];
            } else {
                nums1[i++] = nums2[r++];
            }
        }


        while (l < m)   nums1[i++] = temp[l++];
        while (r < n)   nums1[i++] = nums2[r++];
    }
};

int main() {
    int arr[] = {0, 1, 3, 0, 4, 6, 7};

    vector<int> vec(arr, arr + sizeof(arr)/ sizeof(int));
    Solution().moveZeroes(vec);

    for (int num: vec) {
        cout << num << '\t';
    }

    return 0;
}
