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
 * Reads values from a file, tally result and score for each game using rules in part 1.
 *
 * @param file The FILE pointer for the opened file.
 * @param score Pointer to an integer representing the score.
 * @return true if the result is successfully tallied, false otherwise.
 */
bool tally_part1(FILE *file, int *score) {
    char buf[5];
    char *end;
    while (fgets(buf, sizeof buf, file) != NULL) {
        if(buf[0] != 'A' && buf[0] != 'B' && buf[0] != 'C'){
            printf("Invalid character detected: %c\n", buf[0]);
            return false;
        }
        if(buf[2] != 'X' && buf[2] != 'Y' && buf[2] != 'Z'){
            printf("Invalid character detected: %c\n", buf[2]);
            return false;
        }

        int a = buf[0] - 'A';
        int b = buf[2] - 'X';
        *score += 1 + b;
        if((a == 0 && b == 1) || (a == 1 && b == 2) || (a == 2 && b == 0)){
            *score += 6;
        } else if(a == b){
            *score += 3;
        }
    }
    return true;
}

/**
 * Reads values from a file, tally result and score for each game using rules in part 2.
 *
 * @param file The FILE pointer for the opened file.
 * @param score Pointer to an integer representing the score.
 * @return true if the result is successfully tallied, false otherwise.
 */
bool tally_part2(FILE *file, int *score) {
    char buf[5];
    char *end;
    while (fgets(buf, sizeof buf, file) != NULL) {
        if(buf[0] != 'A' && buf[0] != 'B' && buf[0] != 'C'){
            printf("Invalid character detected: %c\n", buf[0]);
            return false;
        }
        int a = buf[0] - 'A';
        *score += 1;
        if(buf[2] == 'X'){
            *score += (a+2)%3;
        }else if(buf[2] == 'Y'){
            *score += a;
            *score += 3;
        }else if(buf[2] == 'Z'){
            *score += (a+1)%3;
            *score += 6;
        }
        else{
            printf("Invalid character detected: %c\n", buf[2]);
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
        fclose(file);
        return 1;
    }
    report_result(score);
    score = 0;
    fseek(file, 0, SEEK_SET);
    if (!tally_part2(file, &score)) {
        fclose(file);
        return 1;
    }
    report_result(score);

    fclose(file);

    return 0;
}
