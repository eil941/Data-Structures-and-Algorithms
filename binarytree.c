#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef struct tree_node {
  int data;
  struct tree_node* left;
  struct tree_node* right;
} TreeNode;

typedef struct binary_tree {
  TreeNode* root;
} BinaryTree;

/* getter / setter */
void setTreeNodeData(TreeNode* node, int data);
int getTreeNodeData(TreeNode* node);

void setLeftTreeNode(TreeNode* node, TreeNode* left);
TreeNode* getLeftTreeNode(TreeNode* node);

void setRightTreeNode(TreeNode* node, TreeNode* right);
TreeNode* getRightTreeNode(TreeNode* node);

void setTreeRoot(BinaryTree* tree, TreeNode* root);
TreeNode* getTreeRoot(BinaryTree* tree);

/* node */
TreeNode* createTreeNode(int data);

/* tree */
void initBinaryTree(BinaryTree* tree);
int isEmptyBinaryTree(BinaryTree* tree);

int insertRoot(BinaryTree* tree, int data);
int insertLeft(TreeNode* parent, int data);
int insertRight(TreeNode* parent, int data);

/* traversal */
void printPreorder(BinaryTree* tree);
void printInorder(BinaryTree* tree);
void printPostorder(BinaryTree* tree);

void printPreorderNode(TreeNode* node);
void printInorderNode(TreeNode* node);
void printPostorderNode(TreeNode* node);

/* information */
size_t getTreeSize(BinaryTree* tree);
size_t getLeafCount(BinaryTree* tree);
size_t getTreeHeight(BinaryTree* tree);
TreeNode* findTreeNode(BinaryTree* tree, int data);

size_t getTreeNodeSize(TreeNode* node);
size_t getLeafNodeCount(TreeNode* node);
size_t getTreeNodeHeight(TreeNode* node);
TreeNode* findTreeNodeFrom(TreeNode* node, int data);

/* delete */
void clearBinaryTree(BinaryTree* tree);
void clearTreeNode(TreeNode* node);

int main(void) {
  BinaryTree tree;
  TreeNode* p;

  initBinaryTree(&tree);

  /*
          10
         /  \
       20    30
      / \    /
     40 50  60
  */

  p = createTreeNode(10);
  setTreeRoot(&tree, p);

  insertLeft(p, 20);
  insertRight(p, 30);

  p = findTreeNode(&tree, 20);
  insertLeft(p, 40);
  insertRight(p, 50);

  p = findTreeNode(&tree, 30);
  insertLeft(p, 60);

  printf("Preorder  : ");
  printPreorder(&tree);

  printf("Inorder   : ");
  printInorder(&tree);

  printf("Postorder : ");
  printPostorder(&tree);

  printf("Tree size   : %zu\n", getTreeSize(&tree));
  printf("Leaf count  : %zu\n", getLeafCount(&tree));
  printf("Tree height : %zu\n", getTreeHeight(&tree));

  p = findTreeNode(&tree, 50);
  if (p != NULL) {
    printf("find 50 : %d\n", getTreeNodeData(p));
  }

  p = findTreeNode(&tree, 100);
  if (p == NULL) {
    printf("100 not found\n");
  }

  clearBinaryTree(&tree);

  printf("After clear\n");
  printf("Tree size : %zu\n", getTreeSize(&tree));

  return 0;
}

void setTreeNodeData(TreeNode* node, int data) {
  node->data = data;
  return;
}
int getTreeNodeData(TreeNode* node) { return node->data; }
void setLeftTreeNode(TreeNode* node, TreeNode* left) {
  node->left = left;
  return;
}
TreeNode* getLeftTreeNode(TreeNode* node) { return node->left; }
void setRightTreeNode(TreeNode* node, TreeNode* right) {
  node->right = right;
  return;
}
TreeNode* getRightTreeNode(TreeNode* node) { return node->right; }
void setTreeRoot(BinaryTree* tree, TreeNode* root) {
  tree->root = root;
  return;
}
TreeNode* getTreeRoot(BinaryTree* tree) { return tree->root; }

TreeNode* createTreeNode(int data) {
  TreeNode* p;
  if ((p = (TreeNode*)malloc(sizeof(TreeNode))) != NULL) {
    setTreeNodeData(p, data);
    setLeftTreeNode(p, NULL);
    setRightTreeNode(p, NULL);
  }
  return p;
}

void initBinaryTree(BinaryTree* tree) {
  setTreeRoot(tree, NULL);
  return;
}
int isEmptyBinaryTree(BinaryTree* tree) {
  if (getTreeRoot(tree) == NULL) {
    return 1;
  } else {
    return 0;
  }
}
int insertLeft(TreeNode* parent, int data) {
  TreeNode* p;
  if (getLeftTreeNode(parent) != NULL) {
    return 0;
  } else {
    if ((p = createTreeNode(data)) != NULL) {
      setLeftTreeNode(parent, p);
      return 1;
    } else {
      return 0;
    }
  }
}
int insertRight(TreeNode* parent, int data) {
  TreeNode* p;
  if (getRightTreeNode(parent) != NULL) {
    return 0;
  } else {
    if ((p = createTreeNode(data)) != NULL) {
      setRightTreeNode(parent, p);
      return 1;
    } else {
      return 0;
    }
  }
}
void printPreorder(BinaryTree* tree) {
  printPreorderNode(getTreeRoot(tree));
  printf("\n");
  return;
}
void printInorder(BinaryTree* tree) {
  printInorderNode(getTreeRoot(tree));
  printf("\n");
  return;
}
void printPostorder(BinaryTree* tree) {
  printPostorderNode(getTreeRoot(tree));
  printf("\n");
  return;
}

void printPreorderNode(TreeNode* node) {
  if (node == NULL) {
    return;
  }

  printf("%d ", getTreeNodeData(node));
  printPreorderNode(getLeftTreeNode(node));
  printPreorderNode(getRightTreeNode(node));
}
void printInorderNode(TreeNode* node) {
  if (node == NULL) {
    return;
  }

  printInorderNode(getLeftTreeNode(node));
  printf("%d ", getTreeNodeData(node));
  printInorderNode(getRightTreeNode(node));
}
void printPostorderNode(TreeNode* node) {
  if (node == NULL) {
    return;
  }

  printPostorderNode(getLeftTreeNode(node));
  printPostorderNode(getRightTreeNode(node));
  printf("%d ", getTreeNodeData(node));
}

size_t getTreeSize(BinaryTree* tree) {
  TreeNode* p;
  p = getTreeRoot(tree);
  return getTreeNodeSize(p);
}
size_t getLeafCount(BinaryTree* tree) {
  TreeNode* p;
  p = getTreeRoot(tree);
  return getLeafNodeCount(p);
}
size_t getTreeHeight(BinaryTree* tree) {
  TreeNode* p;
  p = getTreeRoot(tree);
  return getTreeNodeHeight(p);
}
TreeNode* findTreeNode(BinaryTree* tree, int data) {
  TreeNode* p;
  p = getTreeRoot(tree);
  return findTreeNodeFrom(p, data);
}

size_t getTreeNodeSize(TreeNode* node) {
  if (node == NULL) {
    return 0;
  }
  return getTreeNodeSize(getLeftTreeNode(node)) +
         getTreeNodeSize(getRightTreeNode(node)) + 1;
}
size_t getLeafNodeCount(TreeNode* node) {
  if (node == NULL) {
    return 0;
  }
  if (getLeftTreeNode(node) == NULL && getRightTreeNode(node) == NULL) {
    return 1;
  }
  return getLeafNodeCount(getLeftTreeNode(node)) +
         getLeafNodeCount(getRightTreeNode(node));
}
size_t getTreeNodeHeight(TreeNode* node) {
  if (node == NULL) {
    return 0;
  }
  return max(getTreeNodeHeight(getLeftTreeNode(node)),
             getTreeNodeHeight(getRightTreeNode(node))) +
         1;
}
TreeNode* findTreeNodeFrom(TreeNode* node, int data) {
  if (node == NULL) {
    return NULL;
  }
  if (getTreeNodeData(node) == data) {
    return node;
  }
  TreeNode *left, *right;
  left = findTreeNodeFrom(getLeftTreeNode(node), data);
  if (left != NULL) {
    return left;
  }
  right = findTreeNodeFrom(getRightTreeNode(node), data);
  if (right != NULL) {
    return right;
  }
  return NULL;
}

void clearBinaryTree(BinaryTree* tree) {
  TreeNode* p;
  p = getTreeRoot(tree);
  clearTreeNode(p);
  setTreeRoot(tree, NULL);
  return;
}
void clearTreeNode(TreeNode* node) {
  TreeNode *left, *right;
  if (node == NULL) {
    return;
  }
  left = getLeftTreeNode(node);
  right = getRightTreeNode(node);
  clearTreeNode(left);
  clearTreeNode(right);
  free(node);
  return;
}