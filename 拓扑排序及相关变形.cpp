/*
题目：

给定一个有向图，图节点的拓扑排序定义如下:
对于图中的每一条有向边 A -> B , 在拓扑排序中A一定在B之前.
拓扑排序中的第一个节点可以是图中的任何一个没有其他节点指向它的节点.
针对给定的有向图找到任意一种拓扑排序的顺序.

思路：

先遍历图，统计所有节点的入度。接着把所有入度为0的节点推入队列。然后是根据队列循环执行“删边”操作：
每次从队列头部取出一个节点，将其所有邻居节点的入度减1（相当于删边），如果减到0，就把该邻居节点推入队列，表示下一轮要优先定位的节点。

拓扑排序可以判断有向图是否有环。方法就是做完上面的操作后，判断一下所得到的拓扑序长度是否等于图中所有节点的数量。
如果有环的话，那么在所有节点被加入队列之前队列就会空（画一下图就能看出来）。

*/

class Solution {
public:
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
        vector<DirectedGraphNode*> ret;
        if (graph.empty()) return ret;
        //1.将所有入度不为零的节点，全部建立map结构，key为节点，value为对应的入度
        unordered_map<DirectedGraphNode*, int> mymap;
        for (auto& node : graph) {
            for (auto& neighbor : node->neighbors) {
                if (mymap.count(neighbor) == 0) {
                    mymap[neighbor] = 1;
                } else {
                    mymap[neighbor]++;
                }
            }
        }
        //2.若map中不存在该节点的key，说明入度为零，存入queue和result中。即bfs模板中的首先入队列的值为入度为0的节点。
        queue<DirectedGraphNode*> q;
        for (auto& node : graph) {
            if (mymap.count(node) == 0) {
                q.push(node);
                ret.push_back(node);
            }
        }
        //3.下面就是bfs的遍历了，出队时要将相关邻居的入度减一，而新节点入队的判断要求为入度是否为0；
        //while退出有两种可能，一是完成了所有节点的遍历，完成拓扑排序，二是存在环，最后任有若干节点的入度不为0；
        while (!q.empty()) {
            auto& cur = q.front(); q.pop();
            for (auto& next : cur->neighbors) {
                mymap[next]--;
                if (mymap[next] == 0) {
                    q.push(next);
                    ret.push_back(next);
                }
            }
        }
        //4.若题目给的图不一定是可以拓扑排序的，即有可能是包括环的，这时可以通过对result中的元素个数判断，不够就说明中间有环。
        //例如：https://www.lintcode.com/problem/course-schedule/description。问的就是是否存在拓扑排序，只要检查不包括环就行。
        return ret;
    }
};

**另外有题目问是否只包含一条拓扑序列，是指queue序列是否时时刻刻只有一个节点在队列中，也就是每一次遍历后只有一个节点入度为0；
还要判断这个拓扑序列与org是否一一相等。
https://www.lintcode.com/problem/sequence-reconstruction/。
答案：
https://www.jiuzhang.com/solutions/sequence-reconstruction/#tag-other-lang-java。
//本题构建的是有向图。
class Solution {
    /**
     * @param org a permutation of the integers from 1 to n
     * @param seqs a list of sequences
     * @return true if it can be reconstructed only one or false
     */
    public:
        
        bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
            // build graph
            unordered_map<int, unordered_set<int>> graph = getGraph(seqs);
            /**
            * we need to build graph from seqs!! cause we are using seqs to try to build org
            * 
            */
            // build indegree
            unordered_map<int, int> indegree = getIndegree(graph);
            
            // get zero indegree, offer in queue
            queue<int> queue;
            for (auto& node : graph) {
                if (indegree[node.first] == 0) {
                    queue.push(node.first);
                }
            }
            // we shoud have a container to compare it to org
            vector<int> sequence;
            // bfs
            while (!queue.empty()) {
                int size = queue.size();
                //这个是关键
                // 因为是唯一构成，所以每个元素的先序应该只有一个，即度为1
                // 只有每次queue中只有一个元素的时候，产生的序列才是唯一的
                if (size > 1) {
                    return false;
                }
                int node = queue.front();
                queue.pop();
                sequence.push_back(node);
                for (auto& neib : graph[node]) {
                    indegree[neib]--;
                    if (indegree[neib] == 0) {
                        queue.push(neib);
                    }
                }
            }
            
            if (sequence.size() != org.size()) { // first compare length, to prevent egde cases.
                return false;
            }
            
            for (int i = 0; i < org.size(); i++) {
                if (sequence[i] != org[i]) {
                    return false;
                }
            }
            
            return true;
        }
    
    private:
        unordered_map<int, unordered_set<int>> getGraph(vector<vector<int>> &seqs) {
            unordered_map<int, unordered_set<int>> graph;
            //给所有节点都建了map,
            for (auto path : seqs) {
                for (int node : path) {
                    unordered_set<int>tmp;
                    graph.insert(make_pair(node, tmp));
                }
            }
            //接着赋值邻居；这里是通过遍历边的出发节点，
            //将出发节点后跟着的节点作为邻居加入set,不同的path中可能有相同的边，所以要用set
            for (auto path : seqs) {
                //这里实际构建的是有向图，因此实际i从0到size-2;
                for (int i = 0; i < path.size() - 1; i++) {
                    graph[path[i]].insert(path[i+1]);
                }
            }
            return graph;
        }
    
    private: 
        unordered_map<int, int> getIndegree(unordered_map<int, unordered_set<int>> graph) {
            unordered_map<int, int> indegree;

            for (auto& node : graph) {
                indegree.insert(make_pair(node.first, 0));
            }
            for (auto& node : graph) {
                for (auto& neib : node.second) {
                    indegree[neib]=indegree[neib] + 1;
                }
            }
            return indegree;
        }
};

//课程表I
class Solution {
public:
    /*
     * @param numCourses: a total of n courses
     * @param prerequisites: a list of prerequisite pairs
     * @return: true if can finish all courses or false
     */
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses);
        
        // 建图,由于知道节点个数和下标关系，所以建图简单，包括入度关系可以用一个数组表示
        for (auto edge: prerequisites) {
            graph[edge.second].push_back(edge.first);
            inDegree[edge.first]++;
        }
        
        int numChoose = 0;
        queue<int> que;
        
        // 将入度为 0 的编号加入队列
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                que.push(i);
            }
        }
        
        while (not que.empty()) {
            int now = que.front();
            que.pop();
            numChoose++;
            // 将每条边删去，如果入度降为 0，再加入队列
            for (int nxt: graph[now]) {
                inDegree[nxt]--;
                if (inDegree[nxt] == 0) {
                    que.push(nxt);
                }
            }
        }
        
        return numChoose == numCourses;
    }
};

###############
综上：
思路：先把图建造好了用dict，然后把入度存到另一个dict里面。把入度为0的点拿出来放进queue 和 我们的拓扑序当中。
使用bfs，从queue中拿出一个点for它的neighbor并且入度减 1。当任意一个neighbor减到0的时候就把他们放进queue和拓扑序列中。
因为这个题考查的是有没有一个拓扑序，所以在每次while queue下面我们都要判断一下这个queue里面是不是只有一个元素。
时间复杂度：O(n*l)
这个题和之前做过的 course schedul1，2. topological sort 很像
sequence reconstruction：是否有且只有一个拓扑序
course schedule 1: 问的是有没有一个拓扑序
course schedule 2:让我们求出任意一个拓扑序
topological sort：让我们求出任意一个拓扑序
这些题目本质都是求拓扑序。不同点是在于topological 之间给了图和adjency list。我们只需要统计一下入度就可以。 但是剩下这三道题都是隐士图。
在course schedule1 和course schedule2 这两道题目中题目暗示了dependent的关系并且又说了找出任意一个序列（不止有一个序列）
这些条件暗示可以用拓扑排序去做。在sequence reconstruction中他给了一个序列。然后又给了几个子序列。问这几个子序列能不能生成那一个给定的序列，
所以等于是变相问我能不能找到有且只有一个拓扑序。
难点：我认为难点在于 course1，2 sequence reconstruction中怎么根据输入来建造图和统计入度。这个应该根据不同的数据结构进行变换。
这两个做完了就是往queue 和 拓扑序里面放入度为0的点。使用bfs，从queue中拿出一个点for它的neighbor并且入度减 1。
当任意一个neighbor减到0的时候就把他们放进queue和拓扑序列中。
以后碰到这种类型的题目需要 1.判断出使用拓扑序的做法
2.根据不同的输入创造图，并且统计每个点的入度，如果点是从0开始可以考虑用数组，如果不是0开始就用dict来存。
3.套用bfs的套路解决问题
