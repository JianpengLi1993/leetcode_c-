/*
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：


	节点的左子树只包含小于当前节点的数。
	节点的右子树只包含大于当前节点的数。
	所有左子树和右子树自身必须也是二叉搜索树。

示例 1:

输入:
    2
   / \
  1   3
输出: true


示例 2:

输入:
    5
   / \
  1   4
     / \
    3   6
输出: false
解释: 输入为: [5,1,4,null,null,3,6]。
     根节点的值为 5 ，但是其右子节点值为 4 。
*/


方案一：分治法
//返回值应该包括子树是否为二叉搜索树，还要包括子树中最大的节点和最小的节点。
class ResultType {
public:
    bool isBST;
    TreeNode *maxNode, *minNode;
    ResultType() {
        this->isBST = true;
        this->maxNode = NULL;
        this->minNode = NULL;
    }
};

class Solution {
public:
    /**
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
    bool isValidBST(TreeNode *root) {
        ResultType result = helper(root);
        return result.isBST;
    }
    //1.确定递归函数返回值：返回以root为根的子树是否是二叉搜索树，且返回子树中最大和最小的节点
    ResultType helper(TreeNode *root) {
        ResultType result;
        //3.出口确定
        if (root == NULL) {
            return result;
        }
        //2.1分治
        ResultType left = helper(root->left);
        ResultType right = helper(root->right);
        
        //2.2整合，利用各种判断，前三种都已确定不是二叉搜索了，所以最大最小节点不重要了，所以没有赋值。
        if (!left.isBST || !right.isBST) {
            result.isBST = false;
            return result;
        }
        
        if (left.maxNode != NULL && left.maxNode->val >= root->val) {
            result.isBST = false;
            return result;
        }
        
        if (right.minNode != NULL && right.minNode->val <= root->val) {
            result.isBST = false;
            return result;
        }
        //此时，说明以root为根的该子树是BST,所以需要赋值。
        result.isBST = true;
        result.minNode = left.minNode == NULL ? root : left.minNode;
        result.maxNode = right.maxNode == NULL ? root : right.maxNode;
        return result;
    }
};

