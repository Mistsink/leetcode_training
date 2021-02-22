#include <iostream>
#include <vector>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



class Solution {
public:
    /**
     * 104. 二叉树的最大深度
     */
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 1;

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;

    }


    /**
     * 226.翻转二叉树
     */
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;

        invertTree(root->left);
        invertTree(root->right);
        swap(root->left, root->right);

        return root;
    }


    /**
     * 112. 路径总和
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        if (root && !root->left && !root->right)
            return targetSum == root->val;

        return hasPathSum(root->left, targetSum-root->val) || hasPathSum(root->right, targetSum-root->val);
    }

    /**
     * 257. 二叉树的所有路径
     */
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;

        if (!root) return res;

        if (!root->left && !root->right) {
            res.push_back(to_string(root->val));
            return res;
        }

        vector<string> leftPath = binaryTreePaths(root->left);
        for (string path: leftPath) res.push_back(to_string(root->val) + "->" + path);

        vector<string> rightPath = binaryTreePaths(root->right);
        for (string path: rightPath) res.push_back(to_string(root->val) + "->" + path);

        return res;
    }


    /**
     * 437. 路径总和 III
     */
    //      返回路径个数
    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        int res;
        res = findPath(root, sum);      //  包含该节点到路径数

        res += pathSum(root->left, sum);    //  不包含该节点到路径数
        res += pathSum(root->right, sum);

        return res;
    }



    /**
     * 235. 二叉搜索树的最近公共祖先
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (!root) return NULL;

        if ((p->val >= root->val && q->val <= root->val)
            || (p->val <= root->val && q->val >= root->val))
            return root;

        if (p->val > root->val) return lowestCommonAncestor(root->right, p, q);
        else return lowestCommonAncestor(root->left, p, q);
    }

private:
    /**
     * 寻找包含node的路径，返回路径个数
     */
    int findPath(TreeNode* node, int sum) {
        //  因为未说明必须遍历到根节点，故终止条件为NULL
        if (!node) return 0;

        int res = 0;

        if (node->val == sum)   //  因为有节点数值为负数，故不可就此返回，应继续遍历
            res += 1;

        res += findPath(node->left, sum - node->val);
        res += findPath(node->right, sum - node->val);

        return res;
    }
};


int main() {
    return 0;
}
