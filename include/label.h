#ifndef ALLEGOR_UI_LABEL_H
#define ALLEGRO_UI_LABEL_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_label(ALLEGRO_FONT* font, ALLEGRO_COLOR color, char* text);
void al_ui_destroy_label(ALLEGRO_UI_WIDGET* label);
void al_ui_label_render(ALLEGRO_UI_WIDGET* label, float x, float y, float width, float height);
float al_ui_label_get_width(ALLEGRO_UI_WIDGET* label, float width);
float al_ui_label_get_height(ALLEGRO_UI_WIDGET* label, float height);
void al_ui_label_handle_event(ALLEGRO_UI_WIDGET* label, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_label_expands_x(ALLEGRO_UI_WIDGET* label);
bool al_ui_label_expands_y(ALLEGRO_UI_WIDGET* label);

#endif
