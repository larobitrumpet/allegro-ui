#ifndef ALLEGRO_UI_BORDER_W
#define ALLEGRO_UI_BORDER_W

#include <allegro5/allegro_primitives.h>
#include "widget.h"

ALLEGRO_UI_WIDGET* al_ui_new_border(float thickness, ALLEGRO_COLOR color, ALLEGRO_UI_WIDGET* child);
void al_ui_destroy_border(ALLEGRO_UI_WIDGET* border);
void al_ui_border_render(ALLEGRO_UI_WIDGET* border, float x, float y, float width, float height);
float al_ui_border_get_width(ALLEGRO_UI_WIDGET* border, float width);
float al_ui_border_get_height(ALLEGRO_UI_WIDGET* border, float height);
void al_ui_border_handle_event(ALLEGRO_UI_WIDGET* border, float x, float y, float width, float height, ALLEGRO_EVENT* event);
bool al_ui_border_expands_x(ALLEGRO_UI_WIDGET* border);
bool al_ui_border_expands_y(ALLEGRO_UI_WIDGET* border);

#endif
