// fonts.h
// Simple module to register fonts with libdragon's rdpq_text api. The
// fonts_id_t enum provides the ids of the registered fonts.
// By intent, no facility is given to customise the loaded fonts, and you must
// edit fonts.c instead.

#pragma once

#include <stdint.h>
#include <limits.h>

// Ids under which this module registers fonts with the rdpq_text system.
// fonts_COUNT is actually the number of fonts + 1, since the first font's id
// is 1 rather than 0 so it's handy for iterating.
typedef enum {
    fonts_BODY = 1,
    fonts_COUNT
} fonts_id_t;
_Static_assert(fonts_COUNT - 1 < UINT8_MAX, "Only 244 fonts are allowed");

// Initialises the fonts module, ensuring all provided font ids are registered
// with the rdpq_text api and are ready to be used.
// Asserts if needed ids are already in use.
void fonts_init();

// Deinitialises the module and unregisters all fonts.
// Asserts if any of the fonts are already unregistered.
void fonts_deinit();