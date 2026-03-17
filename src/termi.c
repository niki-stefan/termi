#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "termi.h"

void ti_enter_alternate_screen(termi_state *termi) {
  tcgetattr(0, &termi->original_termios);

  struct termios termios;

  termios.c_lflag &= ~(ECHO | ICANON);
  termios.c_oflag &= ~(OPOST);

  termios.c_cc[VMIN] = 0;
  termios.c_cc[VTIME] = 1;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);

  write(STDOUT_FILENO, "\x1b[?1049h", 8); // enter alt screen
  write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
  write(STDOUT_FILENO, "\x1b[H", 3); // move cursor to 0,0
}

void ti_leave_alternate_screen(termi_state *termi) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termi->original_termios);

  write(STDOUT_FILENO, "\x1b[?1049l", 8); // leave alt screen
}

void ti_get_screen_size(termi_state *termi) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    // [TODO] Handle error
  } else {
    termi->screen->width = ws.ws_col;
    termi->screen->height = ws.ws_row;
  }
}

void ti_init(termi_state *termi, int alternate_screen) {
  termi->screen = (termi_screen *)malloc(sizeof(termi_screen));

  ti_get_screen_size(termi);
  ti_clean_buffer(termi);

  if (alternate_screen) {
    ti_enter_alternate_screen(termi);
  }
}

void ti_goodbye(termi_state *termi, int alternate_screen) {
  free(termi->screen->buffer);
  free(termi->screen);

  ti_set_cursor(1);

  if (alternate_screen) {
    ti_leave_alternate_screen(termi);
  }
}

void ti_clean_buffer(termi_state *termi) {
  int width = termi->screen->width,
      height = termi->screen->height;

  // Allocate width * height cells
  termi_cell *buffer =
      (termi_cell *)malloc(width * height * sizeof(termi_cell));

  termi->screen->buffer = buffer;

  for (int i = 0; i < width * height; i++) {
    buffer[i] = (termi_cell){
      .ch = ' ',
      .fg = 255,
      .bg = 0
    };
  }
}

void ti_nset_celli(termi_state *termi, int i, char ch, uint8_t fg, uint8_t bg) {
  termi_cell *cell = &termi->screen->buffer[i];

  cell->ch = ch;
  cell->fg = fg;
  cell->bg = bg;
  cell->dirty = 1;
}

void ti_nset_cellrc(termi_state *termi, int row, int col, char ch, uint8_t fg, uint8_t bg) {
  ti_nset_celli(termi, row * termi->screen->width + col, ch, fg, bg);
}

void ti_render_widgets(termi_state *termi) {
  termi_widget **widgets = termi->screen->widgets;

  for (int i = 0; i < termi->screen->widget_count; i++) {
    ti_render_widget(termi, widgets[i]);
  }
}

void ti_render(termi_state *termi) {
  int width = termi->screen->width;
  int height = termi->screen->height;
  termi_cell *buffer = termi->screen->buffer;

  int capacity = width * height * 32;
  char *out = malloc(capacity);
  int pos = 0;

  ti_render_widgets(termi);

  for (int i = 0; i < width * height; i++) {
    if (!buffer[i].dirty) continue;

    int written = snprintf(
      out + pos,
      capacity - pos,
      "\x1b[%d;%dH\x1b[38;5;%d;48;5;%dm%c\x1b[0m",
      i / width + 1,
      i % width + 1,
      buffer[i].fg,
      buffer[i].bg,
      buffer[i].ch
    );

    pos += written;
  }

  write(STDOUT_FILENO, out, pos);

  free(out);
}

void ti_nprint(termi_state *termi, int row, int col, char *message, uint8_t fg, uint8_t bg) {
  for (int i = 0; message[i] != '\0'; i++) {
    ti_nset_cellrc(termi, row, col + i, message[i], fg, bg);
  }
}

void ti_set_cursor(int state) {
  if (state == 1) // show
    write(STDOUT_FILENO, "\x1b[?25h", 6);
  else // hide                    *
    write(STDOUT_FILENO, "\x1b[?25l", 6);
}

void ti_add_widget(termi_state *termi, termi_widget *widget) {
  termi->screen->widget_count++;
  termi->screen->widgets = (termi_widget **)realloc(termi->screen->widgets, termi->screen->widget_count * sizeof(termi_widget *));

  termi->screen->widgets[termi->screen->widget_count - 1] = widget;
}
