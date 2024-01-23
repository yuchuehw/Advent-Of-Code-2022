#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void closeFile(FILE *file) {
    if (file != NULL) {
        fclose(file);
    }
}

void handleFileError(FILE *file, const char *errorMessage) {
    perror(errorMessage);
    closeFile(file);
    exit(EXIT_FAILURE);
}

void handleMemoryError(void *memory) {
    perror("Memory allocation error");
    free(memory);
    exit(EXIT_FAILURE);
}

size_t readFile(const char *filename, char **buffer) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        handleFileError(file, "Error opening file");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = (char *)malloc(fileSize + 1);
    if (*buffer == NULL) {
        handleMemoryError(*buffer);
    }

    size_t bytesRead = fread(*buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        handleFileError(file, "Error reading file");
    }

    closeFile(file);

    (*buffer)[fileSize] = '\0';

    return bytesRead;
}

int main(int argc, char* argv[]) {    
    char *buffer = NULL;
    size_t fsize = readFile(argv[1], &buffer);
    
    bool line_changed = false; 
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    int cum = 0;
    int line = 0;
    for (int i = 0; i < fsize; i++) {
        int j = buffer[i] - '0';
        if(j>=0){
            line_changed = false;
            line*=10;
            line+=j;
        }else if(!line_changed){
            line_changed = true;
            cum += line;
            line = 0;
        }else{
            line_changed = false;
            if(cum >= max1){
                max3 = max2;
                max2 = max1;
                max1 = cum;
            }else if(cum>=max2){
                max3 = max2;
                max2 = cum;
            }else if(cum >= max3){
                max3 = cum;
            }
            cum=0;
        }
    }
    if(cum>=max1){
        max2 = max1;
        max3 = max2;
        max1 = cum;
    }else if(cum>=max2){
        max3 = max2;
        max2 = cum;
    }else if(cum >= max3){
        max3 = cum;
    }
    printf("%i\n",max1);
    printf("%i\n",max1+max2+max3);
    free(buffer);

    return 0;
}
