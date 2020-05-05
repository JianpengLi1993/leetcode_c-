/***************************************************************************/
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

示例:

输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6


这里我不知道计算是否正确，如果不对还望指出~~
方法1： 建立优先队列（最大堆或者最小堆均可），不过不需要全部元素一次性入队；只需要让链表头元素入队即可，弹出该元素后，该链表往后移。
https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/c-you-xian-dui-lie-liang-liang-he-bing-fen-zhi-he-/

空间复杂度 O(k)，时间复杂度 O(nlog(k))；n是所有节点个数，k是链表数
/***************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 优先级队列用法：https://blog.csdn.net/weixin_36888577/article/details/79937886
 auto的用法：https://blog.csdn.net/qq_42957923/article/details/90107840
 
class Solution {
public:
    // 小根堆的回调函数
    struct cmp{  
       bool operator()(ListNode *a,ListNode *b){
          return a->val > b->val;
       }};

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> pri_queue;
        // 建立大小为k的小根堆
        for(auto elem : lists){
            if(elem) pri_queue.push(elem);
        }
        // 可以使用哑节点/哨兵节点
        ListNode dummy(-1);
        ListNode* p = &dummy;
        // 开始出队
        while(!pri_queue.empty()){
            p->next = pri_queue.top(); 
            pri_queue.pop(); 
            p = p->next;
            if(p->next) pri_queue.push(p->next);
        }
        return dummy.next;  
    }
};

方案2：
分治法
class Solution {
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return NULL;
        }
        return mergeHelper(lists, 0, lists.size() - 1);
    }
    
    //1.返回start到end之间的序列进行排序为一个序列的头结点的指针
    ListNode* mergeHelper(vector<ListNode*>& lists, int start, int end) {
        if (start == end) {
            return lists[start];
        }
        
        int mid = start + (end - start) / 2;
        //2.1 分治
        ListNode* left = mergeHelper(lists, start, mid);
        ListNode* right = mergeHelper(lists, mid + 1, end);
        //2.2 整合
        return mergeTwoLists(left, right);
    }
    //整合两个有序序列成一个有序链表。
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //对于链表，往往都是这样，设定一个固定的头，再找一个移动指针。
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        while (list1 != NULL && list2 != NULL) {
            if (list1->val < list2->val) {
                tail->next = list1;
                tail = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                tail = list2;
                list2 = list2->next;
            }
        }
        if (list1 != NULL) {
            tail->next = list1;
        } else {
            tail->next = list2;
        }
        //返回的是next指针
        return dummy->next;
    }
};



方案3：
//////////////////////////////////////////////////////
在做这个题前，我们肯定会遇到 21. 合并两个有序链表 这道题，不了解的伙伴儿可以先移步了解一下。
简单的说，合并两个有序链表可以使用迭代或者递归来完成，思路是一样的；这里就不多做介绍了。
对于合并K个链表，不难想到我们可以从头开始两两合并。

时间复杂度 O(kn) ，空间复杂度 O(1)【不考虑递归调用栈】
//////////////////////////////////////////////////////

class Solution {
public:
    // 合并两个有序链表
    ListNode* merge(ListNode* p1, ListNode* p2){
        if(!p1) return p2;
        if(!p2) return p1;
        if(p1->val <= p2->val){
            p1->next = merge(p1->next, p2);
            return p1;
        }else{
            p2->next = merge(p1, p2->next);
            return p2;
        }
    }

     ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        ListNode* head = lists[0];
        for(int i = 1; i<lists.size(); ++i){
            if(lists[i]) head = merge(head, lists[i]);
        }
        return head;  
    }
};
方案4：
与方案3类似，也是两两merge，但是区别在于，1-2,3-4,5-6,7-8，之间先merge，然后把这一轮生成的新的1、2、3、4个链表继续，1-2,3-4进行merge，
这样的复杂度O(nlogk)
  Java代码：
  
public class Solution {
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    public ListNode mergeKLists(List<ListNode> lists) {  
        if (lists == null || lists.size() == 0) {
            return null;
        }
        
        while (lists.size() > 1) {
            List<ListNode> new_lists = new ArrayList<ListNode>();
            for (int i = 0; i + 1 < lists.size(); i += 2) {
                ListNode merged_list = merge(lists.get(i), lists.get(i+1));
                new_lists.add(merged_list);
            }
            if (lists.size() % 2 == 1) {
                new_lists.add(lists.get(lists.size() - 1));
            }
            lists = new_lists;
        }
        
        return lists.get(0);
    }
    
    private ListNode merge(ListNode a, ListNode b) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;
        while (a != null && b != null) {
            if (a.val < b.val) {
                tail.next = a;
                a = a.next;
            } else {
                tail.next = b;
                b = b.next;
            }
            tail = tail.next;
        }
        
        if (a != null) {
            tail.next = a;
        } else {
            tail.next = b;
        }
        
        return dummy.next;
    }
}
