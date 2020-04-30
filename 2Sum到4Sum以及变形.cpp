两数之和：
只要找到一组解的下标就可以，所以忽略重复元素可能出现重复解的问题。
方案一：HashMap，优势在于不需要排序，如果题目中数组不固定或者随时增加元素，会随时改变，这时用双指针就需要不断排序，复杂度高
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // hash[i]表示nums中数值为i的下标
        unordered_map<int, int> hash;
        vector<int> result;

        // 一边循环每个数，一边加入hash表。
        //这里的关键要注意这种情况：target-nums[i] == nums[i],此时实际上数组中只有nums[i]这一个数字；
        //为了避免这种情况发生，要注意下面两步的先后顺序，一定是后将nums[i]放入hash表中，这样先执行的if判断语句只能搜索这一轮之前的（nums[i]）
        //之前的元素有没有恰好等于target-nums[i]的元素。
        for (int i = 0; i < nums.size(); i++) {
            if (hash.find(target - nums[i]) != hash.end()) {
                // target - nums[i]的下标更小，放在前面
                result.push_back(hash[target - nums[i]]);
                result.push_back(i);
                return result;
            }
            hash[nums[i]] = i;
        }

        // 无解的情况
        result.push_back(-1);
        result.push_back(-1);
        return result;
    }
};



方案二：双指针法，优势在于空间复杂度O(1),但缺点就是需要排序。
先对序列排序（要把原下标一并存好），再首尾两个指针，向中间移动
class Solution {
struct Less {
    bool operator()(pair<int, int> &a, pair<int, int> &b) {
        return a.second < b.second;
    }
};

public:
    /**
     * @param numbers: An array of Integer
     * @param target: target = numbers[index1] + numbers[index2]
     * @return: [index1, index2] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &numbers, int target) {
        // write your code here
        vector<pair<int, int>> number;
        for (int i = 0; i < numbers.size(); i++) {
            number.push_back(make_pair(i, numbers[i])); 
        }
        sort(number.begin(), number.end(), Less());
        int L = 0, R = numbers.size() - 1;
        while (L < R) {
            if (number[L].second + number[R].second == target) {
                int t1 = number[L].first;
                int t2 = number[R].first;
                vector<int> result{min(t1, t2), max(t1, t2)};
                return result;
            }
            if (number[L].second + number[R].second < target) {
                L++;
            } else {
                R--;
            }
        }
        vector<int> result{-1, -1};
        return result;
    }
};

变形一：题目要求数组通过add()函数会被随时增加，此时返回不同时刻的数组中是否存在target组合，只需返回bool.这时，
双指针法就不可以用了。因为要不断排序和插入元素。
Java源码：
public class TwoSum{
    private List<Integer>list = null；
    //key为数值，value出现的次数。
    private Map<Integer， Integer>map = null；
    public TwoSum（）{
        list = new ArrayList<Integer>（）；
        map = new HashMap<Integer，Integer>（）；
    }
    
    public void add(int number){
        if(map.containKey(number)){
            map.put(number, map.get(number) + 1);
        }else {
            map.put(number,1);
            list.add(number);
        }
        
    }
    
    public boolean find(int value){
        for(int i = 0; i < list.size(); i++){
            int num1 = list.get(i), nums2 = value - num1;
            //注意，由于add函数的存在，所以，hash表会先全部建立，
            //所以方案1当中的一边建立一边查找的方式来避免target-nums[i]=nums[i]的方法这里不可以
            //需要存储每个元素出现的次数，若需要的元素和遍历到的元素相等（此时有可能发生这种情况），还要确定对应的个数是否大于1 ！
            if((num1 == num2 && map.get(num1) >1) || (num1 != num2 && map.containsKey(num2))){
                return true;
            }
        }
        return false;
    }
}


变形2：要给出所有组合的个数
class Solution {
public:
    /**
     * @param nums an array of integer
     * @param target an integer
     * @return an integer
     */
    int twoSum6(vector<int> &nums, int target) {
        // Write your code here
        int n = nums.size(), cnt = 0;
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() -1;
        while (l < r) {
            //存在解的情况，当产生一个解时，接着，为了不重复计数，需要调用两个while循环，使得两个指针分别移动到与当前解不同的新位置上。
            if (nums[l] + nums[r] == target) {
                cnt ++;
                l ++, r --;
                while (l < r && nums[r] == nums[r + 1])
                    r --;
                while (l < r && nums[l] == nums[l - 1])
                    l ++;
            } else if (nums[l] + nums[r] > target) {
                r --;
            } else {
                l ++;
            }
        }
        return cnt;
    }
};

变形3：三数之和
将数组排序后，要寻找a+b+c=target,本题target=0;
等价于遍历a的同时，双指针指向a后面的首尾，寻找b+c=target-a;
这里，为了去重，也要考虑当找到一组解时，相同指针跳跃位置的技巧，包括：
1.a遍历过程的去重，即相同的a不需要再找
2.b、c两个指针位置的去重，跳跃
public class Solution {
    /**
     * @param nums : Give an array numbers of n integer
     * @return : Find all unique triplets in the array which gives the sum of zero.
     */
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> results = new ArrayList<>();
        
        if (nums == null || nums.length < 3) {
            return results;
        }
        
        Arrays.sort(nums);

        for (int i = 0; i < nums.length - 2; i++) {
            // 跳跃A,skip duplicate triples with the same first numebr
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1, right = nums.length - 1;
            int target = -nums[i];
            
            twoSum(nums, left, right, target, results);
        }
        
        return results;
    }
    
    public void twoSum(int[] nums,
                       int left,
                       int right,
                       int target,
                       List<List<Integer>> results) {
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                ArrayList<Integer> triple = new ArrayList<>();
                triple.add(-target);
                triple.add(nums[left]);
                triple.add(nums[right]);
                results.add(triple);
                
                left++;
                right--;
                // 跳跃b、c。skip duplicate pairs with the same left
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
                // skip duplicate pairs with the same right
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
            } else if (nums[left] + nums[right] < target) {
                left++;
            } else {
                right--;
            }
        }
    }
}

变形4:数组中三个元素能构成三角形的组合有多少，注意，这里不去冲，即[4,4,4,4]存在4个三角形组合
思想一致，排序（升序）-->固定一条边（看做最长边）进行遍历-->另外两条较短的边（在长边的左侧相向寻找）被双指针指着，求和看是否大于固定的那条边
若满足，则Right-Left中间的所有边都可以和Right一起构成三角形的两条短边
Java版本:
public int triangleCount(int S[]){
    Arrays.sort(S);
    int ans = 0;
    //循环最长边
    for(int i = 0; i<S.length; ++i){
        //left必然从0开始，right从i-1开始；
        int left = 0,right =i - 1;
        while(left <right){
            if(S[left] + S[right] > S[i]){
                ans += right - left;
                right -= 1;
            }else{
                left += 1;
            }
        }
        return ans;
    }
    
}

变形5：与4类似，要求两数之和小于等于targt的个数
public int twoSum5(int [] nums, int target){
    if(nums == null || nums.length < 2){
        return 0;
    }
    Arrays.sort(nums);
    int left = 0, right = nums.length -1;
    int count = 0;
    while(left<right){
        if(nums[left]+nums[right]<=target){
            count += right - left;
            left++;
        }els{
            right--;
        }
    }
    return count;
}

变形6：两数之和最接近目标值的组合，对应目标值的距离是多少

public int twoSumCloset(int [] nums, int target){
    if(nums==null){
        return -1;
    }
    Arrays.sort(nums);
    int i = 0, j = nums.length - 1;
    int best = Integer.MAX_VALUE;
    while(i<j){
        int diff = Math.abs(nums[i] + nums[j] - target);
        best = Math.min(best,diff);
        if(nums[i] + nums[j]<target){
            i++;
        }else{
            j--;
        }
    }
    return best;
}

变形7：给一个包含 n 个整数的数组 S, 找到和与给定整数 target 最接近的三元组，返回这三个数的和。
class Solution {
public:    
    /**
     * @param numbers: Give an array numbers of n integer
     * @param target: An integer
     * @return: return the sum of the three integers, the sum closest target.
     */
    int threeSumClosest(vector<int> nums, int target) {
        sort(nums.begin(), nums.end());
        int result = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size(); i++) {
            int start = i + 1, end = nums.size() - 1;
            while (start < end) {
                if (abs(result - target) > 
                        abs(nums[i] + nums[start] + nums[end] - target)) {
                    result = nums[i] + nums[start] + nums[end];
                }
                if (nums[i] + nums[start] + nums[end] < target) {
                    start++;
                } else {
                    end--;
                }
            }
        }
        return result;
    }
};

变形8：四数之和
固定两个点，然后用双指针的做法，扫描一下后续数组，记录答案即可。
class Solution {
public:
    /*
    题意：找到数列中所有和等于目标数的四元组，需去重
    多枚举一个数后，参照3Sum的做法，O(N^3)
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int len = nums.size();
        int left, right, sum;
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> tmp;
        for (int i = 0; i < len - 3; i++) {
            //去重1
            if (i && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < len - 2; j++) {
                //去重2，还要避免和第一个数相撞；
                if (j != i + 1 && nums[j] == nums[j - 1]) continue;
                sum = target - nums[i] - nums[j];
                left = j + 1;
                right = len - 1;
                while (left < right) {
                    if (nums[left] + nums[right] == sum) {
                        tmp.clear();
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[left]);
                        tmp.push_back(nums[right]);
                        res.push_back(tmp);
                        left++;
                        right--;
                        //去重3、4
                        while (left < right && nums[left] == nums[left - 1]) left++;
                        while (left < right && nums[right] == nums[right + 1]) right--;
                    } else 
                        if (nums[left] + nums[right] > sum) right--;
                        else left++;
                }
            }
        }
        return res;
    }
};

变形9：两数之差等于target
先排序后用双指针。这里用逆向双指针好像不太可行，因为假设target=6, 两个符合条件的数的索引可能是(1,7), (3,9), (7,12)，等等。
假如我们设p1=0, p2=12,但是nums[p2]-nums[p1]>6，那我们是p1++还是p2–呢? 两个都进行就复杂了。
这里用同向双指针比较好。一开始p1=0, p2=1。当两指针指向的值的difference<target时，p2++，
当difference>target时，p1++(但这里要注意p1不能超过p2,若p1==p2，则p2++)，若difference=target，则返回p1,p2。
这里要先用一个class把数组的index保存下来，因为sort后顺序会乱。另外一个要注意的地方是如果用stl::sort的话，
必须把less_pair()定义成static，因为sort是global function()，

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PairClass {
public:
    PairClass(int i=0, int v=0) : index(i), val(v) {}
    int index;
    int val;
};

static bool less_pair(const PairClass &first, const PairClass &second) {
    return first.val < second.val;
}
vector<int> twoSum7(vector<int> &nums, int target) {
    int len=nums.size();
    vector<int> result;
    if (len<=1) return result;

    int p1=0, p2=1;

    //initialize pairs
    vector<PairClass> pairs(len);
    for (int i=0; i<len; ++i)
        pairs[i]=PairClass(i, nums[i]);

    sort(pairs.begin(), pairs.end(), less_pair);

    while(p2<len && p1<p2) {
        int diff = pairs[p2].val-pairs[p1].val;
        if (diff == abs(target)) {
            result.push_back(min(pairs[p1].index, pairs[p2].index)+1);  //vector index begins from 1
            result.push_back(max(pairs[p1].index, pairs[p2].index)+1);  //vector index begins from 1
            return result;
        } else if (diff < abs(target)) {
            p2++;
        } else {
            p1++;
            if (p1==p2) p2++;
        }
    }
    return result;
}

