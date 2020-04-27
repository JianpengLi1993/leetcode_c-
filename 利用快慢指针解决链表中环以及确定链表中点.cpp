*********************************************************
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。

*********************************************************

class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @return: the node where the cycle begins. 
     *           If there is no cycle, return null
     */
    ListNode *detectCycle(ListNode *head) {
        // write your code here
        ListNode* ptr1,* ptr2;
        if(head == NULL)
            return NULL;
        //ptr1为慢指针，ptr2为快指针
        ptr1 = head ;
        ptr2 = head;

        while(ptr2 != NULL && ptr2->next != NULL)  //ptr2快指针
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            if(ptr1 == ptr2)           //快慢指针相遇,说明有环
            {
                ptr1 = head;    		//从头移动ptr1
                while(ptr1 != ptr2)		//同时移动ptr1和ptr2
                {
                    ptr2 = ptr2->next;
                    ptr1 = ptr1->next;
                }
                //二次相遇，此时指针所在位置为环的入口
                return ptr1;		//两指针相遇处即为环的入口
            }

        }
        return NULL;
    }
};

#####利用快慢指针找到链表的中间结点，并将链表分为两个个链表：

    //若链表只有一个节点，返回值就是其本身，若大于一个节点时，返回值分奇偶数
    ////这里利用快慢指针的算法来寻找切分中点。
    //1.当fast和slow初始化同一起点，结束循环时，slow的位置分原序列是奇数个还是偶数个，
    //若是奇数个，slow位于正中间，fast位于最后一个不为null的节点处；
    //若为偶数个，slow位于中间两个数的后一个位置，fast位于倒数第一个节点后面的null节点处；
    //利用prevSlow可以将链表分为[start,mid-1]、[mid]、[mid+1,end]三段；
    ListNode* findMidOfList(ListNode*head){
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* prevSlow = slow;
        //这样判断方式可以判断2个节点的链表；
        while(fast != nullptr && fast -> next != nullptr){
                fast = fast -> next;
                fast = fast -> next;
                prevSlow = slow;
                slow = slow -> next;
            }
        prevSlow -> next = nullptr;
        //此时通过head可以一直走到slow-1的位置；
        //通过slow可以走到结尾；
        ListNode* mid = slow;
        return mid;
    }
    
    
