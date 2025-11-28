// fifth.h
// Provides definitions used by map code.
// How I envision the action system being used:
// int friendly = is_friend("george");
// int special = friendly && get_flag("special_thing");
// acts_queue(
//     friendly ?
//         acts_speak("George", "Hello :D") :
//         acts_nop(),
//     acts_shop(),
//     acts_cb(george_post_shop),
//     special ?
//         acts_speak("George", "And by the way, I have a secret to tell you :)"),
//         acts_nop(),
//     NULL);

#pragma once

#include <stddef.h>

// number of actions you can have in the action queue at the same time.
#define acts_QUEUE_SIZE 64

typedef void (*acts_callback)(int);
typedef struct acts_t_ acts_t;
typedef struct item_t_ item_t;

// Adds any number of actions to the back of the queue to be processed. The
// last varadic argument must be NULL to signal the end, and the first argument
// cannot be null. If there is not enough space in the action queue to add all
// of these actions then that is UB (with an assert on debug builds). The size
// of the queue overall and the number of things in the queue are both
// accessible from this header though so it's your fault and I don't care.
void acts_queue(acts_t *first, ...);

// Same as acts_queue except it adds the actions to the front of the queue.
// They will be added in such an order as to make it that first is the first
// one to be executed etc.
void acts_do(acts_t *first, ...);

// Adds only one action to the back of the queue. Warning about queue size still
// stands.
void acts_queue_one(acts_t *a);

// Same as acts_queue_one but adds it to the start.
void acts_do_one(acts_t *a);

// Tells you how many actions are queued right now.
size_t acts_get_length();

// Makes a speaking action which is where the level shows some text with an
// alleged author until you press a button.
// The strings that are passed are not freed when the action data is freed so
// hopefully they are static or you have some way to deal with that.
acts_t *acts_speak(char const *name, char const *content);

// Makes a speaking action which is where the level shows some text with an
// alleged author until you press a button.
// In this case, the name is not freed but the content is freed automatically so
// this one is good for cases where you dynamically create the content string
// but the name is a normal static string.
acts_t *acts_speak_txt_mngd(char const *name, char *content);

// Makes a speaking action which is where the level shows some text with an
// alleged author until you press a button.
// In this case, the passed strings will be freed when the action is freed so
// you need not worry about that.
acts_t *acts_speak_mngd(char *name, char *content);

// Makes a shop screen show up.
// TODO: gonna need some arguments to define shop stock etc but will do later.
acts_t *acts_shop();

// Makes an action that just triggers a callback and potentially puts more
// actions onto the stack.
acts_t *acts_cb(acts_callback cb);

// Kind of luxious in it's lack of necessity I suppose, but this kind of action
// does nothing and gets skipped, and it's sole purpose is to fill in a space in
// a list of actions that because of some kind of conditional would otherwise
// not be able to be filled with any meaningful value.
acts_t *acts_nop();