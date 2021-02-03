#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tree
{
    int data;
    struct Tree *left;
    struct Tree *right;
} tree;

tree *createNode(int);
tree *buildTree(tree *, int);
tree *binarySearch(tree *, int, tree *);
void preorderTraversal(tree *);
void inorderTraversal(tree *);
void postorderTraversal(tree *);
void deleteTree(tree *);

int main()
{
    tree *root = NULL;

    root = buildTree(root, 40);
    root = buildTree(root, 20);
    root = buildTree(root, 10);
    root = buildTree(root, 45);
    root = buildTree(root, 60);
    root = buildTree(root, 50);
    root = buildTree(root, 12);
    root = buildTree(root, 95);
    root = buildTree(root, 74);
    root = buildTree(root, 41);
    root = buildTree(root, 35);
    root = buildTree(root, 27);

    printf("Preorder traversal\n");
    preorderTraversal(root);
    printf("\n");
    printf("Inorder traversal\n");
    inorderTraversal(root);
    printf("\n");
    printf("Postorder traversal\n");
    postorderTraversal(root);
    printf("\n");

    tree ans;

    root = binarySearch(root, 41, &ans);

    printf("%d", ans.data);

    deleteTree(root);
    return 0;
}

tree *createNode(int data)
{
    tree *p = (tree *)malloc(sizeof(tree));
    if (p == NULL)
    {
        fprintf(stderr, "createNode, malloc error. Line: %d", __LINE__);
        exit(EXIT_FAILURE);
    }
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

tree *buildTree(tree *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data > root->data)
    {
        root->right = buildTree(root->right, data);
    }
    else if (data < root->data)
    {
        root->left = buildTree(root->left, data);
    }

    return root;
}

tree *binarySearch(tree *root, int data, tree *ans)
{
    if (root == NULL)
    {
        ans = NULL;
        return NULL;
    }
    if (data > root->data)
    {
        root->right = binarySearch(root->right, data, ans);
    }
    else if (data < root->data)
    {
        root->left = binarySearch(root->left, data, ans);
    }
    if (data == root->data)
    {
        *ans = *root;
    }
    return root;
}

void preorderTraversal(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    preorderTraversal(root->left);
    printf("%d ", root->data);
    preorderTraversal(root->right);
}

void postorderTraversal(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    printf("%d ", root->data);
}

void deleteTree(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    root = NULL;
}