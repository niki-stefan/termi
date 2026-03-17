#pragma once

#include "widgets/widget.h"
#include <stdint.h>
#include <termios.h>

typedef struct {
    char ch;
    int fg; 
    int bg;

    int dirty;
} termi_cell;

typedef struct {
    int width;
    int height;

    termi_cell *buffer;

    termi_widget **widgets;
    int widget_count;
} termi_screen;

typedef struct termi_state {
  struct termios original_termios;

  termi_screen *screen;
} termi_state;

void ti_init(termi_state *termi, int alternate_screen);
void ti_goodbye(termi_state *termi, int alternate_screen);

void ti_set_cursor(int state);

void ti_enter_alternate_screen(termi_state *termi);
void ti_leave_alternate_screen(termi_state *termi);

void ti_get_screen_size(termi_state *termi);

void ti_clean_buffer(termi_state *termi);
void ti_nset_celli(termi_state *termi, int i, char ch, int fg, int bg);
void ti_nset_cellrc(termi_state *termi, int row, int col, char ch, int fg, int bg);

void ti_nprint(termi_state *termi, int row, int col, char *message, int fg, int bg);

void ti_render(termi_state *termi);

void ti_add_widget(termi_state *termi, termi_widget *widget);
void ti_set_parent(termi_widget *parent, termi_widget *child);
