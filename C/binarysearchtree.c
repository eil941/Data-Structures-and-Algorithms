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

void printBSTTree(BinarySearchTree* tree);
size_t getBSTMaxDataWidth(BSTNode* node);
size_t drawBSTTreeNode(BSTNode* node, size_t depth, size_t* index,
                       size_t cellWidth, char* canvas, size_t lineWidth);

int main(void) {
  BinarySearchTree tree;
  BSTNode* p;
  int select;
  int data;

  initBinarySearchTree(&tree);

  while (1) {
    printf("\n");
    printf("0 : insert\n");
    printf("1 : remove\n");
    printf("2 : find\n");
    printf("3 : tree\n");
    printf("4 : preorder\n");
    printf("5 : inorder\n");
    printf("6 : postorder\n");
    printf("7 : size\n");
    printf("8 : leaf count\n");
    printf("9 : height\n");
    printf("10: clear\n");
    printf("11: exit\n");
    printf("> ");

    scanf("%d", &select);

    switch (select) {
      case 0:
        printf("data: ");
        scanf("%d", &data);

        if (insertBST(&tree, data)) {
          printf("inserted\n");
        } else {
          printf("insert failed\n");
        }
        break;

      case 1:
        printf("data: ");
        scanf("%d", &data);

        if (removeBST(&tree, data)) {
          printf("removed\n");
        } else {
          printf("not found\n");
        }
        break;

      case 2:
        printf("data: ");
        scanf("%d", &data);

        p = findBSTNode(&tree, data);

        if (p != NULL) {
          printf("found: %d\n", getBSTNodeData(p));
        } else {
          printf("not found\n");
        }
        break;

      case 3:
        printBSTTree(&tree);
        break;

      case 4:
        printf("Preorder  : ");
        printBSTPreorder(&tree);
        break;

      case 5:
        printf("Inorder   : ");
        printBSTInorder(&tree);
        break;

      case 6:
        printf("Postorder : ");
        printBSTPostorder(&tree);
        break;

      case 7:
        printf("Tree size: %zu\n", getBSTSize(&tree));
        break;

      case 8:
        printf("Leaf count: %zu\n", getBSTLeafCount(&tree));
        break;

      case 9:
        printf("Tree height: %zu\n", getBSTHeight(&tree));
        break;

      case 10:
        clearBinarySearchTree(&tree);
        printf("cleared\n");
        break;

      case 11:
        clearBinarySearchTree(&tree);
        return 0;

      default:
        printf("invalid input\n");
        break;
    }
  }
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

void printBSTTree(BinarySearchTree* tree) {
  BSTNode* root;
  size_t size, height, maxDataWidth;
  size_t cellWidth, lineWidth, rows;
  size_t index = 0;
  char* canvas;

  root = getBSTRoot(tree);

  if (root == NULL) {
    printf("(empty)\n");
    return;
  }

  size = getBSTSize(tree);
  height = getBSTHeight(tree);
  maxDataWidth = getBSTMaxDataWidth(root);

  cellWidth = maxDataWidth + 3;
  lineWidth = size * cellWidth;
  rows = height * 2 - 1;

  canvas = (char*)malloc(rows * (lineWidth + 1));
  if (canvas == NULL) {
    return;
  }

  for (size_t row = 0; row < rows; row++) {
    for (size_t col = 0; col < lineWidth; col++) {
      canvas[row * (lineWidth + 1) + col] = ' ';
    }
    canvas[row * (lineWidth + 1) + lineWidth] = '\0';
  }

  drawBSTTreeNode(root, 0, &index, cellWidth, canvas, lineWidth);

  for (size_t row = 0; row < rows; row++) {
    char* line = &canvas[row * (lineWidth + 1)];
    size_t end = lineWidth;

    while (end > 0 && line[end - 1] == ' ') {
      end--;
    }

    line[end] = '\0';
    printf("%s\n", line);
  }

  free(canvas);
}

size_t getBSTMaxDataWidth(BSTNode* node) {
  char buffer[32];
  size_t current, left, right;

  if (node == NULL) {
    return 0;
  }

  current =
      (size_t)snprintf(buffer, sizeof(buffer), "%d", getBSTNodeData(node));

  left = getBSTMaxDataWidth(getLeftBSTNode(node));
  right = getBSTMaxDataWidth(getRightBSTNode(node));

  return max(current, max(left, right));
}

size_t drawBSTTreeNode(BSTNode* node, size_t depth, size_t* index,
                       size_t cellWidth, char* canvas, size_t lineWidth) {
  BSTNode *left, *right;
  size_t leftX = 0;
  size_t rightX = 0;
  size_t x;
  size_t row;
  char buffer[32];
  int length;

  left = getLeftBSTNode(node);
  right = getRightBSTNode(node);

  if (left != NULL) {
    leftX =
        drawBSTTreeNode(left, depth + 1, index, cellWidth, canvas, lineWidth);
  }

  x = (*index) * cellWidth + cellWidth / 2;
  (*index)++;

  if (right != NULL) {
    rightX =
        drawBSTTreeNode(right, depth + 1, index, cellWidth, canvas, lineWidth);
  }

  row = depth * 2;

  length = snprintf(buffer, sizeof(buffer), "%d", getBSTNodeData(node));

  for (int i = 0; i < length; i++) {
    canvas[row * (lineWidth + 1) + x - (size_t)length / 2 + (size_t)i] =
        buffer[i];
  }

  if (left != NULL) {
    canvas[(row + 1) * (lineWidth + 1) + (x + leftX) / 2] = '/';
  }

  if (right != NULL) {
    canvas[(row + 1) * (lineWidth + 1) + (x + rightX) / 2] = '\\';
  }

  return x;
}