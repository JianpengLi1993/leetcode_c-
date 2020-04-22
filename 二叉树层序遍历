class Solution {
    /**
     * @param root: The root of binary tree.
     * @return: Level order a list of lists of integer
     */
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        if (root == NULL) {
            return result;
        }
        //1.创建一个队列，霸气是节点都放在里面去（第一层节点）
        queue<TreeNode *> Q;
        Q.push(root);
        //2.while队列不空，处理队列中的节点，进而拓展出新节点
        while (!Q.empty()) {
            int size = Q.size();
            vector<int> level;
            //3.for循环，将上一层节点逐渐扩展到下一层的节点
            for (int i = 0; i < size; i++) {
                TreeNode *head = Q.front(); 
                Q.pop();
                level.push_back(head->val);
                if (head->left != NULL) {
                    Q.push(head->left);
                }
                if (head->right != NULL) {
                    Q.push(head->right);
                }
            }
            
            result.push_back(level);
        }
        
        return result;
    }
};
