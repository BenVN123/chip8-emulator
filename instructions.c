#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "components.h"
#include "utils.h"
#include "instructions.h"

void op_00E0(void) {
    memset(screen, 0, sizeof(screen));
}

void op_00EE(void) {
    pc = stack[--stack_ptr];
}

void op_1nnn(void) {
    pc = opcode & 0xFFFu;
}

void op_2nnn(void) {
    stack[stack_ptr++] = pc;
    pc = opcode & 0xFFFu;
}

void op_3xkk(void) {
    if (registers[(opcode & 0xF00u) >> 8u] == (opcode & 0xFFu)) {
        pc += 2;
    }
}

void op_4xkk(void) {
    if (registers[(opcode & 0xF00u) >> 8u] != (opcode & 0xFFu)) {
        pc += 2;
    }
}

void op_5xy0(void) {
    if (registers[(opcode & 0xF00u) >> 8u] == registers[(opcode & 0xF0u) >> 4u]) {
        pc += 2;
    }
}

void op_6xkk(void) {
    registers[(opcode & 0xF00u) >> 8u] = opcode & 0xFFu;
}

void op_7xkk(void) {
    registers[(opcode & 0xF00u) >> 8u] += opcode & 0xFFu;
}

void op_8xy0(void) {
    registers[(opcode & 0xF00u) >> 8u] = registers[(opcode & 0xF0u) >> 4u];
}

void op_8xy1(void) {
    registers[(opcode & 0xF00u) >> 8u] |= registers[(opcode & 0xF0u) >> 4u];
}

void op_8xy2(void) {
    registers[(opcode & 0xF00u) >> 8u] &= registers[(opcode & 0xF0u) >> 4u];
}

void op_8xy3(void) {
    registers[(opcode & 0xF00u) >> 8u] ^= registers[(opcode & 0xF0u) >> 4u];
}

void op_8xy4(void) {
    uint8_t Vx = (opcode & 0xF00u) >> 8u;
    uint8_t Vy = (opcode & 0xF0u) >> 4u;
    uint16_t sum = registers[Vx] + registers[Vy];

    if (sum > 0xFFu) {
        registers[0xFu] = 1;
    } else {
        registers[0xFu] = 0;
    }

    registers[Vx] = sum & 0xFFu;
}

void op_8xy5(void) {
    uint8_t Vx = (opcode & 0xF00u) >> 8u;
    uint8_t Vy = (opcode & 0xF0u) >> 4u;

    if (registers[Vx] > registers[Vy]) {
        registers[0xFu] = 1;
    } else {
        registers[0xFu] = 0;
    }

    registers[Vx] -= registers[Vy];
}

void op_8xy6(void) {
    unsigned int lsb = registers[(opcode & 0xF00u) >> 8u] & 0x1u;
    registers[0xFu] = lsb;

    registers[(opcode & 0xF00u) >> 8u] >>= 1;
}

void op_8xy7(void) {
    uint8_t Vx = (opcode & 0xF00u) >> 8u;
    uint8_t Vy = (opcode & 0xF0u) >> 4u;

    if (registers[Vy] > registers[Vx]) {
        registers[0xFu] = 1;
    } else {
        registers[0xFu] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

void op_8xyE(void) {
    unsigned int msb = registers[(opcode & 0xF00u) >> 8u] >> 7u;
    registers[0xFu] = msb;

    registers[(opcode & 0xF00u) >> 8u] <<= 1;
}

void op_9xy0(void) {
    uint8_t Vx = registers[(opcode & 0xF00u) >> 8u];
    uint8_t Vy = registers[(opcode & 0xF00u) >> 4u];

    if (Vx != Vy) {
        pc += 2;
    }
}

void op_Annn(void) {
    idx = opcode & 0xFFFu; 
}

void op_Bnnn(void) {
    pc = (opcode & 0xFFFu) + registers[0];
}

void op_Cxkk(void) {
    registers[(opcode & 0xF00u) >> 8u] = rand_byte() & (opcode & 0xFFu);
}

void op_Dxyn(void) {
    uint8_t Vx = (opcode & 0xF00u) >> 8u;
    uint8_t Vy = (opcode & 0xF0u) >> 4u;
    uint8_t height = opcode & 0xFu;

    uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
    uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;
    
    registers[0xFu] = 0;
    for (unsigned int row = 0; row < height; row++) {
        uint8_t sprite_byte = memory[idx + row];
        for (unsigned int col = 0; col < 8; col++) {
            uint8_t sprite_pixel = sprite_byte & (0x80u >> col);
            uint32_t *screen_pixel = screen + VIDEO_WIDTH * (yPos + row) + xPos + col;

            if (sprite_pixel) {
                if (*screen_pixel == 0xFFFFFFFF) {
                    registers[0xFu] = 1;
                }
                *screen_pixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void op_Ex9E(void) {
    if (keypad[registers[(opcode & 0xF00u) >> 8u]]) {
        pc += 2;
    }
}

void op_ExA1(void) {
    if (!keypad[registers[(opcode & 0xF00u) >> 8u]]) {
        pc += 2;
    }
}

void op_Fx07(void) {
    registers[(opcode & 0xF00u) >> 8u] = delay;
}

void op_Fx0A(void) {
    unsigned int key_pressed = 0;

    for (unsigned int i = 0; i < 16; i++) {
        if (keypad[i]) {
            key_pressed = 1;
            registers[(opcode & 0xF00u) >> 8u] = i;
        }
    }

    if (!key_pressed) {
        pc -= 2;
    }
}

void op_Fx15(void) {
    delay = registers[(opcode & 0xF00u) >> 8u];
}

void op_Fx18(void) {
    sound = registers[(opcode & 0xF00u) >> 8u];
}

void op_Fx1E(void) {
    idx += registers[(opcode & 0xF00u) >> 8u];
}

void op_Fx29(void) {
    idx = FONTSET_START_ADDRESS + (5 * registers[(opcode & 0xF00u) >> 8u]);
}

void op_Fx33(void) {
    uint8_t value = registers[(opcode & 0xF00u) >> 8u];
    
    memory[idx + 2] = value % 10;
    value /= 10;

    memory[idx + 1] = value % 10;
    value /= 10;

    memory[idx] = value % 10;
}

void op_Fx55(void) {
    for (uint8_t i = 0; i <= ((opcode & 0xF00u) >> 8u); i++) {
        memory[idx + i] = registers[i];
    }
}

void op_Fx65(void) {
    for (uint8_t i = 0; i <= ((opcode & 0xF00u) >> 8u); i++) {
        registers[i] = memory[idx + i];
    }
}

void op_execute(void) {
    switch ((opcode & 0xF000u) >> 12u) {
        case 0x8u:
            switch (opcode & 0xFu) {
                case 0x0u:
                    op_8xy0();
                    break;
                case 0x1u:
                    op_8xy1();
                    break;
                case 0x2u:
                    op_8xy2();
                    break;
                case 0x3u:
                    op_8xy3();
                    break;
                case 0x4u:
                    op_8xy4();
                    break;
                case 0x5u:
                    op_8xy5();
                    break;
                case 0x6u:
                    op_8xy6();
                    break;
                case 0x7u:
                    op_8xy7();
                    break;
                case 0xEu:
                    op_8xyE();
                    break;
            }
            break;
        case 0x0u:
            switch (opcode & 0xFFu) {
                case 0xE0u:
                    op_00E0();
                    break;
                case 0xEEu:
                    op_00EE();
                    break;
            }
            break;
        case 0xEu:
            switch (opcode & 0xFFu) {
                case 0xA1u:
                    op_ExA1();
                    break;
                case 0x9Eu:
                    op_Ex9E();
                    break;
            }
            break;
        case 0xFu:
            switch (opcode & 0xFFu) {
                case 0x07u:
                    op_Fx07();
                    break;
                case 0x0Au:
                    op_Fx0A();
                    break;
                case 0x15u:
                    op_Fx15();
                    break;
                case 0x18u:
                    op_Fx18();
                    break;
                case 0x1Eu:
                    op_Fx1E();
                    break;
                case 0x29u:
                    op_Fx29();
                    break;
                case 0x33u:
                    op_Fx33();
                    break;
                case 0x55u:
                    op_Fx55();
                    break;
                case 0x65u:
                    op_Fx65();
                    break;
            }
            break;
        default:
            switch ((opcode & 0xF000u) >> 12u) {
                case 0x1u:
                    op_1nnn();
                    break;
                case 0x2u:
                    op_2nnn();
                    break;
                case 0x3u:
                    op_3xkk();
                    break;
                case 0x4u:
                    op_4xkk();
                    break;
                case 0x5u:
                    op_5xy0();
                    break;
                case 0x6u:
                    op_6xkk();
                    break;
                case 0x7u:
                    op_7xkk();
                    break;
                case 0x9u:
                    op_9xy0();
                    break;
                case 0xAu:
                    op_Annn();
                    break;
                case 0xBu:
                    op_Bnnn();
                    break;
                case 0xCu:
                    op_Cxkk();
                    break;
                case 0xDu:
                    op_Dxyn();
                    break;
            }
            break;
    }
}

