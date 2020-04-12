/***********************************************************************/
给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

说明：


	所有输入均为小写字母。
	不考虑答案输出的顺序。
/***********************************************************************/

*使用到map与vector的互转和嵌套。

class Solution1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;  
        string tmp; //临时string
        unordered_map<string,vector<string>> work; //使用无序map的速度会更快,判断排序后单词是否存在，即字母组成是否一致
        for(auto str:strs){
            tmp=str;
            sort(tmp.begin(),tmp.end());
            unordered_map<string,vector<string>>::iterator it=work.find(tmp);
            if(it==work.end()){
                vector<std::string> vec;
                vec.push_back(str);
                work.insert(make_pair(tmp,vec));
            }else{
                work[tmp].push_back(str);
            }
        }
        for (auto it = work.begin(); it != work.end(); ++it) {
            vector<string>::iterator it_inner;
            vector<string>strTmp;
            for (it_inner = it->second.begin(); it_inner != it->second.end(); ++it_inner) {
                
                //std::cout << *it_inner ;
                strTmp.push_back(*it_inner);
            }
            res.push_back(strTmp);
            //std::cout<<endl;
        }
        return res;
    }
};





class Solution2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;  
        int sub=0;  //结果vector的下标值
        string tmp; //临时string
        unordered_map<string,int> work; //判断排序后单词是否存在，即字母组成是否一致
        for(auto str:strs)
        {
            tmp=str;
            sort(tmp.begin(),tmp.end());
            if(work.count(tmp))
            {
               res[work[tmp]].push_back(str);
            }
            else
            {
                vector<string> vec(1,str);
                res.push_back(vec);
                work[tmp]=sub++;
            }
        }
        return res;
    }
};
