#pragma once

typedef struct termi_state termi_state;
typedef struct termi_widget termi_widget;

typedef struct {
    void (*render)(termi_state *termi, termi_widget *widget);
    void (*destroy)(termi_widget *widget);
} termi_widget_vtable;

struct termi_widget {
    int row, col;
    int abs_row, abs_col;
    int width, height;

    termi_widget *parent;
    termi_widget **children;
    int children_count;

    int dirty;

    termi_widget_vtable *vtable;
};

void ti_render_widget(termi_state *termi, termi_widget *widget);
