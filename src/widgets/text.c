#include <stdlib.h>
#include <string.h>

#include "widgets/text.h"
#include "termi.h"

void ti_render_textw(termi_state *termi, termi_widget *widget) {
  termi_textw *textw = (termi_textw *)widget;

  ti_nprint(termi, widget->abs_row, widget->abs_col, textw->text, 255, 0);
}

void ti_destroy_textw(termi_widget *widget) {
  termi_textw *textw = (termi_textw *)widget;

  free(textw->text);
}

termi_widget_vtable textw_vtable = (termi_widget_vtable){
  .render = ti_render_textw,
  .destroy = ti_destroy_textw
};

termi_textw ti_create_textw(char *text, int row, int col) {
  return (termi_textw){
    .widget = {
      .dirty = 1,
      .vtable = &textw_vtable,
      .row = row,
      .col = col,
      .width = strlen(text),
      .height = 1,
      .parent = NULL,
      .children = NULL,
      .children_count = 0
    },
    .text = text
  };
}

void ti_nupdate_textw(termi_state *termi, termi_textw *textw, char *text) {
  int old_len = strlen(textw->text);

  textw->text = text;
  textw->widget.width = strlen(text);
  textw->widget.dirty = 1;

  if (old_len > textw->widget.width) {
    for (int i = 0; i < old_len - textw->widget.width; i++) {
      ti_nset_cellrc(termi, textw->widget.abs_row, textw->widget.abs_col + textw->widget.width + i, ' ', 0, 0);
    }
  }
}
