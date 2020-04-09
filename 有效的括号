/***********************************************************************/
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：

	左括号必须用相同类型的右括号闭合。
	左括号必须以正确的顺序闭合。

注意空字符串可被认为是有效字符串。

示例 1:

输入: "()"
输出: true


示例 2:

输入: "()[]{}"
输出: true


示例 3:

输入: "(]"
输出: false


示例 4:

输入: "([)]"
输出: false


示例 5:

输入: "{[]}"
输出: true


解题的核心思想：ASCII码对应的字符，如果扩后闭合，即对应的ASCII码相邻1或2；否则不闭合。
/***********************************************************************/
class Solution {
public:
    bool isValid(string s) {
        stack<char> linkstack;
        int length=s.size();
        if(length==0)
            return true;
        if(length%2)
            return false;
        linkstack.push(s[0]);
        for(int i=1;i<length;i++){
            if(linkstack.empty())
                linkstack.push(s[i]);
            else if(s[i]-linkstack.top()==1||s[i]-linkstack.top()==2)
                linkstack.pop();
            else
                linkstack.push(s[i]);
        }
        return linkstack.empty(); 
    }
};
