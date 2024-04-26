#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

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
}Package;

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

Node* createNode(char type, int value) {
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
    
    Package package = { .success = false, .charParsed = 0, .node = NULL };
    if (c[0] != '[' && c[length-1] != ']'){
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
            i+=(temp.charParsed+1);
            
        } else if (c[i] == ',' || c[i] == ' ') {
            i++;
        } else if (c[i] == ']'){
            package = (Package){ .success = true, .charParsed = i, .node = head };
            return package;
        } else {
            char *end;
            errno = 0;
            long number = strtol(&c[i], &end, 10);
            if (*end == '\0') { // Corrected condition
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

int main() {
    Package p = parseString2List("[[],[1,[],2,0],[7,9,[[0],[10,9],[3],0],4,[[3,7,2,8],[],[6,5,10],[2,3,4,4],7]],[4,2,[[2,6,10,7],8,6,9,3],1]]");
    Node *list = p.node;
    printList(list);
    printf("\n");
    freeList(list);
    return 0;
}
