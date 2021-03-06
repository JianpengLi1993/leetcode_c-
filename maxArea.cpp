/*****************************************************************/
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。

/*****************************************************************/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int result = 0;
        int heightSize = int(height.size());
        int leftIndex = 0;
        int rightIndex = heightSize - 1;

        while (leftIndex != rightIndex)
        {
            int tmpHeight;
            int tmpWidth = rightIndex - leftIndex;
            //短的一侧向中间移动
            if (height[leftIndex] < height[rightIndex])
            {
                tmpHeight = height[leftIndex];
                leftIndex++;
            }
            else
            {
                tmpHeight = height[rightIndex];
                rightIndex--;
            }
            int tmpResult = tmpWidth * tmpHeight;
            if (tmpResult > result)
            {
                result = tmpResult;
            }
        }
        return result;
    }
};
