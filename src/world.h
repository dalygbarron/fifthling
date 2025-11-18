#pragma once


typedef struct {
    char const *description;
    char const *pic_file;
    world_level_t *north;
    world_level_t *east;
    world_level_t *south;
    world_level_t *west;
} world_level_t;

typedef struct {
    

    // TODO: we will need a hashmap of levels at some point.
} world_map_t;