#include <unistd.h>

#include "termi.h"
#include "input/input.h"
#include "widgets/text.h"
#include "widgets/panel.h"

int main(void) {
  termi_state termi = {};
  ti_init(&termi, 1);

  ti_set_cursor(0);

  termi_panelw panelw = ti_create_panelw(0, 0, 70, 10);
  panelw.padding = 1;
  panelw.draw_box = 1;

  termi_textw panelw_title = ti_create_textw(0, 0, "I'm a happily married panel with four children #{93;0-<3} #{33;0-<3}");

  panelw.title = &panelw_title;
  panelw.draw_title = 1;

  termi_textw textw = ti_create_textw(0, 0, "This is rendered using a widget! :0");
  ti_set_parent((termi_widget *)&panelw, (termi_widget *)&textw);

  termi_textw face = ti_create_textw(2, 0, "Press t to make this face happy :(");
  ti_set_parent((termi_widget *)&panelw, (termi_widget *)&face);

  termi_textw counter = ti_create_textw(4, 0, "I can also count (press n): ");
  ti_set_parent((termi_widget *)&panelw, (termi_widget *)&counter);

  termi_textw rainbow = ti_create_textw(6, 0, "Ever seen a #{196-r}#{208-a}#{226-i}#{46-n}#{39-b}#{51-o}#{93-w}?");
  ti_set_parent((termi_widget *)&panelw, (termi_widget *)&rainbow);

  ti_add_widget(&termi, (termi_widget *)&panelw);

  int is_sad = 1,
      count = 1;

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
      } else if (event.data[0] == 'n') {
        if (count > 5) {
          continue;
        } else if (count == 2) {
          count++;
        } else if (count == 5) {
          ti_nupdate_textw(&termi, &counter, "%s 5 (idk past that)", counter.text);
          ti_render(&termi);

          count++;
          continue;
        }

        ti_nupdate_textw(&termi, &counter, "%s %d", counter.text, count);
        ti_render(&termi);

        count++;
      }
    }
  }

  ti_goodbye(&termi, 1);

  return 0;
}
