#include "../include/main.h"
#include "../include/structs.h"
#include <stdio.h>
#include <stdint.h>
#define HELP_MESSAGE "usage: discover [options] file\n"


int main(int argc, char* argv[]){
    char* file_name = NULL;

    switch(argc){
        case 2:
        file_name = argv[1];
        break;

        default:
        printf(HELP_MESSAGE);
    }

    FILE* file = fopen(file_name, "r");
    uint8_t header_byte;

    while(fread(&header_byte, 1, 1, file)){
        OverInstr* header = (OverInstr*) &header_byte;
        
        if(header->size == 0){
            uint32_t op_a;
            fread(&op_a, sizeof(uint32_t), 1, file);
        }
        else{
            uint32_t op_a;
            uint32_t op_b;
            fread(&op_a, sizeof(uint32_t), 1, file);
            fread(&op_b, sizeof(uint32_t), 1, file);
        }
    }
    return 0;
}
