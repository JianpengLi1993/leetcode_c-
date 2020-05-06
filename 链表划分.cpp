给定一个单链表和数值x，划分链表使得所有小于x的节点排在大于等于x的节点之前。
你应该保留两部分内链表节点原有的相对顺序。

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
双指针方法，用两个指针将两个部分分别串起来。最后在将两个部分拼接起来。
left指针用来串起来所有小于x的结点，
right指针用来串起来所有大于等于x的结点。
得到两个链表，一个是小于x的，一个是大于等于x的，做一个拼接即可。

class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @param x: an integer
     * @return: a ListNode 
     */
    ListNode *partition(ListNode *head, int x) {
        ListNode *leftDummy = new ListNode(0);
        ListNode *rightDummy = new ListNode(0);
        ListNode *leftTail = leftDummy;
        ListNode *rightTail = rightDummy;
        
        while (head != NULL) {
            if (head->val < x) {
                leftTail->next = head;
                leftTail = head;
            } else {
                rightTail->next = head;
                rightTail = head;
            }
            head = head->next;
        }
        
        leftTail->next = rightDummy->next;
        rightTail->next = NULL;
        
        return leftDummy->next;
    }
};
