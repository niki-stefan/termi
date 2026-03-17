#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widgets/text.h"
#include "termi.h"

void ti_render_textw(termi_state *termi, termi_widget *widget) {
  termi_textw *textw = (termi_textw *)widget;
  char *input = textw->text;

  int output_len = 0;

  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == '#') {
      i += 2; // skip # and {

      int color = 0;

      while (input[i] && input[i] != '-' && input[i] >= '0' && input[i] <= '9') {
        color = color * 10 + (input[i++] - '0');
      }

      i++; // skip -

      while (input[i] != '\0' && input[i] != '}') {
        ti_nset_cellrc(termi, widget->abs_row, widget->abs_col + output_len, input[i], color, 0);
        
        output_len++;
        i++;
      }
    } else {
      ti_nset_cellrc(termi, widget->abs_row, widget->abs_col + output_len, input[i], 255, 0);

      output_len++;
    }
  }
}

void ti_destroy_textw(termi_widget *widget) {
  termi_textw *textw = (termi_textw *)widget;

  free(textw->text);
}

termi_widget_vtable textw_vtable = (termi_widget_vtable){
  .render = ti_render_textw,
  .destroy = ti_destroy_textw
};

termi_textw ti_create_textw(int row, int col, char *text, ...) {
  char buffer[256];

  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  char *str = strdup(buffer);

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
    .text = str
  };
}

void ti_nupdate_textw(termi_state *termi, termi_textw *textw, char *text, ...) {
  int old_len = strlen(textw->text);

  char buffer[256];

  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);

  char *str = strdup(buffer);

  if (textw->text) free(textw->text);

  textw->text = str;
  textw->widget.width = strlen(str);
  textw->widget.dirty = 1;

  if (old_len > textw->widget.width) {
    for (int i = 0; i < old_len - textw->widget.width; i++) {
      ti_nset_cellrc(termi, textw->widget.abs_row, textw->widget.abs_col + textw->widget.width + i, ' ', 0, 0);
    }
  }
}
