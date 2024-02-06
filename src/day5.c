#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_BUFFER_SIZE 100

typedef struct {
    int quantity;
    char origin[10];
    char destination[10];
} Instruction;


void reverse_string(const char* input, char* output) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        output[i] = input[length - i - 1];
    }
    output[length] = '\0';  // Null-terminate the reversed string
}

bool fileOpener(int argc, char *argv[], FILE **file) {
    if (argc == 1) {
        printf("No file has been provided\n");
        return false;
    }

    *file = fopen(argv[1], "r"); // Use "r" for reading text files
    if (*file == NULL) {
        perror("Error opening file");
        return false;
    }

    return true;
}

bool simulate(FILE *file){
    char buf[MAX_BUFFER_SIZE];
    char stack_head[100] = "\0";
    char stack_head_2d[100][100];
    char stack_by_pos[100][100];
    char stack_by_head1[100][100];
    char stack_by_head2[100][100];

    Instruction instructions[1000];
    int instruct_counter = 0;
    
    while (fgets(buf, sizeof buf, file) != NULL) {
        if (stack_head[0] == '\0' && buf[0] == ' '){
            strcpy(stack_head, buf);
        }
        else if (stack_head[0] == '\0'){
            for(int i = 0;i<strlen(buf);i++){
                if(buf[i]-'A' >= 0 && buf[i]-'A' <= 25){
                    int j = strlen(stack_by_pos[i]);
                    stack_by_pos[i][j] = buf[i];
                    stack_by_pos[i][j+1] = '\0';
                }
            }
        }
        else if(stack_head[0] != '\0' && buf[0] != '\n'){
            char *token = strtok(buf, " ");
            int i = 0;
            while (token != NULL){
                if(i==1){
                    instructions[instruct_counter].quantity = strtol(token,NULL,10);
                }else if(i==3){
                    strcpy(instructions[instruct_counter].origin,token);
                }else if(i==5){
                    strcpy(instructions[instruct_counter].destination,token);
                    instructions[instruct_counter].destination[strlen(instructions[instruct_counter].destination) - 1] = '\0';
                }
                token = strtok(NULL, " ");
                i++;
            }
            instruct_counter++;
        }
    }
    char stack_head_copy[100];
    strcpy(stack_head_copy,stack_head);

    char *token = strtok(stack_head, " ");
    int stack_counter = 0;
    while (token != NULL){
        int token_index = strstr(stack_head_copy, token) - stack_head_copy;
        strcpy(stack_head_2d[stack_counter],token);
        reverse_string(stack_by_pos[token_index], stack_by_head1[stack_counter]);
        reverse_string(stack_by_pos[token_index], stack_by_head2[stack_counter]);

        token = strtok(NULL, " ");
        stack_counter++;
    }
    
    for(int i=0;i<instruct_counter;i++){
        int i1 = -1;
        int i2 = -1;
        for (int j = 0; j < stack_counter; j++) {
            

            if (i1 == -1 && strcmp(instructions[i].origin, stack_head_2d[j]) == 0) {
                i1 = j;
            }
            if (i2 == -1 && strcmp(instructions[i].destination, stack_head_2d[j]) == 0) {
                i2 = j;
            }
            if (i1 != -1 && i2 != -1) {
                break;
            }
        }
        for(int j=0;j<instructions[i].quantity;j++){
            strcpy(stack_by_head1[i2]+strlen(
                stack_by_head1[i2]),stack_by_head1[i1]+strlen(stack_by_head1[i1])-1);
            stack_by_head1[i1][strlen(stack_by_head1[i1]) - 1] = '\0';    
        }
        strcpy(stack_by_head2[i2]+strlen(                
            stack_by_head2[i2]),stack_by_head2[i1]+strlen(stack_by_head2[i1])-instructions[i].quantity);

        stack_by_head2[i1][strlen(stack_by_head2[i1]) - instructions[i].quantity] = '\0';    

    }
    for(int i=0;i<stack_counter;i++){
        printf("%c",stack_by_head1[i][strlen(stack_by_head1[i])-1]);
    }
    
    printf("\n");
    for(int i=0;i<stack_counter;i++){
        printf("%c",stack_by_head2[i][strlen(stack_by_head2[i])-1]);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (!fileOpener(argc, argv, &file)) {
        return 1;
    }
    simulate(file);
}
