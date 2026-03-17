#include "widgets/widget.h"

void ti_render_widget(termi_state *termi, termi_widget *widget) {
  if (widget->vtable && widget->vtable->render && widget->dirty)
    widget->vtable->render(termi, widget);
}
