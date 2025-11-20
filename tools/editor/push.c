#include <stdio.h>
#include <forms.h>
#include <flimage.h>

#define MARGIN 20
#define MAIN_WIDTH 640
#define MAIN_HEIGHT 360
#define MAP_WIDTH 360
#define MAP_HEIGHT 360

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
}

typedef struct {
    char const *name;
    FL_CALLBACKPTR cb;
} header_item_t;

header_item_t header_items[] = {
    {"File", NULL},
    {"Application", NULL},
    {"Help", NULL},
    {}
};

// CBA to properly document right now but choices is a null terminated array in
// the sense that it stops at the first entry where name is null. If you have no
// null names then you get undefined behaviour instead wahoooooo.
static FL_OBJECT *make_header(
    FL_Coord w,
    FL_Coord h,
    header_item_t *choices
) {
    FL_OBJECT *group = fl_bgn_group();
    FL_Coord x = 0;
    for (int i = 0; choices[i].name != NULL; i++) {
        FL_OBJECT *button = fl_add_button(
            FL_NORMAL_BUTTON,
            x,
            0,
            MARGIN * 4,
            h,
            choices[i].name
        );
        if (choices[i].cb != NULL) {
            fl_set_object_callback(button, choices[i].cb, 0);
        }
        x += MARGIN * 4;
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
    FL_Coord full_width = MAIN_WIDTH + MAP_WIDTH + MARGIN * 3;
    FL_Coord full_height = MAIN_HEIGHT + MARGIN * 2;
    FL_FORM *form = fl_bgn_form(FL_UP_BOX, full_width, full_height);
    FL_OBJECT *header = make_header(full_width, MARGIN, header_items);
    FL_OBJECT *level_v = fl_add_free(
        FL_INACTIVE_FREE,
	MARGIN,
	MARGIN,
	MAIN_WIDTH,
	MAIN_HEIGHT,
	"level",
	level_v_handler
    );
    FL_OBJECT *map_v = fl_add_canvas(
        FL_NORMAL_CANVAS,
	MAIN_WIDTH + MARGIN * 2,
	MARGIN,
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
