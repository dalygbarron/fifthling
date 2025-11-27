#include <fifth.h>

typedef enum {
    action_SPEAK,
    action_SHOP,
    action_CB,
    action_NOP
} action_class_t;

struct action_t_ {
    action_class_t class;
    union {
        struct {
            char const *speaker;
            char const *text;
            int mngd;
        } speak;
        struct {
            // TODO: nothing right now.
        } shop;
        struct {
            action_callback cb;
        } cb;
    } class_data;
};

static action_t *action_queue[action_QUEUE_SIZE];
static size_t queue_front = 0;
static size_t queue_back = 0;

static int add_to_queue(action_t *action) {

}

static action_t *get_from_queue() {
    if (queue_front == queue_back) return NULL;
    action_t *item = action_queue[queue_front];
    queue_front = (queue_front + 1) % action_QUEUE_SIZE;
    return item;
}

void action_exec() {
    action_t *next = get_from_queue();
    if (!next) return;
    switch (next->class) {
        case action_SPEAK:
            // TODO: set level state for this stuff.
            if (next->class_data.speak.mngd) {
                free(next->class_data.speaker);
                free(next->class_data.text);
            }
            break;
        case action_SHOP:
            // TODO: set level state for shop.
            break;
        case action_CB:
            next->class_data.cb.cb();
            break;
        case action_NOP:
            break;
    }
    free(next);
}

int action_queue(action_t *first, ...) {

}

int action_do(action_t *first, ...) {

}

action_t *action_speak(char const *name, char const *content) {
    action_t *action = malloc(sizeof(action_t));
    action->class = action_SPEAK;
    action->class_data.speak.speaker = name;
    action->class_data.speak.text = content;
    action->class_data.speak.mngd = 0;
    return action;
}

action_t *action_speak_mngd(char const *name, char const *content) {
    action_t *action = malloc(sizeof(action_t));
    action->class = action_SPEAK;
    action->class_data.speak.speaker = name;
    action->class_data.speak.text = content;
    action->class_data.speak.mngd = 1;
    return action;
}

action_t *action_shop() {
    action_t *action = malloc(sizeof(action_t));
    action->class = action_SHOP;
    return action;
}

action_t *action_cb(action_callback cb) {
    action_t *action = malloc(sizeof(action_t));
    action->class = action_CB;
    action->class_data.cb.cb = cb;
    return action;
}

action_t *action_nop() {
    action_t *action = malloc(sizeof(action_t));
    action->class = action_NOP;
    return action;
}