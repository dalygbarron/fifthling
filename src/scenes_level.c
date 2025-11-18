#include "scenes.h"
#include <libdragon.h>
#include "fonts.h"
#include "draw.h"

static colour_t bg = RGBA32(70, 0, 0, 255);
static colour_t bgb = RGBA32(70, 0, 60, 255);

static colour_t fg = RGBA32(255, 255, 255, 255);

typedef struct {
    sprite_t *pic;
} level_data_t;

static int update(void *data) {
    return 1;
}

static void draw(void *data) {
    level_data_t *level_data = (level_data_t*)data;
    rdpq_sprite_blit(level_data->pic, 0, 0, NULL);
    rdpq_set_mode_fill(fg);
    rdpq_set_fill_color_stripes(bg, bgb);
    rdpq_fill_rectangle(0, 362, 510, 480);
    rdpq_text_print(
        &(rdpq_textparms_t) {
            .width = 520,
            .wrap = WRAP_ELLIPSES
        },
        fonts_BODY,
        12,
        376,
        "HELLO... It is Worm Time, and it SHALL NOT be delayed again.\n"
        "If you fuck with worm time you SHALL DIE!!!!\n"
        "Line 3\n"
        "Line 4\n"
        "Line 5\n"
        "Line 6\n"
        "Line 7"
    );
}

static void *get_data(char const *key) {
    return NULL;
}

static int receive_data(char const *key, void *value) {
    return 0;
}

static void destroy(void *data) {
    level_data_t *level_data = (level_data_t*)data;
    sprite_free(level_data->pic);
    free(level_data);
}

void scenes_push_level(char const *pic_path) {
    level_data_t *level_data = malloc(sizeof(level_data_t));
    level_data->pic = sprite_load(pic_path);
    scenes_push(update, draw, get_data, receive_data, destroy, level_data);
}