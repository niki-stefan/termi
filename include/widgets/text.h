#include "widgets/widget.h"

typedef struct {
  termi_widget widget;
  char *text;
} termi_textw;

void ti_render_textw(termi_state *termi, termi_widget *widget);
void ti_destroy_textw(termi_widget *widget);

termi_textw ti_create_textw(char *text, int row, int col);
void ti_nupdate_textw(termi_state *termi, termi_textw *textw, char *text);
