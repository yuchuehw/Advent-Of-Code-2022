#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5000

char* intersection_str(const char *buf1, const char *buf2) {
    int str_len1 = strlen(buf1);
    int str_len2 = strlen(buf2);

    // Allocate memory for the intersection buffer
    char buf[str_len1 > str_len2 ? str_len1 + 1 : str_len2 + 1];

    int i = 0;
    for (int j = 0; j < str_len1; j++) {
        for (int k = 0; k < str_len2; k++) {
            if (buf1[j] == buf2[k]) {
                bool flag = true;
                for (int l = 0; l<i; l++){
                    if (buf1[j] == buf[l]){
                        flag = false;
                    }
                }
                if (flag){
                    buf[i] = buf1[j];
                    i++;
                }
            }
        }
    }
    // copy to malloc
    char *return_buf = (char*)malloc( sizeof(char) * (i+1));
    if (return_buf == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < i; j++){
        return_buf[j]=buf[j];
    }
    return_buf[i] = '\0';
    return return_buf;
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

void find_index(char *buf_ptr, int group_size) {
    const int END = strlen(buf_ptr) - group_size; // Removed unnecessary dereference *
    for (int i = 0; i <= END; i++) { // Changed < to <= to include the last group
        char temp = buf_ptr[group_size];
        buf_ptr[group_size] = '\0';
        if (strlen(intersection_str(buf_ptr, buf_ptr)) == group_size) {
            buf_ptr[group_size] = temp;
            printf("%i\n", i + group_size);
            break;
        }
        buf_ptr[group_size] = temp; // Changed GROUP_SIZE to group_size
        buf_ptr++;
    }
}

bool simulate(FILE *file) {
    char buf[MAX_BUFFER_SIZE] = "\0";
    if (fgets(buf, sizeof(buf), file) == NULL) {
        // Handle error or end of file condition
        return false;
    }

    const int GROUP_SIZE1 = 4;
    const int GROUP_SIZE2 = 14;

    find_index(buf, GROUP_SIZE1);

    return true;
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (!fileOpener(argc, argv, &file)) {
        return 1;
    }
    simulate(file);
}
