/******************************************************************/
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

示例 1:

输入: 123
输出: 321


 示例 2:

输入: -123
输出: -321


示例 3:

输入: 120
输出: 21


注意:

假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−231,  231 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。

/******************************************************************/


class Solution
{
public:
    int reverse(int x)
    {
        long result; //利用long避免溢出
        if (x == INT_MIN)
        {
            return 0;
        }
        if (x < 0)
        {
            return -reverse(-x);
        }
        stringstream ss;
        ss << x;
        string tmpStr;
        ss >> tmpStr;

        int tmpStrSize = int(tmpStr.size());
        string resultStr;
        for (int index = tmpStrSize - 1; index >= 0; index--)
        {
            resultStr.push_back(tmpStr[index]);
        }
        ss.clear(); //使用前记得clear
        ss << resultStr;
        ss >> result;
        if (result > INT_MAX)
        {
            return 0;
        }

        return int(result);
    }
};
