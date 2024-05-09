#include "text_box.h"

ALLEGRO_UI_WIDGET* al_ui_new_text_box(ALLEGRO_FONT* font, ALLEGRO_COLOR color, char* start_text) {
    ALLEGRO_UI_WIDGET* box = malloc(sizeof(ALLEGRO_UI_WIDGET));
    box->text_box.type = ALLEGRO_UI_WIDGET_TYPE_TEXT_BOX;
    box->text_box.has_focus = false;
    box->text_box.blink = true;
    box->text_box.blink_interval = ALLEGRO_UI_TEXT_BOX_BLINK_INTERVAL;
    box->text_box.blink_frame = box->text_box.blink_interval;
    box->text_box.cursor_color = ALLEGRO_UI_TEXT_BOX_CURSOR_COLOR;
    box->text_box.cursor_thickness = ALLEGRO_UI_TEXT_BOX_CURSOR_THICKNESS;
    box->text_box.cursor_overhang = ALLEGRO_UI_TEXT_BOX_CURSOR_OVERHANG;
    box->text_box.insert_mode = false;
    box->text_box.child = al_ui_new_border(
        ALLEGRO_UI_TEXT_BOX_BORDER_WIDTH, ALLEGRO_UI_TEXT_BOX_BORDER_COLOR,
        al_ui_new_padding(
            ALLEGRO_UI_TEXT_BOX_PADDING, ALLEGRO_UI_TEXT_BOX_PADDING, ALLEGRO_UI_TEXT_BOX_PADDING, ALLEGRO_UI_TEXT_BOX_PADDING,
            al_ui_new_label(font, color, NULL)
        )
    );
    box->text_box.text = &box->text_box.child->border.child->padding.child->label.text;
    al_ui_text_box_set_text(box, start_text);
    return box;
}

void al_ui_destroy_text_box(ALLEGRO_UI_WIDGET* box) {
    al_ui_destroy_widget(box->text_box.child);
    free(*box->text_box.text);
    free(box);
}

char* al_ui_text_box_get_text(ALLEGRO_UI_WIDGET* box) {
    return *box->text_box.text;
}

void al_ui_text_box_set_text(ALLEGRO_UI_WIDGET* box, char* text) {
    if (*box->text_box.text != NULL)
        free(*box->text_box.text);
    size_t len = strlen(text);
    box->text_box.text_size = len == 0 ? ALLEGRO_UI_TEXT_BOX_TEXT_SIZE_INIT : len + 1;
    *box->text_box.text = (char*)malloc(sizeof(char) * box->text_box.text_size);
    if (len == 0) {
        (*box->text_box.text)[0] = '\0';
    } else {
        // It is safe to use `strcpy` here since the previous code guarentees
        // that `box->text_box.text` is big enough to contain `text`
        strcpy(*box->text_box.text, text);
    }
    box->text_box.text_end = len;
    box->text_box.cursor = box->text_box.text_end;
}

void al_ui_text_box_render(ALLEGRO_UI_WIDGET* box, float x, float y, float width, float height) {
    al_ui_render(box->text_box.child, x, y, width, height);
    if (!box->text_box.has_focus)
        return;
    if (box->text_box.blink != false)
        return;
    if (!al_is_primitives_addon_initialized()) {
        if (!al_init_primitives_addon()) {
            exit(1);
        }
    }
    char* text = malloc(sizeof(char) * (box->text_box.cursor + 1));
    strncpy(text, *box->text_box.text, box->text_box.cursor);
    text[box->text_box.cursor] = '\0';
    float to_cursor_width = al_get_text_width(box->text_box.child->border.child->padding.child->label.font, text);
    float lx1, ly1, lx2, ly2;
    lx1 = x + box->text_box.child->border.thickness + box->text_box.child->border.child->padding.right + to_cursor_width;
    if (box->text_box.insert_mode) {
        char c = (*box->text_box.text)[box->text_box.cursor];
        char cc[2] = {c == '\0' ? 'm' : c, '\0'};
        float cursor_width = al_get_text_width(box->text_box.child->border.child->padding.child->label.font, cc);
        lx2 = lx1 + cursor_width;
        float line_height = al_get_font_line_height(box->text_box.child->border.child->padding.child->label.font);
        ly1 = y + box->text_box.child->border.thickness + box->text_box.child->border.child->padding.up + line_height;
        ly2 = ly1;
    } else {
        lx2 = lx1;
        float cursor_height = al_get_font_line_height(box->text_box.child->border.child->padding.child->label.font);
        ly1 = y + box->text_box.child->border.thickness + box->text_box.child->border.child->padding.up - box->text_box.cursor_overhang;
        ly2 = ly1 + cursor_height + box->text_box.cursor_overhang;
    }
    al_draw_line(lx1, ly1, lx2, ly2, box->text_box.cursor_color, box->text_box.cursor_thickness);
}

float al_ui_text_box_get_width(ALLEGRO_UI_WIDGET* box, float width) {
    return al_ui_get_width(box->text_box.child, width);
}

float al_ui_text_box_get_height(ALLEGRO_UI_WIDGET* box, float height) {
    return al_ui_get_height(box->text_box.child, height);
}

void al_ui_text_box_handle_event(ALLEGRO_UI_WIDGET* box, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
    switch (event->type) {
        case ALLEGRO_EVENT_TIMER:
            if (!box->text_box.has_focus)
                break;
            box->text_box.blink_frame--;
            if (box->text_box.blink_frame <= 0) {
                box->text_box.blink = box->text_box.blink ? false : true;
                box->text_box.blink_frame = box->text_box.blink_interval;
            }
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            if (!box->text_box.has_focus)
                break;
            char c = allegro_keycode_to_character(event->keyboard.keycode, event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
            if (c == '\0') {
                switch (event->keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        box->text_box.has_focus = false;
                        break;
                    case ALLEGRO_KEY_BACKSPACE:
                        if (box->text_box.cursor == 0)
                            break;
                        // Using `memmove` since source and destination overlap
                        memmove(*box->text_box.text + box->text_box.cursor - 1, *box->text_box.text + box->text_box.cursor, box->text_box.text_end - box->text_box.cursor + 1);
                        box->text_box.text_end--;
                        box->text_box.cursor--;
                        break;
                    case ALLEGRO_KEY_INSERT:
                        box->text_box.insert_mode = box->text_box.insert_mode ? false : true;
                        break;
                    case ALLEGRO_KEY_DELETE:
                    case ALLEGRO_KEY_PAD_DELETE:
                        if (box->text_box.cursor == box->text_box.text_end)
                            break;
                        // Using `memmove` since source and destination overlap
                        memmove(*box->text_box.text + box->text_box.cursor, *box->text_box.text + box->text_box.cursor + 1, box->text_box.text_end - box->text_box.cursor);
                        box->text_box.text_end--;
                        break;
                    case ALLEGRO_KEY_HOME:
                        box->text_box.cursor = 0;
                        break;
                    case ALLEGRO_KEY_END:
                        box->text_box.cursor = box->text_box.text_end;
                        break;
                    case ALLEGRO_KEY_PGUP:
                        box->text_box.cursor = 0;
                        break;
                    case ALLEGRO_KEY_PGDN:
                        box->text_box.cursor = box->text_box.text_end;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if (box->text_box.cursor != 0)
                            box->text_box.cursor--;
                        box->text_box.blink_frame = box->text_box.blink_interval;
                        box->text_box.blink = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if (box->text_box.cursor < box->text_box.text_end)
                            box->text_box.cursor++;
                        box->text_box.blink_frame = box->text_box.blink_interval;
                        box->text_box.blink = false;
                        break;
                    case ALLEGRO_KEY_UP:
                        box->text_box.cursor = 0;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        box->text_box.cursor = box->text_box.text_end;
                        break;
                }
                break;
            }
            if (!box->text_box.insert_mode || (box->text_box.insert_mode && (box->text_box.cursor == box->text_box.text_end))) {
                if (box->text_box.text_end == box->text_box.text_size) {
                    box->text_box.text_size = (size_t)(box->text_box.text_size * ALLEGRO_UI_TEXT_BOX_TEXT_SIZE_INCREASE);
                    *box->text_box.text = realloc(*box->text_box.text, sizeof(char) * box->text_box.text_size);
                }
                box->text_box.text_end++;
                // Using `memmove` since source and destination overlap
                memmove(*box->text_box.text + box->text_box.cursor + 1, *box->text_box.text + box->text_box.cursor, box->text_box.text_end - box->text_box.cursor);
            }
            (*box->text_box.text)[box->text_box.cursor] = c;
            box->text_box.cursor++;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (event->mouse.button & 1) {
                float w = al_ui_text_box_get_width(box, width);
                float h = al_ui_text_box_get_height(box, height);

                box->text_box.has_focus = mouse_pos_x >= x && mouse_pos_x <= (x + w) && mouse_pos_y >= y && mouse_pos_y <= (y + h);
                if (box->text_box.has_focus) {
                    float lx = mouse_pos_x - x - box->text_box.child->border.thickness - box->text_box.child->border.child->padding.right;
                    char* text = (char*)malloc(sizeof(char) * (box->text_box.text_end + 1));
                    text[0] = (*box->text_box.text)[0];
                    for (size_t i = 1; i <= box->text_box.text_end + 1; i++) {
                        text[i] = '\0';
                        float wid = al_get_text_width(box->text_box.child->border.child->padding.child->label.font, text);
                        if (lx <= wid) {
                            box->text_box.cursor = i - 1;
                            break;
                        }
                        text[i] = (*box->text_box.text)[i];
                        if (text[i] == '\0')
                            text[i] = 'm';
                    }
                    free(text);
                }
            }
            break;
    }
}

bool al_ui_text_box_expands_x(ALLEGRO_UI_WIDGET* box) {
    return false;
}

bool al_ui_text_box_expands_y(ALLEGRO_UI_WIDGET* box) {
    return false;
}
