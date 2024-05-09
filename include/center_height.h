#ifndef ALLEGRO_UI_CENTER_HEIGHT_H
#define ALLEGRO_UI_CENTER_HEIGHT_H

#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_center_height(ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_center_height(ALLEGRO_UI_WIDGET* center);
void al_ui_center_height_render(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height);
float al_ui_center_height_get_width(ALLEGRO_UI_WIDGET* center, float width);
float al_ui_center_height_get_height(ALLEGRO_UI_WIDGET* center, float height);
void al_ui_center_height_handle_event(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_center_height_expands_x(ALLEGRO_UI_WIDGET* center);
bool al_ui_center_height_expands_y(ALLEGRO_UI_WIDGET* center);

#endif
