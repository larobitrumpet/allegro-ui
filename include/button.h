#ifndef ALLEGRO_UI_BUTTON_H
#define ALLEGRO_UI_BUTTON_H

#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_button(void (*on_press)(void* data), void* data, ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_button(ALLEGRO_UI_WIDGET* button);
void al_ui_button_render(ALLEGRO_UI_WIDGET* button, float x, float y, float width, float height);
float al_ui_button_get_width(ALLEGRO_UI_WIDGET* button, float width);
float al_ui_button_get_height(ALLEGRO_UI_WIDGET* button, float height);
void al_ui_button_handle_event(ALLEGRO_UI_WIDGET* button, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_button_expands_x(ALLEGRO_UI_WIDGET* button);
bool al_ui_button_expands_y(ALLEGRO_UI_WIDGET* button);

#endif
