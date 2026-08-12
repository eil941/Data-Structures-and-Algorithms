#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue_cell {
  int data;
  struct queue_cell* next;
} QueueCell;

typedef struct queue {
  QueueCell* front;
  QueueCell* rear;
} Queue;

void setQueueCellData(QueueCell* cell, int data);
int getQueueCellData(QueueCell* cell);
void setNextQueueCell(QueueCell* cell, QueueCell* next);
QueueCell* getNextQueueCell(QueueCell* cell);
void setQueueFront(Queue* queue, QueueCell* front);
QueueCell* getQueueFront(Queue* queue);
void setQueueRear(Queue* queue, QueueCell* rear);
QueueCell* getQueueRear(Queue* queue);

QueueCell* createQueueCell(int data);

void initQueue(Queue* queue);
int isEmptyQueue(Queue* queue);
int enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
int front(Queue* queue);
size_t getQueueSize(Queue* queue);
void clearQueue(Queue* queue);
void printQueue(Queue* queue);

signed main() {
  Queue q;
  int n, a;

  initQueue(&q);

  while (1) {
    printf("\n");
    printf("0: enqueue\n");
    printf("1: dequeue\n");
    printf("2: front\n");
    printf("3: 空か確認\n");
    printf("4: サイズ取得\n");
    printf("5: 全削除\n");
    printf("6: 終了\n");
    printf("選択: ");

    scanf("%d", &n);

    if (n == 0) {
      printf("値: ");
      scanf("%d", &a);

      if (!enqueue(&q, a)) {
        printf("enqueue失敗\n");
      }

    } else if (n == 1) {
      if (!dequeue(&q)) {
        printf("Queueは空です\n");
      }

    } else if (n == 2) {
      if (isEmptyQueue(&q)) {
        printf("Queueは空です\n");
      } else {
        printf("front: %d\n", front(&q));
      }

    } else if (n == 3) {
      if (isEmptyQueue(&q)) {
        printf("Queueは空です\n");
      } else {
        printf("Queueは空ではありません\n");
      }

    } else if (n == 4) {
      printf("size: %zu\n", getQueueSize(&q));

    } else if (n == 5) {
      clearQueue(&q);

    } else if (n == 6) {
      clearQueue(&q);
      break;

    } else {
      printf("無効な入力です\n");
    }

    printf("Queue: ");
    printQueue(&q);
  }

  return 0;
}

void setQueueCellData(QueueCell* cell, int data) {
  cell->data = data;
  return;
}
int getQueueCellData(QueueCell* cell) { return cell->data; }
void setNextQueueCell(QueueCell* cell, QueueCell* next) {
  cell->next = next;
  return;
}
QueueCell* getNextQueueCell(QueueCell* cell) { return cell->next; }
void setQueueFront(Queue* queue, QueueCell* front) {
  queue->front = front;
  return;
}
QueueCell* getQueueFront(Queue* queue) { return queue->front; }
void setQueueRear(Queue* queue, QueueCell* rear) {
  queue->rear = rear;
  return;
}
QueueCell* getQueueRear(Queue* queue) { return queue->rear; }

QueueCell* createQueueCell(int data) {
  QueueCell* p;
  if ((p = (QueueCell*)malloc(sizeof(QueueCell))) != NULL) {
    setQueueCellData(p, data);
    return p;
  } else {
    return NULL;
  }
}

void initQueue(Queue* queue) {
  setQueueFront(queue, NULL);
  setQueueRear(queue, NULL);
  return;
}
int isEmptyQueue(Queue* queue) {
  if (getQueueFront(queue) == NULL) {
    return 1;
  } else {
    return 0;
  }
}
int enqueue(Queue* queue, int data) {
  QueueCell* p;
  if ((p = createQueueCell(data)) != NULL) {
    setNextQueueCell(p, NULL);
    if (isEmptyQueue(queue)) {
      setQueueFront(queue, p);
    } else {
      setNextQueueCell(getQueueRear(queue), p);
    }
    setQueueRear(queue, p);
    return 1;
  } else {
    return 0;
  }
}

int dequeue(Queue* queue) {
  QueueCell* p;
  if (isEmptyQueue(queue)) {
    return 0;
  } else {
    p = getQueueFront(queue);
    if (getQueueFront(queue) == getQueueRear(queue)) {
      setQueueRear(queue, NULL);
    }
    setQueueFront(queue, getNextQueueCell(getQueueFront(queue)));
    free(p);
  }
  return 1;
}
int front(Queue* queue) { return getQueueCellData(getQueueFront(queue)); }
size_t getQueueSize(Queue* queue) {
  size_t count = 0;
  QueueCell* p = getQueueFront(queue);
  while (p != NULL) {
    p = getNextQueueCell(p);
    count++;
  }
  return count;
}
void clearQueue(Queue* queue) {
  while (!isEmptyQueue(queue)) {
    dequeue(queue);
  }
  return;
}
void printQueue(Queue* queue) {
  QueueCell* p = getQueueFront(queue);

  while (p != NULL) {
    printf("%d", getQueueCellData(p));
    p = getNextQueueCell(p);

    if (p != NULL) {
      printf(" -> ");
    }
  }

  printf("\n");
  return;
}