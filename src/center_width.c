#include "center_width.h"

ALLEGRO_UI_WIDGET* al_ui_new_center_width(ALLEGRO_UI_WIDGET* child) {
	ALLEGRO_UI_WIDGET* center = malloc(sizeof(ALLEGRO_UI_WIDGET));
	center->center_width.type = ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH;
	center->center_width.child = child;
	return center;
}

void al_ui_destroy_center_width(ALLEGRO_UI_WIDGET* center) {
	if (center->center_width.child != NULL)
		al_ui_destroy_widget(center->center_width.child);
	free(center);
}

void al_ui_center_width_render(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height) {
	if (center->center_width.child == NULL)
		return;

	float w = al_ui_get_width(center->center_width.child, width);
	al_ui_render(center->center_width.child, x + (width / 2.0) - (w / 2.0), y, w, height);
}

float al_ui_center_width_get_width(ALLEGRO_UI_WIDGET* center, float width) {
	return width;
}

float al_ui_center_width_get_height(ALLEGRO_UI_WIDGET* center, float height) {
	float child = 0;
	if (center->center_width.child != NULL) {
		child = al_ui_get_height(center->center_width.child, height);
	}
	return child;
}

void al_ui_center_width_handle_event(ALLEGRO_UI_WIDGET* center, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
	if (center->center_width.child == NULL)
		return;
	float w = al_ui_get_width(center->center_width.child, width);
	al_ui_widget_handle_event(center->center_width.child, x + (width / 2.0) - (w / 2.0), y, w, height, mouse_pos_x, mouse_pos_y, event);
}

bool al_ui_center_width_expands_x(ALLEGRO_UI_WIDGET* center) {
	return true;
}

bool al_ui_center_width_expands_y(ALLEGRO_UI_WIDGET* center) {
	return center->center_width.child == NULL ? false : al_ui_expands_y(center->center_width.child);
}
