给出一个整数数组 nums 和一个整数 k。划分数组（即移动数组 nums 中的元素），使得：
所有小于k的元素移到左边
所有大于等于k的元素移到右边
返回数组划分的位置，即数组中第一个位置 i，满足 nums[i] 大于等于 k。
当数组全部小于k时，返回数组的长度

class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
     //和快排的区别在于，当nums[left]（或者nums[right]）与nums[privot]比较时，要严格将比较的元素分到左侧或右侧，
     //而快排中，相等情况是可以作为交换元素的
    int partitionArray(vector<int> &nums, int k) {
        int left = 0, right = nums.size() - 1;
        //这个循环条件与快排一致，要求退出循环时两个指针完全错开位置，且各自代表各自的区域，
        //即nums[left]--nums[end]都大于等于k;nums[0]--nums[right]都小于k.这样当数组元素全部小于k时（包括只有一个元素时），
        //返回的left刚好等于数组长度.
        while (left <= right) {
            while (left <= right and nums[left] < k) {
                left++;
            }
            while (left <= right and nums[right] >= k) {
                right--;
            }
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        return left;
    }
};
