#include <unistd.h>

#include "termi.h"

int main(void) {
  termi_state termi = {};
  ti_init(&termi, 1);

  ti_nset_celli(&termi, 0, '^', 200, 0);
  ti_nset_celli(&termi, 1, '_', 200, 0);
  ti_nset_cellrc(&termi, 0, 2, '^', 200, 0);

  ti_render(&termi);

  while (1) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    if (c == 'q') break;
  }

  ti_goodbye(&termi, 1);

  return 0;
}
