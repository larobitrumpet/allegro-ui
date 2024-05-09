#include "hbox.h"

ALLEGRO_UI_WIDGET* al_ui_new_hbox(ALLEGRO_UI_WIDGET** children, size_t n_children) {
	ALLEGRO_UI_WIDGET* hbox = malloc(sizeof(ALLEGRO_UI_WIDGET));
	hbox->hbox.type = ALLEGRO_UI_WIDGET_TYPE_HBOX;
	hbox->hbox.children = construct_vector(sizeof(ALLEGRO_UI_WIDGET*));
	for (size_t i = 0; i < n_children; i++) {
		vector_enqueue(&hbox->hbox.children, &children[i]);
	}
	return hbox;
}

static bool hbox_destroy_children(void* widget, void* _) {
	al_ui_destroy_widget(*(ALLEGRO_UI_WIDGET**)widget);
	return false;
}

void al_ui_destroy_hbox(ALLEGRO_UI_WIDGET* hbox) {
	vector_iterate(&hbox->hbox.children, hbox_destroy_children, NULL);
	deconstruct_vector(hbox->hbox.children);
	free(hbox);
}

static bool hbox_count_x_expand(void* widget, void* params) {
	int* num = (int*)params;
	*num = *num + (al_ui_expands_x(*(ALLEGRO_UI_WIDGET**)widget) ? 1 : 0);
	return false;
}

static bool hbox_render_children(void* child, void* params) {
	void** pars = (void**)params;
	float* x = pars[0];
	float* y = pars[1];
	float* width = pars[2];
	float* height = pars[3];
	al_ui_render(*(ALLEGRO_UI_WIDGET**)child, *x, *y, *width, *height);
	*x = *x + al_ui_get_width(*(ALLEGRO_UI_WIDGET**)child, *width);
	return false;
}

static bool hbox_non_expand_x_total_width_func(void* widget, void* params) {
	void** pars = (void**)params;
	float* num = (float*)pars[0];
	float* width = (float*)pars[1];
	*num = *num + (al_ui_expands_x(*(ALLEGRO_UI_WIDGET**)widget) ? 0 : al_ui_get_width(*(ALLEGRO_UI_WIDGET**)widget, *width));
	return false;
}

void al_ui_hbox_render(ALLEGRO_UI_WIDGET* hbox, float x, float y, float width, float height) {
	float w;
	int num = 0;
	vector_iterate(&hbox->hbox.children, hbox_count_x_expand, &num);
	float total_non_expand_x_width = 0;
	if (num != 0) {
		void* params[2] = {(void*)&total_non_expand_x_width, (void*)&width};
		vector_iterate(&hbox->hbox.children, hbox_non_expand_x_total_width_func, params);
		w = (width - total_non_expand_x_width) / num;
	} else {
		w = width;
	}
	void* params[4] = {(void*)&x, (void*)&y, (void*)&w, (void*)&height};
	vector_iterate(&hbox->hbox.children, hbox_render_children, params);
}

static void* hbox_child_width_func(void* widget, void* params) {
	ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
	void** pars = (void**)params;
	float* f = (float*)pars[0];
	float* w = (float*)pars[1];
	*f = al_ui_get_width(wid, *w);
	return f;
}

static bool sum_floats(void* data, void* params) {
	float* f = (float*)data;
	float* sum = (float*)params;
	*sum = *sum + *f;
	return false;
}

float al_ui_hbox_get_width(ALLEGRO_UI_WIDGET* hbox, float width) {
	if (al_ui_hbox_expands_x(hbox))
		return width;
	float f;
	void* params[2] = {(void*)&f, (void*)&width};
	VECTOR widths = vector_map(&hbox->hbox.children, sizeof(float), hbox_child_width_func, params);
	float sum = 0;
	vector_iterate(&widths, sum_floats, (void*)&sum);
	return sum;
}

static void* hbox_child_height_func(void* widget, void* params) {
	ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
	void** pars = (void**)params;
	float* f = (float*)pars[0];
	float* h = (float*)pars[1];
	*f = al_ui_get_height(wid, *h);
	return f;
}

static bool float_greater_than(void* f1, void* f2, void* _) {
	return *(float*)f1 > *(float*)f2;
}

float al_ui_hbox_get_height(ALLEGRO_UI_WIDGET* hbox, float height) {
	if (al_ui_hbox_expands_y(hbox))
		return height;
	float f;
	void* params[2] = {(void*)&f, (void*)&height};
	VECTOR heights = vector_map(&hbox->hbox.children, sizeof(float), hbox_child_height_func, params);
	return *(float*)vector_min_max(&heights, float_greater_than, NULL);
}

static bool hbox_children_handle_event(void* child, void* params) {
	void** pars = (void**)params;
	float* x = pars[0];
	float* y = pars[1];
	float* width = pars[2];
	float* height = pars[3];
	float* mouse_pos_x = pars[4];
	float* mouse_pos_y = pars[5];
	ALLEGRO_EVENT* event = pars[6];
	al_ui_widget_handle_event(*(ALLEGRO_UI_WIDGET**)child, *x, *y, *width, *height, *mouse_pos_x, *mouse_pos_y, event);
	*x = *x + al_ui_get_width(*(ALLEGRO_UI_WIDGET**)child, *width);
	return false;
}

void al_ui_hbox_handle_event(ALLEGRO_UI_WIDGET* hbox, float x, float y, float width, float height, float mouse_pos_x, float mouse_pos_y, ALLEGRO_EVENT* event) {
	float w;
	int num = 0;
	vector_iterate(&hbox->hbox.children, hbox_count_x_expand, &num);
	float total_non_expand_x_width = 0;
	if (num != 0) {
		void* params[2] = {(void*)&total_non_expand_x_width, (void*)&width};
		vector_iterate(&hbox->hbox.children, hbox_non_expand_x_total_width_func, params);
		w = (width - total_non_expand_x_width) / num;
	} else {
		w = width;
	}
	void* params[] = {(void*)&x, (void*)&y, (void*)&w, (void*)&height, (void*)&mouse_pos_x, (void*)&mouse_pos_y, (void*)event};
	vector_iterate(&hbox->hbox.children, hbox_children_handle_event, params);
}

static bool hbox_expands_x_itter_func(void* widget, void* expands) {
	ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
	bool* ex = (bool*)expands;
	if (al_ui_expands_y(wid)) {
		*ex = true;
		return true;
	}
	return false;
}

bool al_ui_hbox_expands_x(ALLEGRO_UI_WIDGET* hbox) {
	bool expands = false;
	vector_iterate(&hbox->hbox.children, hbox_expands_x_itter_func, &expands);
	return expands;
}

static bool hbox_expands_y_itter_func(void* widget, void* expands) {
	ALLEGRO_UI_WIDGET* wid = *(ALLEGRO_UI_WIDGET**)widget;
	bool* ey = (bool*)expands;
	if (al_ui_expands_y(wid)) {
		*ey = true;
		return true;
	}
	return false;
}

bool al_ui_hbox_expands_y(ALLEGRO_UI_WIDGET* hbox) {
	bool expands = false;
	vector_iterate(&hbox->hbox.children, hbox_expands_y_itter_func, &expands);
	return expands;
}
