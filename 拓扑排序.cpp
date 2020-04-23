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
        return ret;
    }
};
