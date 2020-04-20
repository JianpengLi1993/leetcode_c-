/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]


示例 1:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

示例 2:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。


说明:
	所有节点的值都是唯一的。
	p、q 为不同节点且均存在于给定的二叉树中。

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
方案一：遍历所有路径，从中将包含两个节点的路径返回，比较

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*>first = findPath(root,p);
        vector<TreeNode*>second = findPath(root,q);
        int i = first.size() - 1;
        int j = second.size() - 1;
        //倒序比较
        while (i >= 0 && j >= 0 && first[i] == second[j]) {
           i--;
           j--;
       }
       return first[i+1]; 
    }
    //1.确定递归函数的返回值：返回以root为根的子树中，自目标值：end到root之间的节点路径，若没有找到，则返回空的vector.
    vector<TreeNode*> findPath(TreeNode* root, TreeNode* end){
         vector<TreeNode*> ans;
        //3.确定出口
        if (root == NULL) {
            return ans;
        }
        //2.1分治，分别得到以root出发，左右子树找到目标值的路径。
        vector<TreeNode*> left = findPath(root->left,end);
        vector<TreeNode*> right = findPath(root->right,end);
        //2.2整合，
        //2.2.1左侧子树若找到目标值，则在返回序列中添加当前层的root，一并返回
        if (!left.empty()) {
            left.push_back(root);
            return left;
        }
        //2.2.2右侧子树若找到目标值，则在返回序列中添加当前层的root，一并返回
        if (!right.empty()) {
            right.push_back(root);
            return right;
        }
        //4.确定当输入只有一个元素时，即此刻左右子树都没有找到，有两种可能，一是当前分支确实没有，另一种情况时root本身就是目标节点。
        if (left.empty() && right.empty()) {
            if (root == end) {
                ans.push_back(root);
                return ans;
            } else {
                return ans;
            }
        }
        return ans;
    }

};

方案二：分治法

class Solution {
    /*这里的递归函数返回值定义不是很清晰，可以包含多种情况，即当返回值不为空时，有以下两种情况：
    
    // （1.1）如果找到了以root为根的子树中同时包含A、B，即左右子树各包含一个，就返回这个root,此时，由于递归是自下而上，
    //        所以第一次发生这种情况时，root为目标LCA.
    
    // （1.2）如果只碰到A，就返回A，或者如果只碰到B，就返回B，即仅有左右子树中一个返回值不为空，
    //    (1.2.1)此时若是比（1.1）情况发生层次靠上，即（1.1）先发生了，则一路返回的是（1.1）对应的LCA,也就是最终的LCA.
    //    (1.2.2)此时若是比（1.1）情况发生层次靠下，则说明（1.1）还未发生，还未找到LCA,此时返回的只是节点A或B本身。
    //           不断递归向上，直到（1.1）发生
    
    // （2）如果都没有，就说明该分支没有目标值，就返回null
    
    // （3）若其中一个目标值是两者中的共同根，即LCA为其中一个目标节点，此时，返回该节点即可。向上递归过程中转化为（1.2.1）的情况。
    */
    public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* node1, TreeNode* node2) {
        if (root == NULL || root == node1 || root == node2) {
            return root;
        }
        
        // Divide
        TreeNode* left = lowestCommonAncestor(root->left, node1, node2);
        TreeNode* right = lowestCommonAncestor(root->right, node1, node2);
        
        // Conquer
        if (left != NULL && right != NULL) {
            return root;
        } 
        if (left != NULL) {
            return left;
        }
        if (right != NULL) {
            return right;
        }
        return NULL;
    }
};


   
