/********************************************************************/
双指针寻找有序数组中两数和为定值的算法，解释如下：当array[p1] + array[p2] < target时，
下一步调整的目标是要使左边的式子增大。由于p1从左往右搜索，array[p1]增大，p2从右往左搜索，array[p2]减小，
则使左边的式子增大的唯一可能是p1右移，即p1++；另外，注意到，当出现一个满足array[p1] + array[p2] == target的情况时，
p1左边的任何位置，或p2右侧的任何位置处均不可能出现满足搜索条件的值(左侧总是小于,右侧总是大于)。
同理可知，当array[p1] + array[p2]  = 或 > 时的指针移动情况。由于p1,p2相遇时正好相当于遍历了一次有序数组，所以算法时间复杂度为O(n)。

受双指针寻找有序数组中两数和为定值算法的启发，我们可以将这个三数和问题转化为两数和问题，但先要进行排序(O(nlogn))，
然后循环选定一个数(O(n))，在这个数“后面”的区间里寻找两数和为定值的数组(O(n))，算法整体的时间复杂度为O(n^2)。

算法中最难的一部分，是去重问题，如前面分析的，题目要求返回不重复的triple，这就要求在搜索时注意技巧。
1)对于目标数来讲，不能为多个相同的目标数搜索合适的组合
2)对于搜索的组合来讲，两个指针都有可能分别遇到前后相邻为同一个元素的情况，此时，两个指针都移动即可。
最终返回三个数，对于每个数，如果其等于它上个位置的数值时，(数组的有序性保证了相等数的相邻性)，它便不能存入返回vector中，
即代码中增加的if判断条件。


题目：给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

 

示例：

给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

*这道题对复杂度要求较高，之前的回溯法不可以用，会超时。
/********************************************************************/
class Solution {
public:
    vector<vector<int> > threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        vector<int > vtemp;
        int len = nums.size();
        sort(nums.begin(),nums.end());//sort the input
        for(int i=0;i<len-2;i++){
            //find the tripe for each nums[i]
            // j1 and j2 log the index of the other two numbers
            //这里是从目标数的角度去重，即不可以为同一个目标做查找组合。
            if(i ==0 ||(i>0 && nums[i] != nums[i-1])){
                int p1 = i+1, p2 = len-1; // set two pointers
                while(p1 < p2){
                    if(nums[p1] + nums[p2] < -nums[i]){
                        p1++;
                    }else if(nums[p1] + nums[p2] == -nums[i]){
                        if(p1 == i+1){//这个判断很有必要，方便第二种情况去重时只在搜索区间内去重，不会对目标数造成影响。
                            vector<int > vtemp{nums[i], nums[p1], nums[p2]};
                            ret.push_back(vtemp);
                            vtemp.clear();

                        }else if(nums[p1] != nums[p1-1]){//这里只需要对两个指针中的一个进行去重判断就行，不需要分别判断。
                            vector<int > vtemp{nums[i], nums[p1], nums[p2]};
                            ret.push_back(vtemp);
                            vtemp.clear();

                        }
                        p1++,p2--;
                    }else{
                         p2--;
                    }
                }
            }


        }
        return ret;

    }
};
