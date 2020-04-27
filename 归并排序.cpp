/*
归并排序利用了分治的思想来对序列进行排序。对一个长为 n 的待排序的序列，我们将其分解成两个长度为 n/2 的子序列。
每次先递归调用函数使两个子序列有序，然后我们再线性合并两个有序的子序列使整个序列有序。

算法:
定义 mergeSort(nums, l, r) 函数表示对 nums 数组里 [l,r]的部分进行排序，整个函数流程如下：

递归调用函数 mergeSort(nums, l, mid) 对 nums 数组里 [l,mid] 部分进行排序。

递归调用函数 mergeSort(nums, mid + 1, r) 对 nums 数组里 [mid+1,r] 部分进行排序。

此时 nums 数组里 [l,mid] 和 [mid+1,r] 两个区间已经有序，我们对两个有序区间线性归并即可使 nums 数组里 [l,r] 的部分有序。
线性归并的过程并不难理解，由于两个区间均有序，所以我们维护两个指针 i 和 j 表示当前考虑到 [l,mid] 里的第 i 个位置和 [mid+1,r]的第 j 个位置。
如果 nums[i] < nums[j] ，那么我们就将 nums[i] 放入临时数组 tmp 中并让 i += 1 ，即指针往后移。
   否则我们就将 nums[j] 放入临时数组 tmp 中并让 j += 1 。
如果有一个指针已经移到了区间的末尾，那么就把另一个区间里的数按顺序加入 tmp 数组中即可。
这样能保证我们每次都是让两个区间中较小的数加入临时数组里，那么整个归并过程结束后 [l,r]即为有序的。

*/
**序列是数组的情况：

class Solution {
    vector<int> tmp;
    //1.确定递归函数的作用：将区间[start,end]进行归并排序，即先将[start，end]分为[start, mid] + [mid + 1, end]两个区间，分别排序
    //再将两个排序好的区间整合回原数组中。
    void mergeSort(vector<int>& nums, int start, int end) {
        //3.确定出口,这里包括两种情况，start=end,即序列只有一个元素，对应左半边，start>end,即序列为空,对应右半边；
        if (start >= end) 
            return;
        int mid = (start + end) >> 1;
        //2.1分治，分别对两个区间进行递归排序
        mergeSort(nums, start, mid);
        mergeSort(nums, mid + 1, end);
        //2.2整合，将两个排序好的区间进行归并整合。
        merge(nums, start, end, mid);
    }
    //整合算法：利用一个临时数组进行归并。
    void merge(vector<int>& nums,int start, int end, int mid){
        int leftIndex = start;
        int rightIndex = mid+1;
        int tempIndex = start;
        while(leftIndex<=mid && rightIndex <= end){
            if(nums[leftIndex]<nums[rightIndex]){
                tmp[tempIndex++]=nums[leftIndex++];
            }else{
                tmp[tempIndex++]=nums[rightIndex++];
            }
        }
        while(leftIndex<=mid){
            tmp[tempIndex++]=nums[leftIndex++];
        }
        while(rightIndex<=end){
            tmp[tempIndex++]=nums[rightIndex++];
        }
        for(int i = start; i<=end;i++){
            nums[i]=tmp[i];
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};
 
**序列是链表的情况：
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @return: You should return the head of the sorted linked list,
                    using constant space complexity.
     */
     //还是采用归并排序思想，找到中点，一分为二，左右各自递归
    ListNode *sortList(ListNode *head) {
        // write your code here
        if(head == NULL) return head;
        if(head -> next == NULL){
            return head;
        }
        //这里利用快慢指针的算法来寻找切分中点。
        //1.fast和slow初始化同一起点，结束循环时，slow的位置分原序列是奇数个还是偶数个，
        //若是奇数个，slow位于正中间，fast位于最后一个不为null的节点处；
        //若为偶数个，slow位于中间两个数的前一个位置，fast位于倒数第二个不为null的节点处；
        ListNode* fast = head;
        ListNode* slow = head;
        //由于fast开始是从头开始的，所以循环的判定要包括fast->next和fast->next->next两步是否有null;
        while(fast -> next != NULL && fast -> next -> next != NULL){
            fast = fast -> next;
            fast = fast -> next;
            slow = slow -> next;
        }
        //这里把slow->next当做中间结点mid，并把slow->next置为null,这样相当于把链表分为[start,mid-1]、[mid,end]两段。
        ListNode* mid = slow -> next;
        slow -> next = NULL;
        
        //继续递归
        ListNode* list1 = sortList(head);
        ListNode* list2 = sortList(mid);
        
        ListNode* sorted = merge(list1 , list2);
        return sorted;
    }
    ListNode* merge(ListNode* list1 , ListNode* list2){
        if(list1 == NULL) return list2;
        if(list2 == NULL) return list1;
        //涉及到链表结构发生变化，仍然使用dummy
        ListNode dummy(-1);
        ListNode* tmp;
        tmp=&dummy;
        
        
        while(list1 != NULL && list2 != NULL){
            if(list1 -> val < list2 -> val){
                tmp -> next = list1;
                tmp = list1;
                list1 = list1 -> next;
            }else{
                tmp -> next = list2;
                tmp = list2;
                list2 = list2 -> next;
            }
        }
        if(list1 != NULL) tmp -> next = list1;
        if(list2 != NULL) tmp -> next = list2;
        
        return dummy.next;
    }
};

延伸问题：
合并两个排序的整数数组A和B变成一个新的数组。且在原数组上修改，A=[1,2,3,Null,Null],B=[4,5].
分析:
    涉及两个有序数组合并,设置i和j双指针,分别从两个数组的尾部想头部移动,即从大到小排序，这是因为这样操作不涉及数组的整体移动，
并判断A[i]和B[j]的大小关系,从而保证最终数组有序,同时每次index从尾部向头部移动。

class Solution {
public:
    /**
     * @param A: sorted integer array A which has m elements, 
     *           but size of A is m+n
     * @param B: sorted integer array B which has n elements
     * @return: void
     */
    void mergeSortedArray(int A[], int m, int B[], int n) {
        int pos = m + n - 1 , i = m - 1 , j = n - 1;
        while (i >= 0 && j >= 0)
            A[pos--] = A[i] > B[j] ? A[i--] : B[j--];
        while (i >= 0)
            A[pos--] = A[i--];
        while (j >= 0)
            A[pos--] = B[j--];
    }
};
