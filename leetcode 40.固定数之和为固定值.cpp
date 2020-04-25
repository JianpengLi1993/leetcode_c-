// 原始的leetcode 40.
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：


	所有数字（包括目标数）都是正整数。
	解集不能包含重复的组合。 


示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]


示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

方案1：DFS递归。
#include <iostream>
#include <vector>

using namespace std;

class Solution {

private:
	vector<int> candidates;
	vector<vector<int>> res;
	vector<int> path;
public:
	void DFS(int start, int target) {
		if (target == 0) {
			res.push_back(path);
			return;
		}

		for (int i = start; i < candidates.size() && target - candidates[i] >= 0; i++) {
			/*这里等效于下面的while循环作用
            		if (i != 0 && candidates[i] == candidates[i - 1])
			    continue;
            		*/
			path.push_back(candidates[i]);
			// 元素不可重复利用，使用下一个即i+1
			DFS(i + 1, target - candidates[i]);
			path.pop_back();
      			while(i < candidates.size() - 1 && candidates[i] == candidates[i+1]){
           		    i++;        
      			}
		}
	}

	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		this->candidates = candidates;
		DFS(0, target);
		return res;
	}
};


*40题的变形：组合的个数也有要求


/*****************************************************************/
https://www.toutiao.com/i6804264996227252743/?tt_from=weixin&utm_campaign=client_share&wxshare_count=1
&timestamp=1586340756&app=news_article&utm_source=weixin&utm_medium=toutiao_ios&req_id=20200408181236010014041158082EC24E
&group_id=6804264996227252743



leetcode 40的变形，要求组合中元素的个数也为固定值
1）原序列中可以有重复元素
2）原序列每个元素只能使用一次，不可重复使用
3）给出的所有组合中，不可以有相同的组合。


示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]


示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

/*****************************************************************/
方案一：递归DFS

class Solution {
public: 
    int m=3;
    void combination(vector<int>& candidates, int start, int end, int target, vector<int> &tmp, vector<vector<int> > &result){
        if (target == 0 && tmp.size() == m){
            result.push_back(tmp);
            return;
        }
        if (start > end){//如果start超过end还没达到目标，那么就直接去掉
            return ;
        }
        for (int i = start; i <= end; i++){        
            tmp.push_back(candidates[i]);        
            combination(candidates, i + 1, end, target - candidates[i], tmp, result);                   
            tmp.pop_back();        
            //在排序的基础上，通过这一步，在有多个相同元素是，保证同一层的分支中，只让挨着的若干相同元素中的"第一个元素"进行向下发展
            //确保不会出现重复组合， 
            //其实，我们要确保只约束同一层，不会影响下一层，就是要保证 i != start,所以这个while放在for的最后，确保了这一点，
            //而如果我们习惯先判断，再执行，可以等效为在for循环中最开始位置加：这里的i != 0主要是边界检测，防止i-1出现负值；
            //if(i != 0 && candidates[i] == candidates[i - 1]){continue;}
            
            while(i < end && candidates[i] == candidates[i+1]){
                i++;        
            }                
        }

    }



    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int target = 0;
        //一定要排序，确保序列中相同元素聚集起来，方便后面去重。
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        int end = nums.size() - 1;
        combination(nums, 0, end, target, tmp, ans);
        return ans;
    }
};




方案2：利用2进制方法
class Solution {
public:
    int NumOf1(int num){
        int count = 0;
        while (num){
            num = num & (num - 1);
            count++;
            if(count>3){
                return false;
            }
        }
        if(count==3){
            return true;
        }else{
            return false;
        }
        
    }   
    vector<vector<int>>setToVec(set<vector<int>>& s){
        vector<vector<int>> result1(s.begin(),s.end());
        return result1;
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        int target=0;
        int len=nums.size();
        int bit=1<<len;
        vector<vector<int>> ans;
        set<vector<int>>anset;
        sort(nums.begin(), nums.end());
        for(int i=7; i<bit;i++){
            int sum =0;
            vector<int>tmp;
            if(NumOf1(i)){
                for(int j = 0; j < len; j++){
                    if ((i & 1 << j) != 0){
                        sum += nums[j];
                        if(sum>0){
                            break;
                        }  
                        tmp.push_back(nums[j]);
                    }
                }
                if (sum == 0){
                    anset.insert(tmp);
                }
            }
        }
        ans=setToVec(anset);
        return ans;
    }
};

方案3：双指针法，局限是目前只用在3数之和；但是这个方法时唯一AC的方案，上面两个都超时了在3数之和问题上，至于其他n数之和会不会超时，不确定。
#############################################
首先对数组进行排序，排序后固定一个数 nums[i]，再使用左右指针指向 nums[i]后面的两端，
数字分别为 nums[L]和 nums[R]，计算三个数的和 sum 判断是否满足为 0，满足则添加进结果集;
如果 nums[i] 大于 0，则三数之和必然无法等于 0，结束循环;
如果 nums[i] == nums[i−1]，则说明该数字重复，会导致结果重复，所以应该跳过;
当 sum == 0 时，nums[L] == nums[L+1] 则会导致结果重复，应该跳过，L++;
当 sum == 0 时，nums[R] == nums[R−1] 则会导致结果重复，应该跳过，R−−;
时间复杂度：O(n2)O(n^2)O(n2)，nnn 为数组长度

#############################################

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int len = nums.size();
        sort(nums.begin(),nums.end());//sort the input，确保我们找的目标数是从负数到0之间。
        for(int i=0;i<len;i++){
            //目标数不可能大于0；
            if(nums[i]>0){
                return ret;
            }
            //这里是从目标数的角度去重，即不可以为同一个目标做查找组合。
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }
               
            //左右两个指针，相加判断是否等于目标数的相反数，并根据比较结果进行对应的移动；
            int L=i+1;
            int R=len-1;
            while(L<R){
                if(nums[i]+nums[L]+nums[R]==0){
                    ret.push_back({nums[i],nums[L],nums[R]});
                    //在已经有了一个确定结果之后，再在指针区域内进行去重跳转，
                    while(L<R && nums[L]==nums[L+1])
                        L=L+1;
                    while(L<R && nums[R]==nums[R-1])
                        R=R-1;
                    L=L+1;
                    R=R-1;
                }
                //没有结果之前，要根据比较结果大小去移动指针位置；
                else if(nums[i]+nums[L]+nums[R]>0)
                    R=R-1;
                else
                    L=L+1;
            }    

        }
        return ret;
    }
};
#演变为4数之和：
############################
 四数之和与前面三数之和的思路几乎是一样的，嗝。（刚好前些天才写了三数之和的题解）
 如果前面的三数之和会做了的话，这里其实就是在前面的基础上多添加一个遍历的指针而已。
 会做三数之和的可以不用看下面的了。。
  
 使用四个指针(a<b<c<d)。固定最小的a和b在左边，c=b+1,d=_size-1 移动两个指针包夹求解。
 保存使得nums[a]+nums[b]+nums[c]+nums[d]==target的解。偏大时d左移，偏小时c右移。c和d相
 遇时，表示以当前的a和b为最小值的解已经全部求得。b++,进入下一轮循环b循环，当b循环结束后。
 a++，进入下一轮a循环。 即(a在最外层循环，里面嵌套b循环，再嵌套双指针c,d包夹求解)。

 上面的解法存在重复解的原因是因为移动指针时可能出现重复数字的情况。所以我们要确保移动指针后，
 对应的数字要发生改变才行哦。
############################
class Solution{
	public: 
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        vector<vector<int> > res;
        if(nums.size()<4)
        return res;
        int a,b,c,d,_size=nums.size();
        for(a=0;a<=_size-4;a++){
        	if(a>0&&nums[a]==nums[a-1]) continue;      //确保nums[a] 改变了
        	for(b=a+1;b<=_size-3;b++){
        		if(b>a+1&&nums[b]==nums[b-1])continue;   //确保nums[b] 改变了
        		c=b+1,d=_size-1;
        		while(c<d){
        			if(nums[a]+nums[b]+nums[c]+nums[d]<target)
        			    c++;
        			else if(nums[a]+nums[b]+nums[c]+nums[d]>target)
        			    d--;
        			else{
        				res.push_back({nums[a],nums[b],nums[c],nums[d]});
        				while(c<d&&nums[c+1]==nums[c])      //确保nums[c] 改变了
        				    c++;
        				while(c<d&&nums[d-1]==nums[d])      //确保nums[d] 改变了
        				    d--;
        				c++;
        				d--;
					}
				}
			}
		}
		return res;
    }
};


方案4：hashMap针对2数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int,int> m;

        for(int i=0;i<nums.size();i++)
            m[nums[i]]=i;   //向map中添加元素
        
        for(int i=0;i<nums.size();i++)
        {
            if(m.find(target-nums[i])!=m.end()&&m[target-nums[i]]!=i)//m中存在对应的键值，并且不为i
                return {i,m[target-nums[i]]};
        }
        return {};
    }
};








