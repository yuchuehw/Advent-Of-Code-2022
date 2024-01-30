#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

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

char find_repeat_chr(const char *buf) {
    int str_len = strlen(buf);
    for (int i = 0; i < str_len / 2; i++) {
        for (int j = str_len / 2; j < str_len; j++) {
            if (buf[i] == buf[j]) {
                return buf[i];
            }
        }
    }
    return '\0';
}

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

bool update_score(char repeat, int *score) {
    if (repeat != '\0') {
        if (repeat >= 'A' && repeat <= 'Z') {
            *score += 27;
            *score += repeat - 'A';
        } else if (repeat >= 'a' && repeat <= 'z') {
            *score += 1;
            *score += repeat - 'a';
        }
        return true;
    } else {
        return false;
    }
}

bool tally_part1(FILE *file, int *score) {
    char buf[MAX_BUFFER_SIZE];

    while (fgets(buf, sizeof buf, file) != NULL) {
        char repeat = find_repeat_chr(buf);
        if (!update_score(repeat, score)) {
            return false;
        }
    }

    return true;
}

bool tally_part2(FILE *file, int *score) {
    char buf1[MAX_BUFFER_SIZE];
    char buf2[MAX_BUFFER_SIZE];
    char buf3[MAX_BUFFER_SIZE];

    while (1) {
        if (fgets(buf1, sizeof buf1, file) == NULL || fgets(buf2, sizeof buf2, file) == NULL ||
            fgets(buf3, sizeof buf3, file) == NULL) {
            break;
        }

        char *buf = intersection_str(intersection_str(buf1, buf2), buf3);

        if (!update_score(buf[0], score)) {
            free(buf);
            return false;
        }

        free(buf);
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

    int score = 0;
    if (!tally_part1(file, &score)) {
        printf("Tally part 1 failed\n");
        fclose(file);
        return 1;
    }
    report_result(score);

    fseek(file, 0, SEEK_SET);
    score = 0;
    if (!tally_part2(file, &score)) {
        printf("Tally part 2 failed\n");
        fclose(file);
        return 1;
    }
    report_result(score);

    fclose(file);
    return 0;
}
