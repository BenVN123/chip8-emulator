#include <stdio.h>
#include <stdlib.h>

#include "components.h"

void read_instructions(char *filename) {
    FILE *file = fopen(filename, "rb");
    long file_size;
    if (!file) {
        return;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 4096 - START_ADDRESS) {
        printf("instructions too large\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(memory + START_ADDRESS, 1, file_size, file);
    fclose(file);
}

void load_fontset(void) {
    for (int i = 0; i < 80; i++) {   // todo: 80 should be fontset_size
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

uint8_t rand_byte(void) {
    return (uint8_t) (rand() % (256));
}

