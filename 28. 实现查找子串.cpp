/***************************************************************/
实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:

输入: haystack = "hello", needle = "ll"
输出: 2


示例 2:

输入: haystack = "aaaaa", needle = "bba"
输出: -1


说明:
当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。
/***************************************************************/
Rabin算法
1）利用hashcode比较原子串与目标串是否一致。O(M+N),M为目标串的长度，N为原串的长度；
2）一个子串的hash值等价于每个元素的hash值累加，从头到尾依次是[1号元素*31^(len-1)]、[2号元素*31^(len-1)]...[m号元素*31^(0)],31的选取单纯是经验；
3）为了防止过大，可以最后取模，模越大，发生hash冲突的概率越小。先加减乘运算后取模与先取模再加减乘一致。
4）abcd与bcd两个子串的hash值转化计算也是O(1)复杂度。即(hash[abcd]-hash[a])%BASE,这里的hash[a]=[a*31^(len-1)]=[a*31^(m)]，
**注意，hash[a]与a所在的字串的长度和位置有关，abcd中的hash[a]=[a*31^(3)],而bcdaef中的hash[a]=[a*31^(2)].

class Solution {
public:
    int strStr(string haystack, string needle) {
        //取模运算，防止溢出int范围
        int BASE=100000;
        int m = needle.length();
        //C++中string类不允许初始化为空指针，所以只需要检测是否为空串"",可以用length()==0或empty()判断
        if(needle.length() == 0 ) {
            return 0;
        }
         if (haystack.length() < m) {
            return -1;
        }
        //31^m，用于后面删除长子序列的第一个元素
        int power = 1;
        for(int i =0;i<m;i++){
            //边计算边取模，防止越界
            power=(power*31)%BASE;
        }
        //从头到尾每个元素的hash值依次为[元素*31^(len-1)]、[元素*31^(len-1)]...[元素*31^(0)]
        //hash[needle]=[从头到尾每个元素的hash值累加]%BASE;
        //先加减乘运算后取模与先取模再加减乘一致。
        int needleCode=0;
        for(int i=0;i<needle.length();i++){
            //边计算边取模，防止越界
            needleCode=(needleCode*31+needle[i])%BASE;
        }

        int hashCode = 0;
        for(int i =0;i<haystack.length();i++){
            //abc串的hash值 对应 i从0取到m-1;d对应i=m;
            //因此，下面实现abc + d的hash值累加计算过程，
            hashCode=(hashCode*31+haystack[i])%BASE;
            //实际让i取到了m;
            if(i<m-1){
                continue;
            }
            //abcd -->bcd，需要由长串的hash值变为短串的hash值，且要求时间复杂度O(1);
            if(i>=m){
                //此时长串的长度为m+1,对应原式为：(hash[abcd]-hash[a])%BASE,这里的hash[a]=[a*31^(len-1)]=[a*31^(m)]
                hashCode=hashCode-(haystack[i-m]*power)%BASE;
                //另外要考虑减法过后为负数，因为减数与被减数都是0-(BASE-1);
                if(hashCode<0){
                    //这样形成一个环路
                    hashCode+=BASE;
                }
            }
            //double check
            if (hashCode==needleCode){
                if(haystack.substr(i-m+1,m)==needle){
                    return i-m+1;
                }
            }
            
        }
        return -1;

    }
};
