#ifndef ALLEGRO_UI_VBOX_H
#define ALLEGRO_UI_VBOX_H

#include "widget.h"
#include "vector.h"

ALLEGRO_UI_WIDGET* al_ui_new_vbox(ALLEGRO_UI_WIDGET** children, size_t n_children);
void al_ui_destroy_vbox(ALLEGRO_UI_WIDGET* vbox);
void al_ui_vbox_render(ALLEGRO_UI_WIDGET* vbox, float x, float y, float width, float height);
float al_ui_vbox_get_width(ALLEGRO_UI_WIDGET* vbox, float width);
float al_ui_vbox_get_height(ALLEGRO_UI_WIDGET* vbox, float height);
void al_ui_vbox_handle_event(ALLEGRO_UI_WIDGET* vbox, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_vbox_expands_x(ALLEGRO_UI_WIDGET* vbox);
bool al_ui_vbox_expands_y(ALLEGRO_UI_WIDGET* vbox);

#endif
