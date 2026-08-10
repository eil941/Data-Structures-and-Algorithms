#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
  int data;
  struct cell* next;
} List;
typedef List Cell;

List* getEmptyList(void);
Cell* createCell(int data, List* next);
void setCellData(Cell* cell, int data);
int getCellData(Cell* cell);
void setNextCell(Cell* cell, List* next);
List* getNextCell(Cell* next);
int isEmptyList(List* head);
int insertHead(List** head, int data);
int removeHead(List** head);
void printList(List* head);

Cell** getNextCellPointer(Cell* cell);
int insertTail(List** head, int data);
int removeTail(List** head);
int insertIndex(List** head, size_t index, int data);
int removeIndex(List** head, size_t index);
int getIndexData(List* head, size_t index, int* out);
int setIndexData(List* head, size_t index, int data);
Cell* findCell(List* head, int data);
int containsData(List* head, int data);
size_t getListSize(List* head);
void clearList(List** head);
void reverseList(List** head);

signed main() {
  List* head;
  int n;
  int data;
  int out;
  size_t index;
  Cell* p;

  head = getEmptyList();

  while (1) {
    printf("\n");
    printf("0: 先頭に追加\n");
    printf("1: 先頭を削除\n");
    printf("2: 末尾に追加\n");
    printf("3: 末尾を削除\n");
    printf("4: 指定位置に追加\n");
    printf("5: 指定位置を削除\n");
    printf("6: 指定位置の値を取得\n");
    printf("7: 指定位置の値を変更\n");
    printf("8: 値を検索\n");
    printf("9: 値が存在するか確認\n");
    printf("10: リストサイズ取得\n");
    printf("11: リストを空にする\n");
    printf("12: リストを反転\n");
    printf("13: 終了\n");
    printf("選択: ");

    scanf("%d", &n);

    if (n == 0) {
      printf("追加する値: ");
      scanf("%d", &data);

      if (!insertHead(&head, data)) {
        printf("追加失敗\n");
      }

    } else if (n == 1) {
      if (!removeHead(&head)) {
        printf("削除失敗\n");
      }

    } else if (n == 2) {
      printf("追加する値: ");
      scanf("%d", &data);

      if (!insertTail(&head, data)) {
        printf("追加失敗\n");
      }

    } else if (n == 3) {
      if (!removeTail(&head)) {
        printf("削除失敗\n");
      }

    } else if (n == 4) {
      printf("index: ");
      scanf("%zu", &index);

      printf("追加する値: ");
      scanf("%d", &data);

      if (!insertIndex(&head, index, data)) {
        printf("追加失敗\n");
      }

    } else if (n == 5) {
      printf("index: ");
      scanf("%zu", &index);

      if (!removeIndex(&head, index)) {
        printf("削除失敗\n");
      }

    } else if (n == 6) {
      printf("index: ");
      scanf("%zu", &index);

      if (getIndexData(head, index, &out)) {
        printf("値: %d\n", out);
      } else {
        printf("取得失敗\n");
      }

    } else if (n == 7) {
      printf("index: ");
      scanf("%zu", &index);

      printf("変更後の値: ");
      scanf("%d", &data);

      if (!setIndexData(head, index, data)) {
        printf("変更失敗\n");
      }

    } else if (n == 8) {
      printf("検索する値: ");
      scanf("%d", &data);

      p = findCell(head, data);

      if (p != NULL) {
        printf("見つかりました: %d\n", getCellData(p));
      } else {
        printf("見つかりませんでした\n");
      }

    } else if (n == 9) {
      printf("確認する値: ");
      scanf("%d", &data);

      if (containsData(head, data)) {
        printf("存在します\n");
      } else {
        printf("存在しません\n");
      }

    } else if (n == 10) {
      printf("サイズ: %zu\n", getListSize(head));

    } else if (n == 11) {
      clearList(&head);

    } else if (n == 12) {
      reverseList(&head);

    } else if (n == 13) {
      clearList(&head);
      break;

    } else {
      printf("無効な入力です\n");
    }

    printf("List: ");
    printList(head);
  }

  return 0;
}
List* getEmptyList(void) { return ((List*)NULL); }
Cell* createCell(int data, List* next) {
  Cell* p;
  if ((p = (Cell*)malloc(sizeof(Cell))) != NULL) {
    setCellData(p, data);
    setNextCell(p, next);
    return p;
  } else {
    return getEmptyList();
  }
}
void setCellData(Cell* cell, int data) {
  cell->data = data;
  return;
}
int getCellData(Cell* cell) { return cell->data; }
void setNextCell(Cell* cell, List* next) {
  cell->next = next;
  return;
}
List* getNextCell(Cell* next) { return next->next; }
int isEmptyList(List* head) {
  if (head == getEmptyList()) {
    return 1;
  } else {
    return 0;
  }
}
int insertHead(List** head, int data) {
  Cell* p;
  p = createCell(data, *head);
  if (p != getEmptyList()) {
    *head = p;
    return 1;
  } else {
    return 0;
  }
}
int removeHead(List** head) {
  Cell* p;
  if (isEmptyList(*head)) {
    return 0;
  }
  p = getNextCell(*head);
  free(*head);
  *head = p;
  return 1;
}
void printList(List* head) {
  Cell* p;
  p = head;
  while (p != getEmptyList()) {
    printf("%d", getCellData(p));
    p = getNextCell(p);
    if (!isEmptyList(p)) {
      printf(" -> ");
    }
  }
  printf("\n");
  return;
}

Cell** getNextCellPointer(Cell* cell) { return &(cell->next); }
int insertTail(List** head, int data) {
  Cell** p = head;
  while (!isEmptyList(*p)) {
    p = getNextCellPointer(*p);
  }
  return insertHead(p, data);
}
int removeTail(List** head) {
  Cell** p = head;
  if (isEmptyList(*p)) {
    return 0;
  }
  while (!isEmptyList(getNextCell(*p))) {
    p = getNextCellPointer(*p);
  }
  return removeHead(p);
}
int insertIndex(List** head, size_t index, int data) {
  Cell** p = head;
  for (size_t i = 0; i < index; i++) {
    if (isEmptyList(*p)) {
      return 0;
    }
    p = getNextCellPointer(*p);
  }
  return insertHead(p, data);
}
int removeIndex(List** head, size_t index) {
  Cell** p = head;
  for (size_t i = 0; i < index; i++) {
    if (isEmptyList(*p)) {
      return 0;
    }
    p = getNextCellPointer(*p);
  }
  return removeHead(p);
}

int getIndexData(List* head, size_t index, int* out) {
  for (int i = 0; i < index && !isEmptyList(head); i++) {
    head = getNextCell(head);
  }
  if (isEmptyList(head)) {
    return 0;
  }
  *out = getCellData(head);
  return 1;
}
int setIndexData(List* head, size_t index, int data) {
  for (int i = 0; i < index && !isEmptyList(head); i++) {
    head = getNextCell(head);
  }
  if (isEmptyList(head)) {
    return 0;
  }
  setCellData(head, data);
  return 1;
}
Cell* findCell(List* head, int data) {
  while (head != getEmptyList() && getCellData(head) != data) {
    head = getNextCell(head);
  }
  if (isEmptyList(head)) {
    return (Cell*)NULL;
  } else {
    return head;
  }
}
int containsData(List* head, int data) {
  while (head != getEmptyList() && getCellData(head) != data) {
    head = getNextCell(head);
  }
  if (isEmptyList(head)) {
    return 0;
  } else {
    return 1;
  }
}
size_t getListSize(List* head) {
  size_t count = 0;
  while (head != getEmptyList()) {
    count++;
    head = getNextCell(head);
  }
  return count;
}
void clearList(List** head) {
  while (*head != getEmptyList()) {
    removeHead(head);
  }
  return;
}
void reverseList(List** head) {
  Cell* prev = getEmptyList();
  Cell* current = *head;
  Cell* next;
  while (current != getEmptyList()) {
    next = getNextCell(current);
    setNextCell(current, prev);
    prev = current;
    current = next;
  }
  *head = prev;
  return;
}
