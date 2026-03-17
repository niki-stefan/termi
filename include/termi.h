#include <stdint.h>
#include <termios.h>

typedef struct {
    char ch;
    uint8_t fg; // use uint8_t (it has 1 byte, int has 4) to make the buffer smaller
    uint8_t bg;
} termi_cell;

typedef struct {
    int width;
    int height;

    termi_cell *buffer;
} termi_screen;

typedef struct {
  struct termios original_termios;

  termi_screen *screen;
} termi_state;

void ti_init(termi_state *termi, int alternate_screen);
void ti_goodbye(termi_state *termi, int alternate_screen);

void ti_enter_alternate_screen(termi_state *termi);
void ti_leave_alternate_screen(termi_state *termi);

void ti_get_screen_size(termi_state *termi);

void ti_clean_buffer(termi_state *termi);
