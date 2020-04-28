给定一个未排序的整数数组，找到其中位数。
中位数是排序后数组的中间值，如果数组的个数是偶数个，则返回排序后数组的第N/2个数。
//这一题重在锻炼通过不断缩小寻找范围，排除若干元素，使得将原问题中寻找第k小的元素任务转化为寻找第(k-h)小的元素任务，h为排除掉比k小的元素的个数；
class Solution:
    """
    @param nums: A list of integers
    @return: An integer denotes the middle number of the array
    """
    def median(self, nums):
        # write your code here
        if not nums or len(nums) == 0:
            return
        
        return self.sortQuick(nums, 0, len(nums) - 1, (len(nums) + 1) // 2)
    //利用快排的思想，找一个无序数组中第k小的元素，
    //1.一次快排之后，左右两个指针left和right分别位于pivot的右侧和左侧，即[start...right,pivot,right...end]，此时：
        //若start到right之间共计(right-start + 1)个元素的个数大于或等于k,说明第k小的元素在[start,...,right]之间，可以丢弃[pivot,...,end],此时要寻找的仍然是第k小的元素，因为丢掉的都是比他大的；
        //若start到left之间的元素个数(left - start + 1),小于或等于k，说明第k小的元素在[left,...,end]之间，可以丢弃[start,...,pivot],共计h = (pivot-start + 1)，此时要寻找的元素为第(k-h)小的元             //素，这是因为这一层替他丢掉了比他小的h个元素；
        //若不是以上两种情况，则说明pivot对应的元素就是要找的第k小的元素，其下标为right+1或left-1;
    //2.若1中的前两种情况递归不断发生，则最终出口是当前层的start==end，即只剩下一个元素。
    def sortQuick(self, nums, start, end, k):
        if start == end:
            return nums[start]
        
            
        left, right =  start, end
        pivot = nums[left + (right - left) // 2]
        while left <= right:
            while left <= right and nums[left] < pivot:
                left += 1
            while left <= right and nums[right] > pivot:
                right -= 1
            if left <= right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1
        
        if start + k - 1 <= right:
            return self.sortQuick(nums, start, right, k)
        if start + k - 1 >= left:
            //k-h=k-(pivot-start+1)=k-(left-1 - start + 1)=k-(left - start)
            return self.sortQuick(nums, left, end, k - (left - start))
            
        return nums[right + 1]
        
方案2：C++ 优先队列，即堆
题解：
使用优先队列维护大小为k的有序集合，优先队列大小小于k时直接压入，等于k时与首个元素判断大小关系，小于时直接压入，并将首个元素弹出。最后输出优先队列的头部元素即可。
优先队列：
        优先队列中，元素被赋予优先级。当访问元素时，具有最高优先级的元素最先删除。优先队列具有最高级先出的行为特征。通常采用堆数据结构来实现。
        默认情况下，优先队列按照非递增顺序排列。
class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: An integer denotes the middle number of the array.
     */
    int median(vector<int> &nums) {
        // write your code here
        int k = (nums.size() + 1) / 2;
        priority_queue<int> que;
        int len = nums.size();
        for(int i = 0; i < len; i ++) {
            if(que.size() == k) {
                if(nums[i] < que.top()) {
                    que.pop();
                    que.push(nums[i]);
                }
            }else {
                que.push(nums[i]);
            }
        }
        return que.top();
    }
};
