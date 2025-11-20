#include <stdio.h>
#include <forms.h>
#include <flimage.h>

#define MARGIN 32
#define MAIN_WIDTH 640
#define MAIN_HEIGHT 360
#define MAP_WIDTH 360
#define MAP_HEIGHT 360

static void button_cb(FL_OBJECT *obj, long data) {
    const char *choice = fl_show_fselector("pick a file", ".", "*", NULL);
    if (choice == NULL || choice[0] == 0) {
        printf("You chose nothing??... ok...\n");
    } else {
        printf("Wow!! you chose: %s\n", choice);
    }
}

typedef struct {
    char const *name;
    FL_CALLBACKPTR cb;
} header_item_t;

header_item_t header_items[] = {
    {"File", button_cb},
    {"Application", NULL},
    {"Help", NULL},
    {}
};

// CBA to properly document right now but choices is a null terminated array in
// the sense that it stops at the first entry where name is null. If you have no
// null names then you get undefined behaviour instead wahoooooo.
static FL_OBJECT *make_header(
    FL_Coord x,
    FL_Coord y,
    FL_Coord w,
    FL_Coord h,
    header_item_t *choices
) {
    FL_OBJECT *group = fl_bgn_group();
    for (int i = 0; choices[i].name != NULL; i++) {
        FL_OBJECT *button = fl_add_button(
            FL_NORMAL_BUTTON,
            x,
            y,
            MARGIN * 2,
            h,
            choices[i].name
        );
        if (choices[i].cb != NULL) {
            fl_set_object_callback(button, choices[i].cb, 0);
        }
        x += MARGIN * 2;
    }
    fl_end_group();
    return group;
}

int main(int argc, char **argv) {
    fl_initialize(&argc, argv, 0, 0, 0);
    flimage_enable_png();
    FL_IMAGE *pic = flimage_load("pic.png");
    if (pic == NULL) {
        printf("Failed to load picture\n");
        return 1;
    }
    FL_Coord full_width = MAIN_WIDTH + MAP_WIDTH + MARGIN * 3;
    FL_Coord full_height = MAIN_HEIGHT + MARGIN * 2;
    FL_FORM *form = fl_bgn_form(FL_UP_BOX, full_width, full_height);
    FL_OBJECT *header = make_header(0, 0, full_width, MARGIN / 3 * 2, header_items);
    FL_OBJECT *obj = fl_add_button(FL_NORMAL_BUTTON, MAIN_WIDTH + MARGIN * 2, MARGIN, 190, 60, "Hello world");
    FL_OBJECT *level_v = fl_add_canvas(FL_NORMAL_CANVAS, MARGIN, MARGIN, MAIN_WIDTH, MAIN_HEIGHT, "level");
    FL_OBJECT *map_v = fl_add_canvas(FL_NORMAL_CANVAS, MAIN_WIDTH + MARGIN * 2, MARGIN, MAP_WIDTH, MAP_HEIGHT, "map");
    fl_set_object_callback(obj, button_cb, 0);
    fl_add_button(FL_NORMAL_BUTTON, 700, 100, 90, 60, "Quit");
    fl_end_form();
    flimage_display(pic, FL_ObjWin(level_v));
    fl_show_form(form, FL_PLACE_ASPECT, FL_FULLBORDER, "Hello, world!");
    fl_do_forms();
    return 0;
}