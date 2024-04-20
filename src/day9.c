#include <stdio.h>
#include <stdlib.h>

typedef struct IntPairNode {
  int x;
  int y;
  struct IntPairNode *next;
} IntPairNode;

typedef struct IntPair {
  int x;
  int y;
  char isNull;
} IntPair;

typedef struct Instruction {
  char direction;
  int moves;
} Instruction;

void getDirctionFromChar(char c, int *arr) {
  // write direction to arr based on c; return 0 when success and 1 when fail.
  if (c == 'U') {
    arr[0] = 0;
    arr[1] = 1;
  } else if (c == 'D') {
    arr[0] = 0;
    arr[1] = -1;
  } else if (c == 'L') {
    arr[0] = -1;
    arr[1] = 0;
  } else if (c == 'R') {
    arr[0] = 1;
    arr[1] = 0;
  } else {
    perror("invalid direction provided");
    return;
  }
  return;
}

int insertIfNew(int x, int y, IntPairNode *linkList) {
  // create and insert a new node if not exist already(return 1) else return 0
  if (linkList == NULL) {
    perror("linkList can not be NULL");
    return 0;
  }
  IntPairNode *current_node = linkList;
  while (1) {
    if (current_node->x == x && current_node->y == y) {
      return 0;
    }
    if (current_node->next == NULL) {
      break;
    }
    current_node = current_node->next;
  }
  current_node->next = malloc(sizeof(IntPairNode));
	if (current_node->next == NULL){
		perror("fail to allocate memory for `current_node->next` line 59");
		exit(1);
	}
  current_node = current_node->next;
  current_node->x = x;
  current_node->y = y;
	current_node->next = NULL;
  return 1;
}

void freeLinkList(IntPairNode *linkList) {
  while (linkList != NULL) {
    IntPairNode *temp = linkList;
    linkList = linkList->next;
    free(temp);
  }
}

int findVisited(IntPair *pairList, const Instruction *instructList) {
  // pairList and instructList must be properly terminated.
  if (pairList[0].isNull == '\0' || pairList[1].isNull == '\0') {
    perror("pairList must have at least 2 elements");
    return -1;
  }
  IntPairNode *linkList = malloc(sizeof(IntPairNode));
	if (linkList == NULL){
		perror("Fail to allocate initial node of linkList line 85");
		exit(1);
	}
  linkList->x = 0;
  linkList->y = 0;
  linkList->next = NULL;
	int linkListLength = 1;

  int i = 0;
  while (instructList[i].direction != '\0') {
    const Instruction *instruction = &instructList[i];
    for (int _ = instruction->moves; _ > 0; _--) {
      int delta[2];
      getDirctionFromChar(instruction->direction, delta);
      pairList[0].x += delta[0];
      pairList[0].y += delta[1];
      IntPair *previousPair = &pairList[0];
      int j = 1;
      int flag = 1;
      while (pairList[j].isNull != '\0') {
        IntPair *currentPair = &pairList[j];
        if (abs(previousPair->x - currentPair->x) > 1 ||
            abs(previousPair->y - currentPair->y) > 1) {
          int x_adjust =
              ((previousPair->x - currentPair->x) > 0)
                  ? 1
                  : (((previousPair->x - currentPair->x) < 0) ? -1 : 0);
          int y_adjust =
              ((previousPair->y - currentPair->y) > 0)
                  ? 1
                  : (((previousPair->y - currentPair->y) < 0) ? -1 : 0);
          currentPair->x += x_adjust;
          currentPair->y += y_adjust;
        } else {
          flag = 0;
          break;
        }
        previousPair = currentPair;
        j++;
      }
      if (flag) {
        if (insertIfNew(previousPair->x, previousPair->y, linkList)) {
          linkListLength++;
        }
      }
    }
    i++;
  }
  freeLinkList(linkList);

  return linkListLength;
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

Instruction *buildInstructList(FILE *file) {
  // try create instruction list. return list on success. NULL on fail.
  char c;
  int max_width = 0;
  int width = 0;
  int height = 1;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      height++;
      if (width > max_width) {
        max_width = width + 3; // so we can include endline char and null char
      }
      width = 0;

    } else if (!width) {
      if (c != 'U' && c != 'D' && c != 'L' && c != 'R') {
        return NULL;
      }
      width++;
    } else {
      width++;
    }
  }
  int i = 0;
  char buf[max_width];
  Instruction *instructList = malloc(sizeof(Instruction) * (height + 1));
  if (instructList == NULL){
		return NULL;
	}
	fseek(file, 0, SEEK_SET);
  while (fgets(buf, sizeof buf, file) != NULL) {
    instructList[i].direction = buf[0];
    instructList[i].moves = atoi(buf + 2);
    i++;
  }
  instructList[i].direction = '\0';
  instructList[i].moves = 0;
  return instructList;
}

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  if (!fileOpener(argc, argv, &file)) {
    return 1;
  }
  Instruction *instructList = buildInstructList(file);
  if (instructList == NULL) {
    printf("Failed to build instruction list.\n");
    return 1;
  }
  fclose(file);

  IntPair pairList1[3];
  IntPair pairList2[11];
  for (int i = 0; i < 2; i++) {
    pairList1[i].x = 0;
    pairList1[i].y = 0;
    pairList1[i].isNull = 'F';
  }
  pairList1[2].isNull = '\0';

  for (int i = 0; i < 10; i++) {
    pairList2[i].x = 0;
    pairList2[i].y = 0;
    pairList2[i].isNull = 'F';
  }
  pairList2[10].isNull = '\0';

  int visited1 = findVisited(pairList1, instructList);
  int visited2 = findVisited(pairList2, instructList);
  printf("%d\n%d\n", visited1, visited2);
  free(instructList);
}
