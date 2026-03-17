#pragma once

#define KEY_ARROW_UP    "\x1b[A"
#define KEY_ARROW_DOWN  "\x1b[B"
#define KEY_ARROW_LEFT  "\x1b[D"
#define KEY_ARROW_RIGHT "\x1b[C"

typedef enum {
  EVENT_KEY_PRESS
} event_kind;

typedef struct {
  event_kind kind;
  char data[10];
} event_data;

int ti_poll_events(event_data *event);
