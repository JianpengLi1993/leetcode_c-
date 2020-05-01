给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]

进阶：

	一个直观的解决方案是使用计数排序的两趟扫描算法。
	首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
	你能想出一个仅使用常数空间的一趟扫描算法吗？

思想：设立了三个指针
1.letf:确保他左侧的元素都是0；
2.right:确保其右侧的元素都是2；
3.middle：从头遍历到与right相遇，包括相遇的时候仍然要判断。分为三种情况：
   （1）当元素是0的时候，与left指针所指元素交换，并且middle与left两个指针一起右移，使得left左侧的都是0；
        这里middle可以直接右移，不需要下一轮再在原地判断，是因为middle是从左侧一路走过来的，走过所有left指向的位置，也都判断过，所以不存在交换之后的位置是2.
   （2）当元素是2的时候，与right指针所指元素交换，并且让right左移，使得right右侧都是2，但是由于不确定换过来的元素是几，
        所以middle不动，在下一轮判断这个位置是几，
   （3）当元素是1的时候，不管，middle++；

class Solution{
public:
    /**
     * @param nums: A list of integer which is 0, 1 or 2 
     * @return: nothing
     */    
    void sortColors(vector<int> &nums) {
        int left = 0, right = nums.size() - 1;
        int middle = 0;
        
        // should be <= not <
        while (middle <= right) {
            if (nums[middle] == 0) {
                swap(nums[middle], nums[left]);
                left++;
                middle++;
            } else if (nums[middle] == 1) {
                middle++;
            } else {
                swap(nums[middle], nums[right]);
                right--;
            }
        }
    }
};
