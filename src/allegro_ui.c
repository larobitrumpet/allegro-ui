#include "allegro_ui.h"

void (*al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
void (*al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height);
float (*al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float width);
float (*al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float height);
void (*al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float widget_x, float widget_y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event);
bool (*al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
bool (*al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);

int al_ui_init() {
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_destroy_label;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_destroy_padding;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_destroy_border;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_destroy_background_color;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_destroy_center_width;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_destroy_center_height;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_destroy_button;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_destroy_text_box;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_destroy_hbox;
	al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_destroy_vbox;

	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_render;
	al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_render;
	
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_get_width;
	al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_get_width;

	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_get_height;
	al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_get_height;

	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_handle_event;
	al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_handle_event;

	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_expands_x;
	al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_expands_x;

	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_LABEL] = al_ui_label_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_PADDING] = al_ui_padding_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_BORDER] = al_ui_border_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_BACKGROUND_COLOR] = al_ui_background_color_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_WIDTH] = al_ui_center_width_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_CENTER_HEIGHT] = al_ui_center_height_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_BUTTON] = al_ui_button_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX] = al_ui_text_box_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_HBOX] = al_ui_hbox_expands_y;
	al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_VBOX] = al_ui_vbox_expands_y;

	return 0;
}

void al_ui_destroy_widget(ALLEGRO_UI_WIDGET* widget) {
	al_ui_destroy_functions[widget->any.type](widget);
}

void al_ui_render(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height) {
	al_ui_render_functions[widget->any.type](widget, x, y, width, height);
}

float al_ui_get_width(ALLEGRO_UI_WIDGET* widget, float width) {
	return al_ui_get_width_functions[widget->any.type](widget, width);
}

float al_ui_get_height(ALLEGRO_UI_WIDGET* widget, float height) {
	return al_ui_get_height_functions[widget->any.type](widget, height);
}

void al_ui_widget_handle_event(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
	al_ui_handle_event_functions[widget->any.type](widget, x, y, width, height, mouse_pos_x, mouse_pos_y, event);
}

void al_ui_handle_event(ALLEGRO_EVENT* event, ALLEGRO_UI_WIDGET* root_widget, float* mouse_pos_x, float* mouse_pos_y, ALLEGRO_UI_DISPLAY_STRETCH_MODE stretch_mode, float widget_x, float widget_y, int buffer_width, int buffer_height, int display_width, int display_height, float display_x_offset, float display_y_offset) {
	switch (event->type) {
		case ALLEGRO_EVENT_MOUSE_AXES:
			if (stretch_mode == ALLEGRO_UI_DISPLAY_STRETCH_MODE_VIEWPORT) {
				*mouse_pos_x = ((event->mouse.x - display_x_offset) / (display_width - display_x_offset * 2)) * buffer_width;
				*mouse_pos_y = ((event->mouse.y - display_y_offset) / (display_height - display_y_offset * 2)) * buffer_height;
			} else {
				*mouse_pos_x = event->mouse.x;
				*mouse_pos_y = event->mouse.y;
			}
			break;
	}
	al_ui_widget_handle_event(root_widget, widget_x, widget_y, buffer_width, buffer_height, *mouse_pos_x, *mouse_pos_y, event);
}

bool al_ui_expands_x(ALLEGRO_UI_WIDGET* widget) {
	return al_ui_expands_x_functions[widget->any.type](widget);
}

bool al_ui_expands_y(ALLEGRO_UI_WIDGET* widget) {
	return al_ui_expands_y_functions[widget->any.type](widget);
}

void al_ui_run_widget_in_new_window(ALLEGRO_UI_WIDGET* widget, int base_width, int base_height, bool fullscreen, bool resize_window, ALLEGRO_UI_DISPLAY_STRETCH_MODE stretch_mode, ALLEGRO_UI_DISPLAY_STRETCH_ASPECT stretch_aspect, ALLEGRO_EVENT_SOURCE** event_sources, size_t n_event_sources, void (*event_function)(ALLEGRO_EVENT*, ALLEGRO_UI_WIDGET*, int, int, int, int, float, float, float, float, bool*, bool*, void*), void* event_function_data) {
	float base_aspect = (float)base_width / (float)base_height;
	al_set_new_display_flags((fullscreen ? ALLEGRO_FULLSCREEN_WINDOW : 0) + (resize_window ? ALLEGRO_RESIZABLE : 0));
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);

	ALLEGRO_DISPLAY* display = al_create_display(base_width, base_height);
	if (display == NULL) {
		printf("Couldn't create display\n");
		exit(1);
	}

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	al_register_event_source(queue, al_get_display_event_source(display));
	for (size_t i = 0; i < n_event_sources; i++) {
		al_register_event_source(queue, event_sources[i]);
	}

	bool redraw = true;
	bool done = false;

	int display_width = al_get_display_width(display);
	int display_height = al_get_display_height(display);
	int buffer_width = base_width;
	int buffer_height = base_height;
	float display_x_offset = 0;
	float display_y_offset = 0;
	float mouse_pos_x = 0.0;
	float mouse_pos_y = 0.0;

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				al_acknowledge_resize(display);
				redraw = true;
				break;
		}

		al_ui_handle_event(&event, widget, &mouse_pos_x, &mouse_pos_y, stretch_mode, 0, 0, buffer_width, buffer_height, display_width, display_height, display_x_offset, display_y_offset);

		if (event_function != NULL)
			event_function(&event, widget, buffer_width, buffer_height, display_width, display_height, display_x_offset, display_y_offset, mouse_pos_x, mouse_pos_y, &done, &redraw, event_function_data);

		if (redraw && al_is_event_queue_empty(queue)) {
			// redraw code
			display_width = al_get_display_width(display);
			display_height = al_get_display_height(display);
			float display_aspect = (float)display_width / (float)display_height;
			//float stretch_x_factor = 0.0;
			//float stretch_y_factor = 0.0;
			switch (stretch_mode) {
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_DISABLED:
					buffer_width = base_width;
					buffer_width = base_height;
					break;
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_2D:
					// TODO
					printf("Stretch mode 2d is not implemented yet\n");
					exit(1);
					break;
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_VIEWPORT:
					if (stretch_aspect & 0b1) {
						buffer_width = base_width;
						if (stretch_aspect & 0b10) {
							buffer_height = base_height;
						} else {
							if (display_aspect < base_aspect) {
								buffer_height = base_width / display_aspect;
							} else {
								buffer_height = base_height;
							}
						}
					} else if (stretch_aspect & 0b10) {
						buffer_height = base_height;
						if (display_aspect > base_aspect) {
							buffer_width = base_height * display_aspect;
						} else {
							buffer_width = base_width;
						}
					} else {
						if (display_aspect < base_aspect) {
							buffer_width = base_width;
							buffer_height = base_width / display_aspect;
						} else if (display_aspect > base_aspect) {
							buffer_width = base_height * display_aspect;
							buffer_height = base_height;
						} else {
							buffer_width = base_width;
							buffer_height = base_height;
						}
					}
					break;
			}
			ALLEGRO_BITMAP* buffer = al_create_bitmap(buffer_width, buffer_height);
			al_set_target_bitmap(buffer);
			al_clear_to_color(al_map_rgb(64, 64, 64));
			al_ui_render(widget, 0, 0, buffer_width, buffer_height);
			al_set_target_backbuffer(display);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			float buffer_aspect = (float)buffer_width / (float)buffer_height;
			int stretch_width;
			int stretch_height;
			float stretch_scale_width = (float)display_width / (float)buffer_width;
			float stretch_scale_height = (float)display_height / (float)buffer_height;
			switch (stretch_mode) {
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_DISABLED:
					stretch_width = buffer_width;
					stretch_height = buffer_height;
					break;
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_2D:
				case ALLEGRO_UI_DISPLAY_STRETCH_MODE_VIEWPORT:
					if (stretch_aspect & 0b100) {
						stretch_width = display_width;
						stretch_height = display_height;
						display_x_offset = 0;
						display_y_offset = 0;
					} else {
						if (display_aspect < buffer_aspect) {
							stretch_width = display_width;
							stretch_height = buffer_height * stretch_scale_width;
							display_x_offset = 0;
							display_y_offset = (display_height - stretch_height) / 2;
						} else if (display_aspect > buffer_aspect) {
							stretch_width = buffer_width * stretch_scale_height;
							stretch_height = display_height;
							display_x_offset = (display_width - stretch_width) / 2;
							display_y_offset = 0;
						} else {
							stretch_width = display_width;
							stretch_height = display_height;
							display_x_offset = 0;
							display_y_offset = 0;
						}
					}
					break;
			}
			al_draw_scaled_bitmap(buffer, 0, 0, buffer_width, buffer_height, display_x_offset, display_y_offset, stretch_width, stretch_height, 0);
			al_flip_display();
			al_destroy_bitmap(buffer);
			redraw = false;
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(queue);
}
