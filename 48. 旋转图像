/*************************************************************/
给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。

说明：

你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

示例 1:

给定 matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

原地旋转输入矩阵，使其变为:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]

/*************************************************************/


方案1：
先将矩阵转置，后按照竖轴左右旋转。
class Solution1 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int len = matrix.size();
        for(int i=0;i<len;i++){
            for(int j=i;j<len;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }

        for(int i=0;i<len;i++){
            for(int j=0;j<(len)/2;j++){
                swap(matrix[i][j],matrix[i][len-1-j]);
            }
        }

    }
};


方案2：
先竖轴对称旋转，后按照主对角线旋转。
class Solution2 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int len = matrix.size();
        int mid = (len-1)/2;
        //flip over x = len/2
        for(int i=0; i<len; i++){
            for(int j=0; j<=mid; j++){
                swap(matrix[i][j],matrix[i][len-1-j]);
            }
        }
        //flip over diag
        for(int i=0; i<len; i++){
            for(int j=0; j<len-1-i; j++){
                swap(matrix[i][j],matrix[len-1-j][len-1-i]);
            }
        }
    }
};

