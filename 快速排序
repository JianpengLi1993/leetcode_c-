/*
* 1.pivot的位置，不能选start或end;
* 2.当出现左left右right两个指针进行比较时，用<=作为循环结束条件;
* 3.当出现A[..]与pivot比较时，应用<小于号.
*/

public class Solution {
    
    public Random rand;
    public void sortIntegers2(int[] A) {
        
        // write your code here
        quickSort(A, 0, A.length - 1);
    }
    
    public void quickSort(int[] A, int start, int end) {
        if (start >= end) {
            return;
        }
        //1.每次的比较点，最好选用mid或随机值，不要用start或end,若原序列有序时，这两种情况复杂度最差
        int index = (start + end) /2;
        int pivot = A[index];
        int left = start;
        int right = end;
        //2.当出现左右两个指针进行比较时，用<=作为循环结束条件，这样确保退出的时候，left>right,
        //使得递归调用下一层的快排时，左右两个子序列不会出现重叠，若使用<小于号，退出循环时left=right=index,
        //有可能出现在不断递归调用的过程中，其中一侧会对同一个字序列反复排序
        while (left <= right) {
            //3. 当出现A[..]与pivot比较时，应用<小于号，这样会将>=pivot的元素都被调换位置，
            //避免当序列中存在大量与pivot相同数值的元素时，pivot左右两侧放置的数字元素不均匀
            while (left <= right && A[left] < pivot) {
                left ++;
            }
            while (left <= right && A[right] > pivot) {
                right --;
            }
            //此时是由于A[..]与pivot比较跳出的两个以上循环，可以进行调换，
            if (left <= right) {
                int temp = A[left];
                A[left] = A[right];
                A[right] = temp;
                
                left ++;
                right --;
            }
        }
        // 由于2的作用，确保左右两侧的递归调用不会发生元素序列重叠，此时right<left;
        quickSort(A, start, right);//A[start... right]
        quickSort(A, left, end);// A[left ... end]
    }
}
