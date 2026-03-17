#include <unistd.h>

#include "input/input.h"

int ti_poll_events(event_data *event) {
  char c = '\0';
  read(STDIN_FILENO, &c, 1);

  if (c != '\0') {
    event->kind = EVENT_KEY_PRESS;

    event->data[0] = c;

    return 1;
  }

  return 0;
}
