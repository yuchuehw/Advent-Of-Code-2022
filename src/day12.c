#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Package{
    char *grid;
    int startX;
    int startY;
    int endx;
    int endy;
    int width;
    int height;
}Package;

int fileOpener(int argc, char *argv[], FILE **file) {
    if (argc == 1) {
    printf("No file has been provided\n");
    return 0;
    }

    *file = fopen(argv[1], "r");
    if (*file == NULL) {
    perror("Error opening file");
    return 0;
    }

    return 1;
}

void getFileDimension(FILE *file, int *dimension) {
    char c;
    int max_width = 0;
    int width = 0;
    int height = 1;
    while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
        height++;
        if (width > max_width) {
            max_width = width;
        }
        width = 0;
    } else {
        width++;
    }
    }
    if (width > max_width) {
        max_width = width;
    }
    dimension[0] = max_width;
    dimension[1] = height;
    rewind(file);
}

Package init_grid(FILE *file){
    int dimension[2];
    getFileDimension(file, dimension);
    int max_width = dimension[0];
    int height = dimension[1];
    
    char *grid = malloc(sizeof(char)*height*max_width);
    Package package;
    package.grid = grid;
    package.width = max_width;
    package.height = height;
    
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n'){
            continue;
        }
        if (c == 'S'){
            package.startX = i % max_width;
            package.startY = i / max_width;
            c = 'a';
        }
        if (c == 'E'){
            package.endx = i % max_width;
            package.endy = i / max_width;
            c = 'z';
        }
        grid[i] = c;
        i ++;
    }
    rewind(file);
    return package;
}


float bfs(const Package *package, int* candidates, int len, int* seen, int steps){
    if(len == 0){
        return INFINITY;
    }
    int nextCandidates[4*len][2];
    int nextLen = 0;
    for (int i = 0; i < len; i++){
        int x = candidates[2*i];
        int y = candidates[2*i+1];
        seen[y*package->width+x] = 1;
        int newPoints[][2] = {{x,y-1},{x,y+1},{x-1,y},{x+1,y}};
        for (int j = 0; j < 4; j++){
            int newX = newPoints[j][0];
            int newY = newPoints[j][1];
            
            if (newX >= 0 && newX < package->width && \
                newY >= 0 && newY < package->height && \
                !seen[newY*package->width+newX] && \
                package->grid[newY*package->width+newX] - 1 <= package->grid[y*package->width+x])
            {
                if (newX == package->endx && newY == package->endy){
                    return steps + 1;
                }
                seen[newY*package->width+newX] = 1;
                nextCandidates[nextLen][0] = newX;
                nextCandidates[nextLen][1] = newY;
                nextLen++;
            }
        }
    }
    return bfs(package, &nextCandidates[0][0], nextLen, seen, steps + 1);
}




void calculate(FILE *file) {

    Package package = init_grid(file);
    int seen[package.width][package.height];
    memset(seen,0,sizeof seen);
    int candidates[][2] = {{package.startX, package.startY}};
    float answer1 = bfs(&package,&candidates[0][0],1,&seen[0][0],0);
    float answer2 = INFINITY;
    for (int i = 0; i < package.width; i++ ){
        for (int j = 0; j < package.height; j++){
            if (package.grid[j*package.width+i] == 'a'){
                memset(seen,0,sizeof seen);
                candidates[0][0] = i;
                candidates[0][1] = j;
                float temp = bfs(&package, &candidates[0][0], 1,&seen[0][0], 0);
                if (temp < answer2){
                    answer2 = temp;
                }
            }
        }
    }
    printf("%d\n",(int)answer1);
    printf("%d\n",(int)answer2);
}


int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (!fileOpener(argc, argv, &file)) {
    return 1;
    }
    calculate(file);

    return 0;
}
