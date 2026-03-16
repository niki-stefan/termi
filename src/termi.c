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
    termi->width = ws.ws_col;
    termi->height = ws.ws_row;
  }
}
