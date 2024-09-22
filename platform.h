#ifndef __PLATFORM__
#define __PLATFORM__

#include <stdint.h>
#include <stdbool.h>

void build_platform(
    char *title,
    int window_width,
    int window_height,
    int texture_width,
    int texture_height
);
void destroy_platform(void);
void update(void const *buffer, int pitch);
bool process_input(uint8_t *keys);

#endif

