/*
给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
要求返回这个链表的 深拷贝。 
我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

	val：一个表示 Node.val 的整数。
	random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
//此法和之前的clone graph一样，都是利用hashmap;
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return NULL;
        }
        unordered_map<Node*, Node*>map;
        //dummy指针的作用是确保链表结构发生修改后，能够准确找到修改后的链表
        Node dummy(-1);
        //基友双指针：pre和curt,两者始终距离不超过1，确保将curt所指的节点链接在pre所指节点的后面；
        Node*pre = &dummy;
        Node* newNode;
        while (head != NULL) {
            //下面这一段if处理，head始终指向旧链表，newNode始终指向新链表，随着while循环，newNode不断创建新节点，并连接到pre所指的节点后面；
            //而为了提高遍历过程的效率，在建立新链表的同时还要将就链表的random指针关系也随之更新到新链表节点上（依靠下面的第二个if处理段落）
            if (map.find(head) != map.end()) {
                //这里是因为random 建立的过程中，已经建立了若干新节点了，这里只需链接上就行，不需要重新建立；
                newNode = map[head];
            } else {
                newNode = new Node(head->val);
                map.insert(make_pair(head, newNode));
            }
            pre->next = newNode;

            if (head->random != NULL) {
                if (map.find(head->random) != map.end()) {
                    newNode->random = map[head->random];
                } else {
                    //建立newNode的random节点，但此时newNode还未真正指向这个节点，所以只是把它放到map中；
                    newNode->random = new Node(head->random->val);
                    map.insert(make_pair(head->random, newNode->random));
                }
            }

            pre = newNode;
            head = head->next;
        }

        return dummy.next;
    }
};


