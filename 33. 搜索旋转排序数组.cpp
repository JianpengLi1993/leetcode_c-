/************************************************************/
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别。

示例 1:

输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4


示例 2:

输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1
/************************************************************/
方案一：先找到旋转点，再二分
class Solution {
public:
    vector<int>nums;
    int target;
    int find_rotate_index(int left, int right){
        
        if(nums[left]<nums[right])
            return 0;
        while(left<=right){
            int pivot = (left + right) / 2;
            if (nums[pivot] > nums[pivot + 1])
                return pivot + 1;
            else {
                if (nums[pivot] < nums[left])
                    right = pivot - 1;
                else
                    left = pivot + 1;
            }
        }
        return 0;

    }
    
    //二分法本身可以泛化为解决：一个数组，让你找数组中第一个/最后一个满足某个条件的位置，这个位置之前是OOOO  O\X  XXXXXX,
    //是要找满足某一个条件的第一个或最后一个位置,而不是非要找一个target
    
    //本题中，旋转点之前的元素都大于整个序列的最后一个元素，旋转点后面的元素都小于整个序列最尾部的元素，
    //因此本身找这个旋转点的函数，可以理解成一个理由二分法找first小于整个序列最尾部的思想。即将[5671234]拆为[567]、[1]、[234]三个序列，
    //要找的是[1]的位置，而1是第一个小于4的元素，可以用二分法找。
    int find_rotate_index(int left, int right){
        if(nums[left]<nums[right])
            return 0;
        int end=right;
        while(left+1<right){
            int pivot=left+(right-left)/2;
            if(nums[pivot]>nums[end]){
                left=pivot;
            }else{
                right=pivot;
            }
        }
        if(nums[left]<nums[right]){
            return left;
        }else{
            return right;
        }
    }

    int binSearch(int left, int right) {
    /*
    Binary search
    */
    while (left <= right) {
      int pivot = (left + right) / 2;
      if (nums[pivot] == target)
        return pivot;
      else {
        if (target < nums[pivot])
          right = pivot - 1;
        else
          left = pivot + 1;
      }
    }
    return -1;
  }


    int search(vector<int>& nums, int target) {
        this->nums=nums;
        this->target=target;
        int n = nums.size();

        if (n == 0)
            return -1;
        if (n == 1)
            return this->nums[0] == target ? 0 : -1;

        int rotate_index = find_rotate_index(0, n - 1);

    // if target is the smallest element
        if (nums[rotate_index] == target)
            return rotate_index;
    // if array is not rotated, search in the entire array
        if (rotate_index == 0)
            return binSearch(0, n - 1);
        if (target < nums[0])
      // search in the right side
            return binSearch(rotate_index, n - 1);
    // search in the left side
        return binSearch(0, rotate_index);
    }
};


方案二：直接二分法，不刻意要求满足OOOO OX XXXXXX,只要一次操作能判断一半数据就可以。
public class Solution {
    public int search(int[] A, int target) {
        if (A == null || A.length == 0) {
            return -1;
        }

        int start = 0;
        int end = A.length - 1;
        int mid;
        
        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (A[mid] == target) {
                return mid;
            }
            //先判断mid点在前半段序列还是后半段序列
            if (A[start] < A[mid]) {
                // situation 1, 此时target在前半段序列中的start--mid中间
                if (A[start] <= target && target <= A[mid]) {
                    end = mid;
                } else {
                //situation 3,target在mid--end中
                    start = mid;
                }
            }//此时mid在后半段 
            else {
                // situation 2, 此时target在后半段序列中的mid--end中间
                if (A[mid] <= target && target <= A[end]) {
                    start = mid;
                }// situation 4,target在start--mid中
                else {
                    end = mid;
                }
            }
        } // while
        
        if (A[start] == target) {
            return start;
        }
        if (A[end] == target) {
            return end;
        }
        return -1;
    }
}
