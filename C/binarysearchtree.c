#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct bst_node {
  int data;
  struct bst_node* left;
  struct bst_node* right;
} BSTNode;

typedef struct binary_search_tree {
  BSTNode* root;
} BinarySearchTree;

/* getter / setter */
void setBSTNodeData(BSTNode* node, int data);
int getBSTNodeData(BSTNode* node);
void setLeftBSTNode(BSTNode* node, BSTNode* left);
BSTNode* getLeftBSTNode(BSTNode* node);
void setRightBSTNode(BSTNode* node, BSTNode* right);
BSTNode* getRightBSTNode(BSTNode* node);
void setBSTRoot(BinarySearchTree* tree, BSTNode* root);
BSTNode* getBSTRoot(BinarySearchTree* tree);

/* node */
BSTNode* createBSTNode(int data);

/* tree */
void initBinarySearchTree(BinarySearchTree* tree);
int isEmptyBinarySearchTree(BinarySearchTree* tree);

/* BST operation */
int insertBST(BinarySearchTree* tree, int data);
int insertBSTFrom(BSTNode* node, int data);
BSTNode* findBSTNode(BinarySearchTree* tree, int data);
BSTNode* findBSTNodeFrom(BSTNode* node, int data);
int removeBST(BinarySearchTree* tree, int data);
BSTNode* removeBSTNode(BSTNode* node, int data);
BSTNode* getMinBSTNode(BSTNode* node);

/* traversal */
void printBSTPreorder(BinarySearchTree* tree);
void printBSTInorder(BinarySearchTree* tree);
void printBSTPostorder(BinarySearchTree* tree);
void printBSTPreorderNode(BSTNode* node);
void printBSTInorderNode(BSTNode* node);
void printBSTPostorderNode(BSTNode* node);

/* information */
size_t getBSTSize(BinarySearchTree* tree);
size_t getBSTLeafCount(BinarySearchTree* tree);
size_t getBSTHeight(BinarySearchTree* tree);
size_t getBSTNodeSize(BSTNode* node);
size_t getBSTLeafNodeCount(BSTNode* node);
size_t getBSTNodeHeight(BSTNode* node);

/* delete */
void clearBinarySearchTree(BinarySearchTree* tree);
void clearBSTNode(BSTNode* node);

signed main(void) {
  BinarySearchTree tree;
  BSTNode* p;

  initBinarySearchTree(&tree);

  /*
              20
            /    \
          10      30
         /  \    /  \
        5   15  25  40
           /
          12
  */

  insertBST(&tree, 20);
  insertBST(&tree, 10);
  insertBST(&tree, 30);
  insertBST(&tree, 5);
  insertBST(&tree, 15);
  insertBST(&tree, 25);
  insertBST(&tree, 40);
  insertBST(&tree, 12);

  printf("Preorder  : ");
  printBSTPreorder(&tree);

  printf("Inorder   : ");
  printBSTInorder(&tree);

  printf("Postorder : ");
  printBSTPostorder(&tree);

  printf("Tree size   : %zu\n", getBSTSize(&tree));
  printf("Leaf count  : %zu\n", getBSTLeafCount(&tree));
  printf("Tree height : %zu\n", getBSTHeight(&tree));

  p = findBSTNode(&tree, 25);
  if (p != NULL) {
    printf("find 25 : %d\n", getBSTNodeData(p));
  }

  p = findBSTNode(&tree, 100);
  if (p == NULL) {
    printf("100 not found\n");
  }

  printf("\n");

  /* 子が0個のノードを削除 */
  printf("remove 5\n");
  removeBST(&tree, 5);
  printf("Inorder : ");
  printBSTInorder(&tree);

  /* 子が1個のノードを削除 */
  printf("remove 15\n");
  removeBST(&tree, 15);
  printf("Inorder : ");
  printBSTInorder(&tree);

  /* 子が2個のノードを削除 */
  printf("remove 30\n");
  removeBST(&tree, 30);
  printf("Inorder : ");
  printBSTInorder(&tree);

  /* rootを削除 */
  printf("remove 20\n");
  removeBST(&tree, 20);
  printf("Inorder : ");
  printBSTInorder(&tree);

  printf("\n");

  printf("Tree size   : %zu\n", getBSTSize(&tree));
  printf("Leaf count  : %zu\n", getBSTLeafCount(&tree));
  printf("Tree height : %zu\n", getBSTHeight(&tree));

  clearBinarySearchTree(&tree);

  printf("\nAfter clear\n");
  printf("Tree size : %zu\n", getBSTSize(&tree));

  return 0;
}

/* getter / setter */
void setBSTNodeData(BSTNode* node, int data) {
  node->data = data;
  return;
}
int getBSTNodeData(BSTNode* node) { return node->data; }
void setLeftBSTNode(BSTNode* node, BSTNode* left) {
  node->left = left;
  return;
}
BSTNode* getLeftBSTNode(BSTNode* node) { return node->left; }
void setRightBSTNode(BSTNode* node, BSTNode* right) {
  node->right = right;
  return;
}
BSTNode* getRightBSTNode(BSTNode* node) { return node->right; }
void setBSTRoot(BinarySearchTree* tree, BSTNode* root) {
  tree->root = root;
  return;
}
BSTNode* getBSTRoot(BinarySearchTree* tree) { return tree->root; }
/* node */
BSTNode* createBSTNode(int data) {
  BSTNode* p;
  if ((p = (BSTNode*)malloc(sizeof(BSTNode))) != NULL) {
    setBSTNodeData(p, data);
    setLeftBSTNode(p, NULL);
    setRightBSTNode(p, NULL);
  }
  return p;
}
/* tree */
void initBinarySearchTree(BinarySearchTree* tree) {
  setBSTRoot(tree, NULL);
  return;
}
int isEmptyBinarySearchTree(BinarySearchTree* tree) {
  if (getBSTRoot(tree) == NULL) {
    return 1;
  } else {
    return 0;
  }
}
/* traversal */
void printBSTPreorder(BinarySearchTree* tree) {
  printBSTPreorderNode(getBSTRoot(tree));
  printf("\n");
  return;
}
void printBSTInorder(BinarySearchTree* tree) {
  printBSTInorderNode(getBSTRoot(tree));
  printf("\n");
  return;
}
void printBSTPostorder(BinarySearchTree* tree) {
  printBSTPostorderNode(getBSTRoot(tree));
  printf("\n");
  return;
}
void printBSTPreorderNode(BSTNode* node) {
  if (node == NULL) {
    return;
  }
  printf("%d ", getBSTNodeData(node));
  printBSTPreorderNode(getLeftBSTNode(node));
  printBSTPreorderNode(getRightBSTNode(node));
}
void printBSTInorderNode(BSTNode* node) {
  if (node == NULL) {
    return;
  }
  printBSTInorderNode(getLeftBSTNode(node));
  printf("%d ", getBSTNodeData(node));
  printBSTInorderNode(getRightBSTNode(node));
}
void printBSTPostorderNode(BSTNode* node) {
  if (node == NULL) {
    return;
  }
  printBSTPostorderNode(getLeftBSTNode(node));
  printBSTPostorderNode(getRightBSTNode(node));
  printf("%d ", getBSTNodeData(node));
}
/* information */
size_t getBSTSize(BinarySearchTree* tree) {
  BSTNode* p;
  p = getBSTRoot(tree);
  return getBSTNodeSize(p);
}
size_t getBSTLeafCount(BinarySearchTree* tree) {
  BSTNode* p;
  p = getBSTRoot(tree);
  return getBSTLeafNodeCount(p);
}
size_t getBSTHeight(BinarySearchTree* tree) {
  BSTNode* p;
  p = getBSTRoot(tree);
  return getBSTNodeHeight(p);
}
size_t getBSTNodeSize(BSTNode* node) {
  if (node == NULL) {
    return 0;
  }
  return getBSTNodeSize(getLeftBSTNode(node)) +
         getBSTNodeSize(getRightBSTNode(node)) + 1;
}
size_t getBSTLeafNodeCount(BSTNode* node) {
  if (node == NULL) {
    return 0;
  }
  if (getLeftBSTNode(node) == NULL && getRightBSTNode(node) == NULL) {
    return 1;
  }
  return getBSTLeafNodeCount(getLeftBSTNode(node)) +
         getBSTLeafNodeCount(getRightBSTNode(node));
}
size_t getBSTNodeHeight(BSTNode* node) {
  size_t leftHeight, rightHeight;
  if (node == NULL) {
    return 0;
  }
  leftHeight = getBSTNodeHeight(getLeftBSTNode(node));
  rightHeight = getBSTNodeHeight(getRightBSTNode(node));
  return max(leftHeight, rightHeight) + 1;
}
/* delete */
void clearBinarySearchTree(BinarySearchTree* tree) {
  BSTNode* p;
  p = getBSTRoot(tree);
  clearBSTNode(p);
  setBSTRoot(tree, NULL);
  return;
}
void clearBSTNode(BSTNode* node) {
  BSTNode *left, *right;
  if (node == NULL) {
    return;
  }
  left = getLeftBSTNode(node);
  right = getRightBSTNode(node);
  clearBSTNode(left);
  clearBSTNode(right);
  free(node);
  return;
}

/* BST operation */
int insertBST(BinarySearchTree* tree, int data) {
  if (isEmptyBinarySearchTree(tree)) {
    BSTNode* p;
    if ((p = createBSTNode(data)) != NULL) {
      setBSTRoot(tree, p);
      return 1;
    } else {
      return 0;
    }
  } else {
    BSTNode* p = getBSTRoot(tree);
    return insertBSTFrom(p, data);
  }
}
int insertBSTFrom(BSTNode* node, int data) {
  BSTNode *p, *cp;
  if (getBSTNodeData(node) > data) {
    p = getLeftBSTNode(node);
    if (p == NULL) {
      cp = createBSTNode(data);
      if (cp != NULL) {
        setLeftBSTNode(node, cp);
        return 1;
      } else {
        return 0;
      }
    } else {
      return insertBSTFrom(p, data);
    }

  } else if (getBSTNodeData(node) < data) {
    p = getRightBSTNode(node);
    if (p == NULL) {
      cp = createBSTNode(data);
      if (cp != NULL) {
        setRightBSTNode(node, cp);
        return 1;
      } else {
        return 0;
      }
    } else {
      return insertBSTFrom(p, data);
    }
  }
  return 0;
}
BSTNode* findBSTNode(BinarySearchTree* tree, int data) {
  BSTNode* p;
  p = getBSTRoot(tree);
  return findBSTNodeFrom(p, data);
}
BSTNode* findBSTNodeFrom(BSTNode* node, int data) {
  if (node != NULL) {
    if (getBSTNodeData(node) < data) {
      return findBSTNodeFrom(getRightBSTNode(node), data);
    } else if (getBSTNodeData(node) > data) {
      return findBSTNodeFrom(getLeftBSTNode(node), data);
    } else {
      return node;
    }
  } else {
    return NULL;
  }
}
int removeBST(BinarySearchTree* tree, int data) {
  BSTNode* p;

  if (findBSTNode(tree, data) == NULL) {
    return 0;
  }

  p = removeBSTNode(getBSTRoot(tree), data);
  setBSTRoot(tree, p);

  return 1;
}

BSTNode* removeBSTNode(BSTNode* node, int data) {
  BSTNode *p, *left, *right;

  if (node == NULL) {
    return NULL;
  }

  if (getBSTNodeData(node) > data) {
    p = removeBSTNode(getLeftBSTNode(node), data);
    setLeftBSTNode(node, p);
    return node;

  } else if (getBSTNodeData(node) < data) {
    p = removeBSTNode(getRightBSTNode(node), data);
    setRightBSTNode(node, p);
    return node;
  }

  left = getLeftBSTNode(node);
  right = getRightBSTNode(node);

  if (left == NULL && right == NULL) {
    free(node);
    return NULL;
  }

  if (left == NULL) {
    free(node);
    return right;
  }

  if (right == NULL) {
    free(node);
    return left;
  }

  p = getMinBSTNode(right);
  setBSTNodeData(node, getBSTNodeData(p));

  right = removeBSTNode(right, getBSTNodeData(p));
  setRightBSTNode(node, right);

  return node;
}

BSTNode* getMinBSTNode(BSTNode* node) {
  if (node == NULL) {
    return NULL;
  }

  if (getLeftBSTNode(node) == NULL) {
    return node;
  }

  return getMinBSTNode(getLeftBSTNode(node));
}