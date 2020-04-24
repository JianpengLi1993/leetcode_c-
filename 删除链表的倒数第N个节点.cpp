/********************************************************************/
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.

说明：

给定的 n 保证是有效的。

进阶：

你能尝试使用一趟扫描实现吗？

思路：上述算法可以优化为只使用一次遍历。我们可以使用两个指针而不是一个指针。
第一个指针从列表的开头向前移动 n+1n+1n+1 步，而第二个指针将从列表的开头出发。
现在，这两个指针被 nnn 个结点分开。我们通过同时移动两个指针向前来保持这个恒定的间隔，
直到第一个指针到达最后一个结点。此时第二个指针将指向从最后一个结点数起的第 nnn 个结点。
我们重新链接第二个指针所引用的结点的 next 指针指向该结点的下下个结点。
/********************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(n <= 0) return head;
        ListNode* l1 = new ListNode(-1);
        l1 = head;
        while(n){
            if(!l1) return NULL;
            l1 = l1->next;
            --n;
        }
        //n>链表长度
        if(!l1) return head->next;
        ListNode* l2 = new ListNode(-1);
        l2 = head;
        while(l1->next){
            l1 = l1->next;
            l2 = l2->next;
        }
        l2->next = l2->next->next;

        return head;

    }
};
