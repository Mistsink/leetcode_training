#include <iostream>
#include <vector>

using namespace std;


//  斐波那契数列
//  版本一：记忆化搜索(存储每次fib的值，减少重复计算)-自上而下递归
int fib (int n, vector<int> & memo) {
    if (n == 0 || n == 1) return n;

    //  memo数组保存n索引的fib值,减少重复计算
    if (memo[n] == -1) memo[n] = fib(n-1, memo) + fib(n-2, memo);

    return memo[n];
}
//  版本二：动态规划-自下而上
int fib (int n) {
    vector<int> memo(n+1, -1);
    memo[0] = 0;
    memo[1] = 1;
    for (int i = 2; i <= n; i ++) memo[i] = memo[i-1] + memo[i-2];

    return memo[n];
}


class Solution {
private:
    int climbStairs(int n, vector<int> &steps) {
        if (n == 1 || n == 0) return 1;

        if (steps[n] == 0)
            steps[n] = climbStairs(n-1, steps) + climbStairs(n-2, steps);
        return steps[n];
    }

    int breakInteger(int n, vector<int> &memo) {
        if (n == 1) return 1;

        if (memo[n] == -1) {
            int res = -1;
            for (int i = 1; i < n; i ++) {
                res = max(res, max(i * breakInteger(n - i, memo), i * (n - i)));
            }
            memo[n] = res;
        }
        return memo[n];
    }

    //  考虑对[index, nums.size() -1] 的房子打劫
    int tryRob(vector<int> &nums, int index, vector<int> &preRes) {
        if (index >= nums.size()) return 0;
        if (preRes[index] == -1) {
            int res = 0;
            for (int i = index; i < nums.size(); i ++) {
                res = max(res, nums[i] + tryRob(nums, i + 2, preRes));
            }
            preRes[index] = res;
        }
        return preRes[index];
    }



    //  是否能 在[0, ... index] 物品中，填满大小为sum的背包
    bool tryPartition (const vector<int> &nums, int index, int sum, vector<vector<bool>> &memo, vector<vector<bool>> &visited) {
        if (sum == 0) return true;
        if (sum < 0 || index < 0) return false;

        if (!visited[index][sum]) {
            visited[index][sum] = true;
            memo[index][sum] = tryPartition(nums, index - 1, sum, memo, visited)
                    || tryPartition(nums, index-1, sum-nums[index], memo, visited);
        }

        return memo[index][sum];
    }

public:
    /**
     * 70. 爬楼梯
     */
    static int climbStairs(int n) {
        vector<int>steps(n+1, 0);
        steps[0] = steps[1] = 1;
        for (int i = 2; i <= n; i ++) steps[i] = steps[i-1] + steps[i-2];
        return steps[n];
    }


    /**
     * 343. 整数拆分
     */
    int integerBreak(int n) {
        vector<int>memo(n+1, -1);

        memo[1] = 1;
        for (int i = 2; i <= n; i ++) {
            for (int j = 1; j < i; j ++) {
                memo[i] = max(memo[i], max(j * (i-j), j * memo[i-j]));
            }
        }

        return memo[n];
    }

    /**
     * 198. 打家劫舍
     */
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        //  [index, n-1] 的收益
        vector<int>memo(nums.size(), -1);
        memo[n-1] = nums[n-1];

        for (int i = n - 2; i >= 0; i --) {
            //  求解memo[i]
            //  [i, .... , n-1]
            for (int j = i; j < n; j ++) {
                memo[i] = max(memo[i], nums[j] +(j + 2 < n ? memo[j + 2] : 0));
            }
        }

        return memo[0];
    }


    /**
     * 416. 分割等和子集------01背包问题
     */
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num: nums) sum += num;

        if (sum%2) return false;

//        //  memo[0 ,.  ... sum/2]   故容量为sum/2 + 1
//        vector<vector<bool>>memo(nums.size(), vector<bool>(sum/2 + 1, false));
//        vector<vector<bool>>visited(nums.size(), vector<bool>(sum/2, false));
//        return tryPartition(nums, nums.size() - 1, sum/2, memo, visited);

        int n = nums.size();
        int C = sum / 2;
        vector<bool> memo(C + 1, false);

        //  考虑是否能将第一个物品放入背包
        for (int i = 0; i <= C; i ++)
            memo[i] = nums[0] == i;

        for (int i = 1; i < n; i ++) {
            for (int j = C; j >= nums[i]; j --) {
                memo[j] = memo[j] || memo[j-nums[i]];
            }
        }

        return memo[C];
    }




    /**
     * 300. 最长递增子序列
     */
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;

        //  memo[i]  表示 以索引 i 为结尾的最长递增子序列长度
        vector<int> memo(nums.size(), 1);

        for (int i = 1; i < nums.size(); i ++) {
            for (int j = 0; j < i; j ++) {
                if (nums[i] > nums[j]) {
                    memo[i] = max(memo[i], memo[j] + 1);
                }
            }
        }

        int res = 1;
        for (int m : memo) {
            res = max(m, res);
        }

        return res;
    }
};


//  01背包问题
class Knapsack01 {
private:
    //  [0, ... , index] 最优解
    //  = max( bestValue[0, ... index-1] , v[index] + bestValue[0, ... index-1] )
    int bestValue(const vector<int> &w, const vector<int> &v, int index, int c, vector<vector<int>> &memo) {
        if (index < 0 || c <= 0) return 0;

        if (memo[index][c] == -1) {
            memo[index][c] = max(
                    bestValue(w, v, index - 1, c, memo),
                    (w[index] <= c ? v[index] + bestValue(w, v, index-1, c-w[index], memo) : 0)
                    );
        }

        return memo[index][c];
    }
public:
    /**
     * 01背包问题，求解所装物品最大价值总和
     * @param w     物品对应重量（所占容量）
     * @param v     物品对应价值
     * @param C     背包总容量
     */
    int knapsack01 (const vector<int> &w, const vector<int> &v, int C) {
        int n = v.size();


        //  因为bestValue最优解与index 和 容量c有关，故memo取二维数组来记忆
        vector<vector<int>> memo(n, vector<int>(C+1, -1));
        /**
        return bestValue(w, v, n - 1, C, memo);
         */
        if (n == 0 || C == 0) return 0;

        //  [0, 0] 范围物品对应各容量c 取得的价值最优解
        for (int c = 0; c <= C; c ++) {
            memo[0][c] = c >= w[0] ? v[0] : 0;
        }

        //  对 [0, ... i] 推导求解
        for (int i = 1; i < n; i ++) {
            for (int c = 0; c <= C; c ++) {
                memo[i][c] = max( memo[i-1][c],
                                  (w[i] <= c ? v[i] + memo[i-1][c-w[i]] : 0)
                                  );
            }
        }
        return memo[n-1][C];
    }



    /**
     * 01背包问题-空间复杂度的优化
     * 由于每一次考虑[0 ~ index]物品中选取时，我们只用到了[0 ~ index -1] 这一行的解
     * 即每次只考虑到了上次的解
     * 所以将memo数组只设为两行来进行空间的节约
     * 而且显而易见，【pre， cur】------pre为偶数index，cur为奇数index
     */
    int knapsack01_better_space (const vector<int> &w, const vector<int> &v, int C) {
        int n = v.size();


        //  因为bestValue最优解与index 和 容量c有关，故memo取二维数组来记忆
        vector<vector<int>> memo(2, vector<int>(C+1, -1));

        if (n == 0 || C == 0) return 0;

        //  [0, 0] 范围物品对应各容量c 取得的价值最优解
        for (int c = 0; c <= C; c ++) {
            memo[0][c] = c >= w[0] ? v[0] : 0;
        }

        //  对 [0, ... i] 推导求解
        for (int i = 1; i < n; i ++) {
            for (int c = 0; c <= C; c ++) {
                memo[i%2][c] = max( memo[(i-1)%2][c],
                                  (w[i] <= c ? v[i] + memo[(i-1)%2][c-w[i]] : 0)
                );
            }
        }
        return memo[(n-1)%2][C];
    }



    /**
     * 01背包问题-空间复杂度的优化
     * 上次将memo数组只设为两行来进行空间的节约
     * 我们发现，在每一趟更新memo数组的时候
     * 只会考虑到pre[c] 和 val[index] + pre[c-w[index]]
     * 也就是 索引 c 和 c-w[i]
     * 那么我们可以从cur[c]开始向cur[0]更新，这样在 < c 的索引上需要考虑的pre值不会变动，可以正常更新
     * 所以可用 一行 的空间来完成，同时 当不需要考虑index索引物品的时候，可以提前跳过当前更新
     * 即 w[i] > c 时，提前跳出当前更新
     */
    int knapsack01_best_space (const vector<int> &w, const vector<int> &v, int C) {
        int n = v.size();


        //  因为bestValue最优解与index 和 容量c有关，故memo取二维数组来记忆
        vector<int> memo(C+1, -1);

        if (n == 0 || C == 0) return 0;

        //  [0, 0] 范围物品对应各容量c 取得的价值最优解
        for (int c = 0; c <= C; c ++) {
            memo[c] = c >= w[0] ? v[0] : 0;
        }

        //  对 [0, ... i] 推导求解
        for (int i = 1; i < n; i ++) {
            for (int c = C; c >= w[i]; c --) {
                memo[c] = max( memo[c],
                               v[i] + memo[c-w[i]]
                );
            }
        }
        return memo[C];
    }
};

int main() {
    int arr[] = {1,2,3,1};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    cout << Solution().rob(nums) << endl;
    return 0;
}
