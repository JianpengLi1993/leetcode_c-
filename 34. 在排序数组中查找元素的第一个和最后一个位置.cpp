/**************************************************************************/
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]

示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
/**************************************************************************/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto first = lower_bound(nums.begin(), nums.end(), target);
        auto last = upper_bound(nums.begin(), nums.end(), target);
        if(first==last){
            return {-1,-1};
        }else{
            return {int(first - nums.begin()), int(last - nums.begin() - 1)};
        }
    }
};


lower_bound与upper_bound类似于 “区间查找”，也就是说在一个有序的数组中找到元素target出现的区间[ left, right )，这里是一个半开半闭的区间。

1）如果数组中存在该元素，那么left是第一个等于target的位置，right是最右一个等于target的位置的下一个位置
（也就是说如果要插入该元素的话，该元素应该被插入的位置）。

2）如果数组中不存在该元素，那么left和right的含义一样，均是插入该元素的位置。left与right指向同一个位置，该区间的大小此时为0！！！




*首先，lower_bound与upper_bound函数返回值都是迭代器
*其次，只有支持随机访问的迭代器才允许算术运算，能进行算术运算的迭代器只有随即访问迭代器，要求容器元素存储在连续内存空间里，
vector，string，deque的迭代器是有加减法的，但是map，set，multimap,multiset的迭代器是没有加减法的，list也不可以
*迭代器算术运算后的结果是int类型，两个迭代器相减是它们之间的距离。
*auto可以自动转换为不同容器的迭代器类型
