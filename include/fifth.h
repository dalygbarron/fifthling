// fifth.h
// Provides definitions used by map code.
// How I envision the action system being used:
// int friendly = is_friend("george");
// int special = friendly && get_flag("special_thing");
// action_queue(
//     friendly ?
//         action_speak("George", "Hello :D") :
//         action_nop(),
//     action_shop(),
//     action_cb(george_post_shop),
//     special ?
//         action_speak("George", "And by the way, I have a secret to tell you :)"),
//         action_nop(),
//     NULL);

#pragma once

// number of actions you can have in the action queue at the same time.
#define action_QUEUE_SIZE 64

typedef void (*action_callback)(void);
typedef struct action_t_ action_t;
typedef struct item_t_ item_t;

// Adds any number of actions to the back of the queue to be processed. The
// last varadic argument must be NULL to signal the end, and the first argument
// cannot be null. If there is not enough space in the action queue to add all
// of these actions then none of them will be added and nothing will change.
// returns 1 if all is well, and 0 if the queue is full.
int action_queue(action_t *first, ...);

// Same as action_queue except it adds the actions to the front of the queue.
// They will be added in such an order as to make it that first is the first
// one to be executed etc.
int action_do(action_t *first, ...);

// Makes a speaking action which is where the level shows some text with an
// alleged author until you press a button.
// The strings that are passed are not freed when the action data is freed so
// hopefully they are static or you have some way to deal with that.
action_t *action_speak(char const *name, char const *content);

// Makes a speaking action which is where the level shows some text with an
// alleged author until you press a button.
// In this case, the passed strings will be freed when the action is freed so
// you need not worry about that.
action_t *action_speak_mngd(char const *name, char const *content);

// Makes a shop screen show up.
// TODO: gonna need some arguments to define shop stock etc but will do later.
action_t *action_shop();

// Makes an action that just triggers a callback and potentially puts more
// actions onto the stack.
action_t *action_cb(action_callback cb);

// Kind of luxious in it's lack of necessity I suppose, but this kind of action
// does nothing and gets skipped, and it's sole purpose is to fill in a space in
// a list of actions that because of some kind of conditional would otherwise
// not be able to be filled with any meaningful value.
action_t *action_nop();