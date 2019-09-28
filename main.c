#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;
SDL_Event sdl_event;
int sample_rate = 44100;
bool running = true;
double frequency_output = 440;
double phase_double = 0;
double octave = 1.0;

int note = 440;

void audio_callback() {
}

int init_sdl() {

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
    SDL_AudioSpec want;
    SDL_zero(want);
    SDL_zero(audio_spec);

    want.freq = 48000;
    want.format = AUDIO_S8;
    want.channels = 2;
    want.samples = 4096;
    want.callback = audio_callback;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &audio_spec, 0);

    if (audio_device == 0) {
        printf("Failed to open audio!\n");
        return 1;
    }

    return 0;
}

void handle_keydown(SDL_Keysym* key) {
    switch(key->sym) {
        case SDLK_a:
            note = 261.63;
        case SDLK_w:
            note = 277.18;
        case SDLK_s:
            note = 293.66;
        case SDLK_e:
            note = 311.13;
        case SDLK_d:
            note = 329.63;
        case SDLK_f:
            note = 349.23;
        case SDLK_t:
            note = 369.99;
        case SDLK_g:
            note = 392.00;
        case SDLK_y:
            note = 415.30;
        case SDLK_h:
            note = 440.00;
        case SDLK_u:
            note = 466.16;
        case SDLK_j:
            note = 493.88;
        case SDLK_k:
            note = 523.25;
        case SDLK_z:
            octave *= 2.0;
        case SDLK_x:
            octave /= 2.0;
    }
}


int main() {

    printf("Welcome\n");
    if (init_sdl() != 0) {
	printf("Exiting\n");
        exit(1);
    }

    printf("Keyboard layout:\n\
		|   |   | |   |   |   |   | |   | |   |   |     | \n\
		|   | W | | E |   |   | T | | Y | | U |   |     | \n\
		|   |___| |___|   |   |___| |___| |___|   |     | \n\
		|     |     |     |     |     |     |     |     | \n\
		|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  | \n\
		|_____|_____|_____|_____|_____|_____|_____|_____| \n\n\
        Octave up: Z\n\
        Octave down: X\n");

    while(running) {
        while(SDL_PollEvent(&sdl_event)) {
            switch(sdl_event.type) {
                case SDL_KEYDOWN:
                    handle_keydown(&sdl_event.key.keysym);
                case SDL_QUIT:
                    running = false;
            }
        }
    }

    SDL_CloseAudioDevice(audio_device);
}
