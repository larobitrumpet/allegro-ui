#ifndef ALLEGRO_UI_WIDGET_H
#define ALLEGRO_UI_WIDGET_H

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "vector.h"

typedef enum ALLEGRO_UI_WIDGET_TYPE {
	ALLEGRO_UI_WIDGET_TYPE_LABEL,
	ALLEGRO_UI_WIDGET_TYPE_PADDING,
	ALLEGRO_UI_WIDGET_TYPE_BORDER,
	ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR,
	ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH,
	ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT,
	ALLEGRO_UI_WIDGET_TYPE_BUTTON,
	ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX,
	ALLEGRO_UI_WIDGET_TYPE_HBOX,
	ALLEGRO_UI_WIDGET_TYPE_VBOX,
	ALLEGRO_UI_WIDGET_TYPE_SIZE,
} ALLEGRO_UI_WIDGET_TYPE;

typedef union ALLEGRO_UI_WIDGET ALLEGRO_UI_WIDGET;

#define _ALLEGRO_UI_WIDGET_HEADER\
	ALLEGRO_UI_WIDGET_TYPE type;

typedef struct ALLEGRO_UI_ANY_WIDGET {
	_ALLEGRO_UI_WIDGET_HEADER
} ALLEGRO_UI_ANY_WIDGET;

typedef struct ALLEGRO_UI_LABEL {
	_ALLEGRO_UI_WIDGET_HEADER

	ALLEGRO_FONT* font;
	ALLEGRO_COLOR color;
	char* text;
} ALLEGRO_UI_LABEL;

typedef struct ALLEGRO_UI_PADDING {
	_ALLEGRO_UI_WIDGET_HEADER

	float right;
	float down;
	float left;
	float up;

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_PADDING;

typedef struct ALLEGRO_UI_BORDER {
	_ALLEGRO_UI_WIDGET_HEADER

	float thickness;
	ALLEGRO_COLOR color;

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_BORDER;

typedef struct ALLEGRO_UI_BACKGROUND_COLOR {
	_ALLEGRO_UI_WIDGET_HEADER

	ALLEGRO_COLOR color;

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_BACKGROUND_COLOR;

typedef struct ALLEGRO_UI_CENTER_WIDTH {
	_ALLEGRO_UI_WIDGET_HEADER

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_CENTER_WIDTH;

typedef struct ALLEGRO_UI_CENTER_HEIGHT {
	_ALLEGRO_UI_WIDGET_HEADER

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_CENTER_HEIGHT;

typedef struct ALLEGRO_UI_BUTTON {
	_ALLEGRO_UI_WIDGET_HEADER

	void* data;
	void (*on_click)(void* data);
	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_BUTTON;

typedef struct ALLEGRO_UI_TEXT_BOX {
	_ALLEGRO_UI_WIDGET_HEADER

	bool has_focus;
	char** text;
	ALLEGRO_COLOR cursor_color;
	float cursor_thickness;
	float cursor_overhang;
	// Private fields
	bool insert_mode;
	bool blink;
	int blink_frame;
	int blink_interval;
	size_t text_size;
	size_t text_end;
	size_t cursor;

	ALLEGRO_UI_WIDGET* child;
} ALLEGRO_UI_TEXT_BOX;

typedef struct ALLEGRO_UI_HBOX {
	_ALLEGRO_UI_WIDGET_HEADER

	// vector to pointers of chlidren
	VECTOR children;
} ALLEGRO_UI_HBOX;

typedef struct ALLEGRO_UI_VBOX {
	_ALLEGRO_UI_WIDGET_HEADER

	// vector to pointers of children
	VECTOR children;
} ALLEGRO_UI_VBOX;

union ALLEGRO_UI_WIDGET {
	ALLEGRO_UI_WIDGET_TYPE type;

	ALLEGRO_UI_ANY_WIDGET any;
	ALLEGRO_UI_LABEL label;
	ALLEGRO_UI_PADDING padding;
	ALLEGRO_UI_BORDER border;
	ALLEGRO_UI_BACKGROUND_COLOR background_color;
	ALLEGRO_UI_CENTER_WIDTH center_width;
	ALLEGRO_UI_CENTER_HEIGHT center_height;
	ALLEGRO_UI_BUTTON button;
	ALLEGRO_UI_TEXT_BOX text_box;
	ALLEGRO_UI_HBOX hbox;
	ALLEGRO_UI_VBOX vbox;
};

void al_ui_destroy_widget(ALLEGRO_UI_WIDGET* widget);
void al_ui_render(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height);
float al_ui_get_width(ALLEGRO_UI_WIDGET* widget, float width);
float al_ui_get_height(ALLEGRO_UI_WIDGET* widget, float height);
void al_ui_widget_handle_event(ALLEGRO_UI_WIDGET* widget, float widget_x, float widget_y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool al_ui_expands_x(ALLEGRO_UI_WIDGET* widget);
bool al_ui_expands_y(ALLEGRO_UI_WIDGET* widget);

#endif
