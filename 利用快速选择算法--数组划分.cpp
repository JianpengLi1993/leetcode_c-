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
     //而快排中，相等情况是可以作为交换元素的。
     //还有就是，这种快速选择方法不能保证子区域内元素有序。只是保证分为两个区域
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

变形1：给定一个只包含字母的字符串，按照先小写字母后大写字母的顺序进行排序。
class Solution {
public:
    bool isLower(char c) {
        return c >= 'a' && c <= 'z';
    }

    void sortLetters(string &letters) {
        int i = 0, j = letters.size() - 1;
        while (i <= j) {
            while (i <= j && isLower(letters[i])) i++;
            while (i <= j && !isLower(letters[j])) j--;
            if (i <= j) {
                char c = letters[i];
                letters[i] = letters[j];
                letters[j] = c;
            }
        }
    }
};

变形2：分割一个整数数组，使得奇数在前偶数在后。
class Solution {
public:
    /*
     * @param nums: an array of integers
     * @return: nothing
     */
    void partitionArray(vector<int> &nums) {
        // write your code here
        if (nums.size() < 2) {
            return;
        }
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            while (left <= right && nums[left] % 2 == 1) {
                left++;
            }
            while (left <= right && nums[right] % 2 == 0) {
                right--;
            }
            if (left <= right) {
                int temp = nums[left];
                nums[left]  = nums[right];
                nums[right] = temp;
                left++;
                right--;
            }
        }
    }
};
