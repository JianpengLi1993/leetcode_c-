/*************************************************************************/
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

示例:

输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].


说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。

*与排列题目不同的是，虽然也用了回溯的思想，但是不需要标记元素是否被使用过，因为每一个数字代表的三个字母都是唯一的。

/*************************************************************************/

class Solution {
public:
    vector<string>ans;
    string curr;
    map<char,string>M={{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"},{'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

    void DFS(int index, string digits) {
        //出口
        if(index == digits.size()) {
            ans.push_back(curr);
            return;
        }
        for(int i = 0; i < M[digits[index]].size(); i++) {
            curr.push_back(M[digits[index]][i]); //临时结果压入一个字母
            DFS(index + 1, digits); //以压入该字母这一“情况”为前提，构造此“分支”的后续结果
            curr.pop_back();    //状态还原，例如临时结果从 "ab" -> "a"，下一次循环尝试"ac" 
        }
    }
    vector<string> letterCombinations(string digits) {
        
        
        if(digits.size() == 0) {
            return ans;
        }
        DFS(0, digits);
        return ans;
    }
    
};




