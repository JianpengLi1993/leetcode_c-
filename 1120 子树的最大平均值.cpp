/*
给一棵二叉树，找到有最大平均值的子树。返回子树的根结点。
*/
方案一：分治法
因为需要求平均数，所以要记录节点和以及接节点个数
自定义一个ResultType，记录节点和以及接节点个数
分治法计算每一颗子树的平均值，打擂台求出最大平均数的子树

class ResultType {
public:
    int sum, size;
    ResultType():sum(0), size(0) {}
    ResultType(int _sum, int _size): sum(_sum), size(_size) {}
};

class Solution {
public:
    /**
     * @param root the root of binary tree
     * @return the root of the maximum average of subtree 
     */
    TreeNode* findSubtree2(TreeNode* root) {
        // Write your code here
        helper(root);
        return node;
    }
    //1. 确定递归函数的返回值，包括左右子树的和，以及包含节点个数
    ResultType helper(TreeNode* root) {
        //3 确定出口
        if (root == NULL) {
            return ResultType();
        }
         // 2.1 分治法计算左右子树的平均值
        ResultType left = helper(root->left);
        ResultType right = helper(root->right);
         // 2.2 当前subtree的结果是左右两颗子树的和的平均值加上自身
        ResultType result = ResultType(left.sum + right.sum + root->val,
                                       left.size + right.size + 1);
         // 利用遍历，打擂台比较得到最大平均值的子树
        if (node == NULL || result.sum * data.size >= data.sum * result.size) {
            data = result;
            node = root;
        }

        return result;
    }

private:
    TreeNode* node = NULL;
    ResultType data;
};
