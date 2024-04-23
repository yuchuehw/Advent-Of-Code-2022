#include <stdio.h>
#include <stdlib.h>

typedef struct CharNode {
  char c;
  struct CharNode *next;
} CharNode;

typedef struct HeadNode {
	int i;
	CharNode *next;
} HeadNode;

void freeLinkList(HeadNode *head) {
	CharNode *linkList = head->next;
	free(head);
	while (linkList != NULL) {
    CharNode *temp = linkList;
    linkList = linkList->next;
    free(temp);
  }
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

int extendLinkList(int cycle, int value, HeadNode *head){
	char new_c = '.';
	if (value - 1 <= (cycle - 1) % 40 && (cycle - 1) % 40 <= value + 1){
		new_c = '#';
	}

	CharNode *node = malloc(sizeof(CharNode));
	node->c = new_c;
	node->next = NULL;
	if (head->next == NULL){
		head->next = node;
	} else{
		CharNode *linkList = head->next;
		while (linkList->next){
			linkList = linkList->next;
		}
		linkList->next = node;
		if (cycle && cycle % 40 == 0){
			CharNode *newLine = malloc(sizeof(CharNode));
			node->next = newLine;
			newLine->c = '\n';
			newLine->next = NULL;
		}
	}

	if (cycle && (cycle - 20) % 40 == 0){
		return cycle * value;
	}
	return 0;
}

HeadNode* simulate(FILE *file){
	HeadNode *head = malloc(sizeof(HeadNode));
	head->next = NULL;
	int value = 1;
	int cycle = 1;

	int answer = 0;

	char buf[20];
	while (fgets(buf, sizeof buf, file) != NULL) {
    answer += extendLinkList(cycle, value, head);
		if (buf[0] == 'n'){
			cycle += 1;
		}else{
			cycle += 1;
			answer += extendLinkList(cycle, value, head);
			cycle += 1;
			value += atoi(buf+5);
		}
  }

	head->i = answer;
	return head;
} 

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  if (!fileOpener(argc, argv, &file)) {
    return 1;
  }
	HeadNode *head = simulate(file);
	printf("%d\n",head->i);
}
