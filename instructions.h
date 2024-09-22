#ifndef __INSTRUCTIONS__
#define __INSTRUCTIONS__

#include <stdint.h>

void op_00E0(void);
void op_00EE(void);
void op_1nnn(void);
void op_2nnn(void);
void op_3xkk(void);
void op_4xkk(void);
void op_5xy0(void);
void op_6xkk(void);
void op_7xkk(void);
void op_8xy0(void);
void op_8xy1(void);
void op_8xy2(void);
void op_8xy3(void);
void op_8xy4(void);
void op_8xy5(void);
void op_8xy6(void);
void op_8xy7(void);
void op_8xyE(void);
void op_9xy0(void);
void op_Annn(void);
void op_Bnnn(void);
void op_Cxkk(void);
void op_Dxyn(void);
void op_Ex9E(void);
void op_ExA1(void);
void op_Fx07(void);
void op_Fx0A(void);
void op_Fx15(void);
void op_Fx18(void);
void op_Fx1E(void);
void op_Fx29(void);
void op_Fx33(void);
void op_Fx55(void);
void op_Fx65(void);

void op_execute(void);

#endif

