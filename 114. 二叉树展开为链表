/*
给定一个二叉树，原地将它展开为链表。

例如，给定二叉树

    1
   / \
  2   5
 / \   \
3   4   6

将其展开为：

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

*/

方案一：遍历递归法
//利用前序遍历+lastNode记录上一个节点
class Solution {
public:
    //设定一个全局变量
    TreeNode* lastNode = NULL;
    void flatten(TreeNode* root) {
        if(root == NULL){
            return;
        }
        if(lastNode!=NULL){
            lastNode->left=NULL;
            lastNode->right=root;
        }
        //在进入下一层之前，记录lastNode.
        lastNode=root;
        //这里必须要提前保存，因为在下一层递归中的lastNode，就是当前层的root,lastNode->right会被修改
        TreeNode* rightNode = root->right;
        flatten(root->left);
        flatten(rightNode);
    }
};

方案二：分治法

class Solution {
    public:
    void flatten(TreeNode* root) {
        helper(root);
    }
    
    //1. 返回以root为根子树变形后的链表的最后一个节点
    private:
    TreeNode* helper(TreeNode* root) {
        //3. 确定出口
        if (root == NULL) {
            return NULL;
        }
        //2.1分治
        TreeNode* leftLast = helper(root->left);
        TreeNode* rightLast = helper(root->right);
        
        //2.2整合，将root、左子树的链表以及右子树的链表三者串起来。
        //需要将左子树的根结点（root->left）连在root的右侧，右子树的根结点（root->right）连在左子树链表的最后一个节点右侧。
        if (leftLast != NULL) {
            leftLast->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
        //若右子树链表存在，则整个连接起来后的链表的最后结点是rightLast
        if (rightLast != NULL) {
            return rightLast;
        }
        //若右子树链表不在，再判断左子树的链表是否存在
        if (leftLast != NULL) {
            return leftLast;
        }
        //若左右子树的链表都不在，则返回根结点作为该层的链表的最后一个节点
        return root;
    }
};
