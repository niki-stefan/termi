#include <unistd.h>

#include "termi.h"

int main(void) {
  termi_state termi = {};

  ti_enter_alternate_screen(&termi);
  ti_get_screen_size(&termi);

  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    if (c == 'q') break;
  }

  ti_leave_alternate_screen(&termi);

  return 0;
}
