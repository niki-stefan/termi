#include <stdlib.h>
#include <string.h>

#include "widgets/panel.h"
#include "termi.h"

void ti_render_panelw(termi_state *termi, termi_widget *widget) {
  termi_panelw *panelw = (termi_panelw *)widget;

  if (panelw->draw_box) {
    for (int i = 0; i < widget->width; i++) {
      ti_nset_cellrc(termi, widget->row, widget->col + i, ' ', 255, 237);
      ti_nset_cellrc(termi, widget->row + widget->height + panelw->padding - 1, widget->col + i, ' ', 255, 237);
    }

    for (int i = 0; i < widget->height + 1; i++) {
      ti_nset_cellrc(termi, widget->row + i, widget->col, ' ', 255, 237);
      ti_nset_cellrc(termi, widget->row + i, widget->col + widget->width - panelw->padding + 1, ' ', 255, 237);
    }
  }

  if (panelw->draw_title) {
    ti_nprint(termi, widget->row, widget->col + 1, panelw->title, 255, 237);
  }

  for (int i = 0; i < widget->children_count; i++) {
    widget->children[i]->abs_row = widget->row + widget->children[i]->row + panelw->padding + panelw->draw_box;
    widget->children[i]->abs_col = widget->col + widget->children[i]->col + panelw->padding + panelw->draw_box;

    ti_render_widget(termi, widget->children[i]);
  }
}

void ti_destroy_panelw(termi_widget *widget) {
  termi_panelw *panelw = (termi_panelw *)widget;

  free(panelw->widget.children);
}

termi_widget_vtable panelw_vtable = (termi_widget_vtable){
  .render = ti_render_panelw,
  .destroy = ti_destroy_panelw
};

termi_panelw ti_create_panelw(int row, int col, int width, int height) {
  return (termi_panelw){
    .widget = {
      .dirty = 1,
      .vtable = &panelw_vtable,
      .row = row,
      .col = col,
      .width = width,
      .height = height,
      .parent = NULL,
      .children = NULL,
      .children_count = 0
    },
    .padding = 0
  };
}
