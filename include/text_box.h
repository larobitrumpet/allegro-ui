#ifndef ALLEGRO_UI_TEXT_BOX_H
#define ALLEGRO_UI_TEXT_BOX_H

#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "widget.h"
#include "label.h"
#include "padding.h"
#include "border.h"
#include "keyboard.h"

#define ALLEGRO_UI_TEXT_BOX_TEXT_SIZE_INIT 8
#define ALLEGRO_UI_TEXT_BOX_TEXT_SIZE_INCREASE 1.5

#define ALLEGRO_UI_TEXT_BOX_BLINK_INTERVAL 30
#define ALLEGRO_UI_TEXT_BOX_CURSOR_COLOR al_map_rgb(0, 0, 0)
#define ALLEGRO_UI_TEXT_BOX_CURSOR_THICKNESS 1.0
#define ALLEGRO_UI_TEXT_BOX_CURSOR_OVERHANG 2.0

#define ALLEGRO_UI_TEXT_BOX_PADDING 4.0
#define ALLEGRO_UI_TEXT_BOX_BORDER_WIDTH 2.0
#define ALLEGRO_UI_TEXT_BOX_BORDER_COLOR al_map_rgb(0, 0, 0)

ALLEGRO_UI_WIDGET* al_ui_new_text_box(ALLEGRO_FONT* font, ALLEGRO_COLOR color, char* start_text);
void al_ui_destroy_text_box(ALLEGRO_UI_WIDGET* box);
char* al_ui_text_box_get_text(ALLEGRO_UI_WIDGET* box);
void al_ui_text_box_set_text(ALLEGRO_UI_WIDGET* box, char* text);
void al_ui_text_box_render(ALLEGRO_UI_WIDGET* box, float x, float y, float width, float height);
float al_ui_text_box_get_width(ALLEGRO_UI_WIDGET* box, float width);
float al_ui_text_box_get_height(ALLEGRO_UI_WIDGET* box, float height);
void al_ui_text_box_handle_event(ALLEGRO_UI_WIDGET* box, float x, float y, float width, float height, ALLEGRO_EVENT* event);
bool al_ui_text_box_expands_x(ALLEGRO_UI_WIDGET* box);
bool al_ui_text_box_expands_y(ALLEGRO_UI_WIDGET* box);

#endif
