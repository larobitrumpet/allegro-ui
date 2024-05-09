#ifndef ALLEGRO_UI_BACKGROUND_COLOR_H
#define ALLEGRO_UI_BACKGROUND_COLOR_H

#include <allegro5/allegro_primitives.h>
#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_background_color(ALLEGRO_COLOR color, ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_background_color(ALLEGRO_UI_WIDGET* back);
void al_ui_background_color_render(ALLEGRO_UI_WIDGET* back, float x, float y, float width, float height);
float al_ui_background_color_get_width(ALLEGRO_UI_WIDGET* back, float width);
float al_ui_background_color_get_height(ALLEGRO_UI_WIDGET* back, float height);
void al_ui_background_color_handle_event(ALLEGRO_UI_WIDGET* back, float x, float  y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_background_color_expands_x(ALLEGRO_UI_WIDGET* back);
bool al_ui_background_color_expands_y(ALLEGRO_UI_WIDGET* back);

#endif
