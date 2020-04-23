/*
给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

示例 1:

给定二叉树 [3,9,20,null,null,15,7]

    3
   / \
  9  20
    /  \
   15   7

返回 true 。

示例 2:

给定二叉树 [1,2,2,3,3,null,null,4,4]

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4

返回 false 。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //判断一个树是否是平衡二叉树，需要两个条件，包括左右子树是否都是平衡二叉树，以及左右子树的高度是否相差小于等于1；
class ResultType {
    public:
    bool isBalanced;
    int maxDepth;
    ResultType(bool isBalanced, int maxDepth) {
        this->isBalanced = isBalanced;
        this->maxDepth = maxDepth;
    }
};

class Solution {
    /**
     * @param root: The root of binary tree.
     * @return: True if this Binary tree is Balanced, or false.
     */
    public:
    bool isBalanced(TreeNode* root) {
        return helper(root)->isBalanced;
    }
    //1.确定递归函数的返回值，包括以root为根的子树是否是平衡二叉树，以及对应的高度
    ResultType* helper(TreeNode* root) {
        //3.出口
        if (root == NULL) {
            return new ResultType(true, 0);
        }
        //2.1分治
        ResultType* left = helper(root->left);
        ResultType* right = helper(root->right);
        //2.2整合处理
        // subtree not balance
        if (!left->isBalanced || !right->isBalanced) {
            return new ResultType(false, -1);
        }
        
        // root not balance
        if (abs(left->maxDepth - right->maxDepth) > 1) {
            return new ResultType(false, -1);
        }
        //4.判断一下是否满足只有一个节点的情况，这里满足。
        return new ResultType(true, max(left->maxDepth, right->maxDepth) + 1);
    }
};
