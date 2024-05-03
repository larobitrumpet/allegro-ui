#ifndef ALLEGRO_UI_HBOX_H
#define ALLEGRO_UI_HBOX_H

#include "widget.h"
#include "vector.h"

ALLEGRO_UI_WIDGET* al_ui_new_hbox();
void al_ui_hbox_render(ALLEGRO_UI_WIDGET* hbox, float x, float y, float width, float height);
void al_ui_destroy_hbox(ALLEGRO_UI_WIDGET* hbox);
float al_ui_hbox_get_width(ALLEGRO_UI_WIDGET* hbox, float width);
float al_ui_hbox_get_height(ALLEGRO_UI_WIDGET* hbox, float height);
void al_ui_hbox_handle_event(ALLEGRO_UI_WIDGET* hbox, float x, float y, float width, float height, ALLEGRO_EVENT* event);
bool al_ui_hbox_expands_x(ALLEGRO_UI_WIDGET* hbox);
bool al_ui_hbox_expands_y(ALLEGRO_UI_WIDGET* hbox);

#endif
