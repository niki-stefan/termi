#include <unistd.h>

#include "termi.h"
#include "input/input.h"

int main(void) {
  termi_state termi = {};
  ti_init(&termi, 1);

  ti_set_cursor(0);

  ti_nset_celli(&termi, 0, '^', 200, 0);
  ti_nset_celli(&termi, 1, '_', 200, 0);
  ti_nset_cellrc(&termi, 0, 2, '^', 200, 0);

  ti_nprint(&termi, 0, 4, "Welcome to termi!", 53, 249);

  ti_nprint(&termi, 2, 0, "Key pressed: ", 57, 235);

  ti_nprint(&termi, 4, 0, "You can press q to exit, but ", 73, 235);
  ti_nprint(&termi, 4, 29, "why would you want to exit?", 196, 235);

  ti_render(&termi);

  event_data event = {};
  while (1) {
    if (ti_poll_events(&event)) {
      if (event.data[0] == 'q') break;

      ti_nprint(&termi, 2, 13, event.data, 28, 237);

      ti_render(&termi);
    }
  }

  ti_goodbye(&termi, 1);

  return 0;
}
