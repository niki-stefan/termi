#include <unistd.h>

#include "termi.h"

int main(void) {
  termi_state termi = {};
  ti_init(&termi, 1);

  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    if (c == 'q') break;
  }

  ti_goodbye(&termi, 1);

  return 0;
}
