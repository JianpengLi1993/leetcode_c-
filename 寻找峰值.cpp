/*峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。
数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。
即一个数组组成若干个山峰，最左必须为升序，最右必须为降序。不允许存在两个相邻的数字相同（山峰为平顶的情况）
你可以假设 nums[-1] = nums[n] = -∞。

示例 1:

输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。

示例 2:

输入: nums = [1,2,1,3,5,6,4]
输出: 1 或 5 
解释: 你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6。

*/

思路：
不属于之前的二分法题目，不存在OOOOO OX XXXXXXXX，这样的序列。
但是，二分法的核心是要每做一次判断，删掉一半的数据，因此，我们可以分析一下，mid处在不同情况下如何删掉一半数据
1）mid处在升序，A[mid] < A[mid + 1]，右侧必然存在峰顶，删掉左侧；
2）mid处在降序，A[mid] < A[mid - 1]，左侧必然存在峰顶，删掉右侧；
3）mid处在山顶或者谷底，此时删左删右都可以，我们默认选择删右侧；


class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        vector<int>A=nums;
        int start = 0, end = A.size()-1; 
        while(start + 1 <  end) {
            int mid = (start + end) / 2;
            if(A[mid] < A[mid - 1]) {
            //情况1
                end = mid;
            } else if(A[mid] < A[mid + 1]) {
            //情况2
                start = mid;
            } else {
            //情况3
                end = mid;
            }
        }
        //兼容数组长度为1和2的情况
        if(A[start] < A[end]) {
            return end;
        } else { 
            return start;
        }

    }
};
