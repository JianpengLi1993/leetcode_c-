/********************************************************/
返回与给定的前序和后序遍历匹配的任何二叉树。

 pre 和 post 遍历中的值是不同的正整数。

示例：

输入：pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
输出：[1,2,3,4,5,6,7]

提示：
	1 <= pre.length == post.length <= 30
	pre[] 和 post[] 都是 1, 2, ..., pre.length 的排列
	每个输入保证至少有一个答案。如果有多个答案，可以返回其中一个。
/********************************************************/



/**
只有每个节点度为2或者0的时候前序和后序才能唯一确定一颗二叉树，只有一个子节点是无法确定的，因为你无法判断他是左子树还是右子树。
因此我们设定了递归出口条件，确保此时输出的为唯一确定的带有左节点的二叉树。

问题核心对前序序列和后序序列划分区间段：根、左子树区间、右子树区间

思路：
前序遍历为：
(根结点) (前序遍历左分支) (前序遍历右分支)

而后序遍历为：
(后序遍历左分支) (后序遍历右分支) (根结点)

例如，如果最终的二叉树可以被序列化的表述为 [1, 2, 3, 4, 5, 6, 7]，那么其前序遍历为 [1] + [2, 4, 5] + [3, 6, 7]，
而后序遍历为 [4, 5, 2] + [6, 7, 3] + [1].
如果我们知道左分支有多少个结点，我们就可以对这些数组进行分组，并用递归生成树的每个分支。

算法
我们令左分支有 L个节点。我们知道左分支的头节点为 pre[1]，但它也出现在左分支的后序表示的最后。
所以 pre[1] = post[L-1]（因为结点的值具有唯一性），因此 L = post.indexOf(pre[1]) + 1。
现在在我们的递归步骤中，左分支由 pre[1 : L+1] 和 post[0 : L] 重新分支，而右分支将由 pre[L+1 : N] 和 post[L : N-1] 重新分支。

 */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        TreeNode* root = search(pre, 0, pre.size() - 1, post, 0, post.size() - 1);
        return root;
    }
    //递归返回值：以前序子序列和后序子序列构造的一个子树的根。
    TreeNode* search(vector<int>& pre, int preStart, int preEnd, vector<int>& post, int postStart, int postEnd) {
        if(preStart > preEnd || postStart > postEnd) {  
        //递归终止条件,这里对应着当这一层的前序序列或者后序序列已经无法再分为三段了，即只有两个元素时，无法确定第二个元素是左子树还是右子树
        //此时上一层调用时的preStart会大于preEnd, postStart也会大于postEnd；此时无法构造树，返回NULL.其实这也是为什么前序+后序无法直接确定一棵二叉树，
       
            return NULL;
        }
        int rootVal = pre[preStart];
        TreeNode* root = new TreeNode(rootVal);
        for(int i = postStart; i < postEnd; ++i) {  //这里由于postEnd已经是root了，所以此处查找的时候不能再包含
            if(post[i] == pre[preStart + 1]) {  //这里由于是后序+前序 所以这里要找到的左子树的根节点
                root->left = search(pre, preStart + 1, preStart + i - postStart + 1, post, postStart, i);
         //当输入只有两个元素时，即不满足唯一确定一棵二叉树时，输出一种情况即可，这时上一条语句可以执行，输出带有左子树的二叉树，而下面这条语句会触发递归终止出口，返回NULL,最终返回的二叉树有左节点无右节点。
                root->right = search(pre, preStart + i - postStart + 2, preEnd, post, i + 1, postEnd - 1);
                break;
            }
        }
        return root;
    }
};
