#include "fonts.h"
#include <libdragon.h>

static int initialised = 0;
static rdpq_font_t *font_objs[fonts_COUNT - 1];

void fonts_init() {
    assertf(
        !initialised,
        "Trying to init font module when already initialised"
    );
    initialised = 1;
    font_objs[fonts_BODY - 1] = rdpq_font_load("rom:/fonts/ubuntu.font64");
    for (int i = fonts_BODY; i < fonts_COUNT; i++) {
        rdpq_text_register_font(i, font_objs[i - 1]);
    }
}

void fonts_deinit() {
    assertf(initialised, "Trying to deinit font module when not initialised");
    initialised = 0;
    for (int i = fonts_BODY; i < fonts_COUNT; i++) {
        rdpq_text_unregister_font(i);
        rdpq_font_free(font_objs[i - 1]);
    }
}