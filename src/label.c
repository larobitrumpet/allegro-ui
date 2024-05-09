#include "label.h"

ALLEGRO_UI_WIDGET* al_ui_new_label(ALLEGRO_FONT* font, ALLEGRO_COLOR color, char* text) {
    ALLEGRO_UI_WIDGET* label = malloc(sizeof(ALLEGRO_UI_WIDGET));
    label->label.type = ALLEGRO_UI_WIDGET_TYPE_LABEL;
    label->label.font = font;
    label->label.color = color;
    label->label.text = text;
    return label;
}

void al_ui_destroy_label(ALLEGRO_UI_WIDGET* label) {
    free(label);
}

void al_ui_label_render(ALLEGRO_UI_WIDGET* label, float x, float y, float width, float height) {
    al_draw_text(label->label.font, label->label.color, x, y, 0, label->label.text);
}

float al_ui_label_get_width(ALLEGRO_UI_WIDGET* label, float width) {
    return al_get_text_width(label->label.font, label->label.text);
}

float al_ui_label_get_height(ALLEGRO_UI_WIDGET* label, float height) {
    return al_get_font_line_height(label->label.font);
}

void al_ui_label_handle_event(ALLEGRO_UI_WIDGET* label, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
    // Function intentionally left empty
}

bool al_ui_label_expands_x(ALLEGRO_UI_WIDGET* label) {
    return false;
}

bool al_ui_label_expands_y(ALLEGRO_UI_WIDGET* label) {
    return false;
}
