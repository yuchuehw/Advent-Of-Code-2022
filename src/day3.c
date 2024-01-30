#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Opens a file and checks for errors.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param file Pointer to a FILE pointer where the opened file will be stored.
 * @return true if the file is successfully opened, false otherwise.
 */
bool fileOpener(int argc, char *argv[], FILE **file) {
    if (argc == 1) {
        printf("No file has been provided\n");
        return false;
    }

    *file = fopen(argv[1], "r"); // Use "r" for reading text files
    if (*file == NULL) {
        printf("Error opening file\n");
        return false;
    }
    return true;
}

/**
 * Reads char from a char buffer, compares 1st half to the second half of the buffer,
 * and returns the first repeated character.
 *
 * @param buf The char buffer.
 * @return The first repeated character, or '\0' if no repetition is found.
 */
char find_repeat_chr(char *buf) {
    int str_len = 0;
    while (buf[str_len] != '\0') {
        str_len += 1;
    }
    str_len -= 1;
    for (int i = 0; i < str_len/2; i++) {
        for (int j = str_len/2; j < str_len; j++) {
            if (buf[i] == buf[j]) {
                return buf[i];
            }
        }
    }
    return '\0';
}

/**
 * Reads values from a file, 
 *
 * @param file The FILE pointer for the opened file.
 * @param score Pointer to an integer representing the score.
 * @return true if the result is successfully tallied, false otherwise.
 */
bool tally_part1(FILE *file, int *score) {
    char buf[100];
    char *end;

    while (fgets(buf, sizeof buf, file) != NULL) {
        char repeat = find_repeat_chr(buf);
        if (repeat != '\0') {
            if(repeat-'A' <= 25){
                *score += 27;
                *score += repeat-'A';
            }else{
                *score += 1;
                *score += repeat-'a';
            }
        }
        else{
            return false;
        }
    }

    return true;
}

/**
 * Prints the top 1 value and the sum of the top 3 values.
 *
 * @param score Integer representing the score.
 */
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
        printf("failed\n");
        fclose(file);
        return 1;
    }
    report_result(score);
    
    fclose(file);
    return 0;
}
