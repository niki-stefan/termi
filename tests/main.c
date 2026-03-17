#include <unistd.h>

#include "termi.h"
#include "input/input.h"
#include "widgets/text.h"

int main(void) {
  termi_state termi = {};
  ti_init(&termi, 1);

  ti_set_cursor(0);

  termi_textw textw = ti_create_textw("This is rendered using a widget! :0", 0, 0);
  ti_add_widget(&termi, (termi_widget *)&textw);

  termi_textw face = ti_create_textw("Press t to make this face happy :(", 2, 0);
  ti_add_widget(&termi, (termi_widget *)&face);

  int is_sad = 1;

  ti_render(&termi);

  event_data event = {};
  while (1) {
    if (ti_poll_events(&event)) {
      if (event.data[0] == 'q') break;

      if (event.data[0] == 't') {
        if (is_sad == 0) {
          ti_nupdate_textw(&termi, &face, "Why do you want to make me sad :(");
        } else {
          ti_nupdate_textw(&termi, &face, "Press t to make this face sad :)");
          is_sad = 0;
        }

        ti_render(&termi);
      }
    }
  }

  ti_goodbye(&termi, 1);

  return 0;
}
