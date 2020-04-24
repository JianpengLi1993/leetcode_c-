/***************************************************************/
题目：给定一个没有重复元素的序列，让我们返回这个序列所有的全排列，并且我们不需要考虑这些排列的顺序。



思路解释：https://www.toutiao.com/i6812069961020736013
/?tt_from=weixin&utm_campaign=client_share&wxshare_count=1&timestamp=1586178291
&app=news_article&utm_source=weixin&utm_medium=toutiao_ios&req_id=202004062104510100140470391F051053
&group_id=6812069961020736013
/***************************************************************/
class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		vector<int> curr;
		vector<bool> flags(nums.size(), false);
		backtracking(nums, res, curr, flags);
		return res;
	}

	void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int>& curr, vector<bool>& flags) {
		if (nums.size() == curr.size()) {
			res.push_back(curr);
		}
		else {
			for (int i = 0; i < nums.size(); ++i) {
				if (flags[i])
					continue;
				curr.push_back(nums[i]);
				flags[i] = true;
				backtracking(nums, res, curr,flags);
				flags[i] = false;
				curr.pop_back();
			}
		}
	}
};

//这种方法不容易想明白原理，因此还使用方案2比较好，通用。
//如果给定的序列中包含了重复元素，此时上面的代码无法去重，因此需要做两点改动
1）对输入先排序
2）对回溯法中每一层分支创造前要先判断，当前元素是否和前一个元素相同
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
		vector<int> curr;
		vector<bool> flags(nums.size(), false);
        sort(nums.begin(),nums.end());
		backtracking(nums, res, curr, flags);
		return res;
    }

    void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int>& curr, vector<bool>& flags) {
		if (nums.size() == curr.size()) {
			res.push_back(curr);
		}
		else {
			for (int i = 0; i < nums.size(); ++i) {
				if (flags[i])
					continue;
                		if(i>0){
				//这个判断是关键，但是属于歪打正着，并不是控制每一层只能一个去发展，
				//而是只让相同元素的最后一个元素去充当这一层的元素.
                    			if(nums[i]==nums[i-1] && flags[i-1])
                        			continue;
                		}
                
				curr.push_back(nums[i]);
				flags[i] = true;
				backtracking(nums, res, curr,flags);
				flags[i] = false;
				curr.pop_back();
			}
		}
	}
};




方案2：利用STL自带的下一个排列函数或者使用上一题我们自己写的next_permutation函数。
**本方案本身兼容序列中含有重复元素的情况。
函数原型：
template <class BidirectionalIterator>提供升序
　　
  bool next_permutation (BidirectionalIterator first, BidirectionalIterator last );
 
template <class BidirectionalIterator, class Compare>
　　
  bool next_permutation (BidirectionalIterator first,BidirectionalIterator last, Compare comp);
  
说明：
next_permutation，重新排列范围内的元素[第一，最后一个）返回按照字典序排列的下一个值较大的组合。
返回值：如果有一个更高的排列，它重新排列元素，并返回true；如果这是不可能的（因为它已经在最大可能的排列），它按升序排列重新元素，并返回false。

另外：
prev_permutation提供降序


#include <iostream>
#include <vector>
#include <algorithm>    /// next_permutation, sort
using namespace std;

vector<vector<int>> permute(vector<int>& nums){

    vector<vector<int>> result;

    

    sort(nums.begin(), nums.end());

    

    do{

        result.push_back(nums);

    }while(next_permutation(nums.begin(), nums.end()));

    

    return result;

}

