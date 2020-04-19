
二分法模板：
1) start + 1 < end;作为while循环的条件，这样最终使得两个指针相邻，即留下两个观察位置需要判断，但是避免了出现死循环的可能；
2) mid = start + (end - start) / 2；这样可以防止直接相加两个特别大的值越界，效果等同于start+end，再除以2
3) A[mid] ==, <, >；循环中中间值与target的大小判断建议完全分开，没必要合并其中的一两个；
4) A[start] A[end] ? target；跳出循环后，两个位置的值需要分别判断，看题目是要找第一个还是最后一个，若是第一个，优先判断start,否则优先判断end。

题目：
给定一个排序的整数数组（升序）和一个要查找的整数target，
用O(logn)的时间查找到target第一次出现的下标（从0开始），如果target不存在于数组中，返回-1。


class Solution {
public:
    int binarySearch(vector<int> &A, int target) {
        if (A.size() == 0) {
            return -1;
        }

        int start = 0;
        int end = A.size() - 1;
        int mid;

        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (A[mid] == target) {
                end = mid;
            } else if (A[mid] < target) {
                start = mid;
            } else if (A[mid] > target) {
                end = mid;
            }
        }

        if (A[start] == target) {
            return start;
        }
        if (A[end] == target) {
            return end;
        }

        return -1;
    }
};


题目2：找最后一个，优先判断end
class Solution {
public:
    int binarySearch(vector<int> &A, int target) {
        if (A.size() == 0) {
            return -1;
        }

        int start = 0;
        int end = A.size() - 1;
        int mid;

        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (A[mid] == target) {
                start = mid;
            } else if (A[mid] < target) {
                start = mid;
            } else if (A[mid] > target) {
                end = mid;
            }
        }
        if (A[end] == target) {
            return end;
        }
        
        if (A[start] == target) {
            return start;
        }
        
        return -1;
    }
};

题目3：若有序序列特别大，无法找到end，如何查找序列中的target元素

class Solution{
public:
    searchBigSortedArray(ArrauRead reader, int target){
        int count =1;
        //不断往后找，找到大于target的2倍位置。
        while(reader.get(count - 1) < target){
            count = count *2;
        }
        int start = count/2,end=count -1;
        while(start + 1 < end){
            int mid = start + (end - start)/2;
            if(reader.get(mid)<target){
                start = mid
            }else{
                end = mid;
            }
        }
        if(reader.get(start)==target){
            return start;
        }
        if(reader.get(end)==target){
            return end;
        }
        
        return -1;
    }
}

