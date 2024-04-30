#ifndef ALLEGRO_UI_KEYBOARD_H
#define ALLEGRO_UI_KEYBOARD_H

#include <stdbool.h>
#include <allegro5/allegro.h>

char allegro_keycode_to_character(int keycode, bool shift);

#endif
