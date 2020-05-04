在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5


示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

说明: 

你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。


方案一，基于快排算法一，但是区间划分要严格注意，小心。
class Solution {
public:
    /*
     * param k : description of k
     * param nums : description of array and index 0 ~ n-1
     * return: description of return
     */
    int findKthLargest(vector<int>& nums, int k) {
        if (nums.size() == 0 || k < 1 || k > nums.size()){
            return -1;
        }
        // 为了方便编写代码，这里将第 k 大转换成第 k+1 小问题。
        return partition(nums, 0, nums.size() - 1, nums.size()-k);
    }
        
private:
    //返回的是第k+1小的元素。
    //本函数就是最终应该返回nums[k]，即想办法在某一轮的循环中使得pivot最终落到nums[k]这一位置上；
    int partition(vector<int> &nums, int start, int end, int k) {
        if (start >= end) {
            return nums[k];
        }
        
        int left = start, right = end;
        int pivot = nums[(start + end) / 2];
        //可以获知pivot的移动位置；
        int index = (start + end) / 2;
        while (left <= right) {
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            while (left <= right && nums[right] > pivot) {
                right--;
            }
            if (left <= right) {
                index=swap(nums, left, right,index);
                left++;
                right--;
            }
        }
        
        

        //快排一轮结果：pivot与左右两个指针的位置无法确定，可能在中间，也可能与一个指针同一个位置，还有可能在其中一个指针的一侧
        //所以，唯一可以确定的就是：start到right位置的元素全部小于或等于pivot（其中pivot就有可能在这中间的某一位置），
        //而left到end都大于或等于pivot（pivot也有可能在这中间的某一位置）。且right<left,0 <left-right<=2.
        //因此，下面的递归分治划分依据是：
        //1. 若下标right大于等于k,则缩小范围在start到right的闭区间找；
        //2. 若下标right小于k，此时包括以下两种情况：
            //2.1 left-right=2且k=right+1,即k为pivot本身，这时说明已经找到了。直接返回nums[k]就行；
            //2.2 left-right=1,说明k>=left,这时应该在left到end的闭区间里面继续找，找到最终使得pivot移动到k的位置上；
        //1
        if (k <= right) {
            
            return partition(nums, start, right, k);
        }
        //2.2
        if (k >= left) {
           
            return partition(nums, left, end, k);
        }
        //2.1
        return nums[k];
    }    
    
    int swap(vector<int> &nums, int i, int j,int index) {
        if(index == i){
            index = j;
        }
        if(index == j){
            index = i;
        }
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        return index;
    }
};


方案二：基于快排中的第二种方法，以端点为pivot。好处在于一轮结束后，nums[left]=pivot，而且左侧都小于等于，右侧都大于等于。
class Solution {
public:
   
    //这种快速排序方法使用left作为pivot，并且先拷贝留一份，最后再把pivot放到left所停下的位置，
    //所以退出循环时要求left与right相等，不可以差开位置，继而递归的时候，要明确+1或-1.
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // 为了方便编写代码，这里将第 k 大转换成第 k+1 小问题。
        k = n - k;
        return partition(nums, 0, n - 1, k);
    }
    //返回的是第k+1小的元素。
    //本函数就是最终应该返回nums[k]，即想办法在某一轮的循环中使得pivot最终落到nums[k]这一位置上；
    int partition(vector<int>& nums, int l, int r, int k) {
        int left = l, right = r;
        int pivot = nums[left];
        //这里是小于，退出时left=right
        while (left < right) {
            //此时nums[left]=pivot，这里严格执行nums[right]大于等于pivot，只有小于才交换，与上一方法不同；
            while (nums[left] <= nums[right] and left < right) {
                right--;
            }
            swap(nums[left], nums[right]);
            //此时nums[right]=pivot，这里严格执行nums[left]小于等于pivot，只有大于才交换，与上一方法不同；
            while (nums[left] <= nums[right] and left < right) {
                left++;
            }
            swap(nums[left], nums[right]);
        }
        nums[left] = pivot;
        // 如果第 k 小在右侧，搜索右边的范围，否则搜索左侧。此时，left=right=pivot存放的位置，若left=k，这说明pivot刚好存放到了nums[k],则得到结果
        if (left < k) return partition(nums, left + 1, r, k);
        if (left > k) return partition(nums, l, left - 1, k);
        cout<<pivot<<endl;
        return nums[k];
    }
};
