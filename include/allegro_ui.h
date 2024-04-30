#ifndef ALLEGRO_UI_H
#define ALLEGRO_UI_H

#include "widget.h"
#include "label.h"
#include "padding.h"
#include "border.h"
#include "background_color.h"
#include "center_width.h"
#include "center_height.h"
#include "button.h"
#include "text_box.h"
#include "hbox.h"
#include "vbox.h"

extern void (*al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
extern void (*al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height);
extern float (*al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float width);
extern float (*al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float height);
extern void (*al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float widget_x, float widget_y, float width, float height, ALLEGRO_EVENT* event);
extern bool (*al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
extern bool (*al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);

int al_ui_init();
void al_ui_handle_event(ALLEGRO_EVENT* event, ALLEGRO_UI_WIDGET* root_widget, float widget_x, float widget_y, float width, float height, float (*x_transform)(float x), float (*y_transform)(float y));

#endif
