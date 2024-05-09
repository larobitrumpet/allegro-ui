#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro_ui.h"

void must_init(bool test, const char *description) {
    if (test) return;

    printf("Couldn't initialize %s\n", description);
}

void event_function(ALLEGRO_EVENT* event, ALLEGRO_UI_WIDGET* widget, int buffer_width, int buffer_height, int display_width, int display_height, float display_x_offset, float display_y_offset, float mouse_pos_x, float mouse_pos_y, bool* done, bool* redraw, void* _) {
	switch (event->type) {
		case ALLEGRO_EVENT_TIMER:
			// game logic
			*redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			*done = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event->keyboard.keycode == ALLEGRO_KEY_F1)
				*done = true;
			break;
	}
}

int main() {
    must_init(al_init(), "Allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    al_ui_init();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    must_init(timer, "timer");

    ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_UI_WIDGET* vbox_children[] = {
		al_ui_new_label(font, al_map_rgb(255, 255, 255), "This is a label"),
		al_ui_new_center_height(
			al_ui_new_label(font, al_map_rgb(255, 255, 255), "This is a different label")
		),
		al_ui_new_center_height(
			al_ui_new_label(font, al_map_rgb(255, 255, 255), "They are all in a vbox")
		),
		al_ui_new_label(font, al_map_rgb(255, 255, 255), "WOW, isn't that cool?")
	};
    ALLEGRO_UI_WIDGET* vbox = al_ui_new_vbox(vbox_children, 4);
    ALLEGRO_UI_WIDGET* wid = al_ui_new_center_width(vbox);

	ALLEGRO_EVENT_SOURCE* event_sources[] = {
		al_get_keyboard_event_source(),
		al_get_mouse_event_source(),
		al_get_timer_event_source(timer)
	};

	int base_width = 427;
	int base_height = 240;


    al_start_timer(timer);

	al_ui_run_widget_in_new_window(wid, base_width, base_height, true, true, ALLEGRO_UI_DISPLAY_STRETCH_MODE_VIEWPORT, ALLEGRO_UI_DISPLAY_STRETCH_ASPECT_EXPAND, event_sources, 3, event_function, NULL);

    al_destroy_timer(timer);

    return 0;
}
