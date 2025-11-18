#include "scenes.h"
#include <libdragon.h>

struct Scene {
    int (*update)(void*);
    void (*draw)(void*);
    void *(*get_data)(char const*);
    int (*receive_data)(char const*, void*);
    void (*destroy)(void*);
    void *userdata;
};

static struct Scene *scene_stack[scenes_MAX];
static int scene_count = 0;

#define top_scene scene_stack[scene_count - 1]

static void free_scene(int index) {
    assertf(index >= 0, "free_scene index below range");
    assertf(index < scene_count, "free_scene index above range");
    scene_stack[index]->destroy(scene_stack[index]->userdata);
    free(scene_stack[index]);
}

int scenes_empty() {
    return scene_count == 0;
}

void scenes_push(
    int (*update)(void*),
    void (*draw)(void*),
    void *(*get_data)(char const*),
    int (*receive_data)(char const *, void*),
    void (*destroy)(void*),
    void *userdata
) {
    assertf(scene_count < scenes_MAX, "Scene stack overflow");
    scene_count++;
    struct Scene *scene = malloc(sizeof(struct Scene));
    scene->update = update;
    scene->draw = draw;
    scene->get_data = get_data;
    scene->receive_data = receive_data;
    scene->destroy = destroy;
    scene->userdata = userdata;
    scene_stack[scene_count - 1] = scene;
}

void *scenes_get_data(char const *key) {
    for (int i = scene_count - 1; i >= 0; i--) {
        void *data = scene_stack[i]->get_data(key);
        if (data != NULL) return data;
    }
    return NULL;
}

int scenes_pass_data(int skip_top, char const *key, void *value) {
    int skip = skip_top ? 2 : 1;
    for (int i = scene_count - skip; i >= 0; i--) {
        int receipt = scene_stack[i]->receive_data(key, value);
        if (receipt) return 1;
    }
    return 0;
}

void scenes_update() {
    assertf(scene_count > 0, "Tried to update empty scene stack");
    int current_scene_count = scene_count;
    int keep = top_scene->update(top_scene->userdata);
    if (!keep) {
        free_scene(current_scene_count);
        scene_count--;
        // if after decrement they are equal it means a scene was added during
        // the update function.
        if (current_scene_count == scene_count) {
            scene_stack[scene_count - 1] = scene_stack[scene_count];
        }
    }
}

void scenes_draw() {
    for (int i = 0; i < scene_count; i++) {
        struct Scene *scene = scene_stack[i];
        scene->draw(scene->userdata);
    }
}