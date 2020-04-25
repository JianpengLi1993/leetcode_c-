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
        //预处理回文判定数组；
        getIsPalindrome(s);
        dfs(s, 0, tmp, ret); 
        return ret;
    }
    
private:
   vector<vector<bool>> isPalindrome;
    //利用区间动态规划，计算一个回文真值数组
    void getIsPalindrome(string s) {
        vector<bool> temp(s.size(), false);
        vector<vector<bool>> isPalindrome(s.size(), temp);
        int n = s.size();
        
        //一个元素的字串
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
        }
        //两个元素的字串
        for (int i = 0; i < n - 1; i++) {
            isPalindrome[i][i + 1] = (s[i] == s[i + 1]);
        }
        //双指针，依据之前的数组元素，逐渐向两端扩展，
        //i的确立是由大到小，从右到左，所以i是倒序；j的确立是有小到大，从左到右，所以j是顺序；
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && s[i] == s[j];
            }
        }
        this->isPalindrome = isPalindrome;
    }


    //s表示的是还需要切分的字符串，tmp表示之前切好的若干字串存放好的数组，
    void dfs(const string &s, int startIndex, vector<string> &tmp, vector<vector<string>> &ret) {
        int n = s.size();
        if (n == startIndex) {
            ret.push_back(tmp);
            return ;
        }
        
        for (int i = startIndex; i < n; i++) {
            //substr(pos, len);
            //isPalindromeFun(s.substr(startIndex, i - startIndex + 1))复杂度更高
            if (isPalindrome[startIndex][i]) {
                tmp.push_back(s.substr(startIndex, i - startIndex + 1));
                dfs(s, i + 1, tmp, ret);
                tmp.pop_back();
            }    
        }
    }
    //判断是否是回文的函数
    bool isPalindromeFun(const string &s) {
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
