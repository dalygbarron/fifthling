#include "draw.h"

void draw_box(int x, int y, int w, int h, int pad, colour_t bg, colour_t fg) {
    rdpq_set_mode_fill(fg);
    rdpq_fill_rectangle(x, y, x + w, y + h);
    rdpq_set_fill_color(bg);
    rdpq_fill_rectangle(x + pad, y + pad, x + w - pad * 2, y + h - pad * 2);
}
