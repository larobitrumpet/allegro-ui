#include "center_height.h"

ALLEGRO_UI_WIDGET* al_ui_new_center_height(ALLEGRO_UI_WIDGET* child) {
    ALLEGRO_UI_WIDGET* center = malloc(sizeof(ALLEGRO_UI_WIDGET));
    center->center_height.type = ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT;
    center->center_height.child = child;
    return center;
}

void al_ui_destroy_center_height(ALLEGRO_UI_WIDGET* center) {
    if (center->center_height.child != NULL)
        al_ui_destroy_widget(center->center_height.child);
    free(center);
}

void al_ui_center_height_render(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height) {
    if (center->center_height.child == NULL)
        return;

    float h = al_ui_get_height(center->center_height.child, height);
    al_ui_render(center->center_height.child, x, y + (height / 2.0) - (h / 2.0), width, h);
}

float al_ui_center_height_get_width(ALLEGRO_UI_WIDGET* center, float width) {
    float child = 0;
    if (center->center_height.child != NULL) {
        child = al_ui_get_width(center->center_height.child, width);
    }
    return child;
}

float al_ui_center_height_get_height(ALLEGRO_UI_WIDGET* center, float height) {
    return height;
}

void al_ui_center_height_handle_event(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height, ALLEGRO_EVENT* event) {
    if (center->center_height.child == NULL)
        return;
    float h = al_ui_get_height(center->center_height.child, height);
    al_ui_widget_handle_event(center->center_height.child, x, y + (height / 2.0) - (h / 2.0), width, h, event);
}

bool al_ui_center_height_expands_x(ALLEGRO_UI_WIDGET* center) {
    return center->center_height.child == NULL ? false : al_ui_expands_x(center->center_height.child);
}

bool al_ui_center_height_expands_y(ALLEGRO_UI_WIDGET* center) {
    return true;
}
