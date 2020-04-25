/*
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。


*/

class Solution {
public:
    /**
     * Get all distinct N-Queen solutions
     * @param n: The number of queens
     * @return: All distinct solutions
     * For example, A string '...Q' shows a queen on forth position
     */
    vector<vector<string> > solveNQueens(int n) {
        // write your code here
        vector<vector<string> > result;
        if( n <= 0 )
        {
            return result;
        }
        vector<int> cols;
        search(n, cols, result);
        return result;
    }
    //排列问题的DFS
    void search(int n, vector<int> &cols, vector<vector<string> > &result)
    {
        if(cols.size() == n)
        {
            result.push_back(drawResult(cols, n));
            return;
        }
        for(int col = 0; col < n; col++)
        {
            if(!isValid(cols, col))
            {
                continue;
            }
            cols.push_back(col);
            search(n, cols, result);
            cols.pop_back();
        }
    }
    //判断是否有效，等效于一般排列问题中关于某个元素是否使用过，而这里要有三点判断：
    //1.该列是否被使用过；
    //2.左上到右下对角线是否冲突：对角线上元素的横纵坐标之差是否相等判断；
    //3.右上到左下对角线是否冲突：对角线上元素的横纵坐标之和是否相等判断；
    bool isValid(vector<int> &cols, int col)
    {
        int row = cols.size();
        for(int i = 0; i < row; ++i)
        {
            if(cols[i] == col)
            {
                return false;
            }
            if(i - cols[i] == row - col)
            {
                return false;
            }
            if(i + cols[i] == row + col)
            {
                return false;
            }
        }
        return true;
    }
    
    vector<string> drawResult(vector<int> &cols, int n)
    {
        vector<string> result;
        for(int i = 0; i < cols.size(); ++i)
        {
            string temp(n, '.');
            temp[cols[i]] = 'Q';
            result.push_back(temp);
        }
        return result;
    }
};
