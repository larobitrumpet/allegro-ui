#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro_ui.h"

void must_init(bool test, const char *description)
{
    if (test) return;

    printf("Couldn't initialize %s\n", description);
}

#define BUFFER_W 427
#define BUFFER_H 240

float DISP_SCALE_W;
float DISP_SCALE_H;
float DISP_W;
float DISP_H;
float DISP_W_OFFSET;
float DISP_H_OFFSET;

ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer;

void disp_init()
{
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_RESIZABLE);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);

    disp = al_create_display(BUFFER_W, BUFFER_H);
    must_init(disp ,"display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(16, 16, 16));
}

void disp_post_draw()
{
    float BUFFER_ASPECT = (float)BUFFER_W / (float)BUFFER_H;
    float D_W = (float)al_get_display_width(disp);
    float D_H = (float)al_get_display_height(disp);
    float DISP_ASPECT = D_W / D_H;

    DISP_SCALE_W = D_W / BUFFER_W;
    DISP_SCALE_H = D_H / BUFFER_H;
    
    if (DISP_ASPECT < BUFFER_ASPECT)
    {
        DISP_W = BUFFER_W * DISP_SCALE_W;
        DISP_H = BUFFER_H * DISP_SCALE_W;

        float DD_H = BUFFER_H * DISP_SCALE_H;

        DISP_H_OFFSET = (DD_H - DISP_H) / 2;
        DISP_W_OFFSET = 0;
    }
    else if (DISP_ASPECT > BUFFER_ASPECT)
    {
        DISP_W = BUFFER_W * DISP_SCALE_H;
        DISP_H = BUFFER_H * DISP_SCALE_H;

        float DD_W = BUFFER_W * DISP_SCALE_W;

        DISP_W_OFFSET = (DD_W - DISP_W) / 2;
        DISP_H_OFFSET = 0;
    }
    else
    {
        DISP_W = BUFFER_W * DISP_SCALE_W;
        DISP_H = BUFFER_H * DISP_SCALE_H;

        DISP_W_OFFSET = 0;
        DISP_H_OFFSET = 0;
    }

    al_set_target_backbuffer(disp);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, DISP_W_OFFSET, DISP_H_OFFSET, DISP_W, DISP_H, 0);

    al_flip_display();
}

float x_screen_space_to_buffer_space(float x) {
    return (x - DISP_W_OFFSET) / (DISP_W / BUFFER_W);
}

float y_screen_space_to_buffer_space(float y) {
    return (y - DISP_H_OFFSET) / (DISP_H / BUFFER_H);
}

ALLEGRO_UI_WIDGET* wid;

void draw()
{
    disp_pre_draw();

    // draw code
    al_ui_render(wid, 0, 0, 427, 240);

    disp_post_draw();
}

void button_func(void* data) {
    void** d = (void**)data;
    int* color = (int*)d[0];
    ALLEGRO_UI_WIDGET* back = (ALLEGRO_UI_WIDGET*)d[1];
    *color = *color + 1;
    *color = *color % 3;
    switch (*color) {
        case 0:
            back->background_color.color = al_map_rgb(255, 0, 0);
            break;
        case 1:
            back->background_color.color = al_map_rgb(0, 255, 0);
            break;
        case 2:
            back->background_color.color = al_map_rgb(0, 0, 255);
            break;
    }
}

int main()
{
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;

    int redraw = true;
    must_init(al_init(), "Allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    al_ui_init();

    // init
    disp_init();

    timer = al_create_timer(1.0 / 60);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // setup_scene();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_UI_WIDGET* back = al_ui_new_background_color(al_map_rgb(0, 0, 255),
        al_ui_new_border(10.0, al_map_rgb(255, 255, 0),
            al_ui_new_padding(40.0, 40.0, 40.0, 40.0,
                al_ui_new_label(font, al_map_rgb(255, 255, 255), "Hello world!")
            )
        )
    );
    int color = 2;
    void* data[2] = {(void*)&color, (void*)back};
    wid = al_ui_new_center_height(
        al_ui_new_center_width(
            al_ui_new_button(button_func, data,
                back
            )
        )
    );

    bool done = false;
    al_start_timer(timer);
    while(true)
    {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(disp);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                }
                break;
        }
        
        al_ui_handle_event(&event, wid, 0, 0, BUFFER_W, BUFFER_H, x_screen_space_to_buffer_space, y_screen_space_to_buffer_space);

        if (done)
        {
            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            // redraw code
            draw();
            redraw = false;
        }
    }

    // deinit
    al_ui_destroy_widget(wid);
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}