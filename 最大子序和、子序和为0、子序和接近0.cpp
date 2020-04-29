
问题已：最大子序和
//前序和算法，
令 PrefixSum[i] = A[0] + A[1] + … A[i - 1], 表示前i个元素的和，下标从0到i-1。PrefixSum[0] = 0
易知构造 PrefixSum 耗费 O(n) 时间和 O(n) 空间
如需计算子数组从下标i到下标j之间的所有数之和
则有 Sum(i~j) = PrefixSum[j + 1] - PrefixSum[i]
所以MaxSum() = PrefixSum[j + 1] - Min(PrefixSum[i])，这时取到Sum(i,j)。
class Solution {
public:    
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> nums) {
        //sum记录前i个数的和，maxSum记录到第i个元素为止，目前的全局最大值，minSum记录前i-1个数中最小和，因此minSum要比sum和maxSum要晚一轮。
        int sum = 0, minSum = 0, maxSum = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            maxSum = max(maxSum, sum - minSum);
            //minSum放最后更新；
            minSum = min(minSum, sum);
        }
        return maxSum;
    }
};


问题二：子数组之和为0
还是利用前序和数组进行运算。
我们建立一个hash表，key为p[i]的值，value为对应加到的数组元素下标i-1;
特别的p[0]=0,表示前0个元素的和0，而为hash[p[0]]=-1，表示对应的index为数组前边一个位置;
p[5]=0--4之间的和，对应的数组下标为4；
p[8]=0--7之间的和，对应的数组下标为7；
当p[5]==p[8],说明从5--7之间的数组和为0,即hash[p[5]]=4,hash[p[8]]=7；
因此，我们最终返回的区间是hash[p[5]]+1到hash[p[8]]，即前一个hash表value+1，以及后一个hash的value。
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    vector<int> subarraySum(vector<int> nums){
        unordered_map<int, int> hash;
        
        int sum = 0;
        hash[0] = -1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (hash.find(sum) != hash.end()) {
                vector<int> result;
                result.push_back(hash[sum] + 1);
                result.push_back(i);
                return result;
            }
            hash[sum] = i;
        }
        
        vector<int> result;
        return result;
    }
};

问题三：在问题二的基础上变形，求最接近0的子数组的下标区间
思路基本一致，那就是比较找出所有前序和数组中最接近的两个元素，并将其对应的hash下标作为子数组区间
1.需要构建hash表，key为p[i]的值，value为对应加到的数组元素下标i-1;
2.对构建好的hash表按照key排序，并两两计算差值，打擂台记录最下的差值对应的hash数组的key,和key+1;
3.根据key和key+1找到对应的value1、value2（表示原数组的相应下标），将两个下标中小的那个进行加一作为区间左端点，大的直接作为区间右端点；
  即left = min(value1,value2) + 1; right = max(value1, value2);

class Solution {
public:
    /*
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number and the index of the last number
     */
    vector<int> subarraySumClosest(vector<int> &nums) {
        if(nums.size() < 2){
            return vector<int>{0, 0};
        }
        //利用vector也可以做字典，而且sort默认按照第一个位序进行排序。
        vector<pair<int, int>> sums;
        sums.push_back(make_pair(0, -1));
        int sum = 0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            sums.push_back(make_pair(sum, i));
        }
        sort(sums.begin(), sums.end());
        int diff = INT_MAX;
        int temp;
        for(int i=1; i<sums.size(); i++){
            if(sums[i].first - sums[i-1].first < diff){
                temp = i-1;
                diff = sums[i].first - sums[i-1].first;
            }
        }
        vector<int> result;
        result.push_back(min(sums[temp].second, sums[temp+1].second) + 1);
        result.push_back(max(sums[temp].second, sums[temp+1].second));
        return result;
    }
};
