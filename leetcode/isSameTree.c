/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    // se os dois caras são NULOS, são iguais
    if (p == NULL && q == NULL) return true;
    // se só um é nulo, são diferentes
    if (p == NULL || q == NULL) return false;
    // se o VALOR do nó é diferente, são diferentes
    if (p->val != q->val) return false;

    // se passou por tudo aquilo e continou, precisamos avaliar os filhos
    bool leftIsSame = isSameTree(p->left, q->left);
    bool rightIsSame = isSameTree(p->right, q->right);

    // se os filhos são iguais, ele é igual
    if (leftIsSame&& rightIsSame) return true;
    return false;
}