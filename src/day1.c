#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct to represent the top 3 values
typedef struct {
    int max1;
    int max2;
    int max3;
} Top3;

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
 * Updates the top 3 values based on the current group sum.
 *
 * @param top Pointer to the Top3 struct representing the top 3 values.
 * @param current_group_sum The current sum of a group of values.
 */
void update_top_3(Top3 *top, int current_group_sum) {
    if (current_group_sum >= top->max1) {
        top->max3 = top->max2;
        top->max2 = top->max1;
        top->max1 = current_group_sum;
    } else if (current_group_sum >= top->max2) {
        top->max3 = top->max2;
        top->max2 = current_group_sum;
    } else if (current_group_sum >= top->max3) {
        top->max3 = current_group_sum;
    }
}

/**
 * Reads values from a file, updates the top 3 values, and handles errors.
 *
 * @param top_values Pointer to the Top3 struct representing the top 3 values.
 * @param file The FILE pointer for the opened file.
 * @return true if the result is successfully tallied, false otherwise.
 */
bool tally_result(Top3 *top_values, FILE *file) {
    int current_group_sum = 0;
    char buf[10];
    char *end;

    while (fgets(buf, sizeof buf, file) != NULL) {
        if (buf[0] != '\n') {
            current_group_sum += strtol(buf, &end, 10);
            if (*end != '\n' && *end != '\0') {
                printf("Error while reading file: Expecting number but got %s\n", buf);
                // Handle error appropriately
                return false;
            }
        } else {
            update_top_3(top_values, current_group_sum);
            current_group_sum = 0;
        }
    }
    update_top_3(top_values, current_group_sum);
    return true;
}

/**
 * Prints the top 1 value and the sum of the top 3 values.
 *
 * @param top_values Pointer to the Top3 struct representing the top 3 values.
 */
void report_result(Top3 *top_values) {
    printf("%i\n", top_values->max1);
    printf("%i\n", top_values->max1 + top_values->max2 + top_values->max3);
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (!fileOpener(argc, argv, &file)) {
        return 1;
    }

    Top3 top_values = {0, 0, 0}; // Initialize top_values

    if (!tally_result(&top_values, file)) {
        fclose(file);
        return 1;
    }
    fclose(file);

    report_result(&top_values);

    return 0;
}
