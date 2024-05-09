#ifndef ALLEGRO_UI_H
#define ALLEGRO_UI_H

#include <stdio.h>
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

typedef enum ALLEGRO_UI_DISPLAY_STRETCH_MODE {
	ALLEGRO_UI_DISPLAY_STRETCH_MODE_DISABLED = 0b00,
	ALLEGRO_UI_DISPLAY_STRETCH_MODE_2D       = 0b10,
	ALLEGRO_UI_DISPLAY_STRETCH_MODE_VIEWPORT = 0b11,
} ALLEGRO_UI_DISPLAY_STRETCH_MODE;

typedef enum ALLEGRO_UI_DISPLAY_STRETCH_ASPECT {
	ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_IGNORE      = 0b111,
	ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_KEEP        = 0b011,
	ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_KEEP_WIDTH  = 0b001,
	ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_KEEP_HEIGHT = 0b010,
	ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_EXPAND      = 0b000
} ALLEGRO_UI_DISPLAY_STRETCH_ASPECT;

extern void (*al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
extern void (*al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height);
extern float (*al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float width);
extern float (*al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float height);
extern void (*al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float widget_x, float widget_y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
extern bool (*al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
extern bool (*al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);

int al_ui_init();
void al_ui_handle_event(ALLEGRO_EVENT* event, ALLEGRO_UI_WIDGET* root_widget, float* mouse_pos_x, float* mouse_pos_y, ALLEGRO_UI_DISPLAY_STRETCH_MODE stretch_aspect, float widget_x, float widget_y, int buffer_width, int buffer_height, int display_width, int display_height, float display_x_offset, float display_y_offset);
void al_ui_run_widget_in_new_window(ALLEGRO_UI_WIDGET* widget, int base_width, int base_height, bool fullscreen, bool resize_window, ALLEGRO_UI_DISPLAY_STRETCH_MODE stretch_mode, ALLEGRO_UI_DISPLAY_STRETCH_ASPECT stretch_aspect, ALLEGRO_EVENT_SOURCE** event_sources, size_t n_event_sources, void (*event_function)(ALLEGRO_EVENT*, ALLEGRO_UI_WIDGET*, int, int, int, int, float, float, float, float, bool*, bool*, void*), void* event_function_data);

#endif
