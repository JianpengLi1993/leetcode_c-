编写一个程序，找出第 n 个丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

说明:  


	1 是丑数。
	n 不超过1690。
想到不断生成丑数，每一个丑数都是由前面的丑数与三个基准相乘得来的，而且每次都需要对当前得到的所有丑数进行排序，取出最小的进行下一轮与基准相乘，
包含popMin、add、查看min三个操作，正好对应优先队列。
利用优先队列有自动排序的功能
每次取出队头元素，存入队头元素*2、队头元素*3、队头元素*5
但注意，像12这个元素，可由4乘3得到，也可由6乘2得到，所以要注意去重

1 //升序队列，小顶堆
2 priority_queue <int,vector<int>,greater<int> > q;
3 //降序队列，大顶堆(默认是大顶堆)
4 priority_queue <int,vector<int>,less<int> >q;

class Solution {
public:
    /*
     * @param n: An integer
     * @return: the nth prime number as description.
     */
    int nthUglyNumber(int n) {
        // write your code here
        priority_queue<long,vector<long>,greater<long>>qu;
        qu.push(1);
        if(n == 1)return 1;
        for(int i = 1;i<n;i++){
            long tmp = qu.top();
            qu.push(tmp*2);
            qu.push(tmp*3);
            qu.push(tmp*5);
            //去重，这里的去重并不是在放入qu之前进行判断的，而是先都放进去了，当取出来作为下一轮的基准时判断是否和之前的一致，如一样，不断pop();
            while(qu.top() == tmp)
                qu.pop();
        }
        return qu.top();
    }
};

也可以用set来做去重：

class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue <double,vector<double>,greater<double> > q;
        set<int> s;
        s.insert(1);
        vector<int> mask({2,3,5});
        double answer=1;
        for (int i=1;i<n;++i)
        {
            for (int &j:mask)
                if (s.count(answer*j)==0)
                {
                    q.push(answer*j);
                    s.insert(answer*j);
                }
            answer=q.top();
            q.pop();
        }
        return answer;
    }
};
