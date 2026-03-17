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

  ti_nprint(&termi, 0, 4, "Welcome to termi!", 57, 235);

  ti_render(&termi);

  event_data event = {};
  while (1) {
    if (ti_poll_events(&event)) {
      if (event.data[0] == 'q') break;

      ti_nset_cellrc(&termi, 1, 0, event.data[0], 28, 237);

      ti_render(&termi);
    }
  }

  ti_goodbye(&termi, 1);

  return 0;
}
