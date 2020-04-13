/***************************************************************************/
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:

输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

/***************************************************************************/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;
        int len = nums.size();
        int sum = 0;
        int left = 0;
        int right = 0;
        for(int i = 0; i < len; i++){
            
            sum += nums[i];
            if(res<sum){
                res=sum;
                right=i;
            }
            //如果sum < 0，重新开始找子序串
            if(sum < 0){
                sum = 0;
                left = i+1;
            }
        }
        //cout<<left<<right<<endl;//子串的区间。
        return res;

    }
};

方案二：
设s[i]=sum(a[0]+a[1]+...a[i]);特别的，s[0]=0,此时不包含a[0].
s[j]=sum(a[0]+a[1]+...+a[i]+...+a[j]);

max(a[i]...a[j])等价于max(s[j]-s[i-1]),在某一i、j的组合下。
那么对于某一时刻，即j固定时，
max(s[j]-s[i-1])等价于s[j]-min(s[i-1]);
所以我们可以遍历j，去找到最大的子序列和。但是一定要注意，s[i-1]=s[0]的情况。
即可以原序列只有1个元素，或者若干正数，或者其他情况（总之此时不需要减去s[i-1]反而更大），为了这种情况代码逻辑统一，我们需要令si[0]=0;


class Solution2 {
public:
    int maxSubArray(vector<int>& nums){
        int res = INT_MIN;
        int len = nums.size();
        int minSi = nums[0];
        int si=0;
        int sj=0;
        vector<int>minarr;//从nums序列的开始到第i个位置的所有累加和中，最小的值。必须考虑最开始不加任何元素的时候的最小值为0.
        minarr.push_back(0);//这一步很重要
        int tmp=0;
        for(int i =0;i<len;i++){
            tmp=tmp+nums[i];
            if(tmp<minarr[i]){
                minarr.push_back(tmp);//实际上都是在确定minarr[i+1]的值要不要更新，若累加和小于minarr[i]，则更新，否则不更新。
            }else{
                minarr.push_back(minarr[i]);
            }
        }
        for(auto it:minarr){
            cout<<it<<endl;
        }
        //将原问题找最大子序列变为，遍历j(最终找到序列的右侧端点)，找到0-j的累加和减去0-i序列累加和中最小的那个序列
        for(int j=0;j<len;j++){
            sj=sj+nums[j];
            if(res<sj-minarr[j]){
                res=sj-minarr[j];
            }

        }
        return res;
    }   
};

