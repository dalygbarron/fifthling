#include <libdragon.h>
#include "fonts.h"
#include "scenes.h"

#define DEG2RAD(d) ((d) * M_PI/180.)
#define RAD2DEG(r) ((r) / (M_PI/180.))

uint32_t const WHITE = 0xffffffff;

int main() {
    debug_init(DEBUG_FEATURE_ALL);
    assert(dfs_init( DFS_DEFAULT_LOCATION ) == DFS_ESUCCESS);
    display_init(
        RESOLUTION_640x480,
        DEPTH_16_BPP,
        3,
        GAMMA_NONE,
        ANTIALIAS_RESAMPLE_FETCH_ALWAYS
    );
    joypad_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    fonts_init();
    scenes_push_level("rom:/pics/test-bg.sprite");
    audio_init(44100, 4);
    mixer_init(16);
    mixer_set_vol(1);
    xm64player_t xmPlayer;
    xm64player_open(&xmPlayer, "rom:/music/bigAssClouds.xm64");
    xm64player_play(&xmPlayer, 0);
    int audiosz = audio_get_buffer_length();
    while (1) {
        while (!audio_can_write()) {}
        int16_t *out = audio_write_begin();
        mixer_poll(out, audiosz);
        audio_write_end();
        joypad_poll();
        scenes_update();
        surface_t *fb = display_get();
        rdpq_attach(fb, NULL);
        rdpq_set_mode_copy(true);
        scenes_draw();
        rdpq_detach_show();
    }
    printf("The end\n");
    return 0;
}
