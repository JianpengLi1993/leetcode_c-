给你一个 山脉数组 mountainArr，请你返回能够使得 mountainArr.get(index) 等于 target 最小 的下标 index 值。
如果不存在这样的下标 index，就请返回 -1。
何为山脉数组？如果数组 A 是一个山脉数组的话，那它满足如下条件：

首先，A.length >= 3
其次，在 0 < i < A.length - 1 条件下，存在 i 使得：

	A[0] < A[1] < ... A[i-1] < A[i]
	A[i] > A[i+1] > ... > A[A.length - 1]

你将 不能直接访问该山脉数组，必须通过 MountainArray 接口来获取数据：


	MountainArray.get(k) - 会返回数组中索引为k 的元素（下标从 0 开始）
	MountainArray.length() - 会返回该数组的长度
示例 1：
输入：array = [1,2,3,4,5,3,1], target = 3
输出：2
解释：3 在数组中出现了两次，下标分别为 2 和 5，我们返回最小的下标 2。

示例 2：
输入：array = [0,1,2,4,2,1], target = 3
输出：-1
解释：3 在数组中没有出现，返回 -1。

提示：
	3 <= mountain_arr.length() <= 10000
	0 <= target <= 10^9
	0 <= mountain_arr.get(index) <= 10^9

 
 /*
 山脉数组的特点就是只有一个峰值，所以思路就是先找出这个峰值；
找出峰值的索引后，剩下的就是一个升序的数组以及一个降序的数组；
完全符合二分法的结题思路。

利用二分法找出这个峰值的索引（是用 mountainArr.get(mid) 与 mountainArr.get(mid+1) 相比较,即属于升序情况作为O,属于降序情况作为X,
还是在OOOOOO X XXXXXX中找第一个X，属于二分法的扩展思路）；
找到峰值后，就可以对左边的升序数组进行二分查找了；
如果升序的数组中没有 target，再对另一个降序的数组进行二分查找。
这里要注意一点就是，数组是降序的，在对 if () 语句进行判断的时候跟升序的是相反的！

 */
 
 
class Solution {
    public int findInMountainArray(int target, MountainArray mountainArr) {
        int len = mountainArr.length();
        int left = 0;
        int right = len - 1;
        
        // 找出最大值的索引
        int maxIndex = findMaxIndex(left, right, target, mountainArr);
        
        // 找出左边升序数组的target，若没有则进行下面的
        int leftIndex = findLeftArr(left, maxIndex, target, mountainArr);
        
        if (leftIndex != -1) {
            return leftIndex;
        }
        
        // 找出右边降序数组的target
        int rightIndex = findRightArr(maxIndex, right, target, mountainArr);
        
        return rightIndex;
    }
    
    private int findMaxIndex(int left, int right, int target,  MountainArray mountainArr) {
        while (left < right) {
            int mid = (left + right) >>> 1;
            if (mountainArr.get(mid) > mountainArr.get(mid+1)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
    
    private int findLeftArr(int left, int maxIndex, int target, MountainArray mountainArr) {
        while (left < maxIndex) {
            int mid = (left + maxIndex) >>> 1;
            if (mountainArr.get(mid) < target) {
                left = mid + 1;
            } else {
                maxIndex = mid;
            }
        }
        if (mountainArr.get(left) != target) {
            return -1;
        }
        return left;
    }
    
    private int findRightArr(int maxIndex, int right, int target, MountainArray mountainArr) {
        while (maxIndex < right) {
            int mid = (maxIndex + right) >>> 1;
            if (mountainArr.get(mid) > target) {
                maxIndex = mid + 1;
            } else {
                right = mid;
            }
        }
        if (mountainArr.get(right) != target) {
            return -1;
        }
        return right;
    }
}
