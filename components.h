#ifndef __COMPONENTS__
#define __COMPONENTS__

#include <stdint.h>

#define FONTSET_SIZE 80

extern const uint16_t START_ADDRESS;

extern uint8_t registers[16];
extern uint8_t memory[4096];
extern uint16_t idx;
extern uint16_t pc;
extern uint16_t stack[16];
extern uint8_t stack_ptr;
extern uint8_t delay;
extern uint8_t sound;
extern uint8_t keypad[16];
extern uint32_t screen[32*64];
extern uint16_t opcode;

extern const unsigned int VIDEO_WIDTH;
extern const unsigned int VIDEO_HEIGHT;

extern const uint8_t fontset[FONTSET_SIZE];

extern const uint16_t FONTSET_START_ADDRESS;

void initialize_chip8(void);

#endif
