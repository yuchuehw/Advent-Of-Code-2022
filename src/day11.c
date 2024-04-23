#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_MONKEYS 8

typedef struct ItemList {
  long long i;
  struct ItemList *next;
} ItemList;

typedef struct Monkey {
  int id;
  ItemList *next;
  long long (*op)(long long);
  int mod;
  int success;
  int fail;
} Monkey;

void freeList(ItemList *list) {
  while (list) {
    ItemList *temp = list->next;
    free(list);
    list = temp;
  }
}

ItemList *arrayToList(int *b) {
  // array must be -1 terminated
  if (b[0] == -1) {
    return NULL;
  }
  ItemList *head = malloc(sizeof(ItemList));
  if (head == NULL) {
    perror("fail to allocate for head.(line 34)");
    return NULL;
  }
  head->i = *b;
  head->next = NULL;
  ItemList *current = head;
  b++;
  int i = 0;
  while (*b != -1) {
    ItemList *newItem = malloc(sizeof(ItemList));
    if (newItem == NULL) {
      perror("fail to allocate for newItem.(line 44)");
      freeList(head);
      return NULL;
    }
    newItem->i = *b;
    newItem->next = NULL;
    current->next = newItem;
    current = newItem;
    b++;
    i++;
    if (i == 20) {
      perror("no termination character found after 20 iterations. do you "
             "forget to terminate the array?");
    }
  }
  return head;
}

Monkey createMonkey(int id, int *items, long long (*operation)(long long),
                    int mod, int success, int fail) {
  Monkey m;
  m.id = id;
  m.next = arrayToList(items);
  m.op = operation;
  m.mod = mod;
  m.success = success;
  m.fail = fail;
  return m;
}

ItemList *copyItemList(ItemList *src) {
  if (src == NULL) {
    return NULL;
  }
  ItemList *head = malloc(sizeof(ItemList));
  if (head == NULL) {
    perror("fail to allocate for head.(line 65)");
    return NULL;
  }
  head->i = src->i;
  ItemList *current = head;
  src = src->next;
  while (src != NULL) {
    current->next = malloc(sizeof(ItemList));
    if (current->next == NULL) {
      perror("fail to allocate next(line 74)");
      freeList(head);
      return NULL;
    }
    current = current->next;
    current->i = src->i;
    current->next = NULL;
    src = src->next;
  }
  return head;
}

long long f0(long long x) { return x * 5; }
long long f1(long long x) { return x + 5; }
long long f2(long long x) { return x * 19; }
long long f3(long long x) { return x + 7; }
long long f4(long long x) { return x + 2; }
long long f5(long long x) { return x + 1; }
long long f6(long long x) { return x * x; }
long long f7(long long x) { return x + 4; }

long long simulate(Monkey *monkeys, long long (*bored)(long long),
                   long long (*post)(long long), int rounds) {
  long long inspected[TOTAL_MONKEYS] = {0};
  for (int i = 0; i < rounds; i++) {
    for (int j = 0; j < TOTAL_MONKEYS; j++) {
      Monkey *m = &monkeys[j];
      ItemList *current = m->next;
      while (current) {
        inspected[m->id]++;
        ItemList *temp = current->next;
        current->next = NULL;
        current->i = (*(m->op))(current->i);
        current->i = (*bored)(current->i);
        int reciving_monkey;
        if (current->i % m->mod == 0) {
          reciving_monkey = m->success;
        } else {
          reciving_monkey = m->fail;
        }
        current->i = (*post)(current->i);
        ItemList *other = monkeys[reciving_monkey].next;
        if (other == NULL) {
          monkeys[reciving_monkey].next = current;
        } else {
          while (other->next) {
            other = other->next;
          }
          other->next = current;
        }
        current = temp;
      }
      monkeys[m->id].next = NULL;
    }
  }

  long long max1 = 0;
  long long max2 = 0;
  for (int i = 0; i < TOTAL_MONKEYS; i++) {
    if (inspected[i] > max1) {
      max2 = max1;
      max1 = inspected[i];
    } else if (inspected[i] > max2) {
      max2 = inspected[i];
    }
  }
  return max1 * max2;
  ;
}

// print(sim(question_input(),NONE,POST,10000))

long long BORED(long long x) { return x / 3; }

long long POST(long long x) { return x % (11 * 19 * 5 * 3 * 13 * 17 * 7 * 2); }

long long NONE(long long x) { return x; }

int main() {
  Monkey MONKEYS[TOTAL_MONKEYS] = {
      createMonkey(0, (int[]){73, 77, -1}, &f0, 11, 6, 5),
      createMonkey(1, (int[]){57, 88, 80, -1}, &f1, 19, 6, 0),
      createMonkey(2, (int[]){61, 81, 84, 69, 77, 88, -1}, &f2, 5, 3, 1),
      createMonkey(3, (int[]){78, 89, 71, 60, 81, 84, 87, 75, -1}, &f3, 3, 1,
                   0),
      createMonkey(4, (int[]){60, 76, 90, 63, 86, 87, 89, -1}, &f4, 13, 2, 7),
      createMonkey(5, (int[]){88, -1}, &f5, 17, 4, 7),
      createMonkey(6, (int[]){84, 98, 78, 85, -1}, &f6, 7, 5, 4),
      createMonkey(7, (int[]){98, 89, 78, 73, 71, -1}, &f7, 2, 3, 2),
  };
  Monkey monkey_copy[TOTAL_MONKEYS];
  memcpy(monkey_copy, MONKEYS, sizeof(monkey_copy));
  for (int i = 0; i < TOTAL_MONKEYS; i++) {
    monkey_copy[i].next = copyItemList(MONKEYS[i].next);
  }
  printf("%lld\n", simulate(monkey_copy, &BORED, &NONE, 20));
  printf("%lld\n", simulate(MONKEYS, &NONE, &POST, 10000));
  for (int i = 0; i < TOTAL_MONKEYS; i++) {
    freeList(MONKEYS[i].next);
    freeList(monkey_copy[i].next);
    MONKEYS[i].next = NULL;
    monkey_copy[i].next = NULL;
  }
  return 0;
}
