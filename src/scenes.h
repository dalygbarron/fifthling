// scenes.h
// Implements a scene stack, which is kind of like a call stack except for
// objects with their own data that can persist until they decide to remove
// themselves from the top of the stack.

#pragma once

#include <stdint.h>

// Maximum scene stack depth.
#define scenes_MAX 8

// Tells you if the scene stack is presently empty.
int scenes_empty();

// Creates a scene object by providing it with the necessary function and
// userdata pointers.
// When all of these functions are called later they will be provided with the
// userdata object as their only argument.
// After creation, the scene is immediately added to the scene stack, so
// generally speaking you will not want to call this function directly, but
// rather use some wrapper that creates the type of scene you actually want.
// Asserts if stack is full.
// The callbacks have the following semantics:
//   - update: called once per frame on the topmost scene; returns non‑zero to
//             keep the scene on the stack and 0 to request that it be popped.
//   - draw: called once per frame for all scenes from bottom to top to render
//           their visuals; has no return value.
//   - get_data: given a key string, returns a pointer to associated data owned
//               by the scene or NULL if the key is not recognized; used by
//               scenes_get_data.
//   - receive_data: given a key and value pointer, returns 1 if the scene
//                   accepts/consumes the data and 0 otherwise; used by
//                   scenes_pass_data.
//   - destroy: called exactly once when the scene is removed from the stack so
//              it can release any resources it owns, including userdata if
//              appropriate.
void scenes_push(
    int (*update)(void*),
    void (*draw)(void*),
    void *(*get_data)(char const*),
    int (*receive_data)(char const *, void*),
    void (*destroy)(void*),
    void *userdata
);

// Queries each scene from top to bottom for the given metadata and returns the
// first received value if any.
void *scenes_get_data(char const *key);

// Tries to give a piece of data to any scene that will accept it, starting at
// the top and working down. The first argument is a flag to optionally skip the
// first element of the stack (so it can pass data down).
// Returns 1 if the data was accepted by a scene and 0 otherwise.
int scenes_pass_data(int skip_top, char const *key, void *value);

// Updates the topmost scene on the stack.
// Asserts if no scenes in stack.
void scenes_update();

// Draws all the scenes on the stack from bottom to top.
void scenes_draw();

// Pushes a game context scene onto the stack.
// Technically doesn't do anything except provide info for other scenes.
void scenes_push_game(uint8_t id);

// Pushes a level scene onto the stack.
// This scene can only be added to the stack when there is already a game scene
// on the stack.
void scenes_push_level(char const *pic_path);

// Pushes an inventory scene onto the stack.
// This scene can only be added to the stack when there is already a game scene
// on the stack.
void scenes_push_inventory();
