/*
给一棵二叉树, 找到和为最小的子树, 返回其根节点。输入输出数据范围都在int内。

*/

//分治法和遍历的结合，遍历强调的是有一个全局变量，一边递归一边更新全局变量。
class Solution {
    private：
    TreeNode subtree = nullptr;
    int subtreeSum = INT_MAX;
    
    public：
    TreeNode findSubtree(TreeNode* root) {
        helper(root);
        return subtree;
    }
    //原接口返回值是子树的根结点，但是左右子树仅凭结点无法做下一步判断，因此，需要重新写一个函数调用，返回子树的和。
    //1.确定递归函数的返回值，以root为根的子树的和。
    int helper(TreeNode* root) {
        //3.确定出口
        if (root == NULL) {
            return 0;
        }
        //2.分割和整合,sum为左右子树的和加上根的值。
        int sum = helper(root->left) + helper(root->right) + root->val;
        //更新subtreeSum;
        if (sum <= subtreeSum) {
            subtreeSum = sum;
            subtree = root;
        }
        return sum;
    }
};

方案二：纯分治法，利用自己构造的返回值类型，使得递归返回值包含多种
//包含最小和子树的根结点（与当前节点不一定是同一个），最小和，以及当前节点对应的子树的和。
class ResultType {
    public:
    TreeNode minSubtree;
    int sum, minSum;
    ResultType(TreeNode* minSubtree, int minSum, int sum) {
        this->minSubtree = minSubtree;
        this->minSum = minSum;
        this->sum = sum;
    }
};

class Solution {
    /**
     * @param root the root of binary tree
     * @return the root of the minimum subtree
     */
    public:
    TreeNode findSubtree(TreeNode* root) {
        ResultType result = helper(root);
        //从返回值类型中选取有用的成员变量
        return result->minSubtree;
    }
    //1.确定递归函数返回值：返回以root为根的子树对应的ResultType
    ResultType helper(TreeNode* node) {
        if (node == NULL) {
            return new ResultType(NULL, INT_MAX, 0);
        }
        //2.1分治，
        ResultType leftResult = helper(node->left);
        ResultType rightResult = helper(node->right);
        //存放当前节点对应的子树和sum，而minSubtree和minSum还需要重新判定后才能确定
        ResultType result = new ResultType(
            node,
            leftResult->sum + rightResult->sum + node->val,
            leftResult->sum + rightResult->sum + node->val
        );
        //2.2整合，找到左右两个子树中最小和的子树节点以及对应的子树和
        if (leftResult->minSum <= result->minSum) {
            result->minSum = leftResult->minSum;
            result->minSubtree = leftResult->minSubtree;
        }
        
        if (rightResult->minSum <= result->minSum) {
            result->minSum = rightResult->minSum;
            result->minSubtree = rightResult->minSubtree;
        }
        
        return result;
    }
}
