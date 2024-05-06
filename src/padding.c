#include "padding.h"

ALLEGRO_UI_WIDGET* al_ui_new_padding(float right, float down, float left, float up, ALLEGRO_UI_WIDGET* child) {
    ALLEGRO_UI_WIDGET* padding = malloc(sizeof(ALLEGRO_UI_WIDGET));
    padding->padding.type = ALLEGRO_UI_WIDGET_TYPE_PADDING;
    padding->padding.right = right;
    padding->padding.down = down;
    padding->padding.left = left;
    padding->padding.up = up;
    padding->padding.child = child;
    return padding;
}

void al_ui_destroy_padding(ALLEGRO_UI_WIDGET* padding) {
    if (padding->padding.child != NULL)
        al_ui_destroy_widget(padding->padding.child);
    free(padding);
}

void al_ui_padding_render(ALLEGRO_UI_WIDGET* padding, float x, float y, float width, float height) {
    if (padding->padding.child != NULL) {
        al_ui_render(padding->padding.child, x + padding->padding.left, y + padding->padding.up, width - padding->padding.left - padding->padding.right, height - padding->padding.up - padding->padding.down);
    }
}

float al_ui_padding_get_width(ALLEGRO_UI_WIDGET* padding, float width) {
    float child_width = 0.0;
    if (padding->padding.child != NULL) {
        child_width = al_ui_get_width(padding->padding.child, width - padding->padding.left - padding->padding.right);
    }
    return padding->padding.left + child_width + padding->padding.right;
}

float al_ui_padding_get_height(ALLEGRO_UI_WIDGET* padding, float height) {
    float child_height = 0.0;
    if (padding->padding.child != NULL) {
        child_height = al_ui_get_height(padding->padding.child, height - padding->padding.up - padding->padding.down);
    }
    return padding->padding.up + child_height + padding->padding.down;
}

void al_ui_padding_handle_event(ALLEGRO_UI_WIDGET* padding, float x, float y, float width, float height, ALLEGRO_EVENT* event) {
    if (padding->padding.child != NULL)
        al_ui_widget_handle_event(padding->padding.child, x + padding->padding.left, y + padding->padding.up, width - padding->padding.left - padding->padding.right, height - padding->padding.up - padding->padding.down, event);
}

bool al_ui_padding_expands_x(ALLEGRO_UI_WIDGET* padding) {
    return padding->padding.child == NULL ? false : al_ui_expands_x(padding->padding.child);
}

bool al_ui_padding_expands_y(ALLEGRO_UI_WIDGET* padding) {
    return padding->padding.child == NULL ? false : al_ui_expands_y(padding->padding.child);
}
