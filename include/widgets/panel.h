#pragma once

#include "widgets/widget.h"

typedef struct termi_textw termi_textw;

typedef struct {
  termi_widget widget;

  int padding;

  int draw_box;

  termi_textw *title;
  int draw_title;
} termi_panelw;

void ti_render_panelw(termi_state *termi, termi_widget *widget);
void ti_destroy_panelw(termi_widget *widget);

termi_panelw ti_create_panelw(int row, int col, int width, int height);
