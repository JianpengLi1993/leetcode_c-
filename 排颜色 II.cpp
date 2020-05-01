给定一个有n个对象（包括k种不同的颜色，并按照1到k进行编号）的数组，将对象进行分类使相同颜色的对象相邻，并按照1,2，...k的顺序进行排序。
注意，这里数字是从1到k,而前面那个三色分类题目中，是从0到2.

class Solution {
public:
    /**
     * @param colors: A list of integer
     * @param k: An integer
     * @return: nothing
     */
    void sortColors2(vector<int> &colors, int k) {
        // write your code here
        partition(colors, 0, colors.size()-1, 1, k);
    }
    //是快速排序与归并排序的一种结合，colors, start, end这三个参数相当于快排，用于快速选择划分指定区域的数组元素，
    //而startk, endk两个参数是借鉴了归并排序的思想，将该层进一步划分为两个区间，进行下一层的排序，而且这两个参数也起到了计算快速排序中pivot的作用。
    //所以，一共需要logk层的递归，每一层需要总共遍历n个元素（n为总个数）进行左右划分。所以O(nlogk).
    void partition(vector<int>& colors, int start, int end, int startk, int endk) {
        //前面是一层当中快速选择的出口，后面那个是层数的出口。
        if (start >= end || startk >= endk) {
            return;
        }
        
        int midk = (startk+endk)/2;
        int i = start, j = end;
        //当endk-startk=2时，退化为快速选择算法。
        while (i <= j) {
            while (i <= j && colors[i] <= midk) {
                i++;
            }
            while (i <= j && colors[j] > midk) {
                j--;
            }
            if (i <= j) {
                int temp = colors[j];
                colors[j] = colors[i];
                colors[i] = temp;
                i++;
                j--;
            }
        }

        partition(colors, start, j, startk, midk);
        partition(colors, i, end, midk+1, endk);
    }
};
