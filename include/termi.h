#include <termios.h>

typedef struct {
  struct termios original_termios;

  int width;
  int height;
} termi_state;

void ti_enter_alternate_screen(termi_state *termi);
void ti_leave_alternate_screen(termi_state *termi);

void ti_get_screen_size(termi_state *termi);
