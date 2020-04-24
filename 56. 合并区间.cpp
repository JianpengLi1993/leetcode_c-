/******************************************************************/
给出一个区间的集合，请合并所有重叠的区间。

示例 1:

输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].


示例 2:

输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。



这种在数组空间上进行各种操作的题目，我一般喜欢利用双指针进行解决。
  这题比较困难的地方在于各种边界情况的判定及其操作，以及如何快速有效的进行合并。
  双指针在解决这类问题的时候总有着很清晰的思路，我们首先要减少冗余，复杂的情况，因此排序应该是自然而然的想法。我们先设双指针，第一个save用于保留和扩展，另一个scan用于扫描。
  因为排完序之后我们对于左边界就不需要考虑了，因此我们还剩三种情况(X代表一个常数)：

eg:[1,3]⏞save,[4,5]⏞scan,这种是最简单的不相交情况，因此我们的save指针所指向的数组可以直接压入ans数组,然后将save移动到scan指针处：[1,3],[4,5]⏞save,[X,X]⏞scan
eg:[1,4]⏞save,[2,3]⏞scan,这种是被包含的情况，因此我们不需要操作save指针，scan指针继续往后移动:[1,4]⏞save,[2,3],[X,X]⏞scan
eg:[1,4]⏞save,[3,5]⏞scan,这种是里面唯一有一点点复杂的情况，即我们需要对于save指针指向的数组进行扩展，所以我们修改[1,4]⏞save→[1,5]⏞save,然后将scanscanscan指针移向下一个，
也就是这样:[1,5]⏞save,[3,5],[X,X]⏞scan

 现在思路非常简单了，只需要考虑一些细节上的问题:
①：排序二维数组，便于后续讨论
②：分情况进行讨论，对与双指针进行操作
③：最后一种特殊情况的处理(也就是scanscanscan指针移动到最后，但是还是没有压入数组中，需要特殊处理)


/******************************************************************/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 0 || intervals.size() == 1) return intervals;
        int u = 0, v = 0;
        vector<vector<int>> ans;
        // 思路①
        std::sort(intervals.begin(), intervals.end());
        // 思路②，整个过程intervals[u]与intervals[v]之间相隔的集合只有3种情况，
        //1.中间相隔的集合都包裹在intervals[u]中；
        //2.intervals[u]与intervals[v]紧挨着；
        //3.intervals[u]与intervals[v]在同一位置。
        while (v < intervals.size()) { 
            if (intervals[v][0] > intervals[u][1]) {
                //这种情况有可能intervals[u]没有加入结果集合
                ans.emplace_back(intervals[u]);
                u = v;
                ++v;
            } else if (intervals[v][1] < intervals[u][1]) {
                //这种情况的intervals[v]可以被忽略。
                ++ v;
            } else {
                //最后这种情况有可能intervals[u]没有加入结果集合
                intervals[u][1] = intervals[v][1];
                ++ v;
            }
        }
        // 思路③，所以最后只需要加intervals[u]
        ans.emplace_back(intervals[u]);
        return ans;
    }
};




//下面想说明sort算法对多维vector数组的排序，默认按第一列升序，也可以自定义

#include <algorithm>

#include <iostream>

#include <vector>

using namespace std;

 

bool cmp(vector<int> a, vector<int> b)

{

	if(a[0] != b[0]) return a[0] > b[0];

	if(a[1] != b[1]) return a[1] > b[1];

	if(a[2] != b[2]) return a[2] > b[2];

}

 

int main()

{

	vector<vector<int>> vec = { {1,4,3}, {1,4,7} , {1,3,5} , {2,9,4} , {2,5,8} , {3,9,6} };

	

	sort(vec.begin(), vec.end(), cmp);

 

	for(auto p : vec)

		cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<endl;

 

	return 0;

}
