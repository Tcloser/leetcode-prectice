#include <iostream>
#include <algorithm>
#include "treeNode.h"

using namespace std;
/* -------------------------------------------
 * 二叉树部分
 * 递归深度 类型 与 112类似 考虑用vector保存
 * ------------------------------------------*/

typedef treeNode_2 TreeNode;
/* -------------------------------------------
 *    0
 *   / \
 *  1  10
 *  /\
 * 3  4
 *     \
 *      9
 * ------------------------------------------*/
TreeNode* initTree(TreeNode* &root)
{
    root->left = new TreeNode;
    root->right= new TreeNode;
    // 此时左右节点已经创建 下一步就是赋值
    root->left->val = 1;
    root->right->val = 10;

    root->left->left= new TreeNode;
    root->left->right= new TreeNode;

    root->left->left->val = 3;
    root->left->right->val = 4;

    root->left->right->right= new TreeNode;
    root->left->right->right->val = 9;
    return root;
}

/* -------------------------------------------
 * 递归 重点是寻找下一个前序遍历节点 并进行链表的链接
 * ------------------------------------------*/
void addTovector(TreeNode* &root,vector<int>&result)
{
    if(root)
    {
        addTovector(root->left,result);
        addTovector(root->right,result);
        result.push_back(root->val);
    }

        return ;
}

void flation(TreeNode* &root)
{
    if(!root) return ;

    vector<int> result;

    addTovector(root,result);

}

int main()
{
    auto *root = new TreeNode;
    initTree(root);

    flation(root);

    return 0;
}