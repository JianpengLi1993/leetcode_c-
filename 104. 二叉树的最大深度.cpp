/******************************************************/
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

    3
   / \
  9  20
    /  \
   15   7

返回它的最大深度 3 。
/******************************************************/




//方案一：分治法：
class Solution {
public:
    //1.确定递归函数返回值含义：返回以root为根的子树的深度；
    int maxDepth(TreeNode* root) {
        //3.确定出口；
        if(root == NULL){
            return 0;
        }
        //4.最后往往需要检查一下若输入只有一个元素，即只有根结点时，程序是否适用。

        //2.1分割左右子树调用递归；
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        //2.2整合：利用分割调用得到的信息整合处理，作为当前的返回值；
        return max(leftDepth,rightDepth)+1;
        
    }
};

//方案二：遍历法
class Solution {
    private: int depth;
    public:
    //1.确定递归函数含义：遍历以root为根的子树，并更新全局变量depth；
        int maxDepth(TreeNode* root) {
        
            this->depth = 0;
            helper(root, 1);
            return this->depth;
        }
    
        void helper(TreeNode* node, int curtDepth) {
            //3.递归出口
            if (node == NULL) {
                return;
            }
        
            if (curtDepth > depth) {
                depth = curtDepth;
            }
            //2.递归分解
            helper(node->left, curtDepth + 1);
            helper(node->right, curtDepth + 1);
        }    
};
