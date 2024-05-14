#include <stdio.h>
#include <string.h>

int main() {
    const char BLOCKS[] = ""
    "####\n"
    "\n"
    ".#.\n"
    "###\n"
    ".#.\n"
    "\n"
    "..#\n"
    "..#\n"
    "###\n"
    "\n"
    "#\n"
    "#\n"
    "#\n"
    "#\n"
    "\n"
    "##\n"
    "##";
    
    const int BLOCK_TYPES = 5;
    const int MAX_BLOCK_HEIGHT = 4;
    const int MAX_BLOCK_WIDTH = 4;
    
    int block_array[BLOCK_TYPES][MAX_BLOCK_HEIGHT][MAX_BLOCK_WIDTH];
    int block_height[BLOCK_TYPES];
    memset(block_array,0,sizeof(block_array));
    memset(block_height,0,sizeof(block_height));
    
    const char *c_ptr = BLOCKS;
    for (int i = 0; i<BLOCK_TYPES; i++){
        int j = 0;
        int k = 0;
        while (1){
            if (*c_ptr == '\n' && *(c_ptr+1) == '\n' || *c_ptr == '\0'){
                c_ptr+=2;
                block_height[i] = j;
                break;
            }
            else if (*c_ptr == '\n'){
                j++;
                k = 0;
            }else if(*c_ptr == '#'){
                block_array[i][j][k] = 1;
                k++;
            }else{
                k++;
            }
            c_ptr++;
        }
        
    }
    for (int i = 0; i<BLOCK_TYPES; i++){
        printf("%d ", block_height[])
    
    return 0;
}
