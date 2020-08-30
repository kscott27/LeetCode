/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
  TreeNode* invertTree(TreeNode* root) {
    recurse(root);
    return root;
  }
private:
  void recurse(TreeNode* node) {
    if( node == NULL )
      return;
    
    recurse(node->left);
    recurse(node->right);
    swap(node->left, node->right);
  }
};