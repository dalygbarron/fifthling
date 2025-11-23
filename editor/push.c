#include <stdio.h>
#include <forms.h>
#include <flimage.h>
#include "ljson.h"

#define MARGIN 50
#define SIDE_MARGIN 5
#define MAIN_WIDTH 640
#define MAIN_HEIGHT 360
#define MAP_WIDTH ((MAIN_WIDTH - SIDE_MARGIN) / 2)
#define MAP_HEIGHT MAP_WIDTH
#define LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define W_LENGTH(x) x, LENGTH(x)

FL_IMAGE *pic = NULL;

int level_v_handler(
    FL_OBJECT *obj,
    int event,
    FL_Coord mx,
    FL_Coord my,
    int key,
    void *xev
) {
    printf("event %d %p %p\n", event, xev, NULL);
    if (event == FL_DRAW) {
        pic->wx = obj->x;
        pic->wy = obj->y;
        pic->w = obj->w;
        pic->h = obj->h;
        pic->display(pic, FL_ObjWin(obj));
    } else if (event == FL_RESIZED) {
        flimage_scale(pic, obj->w, obj->h, FLIMAGE_NOSUBPIXEL);
    }
    return 0;
}

typedef struct {
    char const *name;
    FL_CALLBACKPTR cb;
} header_item_t;

header_item_t header_items[] = {
    {"File", NULL},
    {"Application", NULL},
    {"Help", NULL}
};
header_item_t toolbar_items[] = {
    {"Move", NULL},
    {"Scale", NULL},
    {"Paint", NULL},
    {"Delete", NULL}
};

static FL_OBJECT *make_header(
    FL_Coord x,
    FL_Coord y,
    FL_Coord w,
    FL_Coord h,
    header_item_t *choices,
    int n_choices
) {
    FL_OBJECT *group = fl_bgn_group();
    FL_Coord step = w / n_choices;
    for (int i = 0; i < n_choices; i++) {
        FL_OBJECT *button = fl_add_button(
            FL_NORMAL_BUTTON,
            x,
            y,
            step,
            h,
            choices[i].name
        );
        if (choices[i].cb != NULL) {
            fl_set_object_callback(button, choices[i].cb, 0);
        }
        x += step;
    }
    fl_end_group();
    return group;
}

int main(int argc, char **argv) {
    fl_initialize(&argc, argv, 0, 0, 0);
    flimage_enable_png();
    pic = flimage_load("pic.png");
    if (pic == NULL) {
        printf("Failed to load picture\n");
        return 1;
    }
    FL_Coord full_width = MAIN_WIDTH + SIDE_MARGIN * 2;
    FL_Coord full_height = MAIN_HEIGHT + MAP_HEIGHT + MARGIN + SIDE_MARGIN * 2;
    FL_FORM *form = fl_bgn_form(FL_UP_BOX, full_width, full_height);
    FL_OBJECT *header = make_header(0, 0, full_width, MARGIN / 2, W_LENGTH(header_items));
    FL_OBJECT *toolbar = make_header(0, MARGIN / 2, full_width, MARGIN / 2, W_LENGTH(toolbar_items));
    FL_OBJECT *level_v = fl_add_free(
        FL_INACTIVE_FREE,
        SIDE_MARGIN,
        MARGIN,
        MAIN_WIDTH,
        MAIN_HEIGHT,
        "level",
        level_v_handler
    );
    FL_OBJECT *map_v = fl_add_canvas(
        FL_NORMAL_CANVAS,
        MAP_WIDTH + SIDE_MARGIN * 2,
        MAIN_HEIGHT + MARGIN + SIDE_MARGIN,
        MAP_WIDTH,
        MAP_HEIGHT,
        "map"
    );
    fl_end_form();
    fl_show_form(form, FL_PLACE_ASPECT, FL_FULLBORDER, "Hello, world!");
    fl_do_forms();
    flimage_free(pic);
    return 0;
}
