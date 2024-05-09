#ifndef ALLEGRO_UI_PADDING_H
#define ALLEGRO_UI_PADDING_H

#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_padding(float right, float down, float left, float up, ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_padding(ALLEGRO_UI_WIDGET* padding);
void al_ui_padding_render(ALLEGRO_UI_WIDGET* padding, float x, float y, float width, float height);
float al_ui_padding_get_width(ALLEGRO_UI_WIDGET* padding, float width);
float al_ui_padding_get_height(ALLEGRO_UI_WIDGET* padding, float height);
void al_ui_padding_handle_event(ALLEGRO_UI_WIDGET* padding, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_padding_expands_x(ALLEGRO_UI_WIDGET* padding);
bool al_ui_padding_expands_y(ALLEGRO_UI_WIDGET* padding);

#endif
