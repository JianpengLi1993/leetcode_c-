方案一：非递归
非递归方式实现前序遍历时，首先存入当前节点值，然后先将右儿子压入栈中，再将左儿子压入栈中。对栈中元素遍历访问。
class Solution {
public:
    /**
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
    vector<int> preorderTraversal(TreeNode * root) {
        if (!root) return {};
        vector<int> result = {};
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->right) {
                st.push(node->right);
            }
            if (node->left) {
                st.push(node->left);
            }
        }
        return result;
        
    }
};

方案二：递归分治
class Solution {
public:
    /**
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
     //1.确定递归函数的返回值：返回以root为根的前序遍历序列
    vector<int> preorderTraversal(TreeNode * root) {
        // write your code here
        vector<int> ans;
        if(root == NULL)
            return ans;
        //2.分治，左右子树分别返回对应的前序序列
        vector<int> left = preorderTraversal(root->left);
        vector<int> right = preorderTraversal(root->right);
        //3.整合，先根，后左、右
        ans.push_back(root->val);
        for(auto i : left)
            ans.push_back(i);
        for(auto i : right)
            ans.push_back(i);
        return ans;
    }
};

方案三：递归遍历
class Solution {
    public：
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traverse(root, result);
        return result;
    }
    // 把root为跟的preorder加入result里面
    void traverse(TreeNode* root, vector<int> result) {
        if (root == NULL) {
            return;
        }

        result.push_back(root.val);
        traverse(root.left, result);
        traverse(root.right, result);
    }
};
