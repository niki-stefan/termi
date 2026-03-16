#include <unistd.h>

#include "termi.h"

int main(void) {
  termi_state termi = {};
  enter_alternate_screen(&termi);

  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    if (c == 'q') break;
  }

  leave_alternate_screen(&termi);

  return 0;
}
