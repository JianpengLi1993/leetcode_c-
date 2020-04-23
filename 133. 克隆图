/*
给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。

图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

class Node {
    public int val;
    public List<Node> neighbors;
}

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

*/

class Solution {
public:
    /*
     * @param node: A undirected graph node
     * @return: A undirected graph node
     */
    Node* cloneGraph(Node* node) {
        // write your code here
        if (node == nullptr) {
            return node;
        }
        //1.获取旧图的所有节点
        vector<Node*> nodes = getNodes(node);
        //2.先复制生成另一份全节点，并构建新旧节点之间的map关系；
        unordered_map<Node*, Node*> mapping = cloneNodes(nodes);
        //3.利用全部旧节点中的neighbors信息，以及新旧节点的map关系，将新节点中的neighbor信息填好。
        connectNeighbors(nodes, mapping);
        //返回开始的旧节点对应的新节点。
        return mapping[node];
    }
    
private:
    vector<Node*> getNodes(Node* node) {
        //queue用来实现bfs遍历，
        //Set用来确保节点不重复遍历，即不走回头路
        //nodes用来存放遍历到的节点，即在一个联通图下的节点。
        queue<Node*> Q;
        unordered_set<Node*> Set;
        vector<Node*> nodes;
        
        Q.push(node);
        Set.insert(node);
        nodes.push_back(node);
        while (!Q.empty()) {
            Node* head = Q.front();
            Q.pop();
            for (auto neighbor : head->neighbors) {
                if (Set.find(neighbor) != Set.end()) {
                    continue;
                }
                Q.push(neighbor);
                Set.insert(neighbor);
                nodes.push_back(neighbor);
            }
        }
        
        return nodes;
    }
    
    unordered_map<Node*, Node*> cloneNodes(vector<Node*> nodes) {
        unordered_map<Node*, Node*> mapping;
        for (auto node : nodes) {
            mapping.insert(make_pair(node, new Node(node->val)));
        }
        return mapping;
    }
    
    void connectNeighbors(vector<Node*> nodes,  unordered_map<Node*, Node*> mapping) {
        
         for (auto node : nodes) {
            for (auto neighbor : node->neighbors) {
                Node* newNode = mapping[node];
                Node* newNeighbor = mapping[neighbor];
                newNode->neighbors.push_back(newNeighbor);
            }
        }
    }
};



