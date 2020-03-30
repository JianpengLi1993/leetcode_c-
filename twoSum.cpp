/*********************************************************************************************************/
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
/*********************************************************************************************************/
//方法一：在遍历的同时，进行筛选，这样快捷
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> record;
        for(int i = 0 ; i < nums.size() ; i ++){
            
            int complement = target - nums[i];
            if(record.find(complement) != record.end()){
                
                return {i, record[complement]};
            }
            record[nums[i]] = i;
            
        }
        return {};
    }
};


//方法二：先完整构建map键值对，再从中寻找合适的组合，但需要注意有可能出现一个元素被两次使用的情况，所以m[target-nums[i]]!=i这个条件必不可少

class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int,int> m;

        for(int i=0;i<nums.size();i++)
            m[nums[i]]=i;   //向map中添加元素
        
        for(int i=0;i<nums.size();i++)
        {
            if(m.find(target-nums[i])!=m.end()&&m[target-nums[i]]!=i)//m中存在对应的键值，并且不为i
                return {i,m[target-nums[i]]};
        }
        return {};
    }
};
