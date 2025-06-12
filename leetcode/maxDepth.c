int findMaxDepth(struct TreeNode* root, int d){
    if (root == NULL) return d - 1;
    int left = findMaxDepth(root->left, d+1);
    int right = findMaxDepth(root->right, d+1);

    return left > right ? left : right;
}

int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    return findMaxDepth(root, 1);
}