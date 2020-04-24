/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1:

输入:
11110
11010
11000
00000
输出: 1

示例 2:

输入:
11000
11000
00100
00011
输出: 3
解释: 每座岛屿只能由水平和/或竖直方向上相邻的陆地连接而成。
*/

class Coordinate {  
    public:
    int x, y;
    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Solution {
public:
    //这个是技巧，四个方向
    vector<int> directionX = {0, 1, 0, -1};
    vector<int> directionY = {1, 0, -1, 0};
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        
        int n = grid.size();
        int m = grid[0].size();
        int islands = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]=='1') {
                    markByBFS(grid, i, j);
                    islands++;
                }
            }
        }
        return islands;
    }

    void markByBFS(vector<vector<char>>& grid, int x, int y){
        queue<Coordinate> q;
        //q和grid[x][y]绑定一起更新；
        q.push(Coordinate(x,y));
        grid[x][y]='0';
        //BFS只遍历，不记录层次
        while(!q.empty()){
            Coordinate coor = q.front();
            q.pop();
            //遍历四个方向并更新
            for (int i = 0; i < 4; i++) {
                Coordinate adj(
                    coor.x + directionX[i],
                    coor.y + directionY[i]
                );
                //检测是否越界
                if (!inBound(adj, grid)) {
                    continue;
                }
                if (grid[adj.x][adj.y]=='1') {
                    grid[adj.x][adj.y] = '0';
                    q.push(adj);
                }
            }
        }

    }
    
    bool inBound(Coordinate& coor, vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        return coor.x >= 0 && coor.x < n && coor.y >= 0 && coor.y < m;
    }

};

