/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

 
示例：

给你这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

 */



class Solution {
    /**
     * @param head a ListNode
     * @param k an integer
     * @return a ListNode
     */
    public:
        ListNode* reverseKGroup(ListNode* head, int k) {
            //下面两句，外加return dummy.next;是大部分链表题目的规范用法，
            //使得所有操作都是针对dummy后边的节点，dummy本身不动，dummy->next就可以直接找到后面的头
            ListNode* dummy = new ListNode(-1);;
            dummy->next = head;
            ///Dummy->1->2->3->4->5->6->7->8->9
            ///==>
            ///Dummy->[3->2->1]->[6->5->4]->8->9
            ListNode* prev = dummy;
            while (prev != NULL) {
                //返回的都是翻转操作的那一段完成后的最后一个节点，作为下一侧翻转开始的前一个节点，
                //这样才可以将多段翻转之间相邻的头尾连接上
                prev = reverseK(prev, k);
            }
            
            return dummy->next;
        }
    
        //before： head ->[ n1 -> n2 ... nk ]-> nk+1
        // =>
        //after：  head ->[ nk -> nk-1 ... n1 ]-> nk+1
        //返回值： return n1
        ListNode* reverseK(ListNode* head, int k) {
            ListNode* nk = head;
            for (int i = 0; i < k; i++) {
                nk = nk->next;
                //对n1到nk节点是否存在进行了检查；
                if (nk == NULL) {
                    return NULL;
                }
                
            }
            
            // reverse，只对n1到nk进行翻转；因为翻转完还需要对n1的next与nk+1进行连接，所以提前保留好这两个节点        
            ListNode* n1 = head->next;
            ListNode* nkplus = nk->next; 
            //在反转操作过程中，pre和cur是两个相邻的指针，共同同向移动，进而实现相邻两个节点的翻转；
            ListNode* prev = NULL;
            ListNode* curt = n1;

            //此时一共操作了k次，使得
            //nk->...n2->n1->null
            //cur指向了nk+1，pre指向了nk;
            while (curt != nkplus) {
                ListNode* temp = curt->next;
                curt->next = prev;
                prev = curt;
                curt = temp;
            }
            
            //最后连接首尾，head->nk...->n2->n1->nk+1;
            head->next = nk;
            n1->next = nkplus;
            return n1;
        }
};

补充:单链表的一般翻转
class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @return: The new head of reversed linked list.
     */
    ListNode *reverse(ListNode *head) {
        //prev表示前继节点
        ListNode *prev = NULL;
        ListNode *curt = head;
        //翻转Len次，pre会走到原链表的尾部，也就是新链表的头部，而curt会走到原链表尾部的next，即NULL;
        while (curt != NULL) {
            //temp记录下一个节点，curt是当前节点
            ListNode *temp = curt->next;
            curt->next = prev;
            prev = head;
            curt = temp;
        }
        return prev;
    }
};
