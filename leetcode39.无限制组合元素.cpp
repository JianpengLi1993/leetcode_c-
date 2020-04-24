/*********************************************************************************/
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：


	所有数字（包括 target）都是正整数。
	解集不能包含重复的组合。 


示例 1:

输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]


示例 2:

输入: candidates = [2,3,5], target = 8,
所求解集为:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

/*********************************************************************************/





#include <algorithm>
class Solution {
public:
    vector<vector<int>>finarr;
    vector<int>temp;
    void sumCal(int start, vector<int>&candidates,int target){
        if(target<=0){
            if(target==0){
                finarr.push_back(temp);
            }
            return;
        }
        for(int i = start;i<candidates.size();i++){
            temp.push_back(candidates[i]);
            sumCal(i, candidates, target-candidates[i]);//会控制一个元素是否可以无限使用，也保证了不会出现一个元素重复组合
            temp.pop_back();
            
            while(i < candidates.size()-1 && candidates[i] == candidates[i+1]){//若序列有序，这一步可以起到剪枝
            //因为上面的回溯已经可以找到一个元素参与的全部组合，无需再试，避免相同数值的不同元素重复出现。
                i++;
            }
        }

    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sumCal(0,candidates,target);
        return finarr;
    }
        

};
