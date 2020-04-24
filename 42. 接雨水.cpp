/*************************************************************************/
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。



上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。

示例:

输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
/*************************************************************************/


方案1：
直接按问题描述进行。对于数组中的每个元素，我们找出下雨后水能达到的最高位置，等于两边最大高度的较小值减去当前高度的值。

int trap(vector<int>& height)
{
    int ans = 0;
    int size = height.size();
    for (int i = 1; i < size - 1; i++) {
        int max_left = 0, max_right = 0;
        for (int j = i; j >= 0; j--) { //Search the left part for max bar size
            max_left = max(max_left, height[j]);
        }
        for (int j = i; j < size; j++) { //Search the right part for max bar size
            max_right = max(max_right, height[j]);
        }
        ans += min(max_left, max_right) - height[i];
    }
    return ans;
}





方案2：
在暴力方法中，我们仅仅为了找到最大值每次都要向左和向右扫描一次。但是我们可以提前存储这个值。因此，可以通过动态编程解决。
找到数组中从下标 i 到最左端最高的条形块高度 left_max。
找到数组中从下标 i 到最右端最高的条形块高度 right_max。
扫描数组 height\text{height}height 并更新答案：

累加 min⁡(max_left[i],max_right[i])−height[i] 到 ans上

int trap(vector<int>& height)
{
	if(height.empty())
		return 0;
    int ans = 0;
    int size = height.size();
    vector<int> left_max(size), right_max(size);
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}

方案3：
先遍历一遍，找到最高点，记录高度imax和坐标h
再分别从两边两个指针往中间扫，以当前遍历中遇到的最高点的高度为标准stan
再往中间走，如果当前的坐标高度小于stan，就说明当前坐标能接的雨水为stan-height[i]

class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size()==0) return 0;
        int imax=-1,h;
        for(int i=0;i<height.size();i++)//找到最高点和它的高度
        {
            if(height[i]>imax)
            {
                imax=height[i];
                h=i;
            }
        }
        int stan=0,ans=0;
        for(int i=0;i<h;i++)//从前遍历到最高点
        {
            if(height[i]>stan)
            {
                stan=height[i];
                continue;
            }
            else  ans+=stan-height[i];
        }
        stan=0;//stan归零
        for(int i=height.size()-1;i>h;i--)//从后遍历到最高点
        {
            if(height[i]>stan)
            {
                stan=height[i];
                continue;
            }
            else ans+=stan-height[i];
        }   
        return ans;  
    }
};


