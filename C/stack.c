#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_cell {
  int data;
  struct stack_cell* next;
} StackCell;

typedef struct stack {
  StackCell* top = NULL;
} Stack;

void setStackCellData(StackCell* cell, int data);
int getStackCellData(StackCell* cell);
void setNextStackCell(StackCell* cell, StackCell* next);
StackCell* getNextStackCell(StackCell* cell);
void setStackTop(Stack* stack, StackCell* top);
StackCell* getStackTop(Stack* stack);

StackCell* createStackCell(int data, Stack* top);

void initStack(Stack* stack);
int isEmptyStack(Stack* stack);
int push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
size_t getStackSize(Stack* stack);
void clearStack(Stack* stack);
void printStack(Stack* stack);

signed main() {
  Stack s;
  int n, a;

  initStack(&s);

  while (1) {
    printf("\n");
    printf("0: push\n");
    printf("1: pop\n");
    printf("2: top\n");
    printf("3: 空か確認\n");
    printf("4: サイズ取得\n");
    printf("5: 全削除\n");
    printf("6: 終了\n");
    printf("選択: ");

    scanf("%d", &n);

    if (n == 0) {
      printf("値: ");
      scanf("%d", &a);

      if (!push(&s, a)) {
        printf("push失敗\n");
      }

    } else if (n == 1) {
      if (!pop(&s)) {
        printf("Stackは空です\n");
      }

    } else if (n == 2) {
      if (isEmptyStack(&s)) {
        printf("Stackは空です\n");
      } else {
        printf("top: %d\n", peek(&s));
      }

    } else if (n == 3) {
      if (isEmptyStack(&s)) {
        printf("Stackは空です\n");
      } else {
        printf("Stackは空ではありません\n");
      }

    } else if (n == 4) {
      printf("size: %zu\n", getStackSize(&s));

    } else if (n == 5) {
      clearStack(&s);

    } else if (n == 6) {
      clearStack(&s);
      break;

    } else {
      printf("無効な入力です\n");
    }

    printf("Stack: ");
    printStack(&s);
  }

  return 0;
}

void setStackCellData(StackCell* cell, int data) {
  cell->data = data;
  return;
}
int getStackCellData(StackCell* cell) { return cell->data; }
void setNextStackCell(StackCell* cell, StackCell* next) {
  cell->next = next;
  return;
}
StackCell* getNextStackCell(StackCell* cell) { return cell->next; }
void setStackTop(Stack* stack, StackCell* top) {
  stack->top = top;
  return;
}
StackCell* getStackTop(Stack* stack) { return stack->top; }

void initStack(Stack* stack) {
  setStackTop(stack, NULL);
  return;
}
int isEmptyStack(Stack* stack) {
  if (getStackTop(stack) == NULL) {
    return 1;
  } else {
    return 0;
  }
}
int push(Stack* stack, int data) {
  StackCell* p;
  if ((p = createStackCell(data, stack)) == NULL) {
    return 0;
  } else {
    setStackTop(stack, p);
    return 1;
  }
}
int pop(Stack* stack) {
  StackCell* p;
  if (isEmptyStack(stack)) {
    return 0;
  }
  p = getNextStackCell(getStackTop(stack));
  free(getStackTop(stack));
  setStackTop(stack, p);
  return 1;
}

StackCell* createStackCell(int data, Stack* top) {
  StackCell* p;
  if ((p = (StackCell*)malloc(sizeof(StackCell))) != NULL) {
    setStackCellData(p, data);
    setNextStackCell(p, getStackTop(top));
    return p;
  } else {
    return NULL;
  }
}

int peek(Stack* stack) { return getStackCellData(getStackTop(stack)); }
size_t getStackSize(Stack* stack) {
  int count = 0;
  StackCell* p = getStackTop(stack);
  while (p != NULL) {
    p = getNextStackCell(p);
    count++;
  }
  return count;
}
void clearStack(Stack* stack) {
  while (!isEmptyStack(stack)) {
    pop(stack);
  }
  return;
}
void printStack(Stack* stack) {
  StackCell* p = getStackTop(stack);

  while (p != NULL) {
    printf("%d", getStackCellData(p));
    p = getNextStackCell(p);

    if (p != NULL) {
      printf(" -> ");
    }
  }

  printf("\n");
  return;
}