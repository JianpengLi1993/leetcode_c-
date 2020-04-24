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
