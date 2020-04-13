/******************************************/
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

问总共有多少条不同的路径？
/******************************************/
方案一：递归，有点那切数列的感觉。
class Solution {
public:
    int a[101][101] = {0};//这里记录所有已经计算好的数值，是一个很重要的优化。
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0)
		    return 0;
        else if (m == 1 || n == 1)
            return 1;
        else if (a[m][n] > 0)
            return a[m][n];
        else if(a[n][m] > 0)
            return a[n][m];//对称优化，也是很重要
        a[m - 1][n] = uniquePaths(m - 1, n);
        a[m][n - 1] = uniquePaths(m, n - 1);
        a[m][n] = a[m - 1][n] + a[m][n - 1];
        return a[m][n];
    }
};


方案二：
其实，本道题在排列组合问题中可化为求C(m+n-2,m-1)（或C(m+n-2,n-1)）。
即一共有m行n列，其中需要向下走m-1步，向右走n-1步，一共走m+n-2步。所以就是在m+n-2步中选出哪m-1步是向下走的，其余自动为向右走的步数。
**本方法要注意计算组合数的时候要先化简，且要用unsigned long long/double 来表示，否则会超过范围。
class Solution {
public:
int uniquePaths(int m, int n) {
	if (m == 1 || n == 1)
		return 1;
	if (m > n)
		swap(m, n);//保证m<=n
	//计算阶乘：不用调用函数，节省空间
	unsigned long long int temp = 1;
	unsigned long long int result = 1;
	for (int i = 1; i <= m-1 ; i++)
	{
		temp *= i;
	}
	for (int i = n; i <= m + n - 2; i++)
	{
		result *= i;
	}
	result = result / temp;
	return result;
}
};
