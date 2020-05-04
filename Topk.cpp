//用于vector的降序
bool cmp(const int& a, const int& b) {
    return a > b;
}

class Solution {
private:
    //这里我们用小顶堆，一共存放k个元素，这样堆顶的元素是当前第k大的元素，每添加一个新的元素时，我只要和堆顶比较，大于这个第k大的元素，就可以插进去
    //相当于我存放一个班中前五名到小顶堆中，堆顶是第五名，新来一个同学，只要成绩比第五名好，就可以提出第五名，再把它插入其中，再次排一次，找出新的第五名
    //这样的好处包括空前复杂度为O(k),add的时间复杂度O(logk),topk的时间复杂度为O(klogk);
    //而大顶堆需要将所有元素都放入堆中，空间O(n)，add为O(logn),topk为O(klogn);
    //greater<int>自带的仿函数或谓词；
    priority_queue<int, vector<int>, greater<int>> queue;
    int k;

public:
    Solution(int k) {
        this->k = k;
    }

    void add(int num) {
        if (queue.size() < k) {
            queue.push(num);
        } else if (queue.top() < num) {
            queue.pop();
            queue.push(num);
        }
    }

    vector<int> topk() {
        vector<int> topk;
        int n = queue.size();
        for (int i = 0; i < k && i < n ; ++i) {
            topk.push_back(queue.top());
            queue.pop();
        }
        //还要放回去
        for (int i = 0; i < n; ++i)
            queue.push(topk[i]);
        //最后再反向排序一下    
        sort(topk.begin(), topk.end(), cmp);
        return topk;
    }
};


方案二：
其实可以利用前面的寻找第k大的算法，找到第k大的数字是谁，然后其后面的子区间就是topk的其他元素。
