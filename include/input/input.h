typedef enum {
  EVENT_KEY_PRESS
} event_kind;

typedef struct {
  event_kind kind;
  char *data;
} event_data;

int ti_poll_events(event_data *event);
