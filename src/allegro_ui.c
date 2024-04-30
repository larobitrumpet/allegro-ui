#include "allegro_ui.h"

void (*al_ui_destroy_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
void (*al_ui_render_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height);
float (*al_ui_get_width_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float width);
float (*al_ui_get_height_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float height);
void (*al_ui_handle_event_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget, float widget_x, float widget_y, float width, float height, ALLEGRO_EVENT* event);
bool (*al_ui_expands_x_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);
bool (*al_ui_expands_y_functions[ALLEGRO_UI_WIDGET_TYPE_SIZE])(ALLEGRO_UI_WIDGET* widget);

float al_ui_mouse_pos_x;
float al_ui_mouse_pos_y;

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

void al_ui_widget_handle_event(ALLEGRO_UI_WIDGET* widget, float x, float y, float width, float height, ALLEGRO_EVENT* event) {
    al_ui_handle_event_functions[widget->any.type](widget, x, y, width, height, event);
}

void al_ui_handle_event(ALLEGRO_EVENT* event, ALLEGRO_UI_WIDGET* root_widget, float widget_x, float widget_y, float width, float height, float (*x_transform)(float), float (*y_transform)(float)) {
    switch (event->type) {
        case ALLEGRO_EVENT_MOUSE_AXES:
            al_ui_mouse_pos_x = x_transform == NULL ? event->mouse.x : x_transform(event->mouse.x);
            al_ui_mouse_pos_y = y_transform == NULL ? event->mouse.y : y_transform(event->mouse.y);
            break;
    }
    al_ui_widget_handle_event(root_widget, widget_x, widget_y, width, height, event);
}

bool al_ui_expands_x(ALLEGRO_UI_WIDGET* widget) {
    return al_ui_expands_x_functions[widget->any.type](widget);
}

bool al_ui_expands_y(ALLEGRO_UI_WIDGET* widget) {
    return al_ui_expands_y_functions[widget->any.type](widget);
}
