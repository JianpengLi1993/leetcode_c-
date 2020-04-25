// 原始的leetcode 40.
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：


	所有数字（包括目标数）都是正整数。
	解集不能包含重复的组合。 


示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]


示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

方案1：DFS递归。
#include <iostream>
#include <vector>

using namespace std;

class Solution {

private:
	vector<int> candidates;
	vector<vector<int>> res;
	vector<int> path;
public:
	void DFS(int start, int target) {
		if (target == 0) {
			res.push_back(path);
			return;
		}

		for (int i = start; i < candidates.size() && target - candidates[i] >= 0; i++) {
			/*这里等效于下面的while循环作用
            if (i > start&& candidates[i] == candidates[i - 1])
			    continue;
            */
			path.push_back(candidates[i]);
			// 元素不可重复利用，使用下一个即i+1
			DFS(i + 1, target - candidates[i]);
			path.pop_back();
      while(i < candidates.size() - 1 && candidates[i] == candidates[i+1]){
           i++;        
      }
		}
	}

	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		   sort(candidates.begin(), candidates.end());
		   this->candidates = candidates;
		   DFS(0, target);
		   return res;
	}
};


*40题的变形：组合的个数也有要求


/*****************************************************************/
https://www.toutiao.com/i6804264996227252743/?tt_from=weixin&utm_campaign=client_share&wxshare_count=1
&timestamp=1586340756&app=news_article&utm_source=weixin&utm_medium=toutiao_ios&req_id=20200408181236010014041158082EC24E
&group_id=6804264996227252743



leetcode 40的变形，要求组合中元素的个数也为固定值
1）原序列中可以有重复元素
2）原序列每个元素只能使用一次，不可重复使用
3）给出的所有组合中，不可以有相同的组合。


示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]


示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

/*****************************************************************/

class Solution {
public: 
    int m=3;
    void combination(vector<int>& candidates, int start, int end, int target, vector<int> &tmp, vector<vector<int> > &result){
        if (target == 0 && tmp.size() == m){
            result.push_back(tmp);
            return;
        }
        if (start > end){//如果start超过end还没达到目标，那么就直接去掉
            return ;
        }
        for (int i = start; i <= end; i++){        
            tmp.push_back(candidates[i]);        
            combination(candidates, i + 1, end, target - candidates[i], tmp, result);                   
            tmp.pop_back();        
            //在排序的基础上，通过这一步，在有多个相同元素是，保证同一层的分支中，只让挨着的若干相同元素中的"第一个元素"进行向下发展
            //确保不会出现重复组合， 
            //其实，我们要确保只约束同一层，不会影响下一层，就是要保证 i != start,所以这个while放在for的最后，确保了这一点，
            //而如果我们习惯先判断，再执行，可以等效为在for循环中最开始位置加：
            //if(i != start && candidates[i] == candidates[i - 1]){continue;}
            
            while(i < end && candidates[i] == candidates[i+1]){
                i++;        
            }                
        }

    }



    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int target = 0;
        //一定要排序，确保序列中相同元素聚集起来，方便后面去重。
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        int end = nums.size() - 1;
        combination(nums, 0, end, target, tmp, ans);
        return ans;
    }
};




方案2：利用2进制方法
class Solution {
public:
    int NumOf1(int num){
        int count = 0;
        while (num){
            num = num & (num - 1);
            count++;
            if(count>3){
                return false;
            }
        }
        if(count==3){
            return true;
        }else{
            return false;
        }
        
    }   
    vector<vector<int>>setToVec(set<vector<int>>& s){
        vector<vector<int>> result1(s.begin(),s.end());
        return result1;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        int target=0;
        int len=nums.size();
        int bit=1<<len;
        vector<vector<int>> ans;
        set<vector<int>>anset;
        sort(nums.begin(), nums.end());
        for(int i=7; i<bit;i++){
            int sum =0;
            vector<int>tmp;
            if(NumOf1(i)){
                for(int j = 0; j < len; j++){
                    if ((i & 1 << j) != 0){
                        sum += nums[j];
                        if(sum>0){
                            break;
                        }  
                        tmp.push_back(nums[j]);
                    }
                }
                if (sum == 0){
                    anset.insert(tmp);
                }
            }
        }
        ans=setToVec(anset);
        return ans;
    }
};








