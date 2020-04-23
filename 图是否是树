/*
1.n个节点必然存在n-1条边；
2.n个节点构成一个连通图；

本题重点：
1.构建邻接链表；
2.STL的嵌套以及初始化。
*/

using adjacentList = unordered_map<int, unordered_set<int>>;

class Solution {
public:
    /**
     * @param n: An integer
     * @param edges: a list of undirected edges
     * @return: true if it's a valid tree, or false
     */
    bool validTree(int n, vector<vector<int>> &edges) {
        // write your code here
        if (n == 0)
            return false;
        //前提条件：二叉树的节点个数与边的个数必然存在这一关系。   
        if (edges.size() != n - 1)
            return false;
            
        adjacentList graph = initializeGraph(n, edges);
        
        queue<int> q;
        unordered_set<int> hash;
        //queue是用来bfs模板进行层次遍历的，hash是用来记录是否是一个连通图。
        q.push(0);
        hash.insert(0);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            //返回值是一个set集合
            auto neighbors = graph[node];
            for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
                if (hash.find(*it) != hash.end())
                    continue;
                hash.insert(*it);
                q.push(*it);
            }
        }
        
        return (hash.size() == n);
    }
    
private:
    //构建邻接链表
    adjacentList initializeGraph(int n, vector<vector<int>>& edges) {
        adjacentList graph;
        
        for (int i = 0; i < n; ++i) {
            unordered_set<int> temp;
            graph.insert(make_pair(i, temp));
        }
        
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[v].insert(u);
            graph[u].insert(v);
        }
        
        return graph;
        
    }

};
