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



    /**
     * 求解C(n, k), 保存在preC中
     * @param start     当前需要求解的数字
     * @param preC      过去已求得的解的数组
     */
    void generateCombinations(int n, int k, int start, vector<int> &preC, vector<vector<int>> &res) {

        if (preC.size() == k) {     //  已求得k个解
            res.push_back(preC);
            return;
        }

        //  start作为初始值，使其向后求解，同时start之前的值也都被用过了，不需要进行额外的标记
        //  剪枝：preC中还剩下k - preC.size()个空位，那么[i ~ n]应该最少有k - preC.size()个数
        //          所以：n - i + 1 >= k - preC.size()
        for (int i = start; i <= n - k + preC.size() + 1; i ++) {
            preC.push_back(i);
            generateCombinations(n, k, i + 1, preC, res);
            preC.pop_back();
        }
    }



    int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    /**
     * 在board的[startX, startY]位置去寻找word的index索引字符
     */
    bool searchWord(const vector<vector<char>> &board, const string &word, int index, int startX, int startY, vector<vector<bool>> &visited) {
        if (index == word.size() - 1) return board[startY][startX] == word[index];

        if (board[startY][startX] == word[index]) {

            visited[startX][startY] = true;

            //  往四个方向继续寻找
            for (int i = 0; i < 4; i ++) {
                int newX = startX + d[i][1];
                int newY = startY + d[i][0];
                if (inArea(board, newX, newY) && !visited[newX][newY]) {
                    if(searchWord(board, word, index + 1, newX, newY, visited)) return true;
                }
            }

            visited[startX][startY] = false;
        }

        return false;
    }
    bool inArea(const vector<vector<char>>&board, int x, int y) {
        int mX = board[0].size(), mY = board.size();

        return x >= 0 && x < mX && y >= 0 && y < mY;
    }


    void dfs (const vector<vector<char>> &grid, int startX, int startY, vector<vector<bool>> &visited) {
        visited[startX][startY] = true;

        //  往四个方向继续寻找
        for (int i = 0; i < 4; i ++) {
            int newX = startX + d[i][1];
            int newY = startY + d[i][0];
            if (inArea(grid, newX, newY) && grid[newY][newX] == '1' && !visited[newX][newY]) {
                dfs(grid, newX, newY, visited);
            }
        }

    }

    /**
     * 在n皇后问题中，求解放置index索引的皇后(即index行)
     * @param row       求解得到的每一行上皇后所在列索引的解
     */
    void putQueen(int n, int index, vector<int> &row, vector<vector<string>> &res) {
        if (index == n) {
            res.push_back( generateBoard(n, row) );
            return;
        }

        for (int i = 0; i < n; i ++) {
            //  在index索引行中，寻求i列的合法解
            if ( !col[i] && !dia1[index + i] && !dia2[index - i + n -1] ) {
                col[i] = dia1[index + i] = dia2[index - i+n-1] = true;
                row.push_back(i);
                putQueen(n, index + 1, row, res);

                col[i] = dia1[index + i] = dia2[index - i+n-1] = false;
                row.pop_back();
            }
        }
    }
    vector<bool> col, dia1, dia2;   //  分别记录每一列上，左对角线，右对角线上是否有皇后
    vector<string> generateBoard(int n, vector<int> & row) {
        vector<string> board(n, string(n, '.'));
        for (int i = 0; i < n; i ++) {
            board[i][row[i]] = 'Q';
        }
        return board;
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



    /**
     * 77. 组合
     */
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;

        if (n <=0 || k <= 0) return res;

        vector<bool>visited(n-1, false);

        vector<int> preC;
        generateCombinations(n, k, 1, preC, res);

        return res;
    }




    /**
     * 79. 单词搜索
     */
    bool exist(vector<vector<char>>& board, string word) {

        vector<vector<bool>> visited(board[0].size(), vector<bool>(board.size(), false));

        for (int i = 0; i < board.size(); i ++) {
            for (int j = 0; j < board[i].size(); j ++) {
                if (searchWord(board, word, 0, j, i, visited)) return true;
            }
        }

        return false;
    }


    /**
     * 200. 岛屿数量
     */
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited(grid[0].size(), vector<bool>(grid.size(), false));

        int res = 0;

        for (int i = 0; i < grid.size(); i ++) {
            for (int j = 0; j < grid[i].size(); j ++) {
                if (grid[i][j] == '1' && !visited[j][i]){
                    res ++;
                    dfs(grid, j, i, visited);
                }
            }
        }

        return res;
    }



    /**
     * 51. N 皇后
     */
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> row;

        col = vector<bool>(n, false);
        dia1 = dia2 = vector<bool>(2 * n -1, false);

        putQueen(n, 0, row, res);
        return res;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
