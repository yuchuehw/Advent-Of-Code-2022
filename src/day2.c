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

int readFile(const char *filename, char **buffer) {
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

    int bytesRead = fread(*buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        handleFileError(file, "Error reading file");
    }

    closeFile(file);

    (*buffer)[fileSize] = '\0';

    return bytesRead;
}

int main(int argc, char* argv[]) {    
    char *buffer = NULL;
    int fsize = readFile(argv[1], &buffer);
    int score = 0;
    for(int i=0;i<fsize/4;i++){
        int a = buffer[i*4] - 'A';
        int b = buffer[i*4+2] - 'X';
        score+=1+b;
        if((a==0&&b==1)||(a==1&&b==2)||(a==2&&b==0)){
            score+=6;
        }else if(a==b){
            score+=3;
        }
    }
    printf("%i\n",score);
}
