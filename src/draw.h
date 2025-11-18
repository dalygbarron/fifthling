// draw.h
// This module provides some miscellanious drawing functions which all use
// libdragon's rdpq api in the background.

#pragma once

#include <libdragon.h>

// Australia moment.
typedef color_t colour_t;

// Draws a box with the specified position. bg is the colour of the inside of
// the box, fg is the border colour, and pad is how many pixels thick it is.
void draw_box(int x, int y, int w, int h, int pad, colour_t bg, colour_t fg);