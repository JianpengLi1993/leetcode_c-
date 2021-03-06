/*
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0


示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5

*/

class Solution {
public:
    /*
    本题基本思路是做问题转化：
    1.先将寻找两个数组整体的中位数，转化为编写一个函数findKth(K),用于在两个数组中查找第K或小的元素（升序序列中）；
    2.从代码复杂度的考虑上讲，如果直接对两个数组进行merg(),再根据下标找，复杂度是O(m+n),为了更小，想变为log(m+n)级别，想到要从广义二分下手，
        一次O(1)操作，实现一半大量数据砍掉
        因此，想到用递归，要想找到第K小的元素，可以通过砍掉K/2个元素，使得要找的元素变为剩余数组中的第(K-K/2)小的元素，进而调用findKth((K-K/2));
        就像学生在班级排名为第10，当删掉前九排名的5人，他的排名就会变为第5.
    3.砍掉K/2个元素，为了不会砍掉真正要找的第K小的元素，在砍的过程是通过比较两个数组的第K/2个元素(下标为(start + k/2 -1))的大小来确定砍掉哪部分，
        即A[A_st + k / 2 - 1]与B[B_st + k / 2 - 1]比较;
    4.以上过程会遇到一些边界情况：
        4.1递归过程中的出口情况1，对于每个数组来说，当前轮的开始下标以及>=size(),即上一轮删完k/2个元素后，该数组刚好没了。
        这时，我们只需要返回另一个数组的第k(该层需要求的所谓的第k小的元素)个元素就是要找的最终中位数；
        4.2递归过程中的出口情况2，递归到k=1时，就可以直接比较两个数组当前层的首个元素较小的那一个就是最终要找的中位数。
        4.3递归过程中，在进行比较两个数组的A[A_st + k / 2 - 1]与B[B_st + k / 2 - 1]大小时，其中一个数组长度已经不够k/2了（包括该数组只剩一个元素的情况）。
        这时，我们可以将该数组不存在的那个位置的数值看做无穷大，使得去砍掉另一个数组的k/2个元素；这样仍然能保证该层需要寻找的第K个元素没被丢掉；
        这是因为，长度不够的数组元素个数 + 另一个数组的前k/2个元素，仍然小于k个。因此，这一层的第k元素必然存在于st+k/2之后，即不会被丢掉。
    5.还要注意一些下标和第几大的关系：
        第k小的元素下标是start+(k-1);
        第k/2小的元素下标是start+(k/2-1);
        下一轮开始的下标是start+k/2;(这一轮扔了k/2个元素的数组)。
        通过砍掉K/2个元素，使得要找的元素变为剩余数组中的第(K-K/2)小的元素，而不能直接变为k/2小的元素，因为存在数组长度有奇偶情况
    6.另外在最开始调用findKth的时候，要区分两个数组加起来的总个数是奇数还是偶数，来确定中位数具体怎么调用findKth
    */
   //返回两个有序数组中，整体的第k小的元素的数值；
    double findKth(vector<int>& A, vector<int>& B, int A_st, int B_st, int k) {
        // 边界情况1，任一数列为空
        if (A_st >= A.size()) {
            return B[B_st + k - 1];
        }
        if (B_st >= B.size()) {
            return A[A_st + k - 1];
        }
        // 边界情况2， k等于1时表示取最小值，直接返回min
        if (k == 1) return min(A[A_st], B[B_st]);
        //确定将要比较的两个数值，有可能存在一个数组长度不够的情况；
        int A_key = A_st + k / 2 - 1 >= A.size() ? INT_MAX : A[A_st + k / 2 - 1];
        int B_key = B_st + k / 2 - 1 >= B.size() ? INT_MAX : B[B_st + k / 2 - 1];

        if (A_key < B_key){
            return findKth(A, B, A_st + k / 2, B_st, k - k / 2);
        } else {
            return findKth(A, B, A_st, B_st + k / 2, k - k / 2);
        }
        
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sum = nums1.size() + nums2.size();
        double ret;
        //位运算，按位进行与运算，相当于取最后一位是否是1，用来判定奇偶
        if (sum & 1) {
            ret = findKth(nums1, nums2, 0, 0, sum / 2 + 1);
        } else {
            ret = ((findKth(nums1, nums2, 0, 0, sum / 2)) +
                    findKth(nums1, nums2, 0, 0, sum / 2 + 1)) / 2.0;
        }
        return ret;
    }
};
