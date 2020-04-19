/**
给定一个二叉树，返回所有从根节点到叶子节点的路径。

说明: 叶子节点是指没有子节点的节点。

示例:

输入:

   1
 /   \
2     3
 \
  5

输出: ["1->2->5", "1->3"]

解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

 */
 
 分治法：
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        //3.出口
        if(root == NULL){
            return paths;
        }
        //2.1 分割左右子树
        vector<string> leftpaths = binaryTreePaths(root->left);
        vector<string> rightpaths = binaryTreePaths(root->right);
        
        //2.2 整合处理
        for(auto tmpPath : leftpaths){
            tmpPath = to_string(root->val) + "->" + tmpPath;
            paths.push_back(tmpPath);
            cout << tmpPath << endl;
        }
        for(auto tmpPath : rightpaths){
            tmpPath = to_string(root->val) + "->" + tmpPath;
            paths.push_back(tmpPath);
            cout << tmpPath << endl;
        }
        //4.判断一下当root只有一个元素时，是否能通过程序，显然此时以上leftpaths、rightpaths两个集合为空，导致paths也为空；需要特意处理
        if(paths.size()==0){

            paths.push_back( to_string(root->val) );
        }
        return paths;

    }
};
