#include "background_color.h"

ALLEGRO_UI_WIDGET* al_ui_new_background_color(ALLEGRO_COLOR color, ALLEGRO_UI_WIDGET* child) {
    ALLEGRO_UI_WIDGET* back = malloc(sizeof(ALLEGRO_UI_WIDGET));
    back->background_color.type = ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR;
    back->background_color.color = color;
    back->background_color.child = child;
    return back;
}

void al_ui_destroy_background_color(ALLEGRO_UI_WIDGET* back) {
    if (back->background_color.child != NULL)
        al_ui_destroy_widget(back->background_color.child);
    free(back);
}

void al_ui_background_color_render(ALLEGRO_UI_WIDGET* back, float x, float y, float width, float height) {
    if (!al_is_primitives_addon_initialized()) {
        if (!al_init_primitives_addon()) {
            exit(1);
        }
    }

    float w = al_ui_background_color_get_width(back, width);
    float h = al_ui_background_color_get_height(back, height);
    
    al_draw_filled_rectangle(x, y, x + w, y + h, back->background_color.color);

    if (back->background_color.child != NULL) {
        al_ui_render(back->background_color.child, x, y, w, h);
    }
}

float al_ui_background_color_get_width(ALLEGRO_UI_WIDGET* back, float width) {
    return al_ui_get_width(back->background_color.child, width);
}

float al_ui_background_color_get_height(ALLEGRO_UI_WIDGET* back, float height) {
    return al_ui_get_height(back->background_color.child, height);
}

void al_ui_background_color_handle_event(ALLEGRO_UI_WIDGET* back, float x, float  y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
    if (back->background_color.child != NULL)
        al_ui_widget_handle_event(back->background_color.child, x, y, width, height, mouse_pos_x, mouse_pos_y, event);
}

bool al_ui_background_color_expands_x(ALLEGRO_UI_WIDGET* back) {
    return back->background_color.child == NULL ? false : al_ui_expands_x(back->background_color.child);
}

bool al_ui_background_color_expands_y(ALLEGRO_UI_WIDGET* back) {
    return back->background_color.child == NULL ? false : al_ui_expands_y(back->background_color.child);
}
