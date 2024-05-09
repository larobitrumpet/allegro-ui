#include "button.h"

ALLEGRO_UI_WIDGET* al_ui_new_button(void (*on_click)(void* data), void* data, ALLEGRO_UI_WIDGET* child) {
	ALLEGRO_UI_WIDGET* button = malloc(sizeof(ALLEGRO_UI_WIDGET));
	button->button.type = ALLEGRO_UI_WIDGET_TYPE_BUTTON;
	button->button.on_click = on_click;
	button->button.data = data;
	button->button.child = child;
	return button;
}

void al_ui_destroy_button(ALLEGRO_UI_WIDGET* button) {
	if (button->button.child != NULL)
		al_ui_destroy_widget(button->button.child);
	free(button);
}

void al_ui_button_render(ALLEGRO_UI_WIDGET* button, float x, float y, float width, float height) {
	if (button->button.child != NULL)
		al_ui_render(button->button.child, x, y, width, height);
}

float al_ui_button_get_width(ALLEGRO_UI_WIDGET* button, float width) {
	if (button->button.child != NULL)
		return al_ui_get_width(button->button.child, width);
	return 0.0;
}

float al_ui_button_get_height(ALLEGRO_UI_WIDGET* button, float height) {
	if (button->button.child != NULL)
		return al_ui_get_height(button->button.child, height);
	return 0.0;
}

void al_ui_button_handle_event(ALLEGRO_UI_WIDGET* button, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
	switch (event->type) {
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (event->mouse.button & 1) {
				float w = al_ui_button_get_width(button, width);
				float h = al_ui_button_get_height(button, height);

				if (mouse_pos_x >= x && mouse_pos_x <= (x + w) && mouse_pos_y >= y && mouse_pos_y <= (y + h)) {
					if (button->button.on_click != NULL)
						button->button.on_click(button->button.data);
				}
			}
			break;
	}

	if (button->button.child != NULL)
		al_ui_widget_handle_event(button->button.child, x, y, width, height, mouse_pos_x, mouse_pos_y, event);
}

bool al_ui_button_expands_x(ALLEGRO_UI_WIDGET* button) {
	return button->button.child == NULL ? false : al_ui_expands_x(button->button.child);
}

bool al_ui_button_expands_y(ALLEGRO_UI_WIDGET* button) {
	return button->button.child == NULL ? false : al_ui_expands_y(button->button.child);
}
