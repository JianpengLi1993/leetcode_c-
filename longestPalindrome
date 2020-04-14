/********************************************************************/
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。


示例 2：

输入: "cbbd"
输出: "bb"


/********************************************************************/

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.length()<1){
            return"";
        }
        int start =0, end=0;
        for(int i = 0;i<s.length();i++){
            int len1=expandAroundCenter(s,i,i);//单元素中心查找
            int len2=expandAroundCenter(s,i,i+1);//双元素中心查找
            int maxlen=max(len1,len2);
            if(maxlen>end-start){
                start=i-(maxlen-1)/2;
                end=i+maxlen/2;
            }
        }
        return s.substr(start,end-start+1);
    }

    int expandAroundCenter(string s, int left, int right){
        
        while(left>=0 && right<s.length() && s[left]==s[right])
        {
            left--;
            right++;
        }
        return right-left-1;
    }

	int expandAroundCenter1(string s, int left, int right)
	{
		int L = left, R = right;
		while (L >= 0 && R < s.length() && s[L] == s[R])
		{// 计算以left和right为中心的回文串长度
			L--;
			R++;
		}
		return R - L - 1;
	}
};



方案2：动态规划：
isPalindrome[left + 1][right - 1] == 1 and s[left] == s[right]这句话是核心，即短序列是回文，且两边各加一也相等，则整体是回文。
所以需要先算短的状态矩阵，后算长的。

class Solution {
public:
    /**
     * @param s: input string
     * @return: the longest palindromic substring
     */
    string longestPalindrome(string &s) {
        int len = s.length();
        vector<vector<int>> isPalindrome(len, vector<int>(len));
        int maxLen = 1;
        int start = 0;
        
        // 将长度为 1 的 dp 值设为真
        for (int i = 0; i < len; i++) {
            isPalindrome[i][i] = 1;
        }
	//将长度为 2 的 dp 值进行判断设置
        for (int i = 0; i + 1 < len; i++) {
            if (s[i] == s[i + 1]) {
                isPalindrome[i][i + 1] = 1;
                maxLen = 2;
                start = i;
            }
        }
        for (int left = len - 1; left >= 0; left--) {
	//转移方程中，left是由大往小推算，right是由小到大推算，所以循环中，left是逆着来。right顺着来，且从长度为3开始算就行。
            for (int right = left + 2; right < len; right++) {
                if (isPalindrome[left + 1][right - 1] == 1
                        and s[left] == s[right]) {
                    
                    isPalindrome[left][right] = 1;
                    // 更新答案
                    if (right - left + 1 > maxLen) {
                        maxLen = right - left + 1;
                        start = left;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};
