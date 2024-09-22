#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "components.h"
#include "instructions.h"
#include "platform.h"
#include "utils.h"
#include "main.h"


void cycle(void) {
    opcode = (memory[pc] << 8u) | memory[pc + 1];
    pc += 2;
    op_execute();

    if (delay > 0) {
        delay--;
    }

    if (sound > 0) {
        sound--;
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));

    initialize_chip8();

    if (argc != 4) {
        printf("Usage: <scale> <delay> <ROM>\n");
        exit(EXIT_FAILURE);
    }

    int video_scale = atoi(argv[1]);
    int cycle_delay = atoi(argv[2]);
    char *filename = argv[3];

    build_platform(
        "chip-8 emulator",
        VIDEO_WIDTH * video_scale,
        VIDEO_HEIGHT * video_scale,
        VIDEO_WIDTH,
        VIDEO_HEIGHT
    );

    read_instructions(filename);

    int video_pitch = sizeof(uint32_t) * VIDEO_WIDTH;
    
    struct timespec last_cycle;
    clock_gettime(CLOCK_MONOTONIC, &last_cycle);
    int quit = 0;

    while (!quit) {
        quit = process_input(keypad);

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        float dt = (current_time.tv_sec - last_cycle.tv_sec) * 1000.0f
            + (current_time.tv_nsec - last_cycle.tv_nsec) / 1000000.0f;
        
        if (dt > cycle_delay) {
            last_cycle = current_time;
            cycle();
            update(screen, video_pitch);
        }
    }

    destroy_platform();
    return EXIT_SUCCESS;
}

