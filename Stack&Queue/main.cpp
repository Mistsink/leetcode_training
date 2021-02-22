#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Command {
    string s;       // go | operate
    TreeNode* node;
    Command(string s, TreeNode* node): s(s), node(node){}
};


class Solution {
public:

    /**
     * 20. 有效的括号
     */
    bool isValid(string s) {
        stack<char> stack;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stack.push(s[i]);
                continue;
            }

            if (stack.size()) {
                if (s[i] == ')' && stack.top() != '(') return false;
                if (s[i] == ']' && stack.top() != '[') return false;
                if (s[i] == '}' && stack.top() != '{') return false;

                stack.pop();
            } else return false;
        }

        return stack.size() == 0;
    }


    /**
     * 144. 二叉树的前序遍历
     */
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == NULL) return res;

        stack<Command> stack;
        stack.push(Command("go", root));

        while (!stack.empty()) {
            Command cur = stack.top();
            stack.pop();

            if (cur.s == "operate") {
                res.push_back(cur.node->val);
            } else {

                if (cur.node -> right) {
                    stack.push(Command("go", cur.node->right));
                }

                if (cur.node->left) {
                    stack.push(Command("go", cur.node->left));
                }

                stack.push(Command("operate", cur.node));
            }
        }

        return res;

    }


    /**
     * 102. 二叉树的层序遍历
     */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;

        queue<pair<TreeNode*, int>> queue;

        queue.push(make_pair(root, 0));

        while (!queue.empty()) {
            TreeNode* cur = queue.front().first;
            int level = queue.front().second;
            queue.pop();

            if (level == res.size()) // 此时res中没有level索引项
                res.push_back(vector<int>());
            res[level].push_back(cur->val);

            if (cur->left) queue.push(make_pair(cur->left, level+1));
            if (cur->right) queue.push(make_pair(cur->right, level+1));
        }

        return res;
    }



    /**
     * 279. 完全平方数
     */
     //     转换为图论的问题，每个数字为顶点，差值为完全平方数的数字间有边
     [[noreturn]] int numSquares(int n) {

        assert(n > 0);

        queue<pair<int, int>> queue;        // <num, steps>: steps 表示从参数n到该数字num所经过的步骤数
        queue.push(make_pair(n, 0));

        vector<bool> visited(n+1, false);   // 记录0-n这n+1个数字是否被访问过
        visited[n] = true;

        while (!queue.empty()) {
            int num = queue.front().first, step = queue.front().second;
            queue.pop();

            for (int i = 1; ; i ++) {
                int a = num - i*i;

                if (a < 0) {
                    break;
                }

                if (a == 0) {
                    return step+1;
                }

                if (!visited[num-i*i]) {
                    queue.push(make_pair(num - i*i, step+1));
                    visited[num-i*i] = true;
                }
            }

        }
    }



    /**
     * 347. 前 K 个高频元素
     */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;       // <num, freq>
        for (int num: nums) freqMap[num]++;

        // pair: <freq, num>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (unordered_map<int, int>::iterator iter = freqMap.begin();
            iter != freqMap.end(); iter ++){
            if (pq.size() == k) {
                if (iter->second > pq.top().first) {
                    pq.pop();
                    pq.push(make_pair(iter->second, iter->first));
                }
            } else {
                pq.push(make_pair(iter->second, iter->first));
            }
        }

        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;

    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
