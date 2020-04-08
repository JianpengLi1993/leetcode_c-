/*****************************************************************************/
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例:

输入: [1,2,3,null,5,null,4]
输出: [1, 3, 4]
解释:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---


/*****************************************************************************/
/**
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
    vector<int> rightSideView(TreeNode* root) {
         vector<int> res;
         if(root==NULL){
             return res;
         }
         queue<TreeNode*> q;
         q.push(root);
         while(!q.empty()){
             int n=q.size(); //一层pop之后，剩余的size为下一层的元素个数。
             for(int i=1;i<=n;i++){
                 TreeNode* node =q.front();
                 q.pop();
                 if(i==n){//当i==0时，输出的是每一层的第一个元素，即左视图。
                     res.push_back(node->val);
                 }
                 if(node->left){
                     q.push(node->left);
                 }
                 if(node->right){
                     q.push(node->right);
                 }
             }
         }
         return res;
    }
};
