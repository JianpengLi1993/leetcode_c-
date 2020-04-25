##########################################################3
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回 s 所有可能的分割方案。

示例:

输入: "aab"
输出:
[
  ["aa","b"],
  ["a","a","b"]
]

##########################################################


//求分割回文串方案相当于在n-1个数字的全部子集（对应切割位置）找其中的若干种子集，这些子集是满足切割后各个子串是回文串的切割位置。
abc----相当于元素集[1,2]
a|b|c ----相当于[1,2]
a|bc  ----相当于[1]
ab|c  ----相当于[2]
abc   ----相当于[]
其中[1,2]这个子集对应的切割位置满足要求；

class Solution {
public:
    /*
     * @param s: A string
     * @return: A list of lists of string
     */
    vector<vector<string>> partition(string &s) {
        vector<vector<string>> ret;
        vector<string> tmp;
        dfs(s, tmp, ret); 
        return ret;
    }
    
private:
    //s表示的是还需要切分的字符串，tmp表示之前切好的若干字串存放好的数组，
    void dfs(const string &s, vector<string> &tmp, vector<vector<string>> &ret) {
        int n = s.size();
        if (n == 0) {
            ret.push_back(tmp);
            return ;
        }
        
        for (int i = 0; i < n; i++) {
            //substr(pos, len);
            if (isPalindrome(s.substr(0, i + 1))) {
                tmp.push_back(s.substr(0, i + 1));
                dfs(s.substr(i + 1), tmp, ret);
                tmp.pop_back();
            }    
        }
    }
    //判断是否是回文
    bool isPalindrome(const string &s) {
        for (int l = 0, r = s.size() - 1; l < r; l++, r--) {
            if (s[l] != s[r]) {
                return false;
            }
        } 
        return true;
    }
};

//求全部子集的方案如下:
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
