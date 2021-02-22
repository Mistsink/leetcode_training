#include <iostream>
#include <vector>

using namespace std;


class Solution {
private:
    const string letterMap[10] = {
            " ",
            "",
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz",
    };



    /**
     * 寻找digits[index]的解，并与preStr拼接
     * @param digits    数字字符串
     * @param index     当前数字索引
     * @param preStr    已翻译成功的字符串
     * @param <string>  完全翻译后的解的数组
     */
    void findCombination(const string &digits, int index, const string &preStr, vector<string> &res) {
        if (index == digits.size()) {
            res.push_back(preStr);
            return;
        }

        string letters = letterMap[digits[index]-'0'];

        for (char letter: letters) {
            findCombination(digits, index + 1, preStr + letter, res);
        }

    }


    /**
     * 生成[0 ~ index] 的全排列
     * @param nums      提供的所有数字
     * @param index     当前所要排列的索引
     * @param prePer    [0 ~ index-1]已排列好的数字组合
     * @param res       所有的解的数组
     * @param visited   记录已经被遍历的数字
     */
    void generatePermutation(vector<int> &nums, int index, vector<int> &prePer, vector<vector<int>> &res, vector<bool> visited) {
        if (index == nums.size()) {
            res.push_back(prePer);
            return;
        }

        for (int i = 0; i < nums.size(); i ++) {
            if (!visited[i]) {
                prePer.push_back(nums[i]);
                visited[i] = true;
                generatePermutation(nums, index+1, prePer, res, visited);

                //  下面将prePer和visited进行回溯的状态回退
                prePer.pop_back();
                visited[i] = false;
            }
        }
    }

public:
    /**
     * 17. 电话号码的字母组合
     */
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits == "") return res;
        findCombination(digits, 0, "", res);
        return res;
    }

    /**
     * 46. 全排列
     */
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty()) return res;

        vector<int> prePer;
        vector<bool> visited(nums.size(), false);
        generatePermutation(nums, 0, prePer, res, visited);

        return res;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
