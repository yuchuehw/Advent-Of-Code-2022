#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  union {
    int i;
    struct Node *list;
  } data;
  char dataType;
  struct Node *next;
} Node;

typedef struct Package {
  bool success;
  int charParsed;
  Node *node;
} Package;

void printList(Node *n) {
  printf("[");
  while (n != NULL) {
    if (n->dataType == 'l') {
      printList(n->data.list);
    } else {
      printf("%d", n->data.i);
    }
    if (n->next != NULL) {
      printf(", ");
    }
    n = n->next;
  }
  printf("]");
}

void freeList(Node *n) {
  while (n != NULL) {
    Node *temp = n;
    n = n->next;
    if (temp->dataType == 'l') {
      freeList(temp->data.list);
    }
    free(temp);
  }
}

Node *createNode(char type, int value) {
  Node *node = calloc(1, sizeof(Node));
  if (node == NULL) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }
  node->dataType = type;
  if (type == 'i') {
    node->data.i = value;
  }
  return node;
}

Package parseString2List(char *c) {
  int length = strlen(c);

  Package package = {.success = false, .charParsed = 0, .node = NULL};
  if (c[0] != '[' && c[length - 1] != ']') {
    return package;
  }

  Node *current = NULL;
  Node *head = NULL;

  int i = 1;
  while (i < length) {
    if (c[i] == '[') {
      Package temp = parseString2List(&c[i]);

      if (!temp.success) {
        package.charParsed = i + temp.charParsed;
        return package;
      }
      Node *nestedList = temp.node;
      Node *newNode = createNode('l', 0);
      if (current == NULL) {
        head = newNode;
      } else {
        current->next = newNode;
      }
      newNode->data.list = nestedList;
      current = newNode;
      i += (temp.charParsed + 1);

    } else if (c[i] == ',' || c[i] == ' ') {
      i++;
    } else if (c[i] == ']') {
      package = (Package){.success = true, .charParsed = i, .node = head};
      return package;
    } else {
      char *end;
      errno = 0;
      long number = strtol(&c[i], &end, 10);
      if (*end == '\0') {
        fprintf(stderr, "Error parsing integer\n");
        freeList(head);
        return package;
      }
      Node *newNode = createNode('i', (int)number);
      if (current == NULL) {
        head = newNode;
      } else {
        current->next = newNode;
      }
      current = newNode;
      i = end - c;
    }
  }
  package.charParsed = i;
  fprintf(stderr, "List never terminated\n");
  freeList(head);
  return package;
}

int fileOpener(int argc, char *argv[], FILE **file) {
  if (argc == 1) {
    printf("No file has been provided\n");
    return 0;
  }

  *file = fopen(argv[1], "r");
  if (*file == NULL) {
    perror("Error opening file");
    return 0;
  }

  return 1;
}

int compare(const void *a, const void *b) {

  Node *nodeA = (Node *)a;
  Node *nodeB = (Node *)b;

  if (a == NULL && b == NULL) {
    return 0;
  } else if (a == NULL) {
    return -1;
  } else if (b == NULL) {
    return 1;
  }

  if (nodeA->dataType == 'i' && nodeB->dataType == 'i') {
    if (nodeA->data.i < nodeB->data.i)
      return -1;
    else if (nodeA->data.i > nodeB->data.i)
      return 1;
    else
      return compare(nodeA->next, nodeB->next);
  }

  if (nodeA->dataType == 'i') {
    Node newNode = {.dataType = 'l', .data.list = nodeA, .next = NULL};
    return compare(&newNode, nodeB);
  }
  if (nodeB->dataType == 'i') {
    Node newNode = {.dataType = 'l', .data.list = nodeB, .next = NULL};
    return compare(nodeA, &newNode);
  }

  int r = compare(nodeA->data.list, nodeB->data.list);
  if (r != 0) {
    return r;
  }
  return compare(nodeA->next, nodeB->next);
}

void getFileDimension(FILE *file, int *dimension) {
  char c;
  int max_width = 0;
  int width = 0;
  int height = 1;
  fseek(file, 0, SEEK_SET);
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      height++;
      if (width > max_width) {
        max_width = width + 3;
      }
      width = 0;
    } else {
      width++;
    }
  }
  if (width > max_width) {
    max_width = width + 3;
  }
  dimension[0] = max_width;
  dimension[1] = height;
  fseek(file, 0, SEEK_SET);
}

void calculate(FILE *file) {
  int dimension[2];
  getFileDimension(file, dimension);
  int max_width = dimension[0];
  int height = dimension[1];
  const int SIZE = ((height + 4) * 2) / 3;

  char buf[max_width];
  Package p;
  Node *listOfList[SIZE];

  int i = -1;
  int j = 0;

  int answer1 = 0;
  int answer2 = 1;

  Package temp_package = parseString2List("[[2]]");
  Node *FLAG1 = temp_package.node;
  temp_package = parseString2List("[[6]]");
  Node *FLAG2 = temp_package.node;

  while (fgets(buf, sizeof buf, file) != NULL) {
    i++;
    if (i % 3 == 2) {
      continue;
    }
    j = i * 2 / 3 + i % 3;
    p = parseString2List(buf);
    if (!p.success) {
      return;
    }
    listOfList[j] = p.node;
    ;

    if (j % 2 != 0) {
      if (compare(listOfList[j - 1], listOfList[j]) <= 0) {
        answer1 += (i / 3) + 1;
      }
    }
  }
  printf("%d\n", answer1);
  listOfList[j + 1] = FLAG1;
  listOfList[j + 2] = FLAG2;

  qsort(listOfList, SIZE, sizeof(Node *), &compare);
  for (i = 0; i < SIZE; i++) {
    if (listOfList[i] == FLAG1) {
      answer2 *= (i + 1);
    } else if (listOfList[i] == FLAG2) {
      answer2 *= (i + 1);
    }
    freeList(listOfList[i]);
  }
  printf("%d\n", answer2);
}

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  if (!fileOpener(argc, argv, &file)) {
    return 1;
  }
  calculate(file);

  return 0;
}
