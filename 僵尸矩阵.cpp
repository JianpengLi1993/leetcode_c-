/*
给一个二维网格，每一个格子都有一个值，2 代表墙，1 代表僵尸，0 代表人类(字符 0, 1, 2)。
僵尸每天可以将上下左右最接近的人类感染成僵尸，但不能穿墙。将所有人类感染为僵尸需要多久，如果不能感染所有人则返回 -1。
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
    char PEOPLE = '0';
    char ZOMBIE = '1';
    char WALL = '2';
    
    int deltaX[4] = {1, 0, 0, -1};
    int deltaY[4] = {0, 1, -1, 0};
     
    /**
     * @param grid a 2D integer grid
     * @return an integer
     */
    int zombie(vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        
        int n = grid.size();
        int m = grid[0].size();
        
        // initialize the queue & count people
        int people = 0;
        queue<Coordinate> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == PEOPLE) {
                    people++;
                } else if (grid[i][j] == ZOMBIE) {
                    Coordinate tmp(i,j);
                    q.push(tmp);
                }
            }
        }
        
        // corner case
        if (people == 0) {
            return 0;
        }
        
        // bfs
        //days相当于层序
        int days = 0;
        while (!q.isEmpty()) {
            days++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Coordinate zb = q.front();
                q.poll()
                for (int direction = 0; direction < 4; direction++) {
                    Coordinate adj(
                        zb.x + deltaX[direction],
                        zb.y + deltaY[direction]
                    );
                    //判断，若不是人类（僵尸或墙），则继续
                    if (!isPeople(adj, grid)) {
                        continue;
                    }
                    //当是人类时，进行转化为僵尸
                    grid[adj.x][adj.y] = ZOMBIE;
                    people--;
                    if (people == 0) {
                        return days;
                    }
                    //将新转化来的节点入队列；
                    q.push(adj);
                }
            }
        }
        
        return -1;
    }
    
    private boolean isPeople(Coordinate& coor, vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        if (coor.x < 0 || coor.x >= n) {
            return false;
        }
        if (coor.y < 0 || coor.y >= m) {
            return false;
        }
        return (grid[coor.x][coor.y] == PEOPLE);
    }
};
