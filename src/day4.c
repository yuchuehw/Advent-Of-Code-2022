#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 20

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

bool tally_part1(FILE *file, int *score1, int *score2) {
    char buf[MAX_BUFFER_SIZE];
    int l[10];
    while (fgets(buf, sizeof buf, file) != NULL) {
        char *buf_pointer= buf;
        char *end;
        int flag = 1;
        int i = 0;
        while (1){
            if(buf_pointer[0] == '\0'){
                break;
            }
            else if(buf_pointer[0]<'0' || buf_pointer[0]>'9'){
                flag = 1;
            }else if(flag==1){
                flag = 0;
                l[i] = atoi(buf_pointer);

                i++;
            }else{
                flag = 0;
            }
            buf_pointer++;
        }
        if(l[2]<=l[0]&&l[1]<=l[3]){
            *score1+=1;
        }else if(l[0]<=l[2]&&l[3]<=l[1]){
            *score1+=1;
        }
        if(l[0]<=l[2] && l[2]<=l[1]){
            *score2+=1;

        }else if(l[0]<=l[3] && l[3]<=l[1]){
            *score2+=1;

        }else if(l[2]<=l[0] && l[0]<=l[3]){
            *score2+=1;

        }else if(l[2]<=l[1] && l[1]<=l[3]){
            *score2+=1;

        }
    }

    return true;
}

void report_result(int score) {
    printf("%i\n", score);
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (!fileOpener(argc, argv, &file)) {
        return 1;
    }

    int score1 = 0;
    int score2 = 0;
    if (!tally_part1(file, &score1, &score2)) {
        printf("Tally part 1 failed\n");
        fclose(file);
        return 1;
    }
    report_result(score1);
    report_result(score2);

}
