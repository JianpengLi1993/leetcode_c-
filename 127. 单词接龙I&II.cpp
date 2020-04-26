/*
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：
	1.每次转换只能改变一个字母。
	2.转换过程中的中间单词必须是字典中的单词。

说明:

	如果不存在这样的转换序列，返回 0。
	所有单词具有相同的长度。
	所有单词只由小写字母组成。
	字典中不存在重复的单词。
	你可以假设 beginWord 和 endWord 是非空的，且二者不相同。

示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出: 5

解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     返回它的长度 5。


示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: 0

解释: endWord "cog" 不在字典中，所以无法进行转换。

*/
思想：简单图最短路径，利用BFS.难点在于建图，即确定单词节点间的邻接关系
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int L = beginWord.length();
        //确立单词间的图关系；
        //建立一个倒序表，key是通用化后的单词，value是相应的所有原单词列表；
        unordered_map<string,vector<string>> allComboDict;
        for(auto word:wordList){
            for(int i = 0; i < L; i++){
                string newWord = word;
                newWord[i]='*';
                if(allComboDict.find(newWord) != allComboDict.end()){
                    allComboDict[newWord].push_back(word);
                }else{
                    vector<string> tmp;
                    tmp.push_back(word);
                    allComboDict.insert(make_pair(newWord,tmp));
                    tmp.clear();
                }

            }
        }
        //开始BFS
        // Queue for BFS,这里的pair必须加
        queue<pair<string, int>>Q;
        Q.push(make_pair(beginWord,1));
        // Visited to make sure we don't repeat processing same word.防止出现循环变化；
        unordered_map<string, bool> visited;
        visited.insert(make_pair(beginWord, true));

        while (!Q.empty()) {
            pair<string, int> node = Q.front();
            Q.pop();

            string word = node.first;
            int level = node.second;
            //对于出队的每一个元素，进行逐个位置的通用化变换，并找出遍历相关的词列表，将其入队，
            //相当于与出队的这个单词邻接的单词就是下一层单词，可以入队
            for (int i = 0; i < L; i++) {

                // Intermediate words for current word
                string newWord = word;
                newWord[i]='*';

                // 逐个遍历可以一步转化的单词Next states are all the words which share the same intermediate state.
                for (auto adjacentWord : allComboDict[newWord]) {
                    // If at any point if we find what we are looking for
                    // i.e. the end word - we can return with the answer.
                    if (adjacentWord == endWord) {
                        return level + 1;
                    }
                    // Otherwise, add it to the BFS Queue. Also mark it visited
                    if (visited.find(adjacentWord)==visited.end()) {
                        visited.insert(make_pair(adjacentWord, true));
                        Q.push(make_pair(adjacentWord, level + 1));
                    }
                }
            }
        }

    return 0;
    }
};


同一思路的另一种Java实现：
public class Solution {
    public int ladderLength(String start, String end, Set<String> dict) {
        if (dict == null) {
            return 0;
        }

        if (start.equals(end)) {
            return 1;
        }
        
        dict.add(start);
        dict.add(end);
	//两者绑定了。
        HashSet<String> hash = new HashSet<String>();
        Queue<String> queue = new LinkedList<String>();
        queue.offer(start);
        hash.add(start);
        
        int length = 1;
        while(!queue.isEmpty()) {    		//开始bfs
            length++;
	    //记录层数
            int size = queue.size();		//当前步数的队列大小
            for (int i = 0; i < size; i++) {
                String word = queue.poll();
                for (String nextWord: getNextWords(word, dict)) {	//得到新单词列表
                    if (hash.contains(nextWord)) {
                        continue;
                    }
                    if (nextWord.equals(end)) {
                        return length;
                    }
                    
                    hash.add(nextWord);
                    queue.offer(nextWord);			//存入队列继续搜索
                }
            }
        }
        return 0;
    }

    // replace character of a string at given index to a given character
    // return a new string
    private String replace(String s, int index, char c) {
        char[] chars = s.toCharArray();
        chars[index] = c;
        return new String(chars);
    }
    
    // get connections with given word.
    // for example, given word = 'hot', dict = {'hot', 'hit', 'hog'}
    // it will return ['hit', 'hog']
    private ArrayList<String> getNextWords(String word, Set<String> dict) {
        ArrayList<String> nextWords = new ArrayList<String>();
        for (int i = 0; i < word.length(); i++) {//枚举替换位置
            for (char c = 'a'; c <= 'z'; c++) {	 //枚举当前替换字母
                if (c == word.charAt(i)) {
                    continue;
                }
                String nextWord = replace(word, i, c);
                if (dict.contains(nextWord)) {		//如果dict中包含新单词，存入nextWords
                    nextWords.add(nextWord);
                }
            }
        }
        return nextWords;							//构造当前单词的全部下一步方案							     							

    }
}


题目变形：
======================================================
给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：


	每次转换只能改变一个字母。
	转换过程中的中间单词必须是字典中的单词。


说明:


	如果不存在这样的转换序列，返回一个空列表。
	所有单词具有相同的长度。
	所有单词只由小写字母组成。
	字典中不存在重复的单词。
	你可以假设 beginWord 和 endWord 是非空的，且二者不相同。


示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]


示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: []

解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。

======================================================
从 end 到 start 做一次 BFS，并且把距离 end 的距离都保存在 distance 中，并且生成这些路径上的相关节点之间的网络图
（当：存在某些节点不在最短路径上时，会缺少这部分节点与相关这些路径上节点之间的图）。
然后在从 start 到 end 做一次 DFS，每走一步必须确保离 end 的 distance 越来越近。剪枝的作用。

class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: a list of lists of string
     */
    void bfs(string &start, 
             string &end, 
             unordered_set<string> &dict,
             unordered_map<string, int> &dist,
             unordered_map<string, vector<string>> &neighbors) {
                 
        queue<string> strQueue;
        strQueue.push(end);
        dist[end] = 0;
        while (!strQueue.empty()) {
            string curt = strQueue.front(); 
            strQueue.pop();
            int step = dist[curt];
            vector<string> next;
            for (int i = 0; i < start.length(); i++) {
                string neibr = curt;
                for (char x = 'a'; x <= 'z'; x++) {
                    neibr[i] = x;
                    if (curt == neibr || dict.find(neibr) == dict.end()) {
                        continue;
                    }
                    //确保距离是最短距离；                   
                    if (dist.find(neibr) == dist.end()) {
                        strQueue.push(neibr);
                        dist[neibr] = step + 1;
                    }
                    next.push_back(neibr);
                }
            }
            neighbors[curt] = next;
            //走到start就退出了，所以地图以及距离字典不是完全的；
            //若需要一个完整的地图和距离字典，可以一删掉下面这个if判断就行；
            if(curt == start) {
                break;
            } 
        }
    }

    void dfs(string &start, 
             string &end, 
             vector<vector<string>> &allPath,
             vector<string> &path,
             unordered_map<string, int> &dist,
             unordered_map<string, vector<string>> &neighbors) {

        if (start == end) {
            allPath.push_back(path);
            return;
        }
        for (string neibr :neighbors[start]) {
            //第一个条件是为了排除那些：自end到start最短层序遍历过程中没有遇到的单词；这是由于bfs中的地图和距离字典的构建是不完备的，仅是end到start最短路径上相关节点的距离字典，和不完备地图；
            if(dist.find(neibr) == dist.end() || dist[neibr] != dist[start] - 1){
                continue;
            }
            path.push_back(neibr);
            dfs(neibr, end, allPath, path, dist, neighbors);
            path.pop_back();
        }
    }   

    vector<vector<string>> findLadders(string &start, string &end,  vector<string>& wordList) {
        // write your code here
        unordered_set<string> dict(wordList.begin(),wordList.end()); 
        vector<vector<string>> allPath;
        unordered_map<string, vector<string>> mapNeighbors;
        unordered_map<string, int> dist;
        vector<string> path;
        //必须插入start,这是因为我们利用bfs从end找到start的层序遍历过程中，最终的终点是start,而原来的wordList里面不包括start的，来绘制图和距离字典
        dict.insert(start);
        //而end是不可以插入的，因为题目强调，若wordList中不包括end，则说明不存在可行的转换路径
        //dict.insert(end);
        if (dict.find(end) == dict.end()) {
            return allPath;
        }
        //利用bfs,从end到start进行层序遍历，构建两部分内容：
        //1.整个词表之间的图关系---mapNeighbors;
        //2.整个词表中每一个单词若可以到达end,对应的距离关系---dist;
        bfs(start, end, dict, dist, mapNeighbors);
        path.push_back(start);
        dfs(start, end, allPath, path, dist, mapNeighbors);       
        return allPath;       
    }
};
