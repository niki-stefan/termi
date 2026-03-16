#include <termios.h>

typedef struct {
  struct termios original_termios;
} termi_state;

void enter_alternate_screen(termi_state *termi);
void leave_alternate_screen(termi_state *termi);
