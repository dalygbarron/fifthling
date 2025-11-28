#include <fifth.h>
#include <libdragon.h>

#define CLASSES \
    X(SPEAK) \
    X(SPEAK_TXT_MNGD) \
    X(SPEAK_MNGD) \
    X(SHOP) \
    X(CB) \
    X(NOP)

typedef enum {
#define X(name) name,
    CLASSES
#undef X
} class_t;

struct acts_t_ {
    class_t class;
    union {
        struct {
            union {
                char const *speaker;
                char *speaker_mngd;
            };
            union {
                char const *txt;
                char *txt_mngd;
            };
        } speak;
        struct {
            // TODO: nothing right now.
        } shop;
        struct {
            acts_callback cb;
        } cb;
    };
};

static acts_t *action_queue[acts_QUEUE_SIZE];
static size_t queue_front = 0;
static size_t queue_back = 0;
static int last_response = 0;

static void add_to_queue(acts_t *action) {

}

static acts_t *get_from_queue() {
    if (queue_front == queue_back) return NULL;
    acts_t *item = action_queue[queue_front];
    queue_front = (queue_front + 1) % acts_QUEUE_SIZE;
    return item;
}

static inline void exec_SPEAK(acts_t *a, int last) {

}

static inline void exec_SPEAK_TXT_MNGD(acts_t *a, int last) {
    // TODO: main part.
    free(a->speak.txt_mngd);
}

static inline void exec_SPEAK_MNGD(acts_t *a, int last) {
    // TODO: main part.
    free(a->speak.speaker_mngd);
    free(a->speak.txt_mngd);
}

static inline void exec_SHOP(acts_t *a, int last) {

}

static inline void exec_CB(acts_t *a, int last) {
    a->cb.cb(last);
}

static inline void exec_NOP(acts_t *a, int last) {
    return;
}

void acts_exec(int last_response) {
    acts_t *next = get_from_queue();
    if (!next) return;
    switch (next->class) {
        #define X(name) case name: exec_##name(next, last_response); break;
            CLASSES
        #undef X
    }
    free(next);
}

void acts_queue(acts_t *first, ...) {

}

void acts_do(acts_t *first, ...) {

}

acts_t *acts_speak(char const *name, char const *content) {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = SPEAK;
    a->speak.speaker = name;
    a->speak.txt = content;
    return a;
}

acts_t *acts_speak__txt_mngd(char const *name, char *content) {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = SPEAK_TXT_MNGD;
    a->speak.speaker = name;
    a->speak.txt_mngd = content;
    return a;
}

acts_t *acts_speak_mngd(char *name, char *content) {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = SPEAK_MNGD;
    a->speak.speaker_mngd = name;
    a->speak.txt_mngd = content;
    return a;
}

acts_t *acts_shop() {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = SHOP;
    return a;
}

acts_t *acts_cb(acts_callback cb) {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = CB;
    a->cb.cb = cb;
    return a;
}

acts_t *acts_nop() {
    acts_t *a = malloc(sizeof(acts_t));
    assert(a);
    a->class = NOP;
    return a;
}