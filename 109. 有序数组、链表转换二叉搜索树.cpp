
将有序数组转化为二叉搜索树：
重点在于找到根结点，进而划分左右子树继续递归；
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return bst(nums,0,nums.size()-1);
    }
    TreeNode* bst(vector<int>& a,int l,int r){
        //start和end的出口确定，是大于等于、还是大于，要看具体问题，=对应了只剩下一个节点的情况，>对应是空节点的情况
        //对于本题，一个节点仍然要继续递归，构建root和两个null子树的情况，所以只能>;
        //而在归并排序算法中，只剩一个节点和空节点都不用继续递归了，直接返回，并开始调用merg()函数将这个单一节点（或空节点）和另一半序列合并就行
        if(l>r) return NULL;
        int mid=(r-l)/2+l;
        TreeNode* root=new TreeNode(a[mid]);
        root->left=bst(a,l,mid-1);
        root->right=bst(a,mid+1,r);
        return root;
    }
};

//将有序链表转为二叉搜索树：

class Solution {

  public:
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
        cout<<slow->val<<endl;
        return slow;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        //3.1 此时对应节点为空，说明该子树不存在，返回空，是第一个出口；
        if (head == nullptr) {
            return nullptr;
        }
        //3.2 这个判断很重要，若mid与head相等时，说明只有一个节点，是第二个出口；
        if(head->next == nullptr){
            return new TreeNode(head->val);
        }
        //其余情况，即链表节点个数至少两个；
        ListNode*mid = findMidOfList(head);
        TreeNode* root = new TreeNode(mid->val);
        
        //2分治，
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(mid->next);
        return root;
  }
};

//不拆分链表，直接通过类似于index来划分子链表；
class Solution1 {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return buildTree(head, nullptr);
    }
    TreeNode * buildTree(ListNode* head, ListNode * tail){
        if(head == tail) return nullptr;
        ListNode* slow = head, *fast = head;
        while(fast != tail && fast->next != tail){
            slow = slow->next;
            fast = fast->next->next;
        }
        cout<<slow->val<<endl;
        TreeNode * root = new TreeNode(slow->val);
        root->left = buildTree(head, slow);
        root->right = buildTree(slow->next, tail);
        return root;
    }
};
