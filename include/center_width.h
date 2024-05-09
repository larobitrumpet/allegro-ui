#ifndef ALLEGRO_UI_CENTER_WIDTH_H
#define ALLEGRO_UI_CENTER_WIDTH_H

#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_center_width(ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_center_width(ALLEGRO_UI_WIDGET* center);
void al_ui_center_width_render(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height);
float al_ui_center_width_get_width(ALLEGRO_UI_WIDGET* center, float width);
float al_ui_center_width_get_height(ALLEGRO_UI_WIDGET* center, float height);
void al_ui_center_width_handle_event(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_center_width_expands_x(ALLEGRO_UI_WIDGET* center);
bool al_ui_center_width_expands_y(ALLEGRO_UI_WIDGET* center);

#endif
