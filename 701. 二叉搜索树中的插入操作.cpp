/**
给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 保证原始二叉搜索树中不存在新值。

 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    //1.确定分治递归函数：返回插入元素val到以root为根的二叉搜索树后的新树的根结点
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        //3.出口，这里返回值是新叶子节点；
        if (!root) 
            return new TreeNode(val);
        //2.1分治：分别返回若将val插入左右子树后对应的新根节点；
        if (val < root->val)
            root->left = insertIntoBST(root->left, val);
        else 
            root->right = insertIntoBST(root->right, val);   
        //2.2整合：返回当前根
        return root;        
    }
};
