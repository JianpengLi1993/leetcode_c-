序列化过程，空节点用#号代替，只要父节点不为空，两个子节点都要保留，若父节点为空，不继续保留子节点，序列化后的字符串结尾的#号去除

class Solution {
public:
    //序列化函数
    string serialize(TreeNode *root) {
        vector<TreeNode *> Q;
        Q.push_back(root);

        for (int i = 0; i < Q.size(); i++) {
            TreeNode *node = Q[i];
            if (node == NULL) {
                continue;
            }
            Q.push_back(node->left);
            Q.push_back(node->right);
        }
        //去除尾部的连续空节点，即若结尾是若干#号时，去除。
        while (Q.size() > 0 && Q[Q.size() - 1] == NULL) {
            Q.pop_back();
        }

        if (Q.size() == 0) {
            return "{}";
        }
        //将队列中元素转化为序列串。
        stringstream ss;
        ss << "{" << Q[0]->val;
        for (int i = 1; i < Q.size(); i++) {
            if (Q[i] == NULL) {
                ss << ",#";
            } else {
                ss << "," << Q[i]->val;
            }
        }
        ss << "}";
    
        return ss.str(); 
    }
    //反序列化函数
    TreeNode *deserialize(string data) {
        if (data == "{}") {
            return NULL;
        }

        vector<string> vals = split(data.substr(1, data.size() - 2), ",");
        TreeNode *root = new TreeNode(atoi(vals[0].c_str()));
        queue<TreeNode *> Q;
        Q.push(root);

        bool isLeftChild= true;
        for (int i = 1; i < vals.size(); i++) {
            if (vals[i] != "#") {
                TreeNode *node = new TreeNode(atoi(vals[i].c_str()));
                if (isLeftChild) {
                    Q.front()->left = node;
                } else {
                    Q.front()->right = node;
                }
                Q.push(node);
            }
            if (!isLeftChild) {
                Q.pop();
            }

            isLeftChild = !isLeftChild; 
        }
        return root;
    }
    //分割函数，
    vector<string> split(const string &str, string delim) {
        vector<string> results;
        int lastIndex = 0, index;
        while ((index = str.find(delim, lastIndex)) != string::npos) {
            results.push_back(str.substr(lastIndex, index - lastIndex));
            lastIndex = index + delim.length();
        }
        //若字符串结尾不为delim时，最后还会有一个子串需要加入results.
        if (lastIndex != str.length()) {
            results.push_back(str.substr(lastIndex, str.length() - lastIndex));
        }

        return results;
    }
};
