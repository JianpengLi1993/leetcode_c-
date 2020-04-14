/************************************************/
给定一个含不同整数的集合，返回其所有的子集。
/************************************************/
方案1：一般递归
class Solution {
 private:
    void helper(vector<vector<int> > &results,
                vector<int> &subset,
                vector<int> &nums,
                int start) {
        results.push_back(subset);
        
        for (int i = start; i < nums.size(); i++) {
            subset.push_back(nums[i]);
            helper(results, subset, nums, i + 1);
            subset.pop_back();
        }
    }
    
 public:
    vector<vector<int> > subsets(vector<int> &nums) {
        vector<vector<int> > results;
        vector<int> subset;
        if(nums.empty())
            return results;
        sort(nums.begin(), nums.end());
        helper(results, subset, nums, 0);

        return results;
    }
};

方案2:二进制数组合
0--000--{}
1--001--{1}
2--010--{2}
3--011--{1, 2}
4--100--{3}
5--101--{1, 3}
6--110--{2, 3}
7--111--{1, 2, 3}


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>>res;
        int all_set = 1 << nums.size();
        for(int i = 0; i < all_set; i++){
            vector<int>item;
            for(int j = 0; j < nums.size(); j++){
                if(i >> j & 1){//重点 i 的二进制位表示的第j位是否为1
                    item.push_back(nums[j]);
                }
            }
            res.push_back(item);
        }
        return res;
    }
};

/************************************************/
给定一个可能含相同整数的集合，返回其所有的子集。

只需要把方案一中的递归代码加一个约束即可。即一层只用一个相同的元素，由于有了排序的基础，所以相同元素必定在一起
/************************************************/
    void helper(vector<vector<int> > &results,
                vector<int> &subset,
                vector<int> &nums,
                int start) {
        results.push_back(subset);
        
        for (int i = start; i < nums.size(); i++) {
            if(i != start && nums[i]==nums[i-1]){//i != start 确保只约束本层，而不约束跨层。
                continue;
            }
            subset.push_back(nums[i]);
            helper(results, subset, nums, i + 1);
            subset.pop_back();
        }
    }
