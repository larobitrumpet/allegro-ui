#include "border.h"

ALLEGRO_UI_WIDGET* al_ui_new_border(float thickness, ALLEGRO_COLOR color, ALLEGRO_UI_WIDGET* child) {
	ALLEGRO_UI_WIDGET* border = malloc(sizeof(ALLEGRO_UI_WIDGET));
	border->border.type = ALLEGRO_UI_WIDGET_TYPE_BORDER;
	border->border.thickness = thickness;
	border->border.color = color;
	border->border.child = child;
	return border;
}

void al_ui_destroy_border(ALLEGRO_UI_WIDGET* border) {
	if (border->border.child != NULL)
		al_ui_destroy_widget(border->border.child);
	free(border);
}

void al_ui_border_render(ALLEGRO_UI_WIDGET* border, float x, float y, float width, float height) {
	if (!al_is_primitives_addon_initialized()) {
		if (!al_init_primitives_addon()) {
			exit(1);
		}
	}
	float w = al_ui_border_get_width(border, width);
	float h = al_ui_border_get_height(border, height);
	float half_thickness = border->border.thickness / 2;
	al_draw_rectangle(x + half_thickness, y + half_thickness, x + w - half_thickness, y + h - half_thickness, border->border.color, border->border.thickness);
	if (border->border.child != NULL) {
		al_ui_render(border->border.child, x + border->border.thickness, y + border->border.thickness, w - border->border.thickness * 2, h - border->border.thickness * 2);
	}
}

float al_ui_border_get_width(ALLEGRO_UI_WIDGET* border, float width) {
	float child_width = 0.0;
	if (border->border.child != NULL) {
		child_width = al_ui_get_width(border->border.child, width - border->border.thickness * 2);
	}
	return child_width + border->border.thickness * 2;
}

float al_ui_border_get_height(ALLEGRO_UI_WIDGET* border, float height) {
	float child_height = 0.0;
	if (border->border.child != NULL) {
		child_height = al_ui_get_height(border->border.child, height - border->border.thickness * 2);
	}
	return child_height + border->border.thickness * 2;
}

void al_ui_border_handle_event(ALLEGRO_UI_WIDGET* border, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
	if (border->border.child == NULL)
		return;

	float w = al_ui_border_get_width(border, width);
	float h = al_ui_border_get_height(border, height);
	al_ui_widget_handle_event(border->border.child, x + border->border.thickness, y + border->border.thickness, w - border->border.thickness, h - border->border.thickness, mouse_pos_x, mouse_pos_y, event);
}

bool al_ui_border_expands_x(ALLEGRO_UI_WIDGET* border) {
	return border->border.child == NULL ? false : al_ui_expands_x(border->border.child);
}

bool al_ui_border_expands_y(ALLEGRO_UI_WIDGET* border) {
	return border->border.child == NULL ? false : al_ui_expands_y(border->border.child);
}
