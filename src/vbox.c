#include "vbox.h"

ALLEGRO_UI_WIDGET* al_ui_new_vbox(ALLEGRO_UI_WIDGET** children, size_t n_children) {
    ALLEGRO_UI_WIDGET* vbox = malloc(sizeof(ALLEGRO_UI_WIDGET));
    vbox->vbox.type = ALLEGRO_UI_WIDGET_TYPE_VBOX;
    vbox->vbox.children = construct_vector(sizeof(ALLEGRO_UI_WIDGET*));
	for (size_t i = 0; i < n_children; i++) {
		vector_enqueue(&vbox->vbox.children, &children[i]);
	}
    return vbox;
}

static bool vbox_destroy_children(void* widget, void* _) {
    al_ui_destroy_widget(*(ALLEGRO_UI_WIDGET**)widget);
    return false;
}

void al_ui_destroy_vbox(ALLEGRO_UI_WIDGET* vbox) {
    vector_iterate(&vbox->vbox.children, vbox_destroy_children, NULL);
    deconstruct_vector(vbox->vbox.children);
    free(vbox);
}

static bool vbox_count_y_expand(void* widget, void* params) {
    int* num = (int*)params;
    *num = *num + (al_ui_expands_y(*(ALLEGRO_UI_WIDGET**)widget) ? 1 : 0);
    return false;
}

static bool vbox_render_children(void* child, void* params) {
    void** pars = (void**)params;
    float* x = pars[0];
    float* y = pars[1];
    float* width = pars[2];
    float* height = pars[3];
    al_ui_render(*(ALLEGRO_UI_WIDGET**)child, *x, *y, *width, *height);
    *y = *y + al_ui_get_height(*(ALLEGRO_UI_WIDGET**)child, *height);
    return false;
}

static bool vbox_non_expand_y_total_height_func(void* widget, void* params) {
    void** pars = (void**)params;
    float* num = (float*)pars[0];
    float* height = (float*)pars[1];
    *num = *num + (al_ui_expands_y(*(ALLEGRO_UI_WIDGET**)widget) ? 0 : al_ui_get_height(*(ALLEGRO_UI_WIDGET**)widget, *height));
    return false;
}

void al_ui_vbox_render(ALLEGRO_UI_WIDGET* vbox, float x, float y, float width, float height) {
    float h;
    int num = 0;
    vector_iterate(&vbox->vbox.children, vbox_count_y_expand, &num);
    float total_non_expand_y_height = 0;
    if (num != 0) {
        void* params[2] = {(void*)&total_non_expand_y_height, (void*)&height};
        vector_iterate(&vbox->vbox.children, vbox_non_expand_y_total_height_func, params);
        h = (height - total_non_expand_y_height) / num;
    } else {
        h = height;
    }
    void* params[4] = {(void*)&x, (void*)&y, (void*)&width, (void*)&h};
    vector_iterate(&vbox->vbox.children, vbox_render_children, params);
}

static void* vbox_child_width_func(void* widget, void* params) {
    ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
    void** pars = (void**)params;
    float* f = (float*)pars[0];
    float* w = (float*)pars[1];
    *f = al_ui_get_width(wid, *w);
    return f;
}

static bool float_greater_than(void* f1, void* f2, void* _) {
    return *(float*)f1 > *(float*)f2;
}

float al_ui_vbox_get_width(ALLEGRO_UI_WIDGET* vbox, float width) {
    if (al_ui_vbox_expands_x(vbox))
        return width;
    float f;
    void* params[2] = {(void*)&f, (void*)&width};
    VECTOR widths = vector_map(&vbox->vbox.children, sizeof(float), vbox_child_width_func, params);
    return *(float*)vector_min_max(&widths, float_greater_than, NULL);
}

static void* vbox_child_height_func(void* widget, void* params) {
    ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
    void** pars = (void**)params;
    float* f = (float*)pars[0];
    float* h = (float*)pars[1];
    *f = al_ui_get_height(wid, *h);
    return f;
}

static bool sum_floats(void* data, void* params) {
    float* f = (float*)data;
    float* sum = (float*)params;
    *sum = *sum + *f;
    return false;
}

float al_ui_vbox_get_height(ALLEGRO_UI_WIDGET* vbox, float height) {
    if (al_ui_vbox_expands_y(vbox))
        return height;
    float f;
    void* params[2] = {(void*)&f, (void*)&height};
    VECTOR heights = vector_map(&vbox->vbox.children, sizeof(float), vbox_child_height_func, params);
    float sum = 0;
    vector_iterate(&heights, sum_floats, (void*)&sum);
    return sum;
}

static bool vbox_children_handle_event(void* child, void* params) {
    void** pars = (void**)params;
    float* x = pars[0];
    float* y = pars[1];
    float* width = pars[2];
    float* height = pars[3];
	float* mouse_pos_x = pars[4];
	float* mouse_pos_y = pars[5];
    ALLEGRO_EVENT* event = pars[6];
    al_ui_widget_handle_event(*(ALLEGRO_UI_WIDGET**)child, *x, *y, *width, *height, *mouse_pos_x, *mouse_pos_y, event);
    *y = *y + al_ui_get_height(*(ALLEGRO_UI_WIDGET**)child, *height);
    return false;
}

void al_ui_vbox_handle_event(ALLEGRO_UI_WIDGET* vbox, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
    float h;
    int num = 0;
    vector_iterate(&vbox->vbox.children, vbox_count_y_expand, &num);
    float total_non_expand_y_height = 0;
    if (num != 0) {
        void* params[2] = {(void*)&total_non_expand_y_height, (void*)&height};
        vector_iterate(&vbox->vbox.children, vbox_non_expand_y_total_height_func, params);
        h = (height - total_non_expand_y_height) / num;
    } else {
        h = height;
    }
    void* params[] = {(void*)&x, (void*)&y, (void*)&width, (void*)&h, (void*)&mouse_pos_x, (void*)&mouse_pos_y, (void*)event};
    vector_iterate(&vbox->vbox.children, vbox_children_handle_event, params);
}

static bool vbox_expands_x_itter_func(void* widget, void* expands) {
    ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
    bool* ex = (bool*)expands;
    if (al_ui_expands_x(wid)) {
        *ex = true;
        return true;
    }
    return false;
}

bool al_ui_vbox_expands_x(ALLEGRO_UI_WIDGET* vbox) {
    bool expands = false;
    vector_iterate(&vbox->vbox.children, vbox_expands_x_itter_func, &expands);
    return expands;
}

static bool vbox_expands_y_itter_func(void* widget, void* expands) {
    ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
    bool* ey = (bool*)expands;
    if (al_ui_expands_y(wid)) {
        *ey = true;
        return true;
    }
    return false;
}

bool al_ui_vbox_expands_y(ALLEGRO_UI_WIDGET* vbox) {
    bool expands = false;
    vector_iterate(&vbox->vbox.children, vbox_expands_y_itter_func, &expands);
    return expands;
}
