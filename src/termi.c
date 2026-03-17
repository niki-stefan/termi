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
      .fg = 0,
      .bg = 0
    };
  }
}
